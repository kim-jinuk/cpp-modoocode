# 08. C++ Exception — 실전 요약 & 베스트 프랙티스

## 0) TL;DR
- **예외는 “정상 흐름이 아닌 실패 경로”에만** 쓰자. 빠른 경로(핫 루프)는 에러 코드/`expected`가 유리할 때가 많다.
- **표준 계층(std::exception 파생)**만 던지고, **항상 `const&`로 잡아라.**
- **소멸자에서 예외 금지.** 예외 중복(언와인딩 중 예외)이면 `std::terminate`.
- **예외 안전성 3단계**를 알고, 가능하면 **Strong(롤백)** 을 지향하되 비용 고려.
- **`noexcept`는 성능 스위치.** 이동/`swap`에 붙여서 컨테이너 재할당 최적화 유도.
- **임베디드/RT/라이브러리**: 예외 비활성(`-fno-exceptions`) 환경 고려 → **양면 API**(예외/에러코드) 또는 `std::expected`.

---

## 1) 목차
- 기본 구조: `try` / `throw` / `catch`
- 표준 예외 계층 & 커스텀 예외
- 스택 언와인딩 & RAII
- 예외 안전성(Strong/Basic/No-throw)과 패턴
- `noexcept`(선언/연산자/조건부)와 옛 `throw()` 스펙 차이
- 재던지기(`throw;`) / `exception_ptr` / nested exception
- 성능/빌드 옵션/임베디드 가이드
- 실수 리스트 & 체크리스트

---

## 2) 핵심 개념 & 용어표

| 개념 | 요점 | 코멘트 |
|---|---|---|
| `throw` | 예외 객체를 **던짐** | 표준 예외 또는 사용자 정의 예외 |
| `try`/`catch` | 실패를 **포착/복구** | `catch`는 **파생→기저 순서** |
| 예외 안전성 | 실패 시 **불변식/자원**을 지키는 수준 | **Basic / Strong / No-throw** |
| `std::exception` | 표준 예외의 **루트** | `what()` 을 통해 메시지 |
| `noexcept` | 예외 **미발생 보증** | 이동/`swap` 최적화에 중요 |
| 스택 언와인딩 | 예외 전파 중 **파괴자 호출** | **RAII**로 리소스 회수 |
| `exception_ptr` | 스레드 간 **예외 전달** | `current_exception`/`rethrow_exception` |

---

## 3) 문법 101: 던지기/받기/재던지기

### 3-1 기본
```cpp
#include <iostream>
#include <stdexcept>

int main() {
  try {
    // ...
    throw std::runtime_error("boom");  // 표준 파생 예외 권장
  } catch (const std::runtime_error& e) { // 파생 먼저
    std::cerr << e.what() << "\n";
  } catch (const std::exception& e) {     // 기저 나중
    std::cerr << e.what() << "\n";
  }
}
```
- **반드시 `const&`로 잡아라.** 값으로 받으면 slicing, 불필요 복사.

### 3-2 재던지기
```cpp
try {
  risky();
} catch (...) {
  log();      // 컨텍스트 추가
  throw;      // 현재 예외를 **그대로** 재던지기(타입/정보 유지)
}
```
- `throw;` (빈 `throw`)가 **원형 보존**.  
- `throw e;` 는 **복사/재구성**이라 정보/타입 손실 가능.

---

## 4) 표준 예외 계층 & 커스텀 예외

### 4-1 대표 계층
- `std::exception` (루트, `virtual const char* what() const noexcept`)
  - `std::logic_error` (`invalid_argument`, `domain_error`, `length_error`, `out_of_range` …)
  - `std::runtime_error` (`range_error`, `overflow_error`, `underflow_error`, `system_error` …)
  - 그 외: `bad_alloc`, `bad_cast`, `bad_function_call`, `filesystem_error` 등

### 4-2 커스텀 예외 — **표준 파생 사용** 권장
```cpp
struct my_error : std::runtime_error {
  using std::runtime_error::runtime_error; // 생성자 상속
};
// 사용
throw my_error("config missing: /etc/app.toml");
```
- `what()` 문자열은 내부에 보관한 버퍼의 `c_str()`을 반환(수명 관리 주의).  
- **원시 타입/문자열 리터럴** 그대로 던지는 것 금지(일관성/호환성 떨어짐).

---

