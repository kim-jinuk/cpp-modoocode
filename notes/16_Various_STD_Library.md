# 16. Various STD Library

## 1. 목차
- <utility> : std::pair, std::move, std::forward
- <tuple> : 다중 반환과 구조화 바인딩
- <optional> : 값이 있을 수도 없을 수도 있음
- <variant> : 타입 안전 유니언
- <any>, <bitset>, <chrono> 등 대표 예시
- Best Practice

---

## 2. 핵심 용어 & 분류
| 개념 | 정의 | 비고 |
|------|------|------|
| **std::pair** | 2개 값 묶음 | first, second |
| **std::tuple** | 여러 타입 값 묶음 | tie, structured binding |
| **std::optional** | 값 존재 유무 표현 | monadic |
| **std::variant** | 여러 타입 중 하나 | 타입 안전 유니언 |
| **std::any** | 아무 타입 저장 | 타입 체크 필요 |
| **std::bitset** | 고정 크기 비트 벡터 | |
| **std::chrono** | 시간/기간 라이브러리 | |

---

## 3. 대표 구조 설계 포인트

### 3-1 <utility> : pair, move, forward
```cpp
std::pair<int, std::string> p = {1, "hello"};
auto [num, str] = p;

int&& x = std::move(num);
```

### 3-2 <tuple> : 다중 반환
```cpp
std::tuple<int, double, std::string> t = {1, 2.5, "hi"};
auto [i, d, s] = t;

auto get_values() {
  return std::make_tuple(1, 2.0);
}
```

### 3-3 <optional>
```cpp
std::optional<int> maybe = 5;
if (maybe) std::cout << *maybe;
```

### 3-4 <variant>
```cpp
std::variant<int, std::string> v = "hi";
std::visit([](auto&& arg){ std::cout << arg; }, v);
```

### 3-5 기타 <any>, <bitset>, <chrono>
```cpp
std::any a = 42;

std::bitset<8> bs("10101010");

auto start = std::chrono::steady_clock::now();
// ... do work ...
auto end = std::chrono::steady_clock::now();
```

---

## 4. 대표 예시: 패턴 & Idiom
| 패턴 | 핵심 아이디어 | 사례 |
|------|----------------|------|
| **Structured Binding** | tuple, pair 분해 | auto [a,b] = pair |
| **Optional Return** | 실패 가능 값 | optional<T> |
| **Visitor Pattern** | variant 처리 | std::visit |

---

## 5. 비용 / 관리 포인트
```text
pair, tuple 값 복사 비용 주의
optional 값 없으면 예외 X, 안전
variant 잘못된 타입 접근 시 예외
any: 타입 정보 필요 → casting 비용
```

---

## 6. 흔한 실수 & Best Practice
- pair/tuple은 auto [a,b] structured binding 적극 활용
- optional은 값 존재 여부 먼저 체크
- variant는 반드시 방문자 패턴 사용
- chrono는 duration_cast로 단위 변환

---

## 7. 더 읽어볼 것
- cppreference: [utility](https://en.cppreference.com/w/cpp/utility)
- cppreference: [tuple](https://en.cppreference.com/w/cpp/utility/tuple)
- cppreference: [optional](https://en.cppreference.com/w/cpp/utility/optional)
- Effective Modern C++, Item 32~35
