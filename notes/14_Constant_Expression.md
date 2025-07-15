# 14. Constant Expression

## 1. 목차
- const와 constexpr의 차이
- 컴파일 타임 상수 계산
- constexpr 함수와 if constexpr
- Literal Type과 제한
- Best Practice

---

## 2. 핵심 용어 & 분류
| 개념 | 정의 | 비고 |
|------|------|------|
| **const** | 불변 변수/객체 | 런타임 상수 가능 |
| **constexpr** | 컴파일 타임 상수 | 함수, 객체, 생성자 |
| **Literal Type** | 컴파일 상수로 계산 가능 타입 | |
| **if constexpr** | 조건부 분기 제거 | C++17 |
| **Compile-time** | 컴파일 시점 계산 | 성능 최적화 |

---

## 3. 상수 표현식 설계 포인트

### 3-1 const vs constexpr
```cpp
const int x = 5;
constexpr int y = 10;
```

### 3-2 constexpr 함수
```cpp
constexpr int square(int x) { return x * x; }
int arr[square(3)];
```

### 3-3 if constexpr
```cpp
template<typename T>
void print(T t) {
  if constexpr (std::is_integral_v<T>) {
    std::cout << "Integral";
  } else {
    std::cout << "Other";
  }
}
```

### 3-4 Literal Type 제한
- constexpr는 Literal Type에만 적용
- 사용자 정의 타입도 모든 멤버 constexpr 필요

---

## 4. 대표 예시: 패턴 & Idiom
| 패턴 | 핵심 아이디어 | 사례 |
|------|----------------|------|
| **Constexpr Function** | 컴파일 시점 계산 | constexpr int add() |
| **Compile-time Branch** | if constexpr | 템플릿 분기 |
| **Literal Struct** | 구조체 상수화 | constexpr 생성자 |

---

## 5. 비용 / 관리 포인트
```text
constexpr로 런타임 계산 제거
컴파일 시점 복잡도 ↑ 빌드 시간 ↑
Literal Type만 가능
```

---

## 6. 흔한 실수 & Best Practice
- constexpr는 항상 컴파일 시점 평가 가능해야 함
- 런타임 상수만 필요하다면 const 사용
- Literal Type 아닌 타입에는 constexpr 불가
- constexpr 멤버 함수는 inline 포함 의미

---

## 7. 더 읽어볼 것
- cppreference: [constexpr](https://en.cppreference.com/w/cpp/language/constexpr)
- Effective Modern C++, Item 15~17
- Scott Meyers, Compile-time constant patterns