## 5) 스택 언와인딩 & RAII (자원 관리 핵심)
- 예외가 던져지면 **경로를 타고 올라가며** 이미 생성된 **지역 객체 파괴자 호출** → 이게 **언와인딩**.
- 리소스는 **RAII**로 잡아라(파일/락/메모리). 소멸 시 자동 회수.

```cpp
struct File {
  FILE* f{};
  explicit File(const char* p) : f(std::fopen(p, "rb")) {
    if (!f) throw std::runtime_error("open fail");
  }
  ~File() noexcept { if (f) std::fclose(f); } // 소멸자는 noexcept 유지
};

void read_config() {
  File in("config.bin");         // 여기까지 성공하면
  parse(in);                     // 중간에 예외 발생해도
}                                // in의 소멸자로 닫힌다
```
> **중요:** **소멸자에서 예외를 던지지 말 것.** 언와인딩 중 예외가 또 발생하면 `std::terminate`.

---

## 6) 예외 안전성 3단계 & 패턴

| 단계 | 보장 | 의미 | 구현 힌트 |
|---|---|---|---|
| **No-throw** | 예외 절대 X | 실패가 없음 | `noexcept` 함수/이동/`swap` |
| **Strong** | **전부 성공 or 롤백** | 실패 시 상태 불변 | **copy-and-swap**, 임시객체로 커밋 |
| **Basic** | 불변식 유지, 리소스 누수 X | 일부 상태 변화 가능 | RAII, 강한 예외 보장 어려울 때 대안 |

### 6-1 Copy-and-Swap (Strong)
```cpp
struct S {
  std::vector<int> v;

  void swap(S& other) noexcept { v.swap(other.v); }

  S& operator=(S other) noexcept( noexcept(swap(other)) ) {
    swap(other);     // 강한 보장: 실패하면 기존 상태 유지
    return *this;
  }
};
```

### 6-2 Nothrow Swap / 이동 최적화
- 컨테이너는 **이동이 `noexcept`면** 재할당에서 복사 대신 이동 → **큰 성능 차이**.
```cpp
struct Big {
  std::unique_ptr<int[]> buf;
  Big(Big&&) noexcept = default;          // 이동은 noexcept로!
  Big& operator=(Big&&) noexcept = default;
};
```

---

## 7) `noexcept` 완전 정복

### 7-1 선언 vs 연산자
```cpp
void f() noexcept;                  // 선언: f는 예외 안 던짐(던지면 terminate)
static_assert(noexcept(f()));       // 연산자: 컴파일 타임 점검
```

### 7-2 **조건부 `noexcept`**
```cpp
template <class T>
void sink(T&& t) noexcept(noexcept(T(std::forward<T>(t)))) {
  // T의 이동 생성자가 noexcept일 때만 noexcept
}
```

### 7-3 예외 발생 시 동작
- `noexcept` 함수에서 예외가 **밖으로 새면** → **`std::terminate`**.
- **정말** 던질 일이 없을 때만 붙여라. (이동/`swap`/소멸자/로깅 등)

### 7-4 옛 `throw()` 스펙 (Dynamic Exception Specification)
- `void f() throw();` 는 C++17에서 **제거**(C++11부터 폐기). 의미상 `noexcept(true)`과 유사했지만 **사용 금지**.

---

## 8) 실전 예외 패턴

### 8-1 에러 정책: 예외 vs 에러코드 vs `expected`
- **예외**: 드문 실패, 깊은 스택, 즉시 중단/롤백 필요.
- **에러코드/`std::error_code`**: OS/IO/성능 민감, 반복적 실패가 정상인 시나리오.
- **`std::expected<T,E>`(C++23)**: 함수형 스타일, 분기 제거, RVO 친화.
```cpp
#include <expected>
std::expected<int, std::string> parse_int(std::string_view s);

auto r = parse_int("42");
if (!r) { log(*r.error()); return; }
use(*r);
```

### 8-2 `std::system_error` / `error_code`
```cpp
#include <system_error>
void open_or_throw() {
  std::error_code ec;
  // ... OS 호출
  if (ec) throw std::system_error(ec, "open failed");
}
```

### 8-3 스레드 간 예외 전달: `exception_ptr`
```cpp
#include <exception>
#include <thread>

std::exception_ptr ep;

void worker() {
  try { risky(); }
  catch (...) { ep = std::current_exception(); }
}

int main() {
  std::thread t(worker); t.join();
  if (ep) std::rethrow_exception(ep);
}
```

