# 08. C++ Exception

## 1. 목차
- C++ 예외 처리 **기본 구조**
- **try** / **catch** / **throw** 사용법
- **예외 안전성**(Exception Safety) 3단계
- 표준 예외 클래스 계층
- **noexcept**와 throw specifier

---

## 2. 핵심 용어 & 분류
| 개념 | 정의 | 비고 |
|------|------|------|
| **try / catch** | 예외 발생 블록과 처리 블록 | |
| **throw** | 예외 객체 던짐 | |
| **Exception Safety** | 예외 발생 시 프로그램 일관성 보장 | **Basic** / **Strong** / **Nothrow** |
| **std::exception** | 모든 표준 예외의 **베이스 클래스** | |
| **noexcept** | 예외가 던져지지 않음을 보장 | **함수 선언 시 사용** |

---

## 3. 예외 처리 설계 포인트

### 3-1 try / catch / throw 기본 구조
```cpp
try {
  if (error) throw std::runtime_error("error!");
} catch (const std::exception& e) {
  std::cerr << e.what() << std::endl;
}
```

### 3-2 표준 예외 클래스
- **std::exception**: 최상위
- **std::runtime_error**, **std::logic_error**, **std::out_of_range** 등
- **.what()** 메서드로 메시지 확인

### 3-3 Exception Safety 3단계
- **Basic**: 리소스 누수 없고 불변식 유지
- **Strong**: 실패 시 **상태 롤백**
- **Nothrow**: 절대 예외 안 던짐 (**소멸자** 등)

### 3-4 noexcept
```cpp
void func() noexcept { /* 절대 throw 안 함 */ }
```
- STL 컨테이너 **이동 연산자 최적화**에 중요
- **noexcept 위반 시 프로그램 강제 종료**

---

## 4. 대표 예시: 패턴 & Idiom
| 패턴 | 핵심 아이디어 | 사례 |
|------|----------------|------|
| **RAII** | 자원 누수 방지 | 스마트포인터 |
| **Copy-and-Swap** | Strong Exception Safety | 대입 연산자 |
| **Nothrow Swap** | noexcept 이동 최적화 | std::swap |

---

## 5. 예외 처리 비용 / 관리 포인트
```text
throw/catch   스택 언와인딩 비용 있음
try 블록 자체는 오버헤드 적음
예외 전파 깊어지면 디버깅 복잡
```

---

## 6. 흔한 실수 & Best Practice
- **소멸자**에서 예외 던지지 않기
- **불필요한 catch(...)** 남발 금지
- 강제 종료 방지 위해 std::terminate 동작 파악
- noexcept 선언은 진짜 안전할 때만

---

## 7. 더 읽어볼 것
- cppreference: [Exception Handling](https://en.cppreference.com/w/cpp/language/exceptions)
- Effective C++, Item 8: 소멸자에서 예외 피하기
- Herb Sutter, Exception Safety 3단계
