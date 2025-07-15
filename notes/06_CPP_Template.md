# 06. C++ Template

## 1. 목차
- 함수 템플릿과 클래스 템플릿 기본 구조
- 템플릿 인자 추론과 특수화
- SFINAE와 enable_if
- 템플릿 메타프로그래밍(TMP) 간단 입문
- CRTP (Curiously Recurring Template Pattern)

---

## 2. 핵심 용어 & 분류
| 개념 | 정의 | 비고 |
|------|------|------|
| **Function Template** | 타입에 독립적인 함수 | template<typename T> |
| **Class Template** | 타입에 독립적인 클래스 | template<class T> |
| **Specialization** | 특정 타입에 맞춘 구현 | Partial / Full |
| **SFINAE** | Substitution Failure Is Not An Error | enable_if |
| **CRTP** | 자기 자신 타입을 파라미터로 전달 | 정적 다형성 |
| **Metaprogramming** | 컴파일 타임 계산 | constexpr + TMP |

---

## 3. 템플릿 설계 포인트

### 3-1 함수 템플릿
```cpp
template<typename T>
T add(T a, T b) { return a + b; }

int x = add(1, 2);
double y = add(1.5, 2.5);
```

### 3-2 클래스 템플릿
```cpp
template<typename T>
class Box {
    T value;
public:
    Box(T v) : value(v) {}
    T get() const { return value; }
};
Box<int> b(123);
```

### 3-3 특수화와 Partial Specialization
```cpp
template<typename T> struct Printer;
template<> struct Printer<int> {
    void print() { std::cout << "int!\n"; }
};
```

### 3-4 SFINAE & enable_if
```cpp
template<typename T>
std::enable_if_t<std::is_integral_v<T>, bool>
is_odd(T i) { return bool(i % 2); }
```

### 3-5 CRTP 예시
```cpp
template <typename Derived>
class Base {
public:
    void interface() {
        static_cast<Derived*>(this)->implementation();
    }
};
class Derived : public Base<Derived> {
public:
    void implementation() { /* ... */ }
};
```

---

## 4. 대표 예시: 패턴 & Idiom
| 패턴 | 핵심 아이디어 | 사례 |
|------|----------------|------|
| **Type Traits** | 타입 속성 판별 | std::is_integral |
| **Policy-based Design** | 정책을 템플릿으로 주입 | STL allocator |
| **CRTP** | 정적 다형성 | iterator facade |
| **SFINAE** | 오버로드 조건 제한 | enable_if |

---

## 5. 템플릿 비용 / 관리 포인트
```text
컴파일 타임 길어짐: 인스턴스화 개수↑
디버깅 난이도↑: 에러 메시지 길어짐
객체 파일 부피↑: 각 타입마다 복제됨
```

---

## 6. 흔한 실수 & Best Practice
- 템플릿 정의와 구현은 보통 .hpp에 같이 둔다 (분리 시 링커 에러)
- 너무 복잡하면 concepts (C++20)로 대체
- TMP는 constexpr로 점진적 대체
- 인스턴스 수 줄여서 코드 부피 관리

---

## 7. 더 읽어볼 것
- cppreference: [Templates](https://en.cppreference.com/w/cpp/language/templates)
- Scott Meyers, Effective Modern C++
- Boost Type Traits, CRTP 사례
- Sutter, Alexandrescu: Modern C++ Design