### 8-4 중첩 예외: 원인 체인
```cpp
#include <exception>

try {
  try { load(); }
  catch (...) { std::throw_with_nested(std::runtime_error("load failed")); }
} catch (const std::exception& e) {
  // rethrow_if_nested로 체인 풀기
  try { std::rethrow_if_nested(e); }
  catch (const std::exception& inner) { /* inner.what() */ }
}
```

---

## 9) 생성자/소멸자와 예외

- **생성자**에서 예외 → **부분 생성된 서브객체는 자동 파괴**.
- **소멸자 기본은 `noexcept(true)`**. 던지면 terminate. 필요하면 내부에서 **삼킴/로그**:
```cpp
~X() noexcept {
  try { may_throw(); }
  catch (...) { log(); /* 삼키기 */ }
}
```

---

## 10) 성능/바이너리/플래그

- 대부분의 구현(예: Itanium ABI)은 **비(非)예외 경로에 런타임 오버헤드 0**(대신 **코드/메타데이터 크기 증가**).
- 빈번한 실패/핫패스는 예외 부적합. 측정이 답.
- **예외 비활성**: `-fno-exceptions`(GCC/Clang). 이 모드에서는 `throw` → **즉시 terminate**.  
  라이브러리 의존성까지 확인 필요. (`-fno-rtti`와 함께 쓰는 사례도 있으나 신중)

---

## 11) 흔한 실수 & 베스트 프랙티스

**하지 말 것**
- 소멸자/`operator delete`/`swap`에서 예외 던지기
- `catch (...)` 남발 후 **침묵**(로그/복구/재던지기 없이 삼키기)
- **값으로** `catch` (slicing 위험)
- **원시 타입/문자열** 던지기

**할 것**
- **표준 계층 파생**만 던지기, 메시지/컨텍스트 제공
- **파생→기저 순서**로 `catch`
- **RAII**로 자원 수명 고정, 필요한 곳에만 `try` 경계
- **이동/`swap`을 `noexcept`**로 만들어 컨테이너 최적화 활용
- 라이브러리라면 **양면 API** 제공(예외 버전 + `expected`/에러코드 버전)

---

## 12) 스니펫 모음

### 12-1 강한 보장 대입 연산자
```cpp
struct Buf {
  std::unique_ptr<int[]> p;
  size_t n{};
  void swap(Buf& o) noexcept { std::swap(p, o.p); std::swap(n, o.n); }

  Buf& operator=(Buf other) noexcept { // by value + swap
    swap(other);                       // 강한 보장
    return *this;
  }
};
```

### 12-2 `noexcept` 이동이 컨테이너에 미치는 영향
```cpp
struct Moveable {
  Moveable(Moveable&&) noexcept = default;
  Moveable& operator=(Moveable&&) noexcept = default;
  // vector<Moveable> reallocate 시 복사 대신 이동 사용
};
```

### 12-3 재던지기 vs 새로 던지기
```cpp
catch (const std::exception& e) {
  log(e);
  throw;      // ✅ 원형 보존
  // throw e; // ⚠️ 재구성: 타입/정보 손실 가능
}
```

---

## 13) 체크리스트 (PR 전에 훑어보기)
- [ ] 예외는 **정말 예외적인 상황**에만?
- [ ] **표준 파생 타입**만 던짐? (`std::runtime_error` 등)
- [ ] `catch`는 **`const&`**? 파생→기저 순서?
- [ ] **소멸자/이동/`swap`**은 `noexcept`?
- [ ] 변경 연산은 **Basic/Strong** 보장 명확?
- [ ] 핫패스에서 예외 남발하지 않음?
- [ ] 라이브러리면 **예외+에러코드/expected** 양면 지원?
- [ ] 스레드 경계 넘길 때 `exception_ptr` 고려?
- [ ] **임베디드/RT** 타깃에서 `-fno-exceptions` 시나리오 점검?

---

## 14) 참고
- cppreference — *Language support / Exceptions*  
- Herb Sutter — *Exception-Safety in C++*  
- Meyers — *Effective C++*: 소멸자에서 예외 피하기, 예외 중립성  
- P0323 — `std::expected` (C++23)
