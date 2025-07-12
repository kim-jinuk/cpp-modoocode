# 03. Class Inheritance

## 1. 목차
- 상속의 기본 구조와 사용 목적
- public / protected / private 상속 차이
- 다중 상속과 가상 상속
- Base 클래스 설계 시 주의사항

---

## 2. 핵심 용어 & 분류
| 개념 | 정의 | 비고 |
|------|------|------|
| **Base / Derived Class** | 부모 클래스 / 자식 클래스 | |
| **Access Specifier** | 상속 시 멤버 접근성 | public, protected, private |
| **Virtual Inheritance** | 다중 상속 다이아몬드 문제 해결 | `virtual` 키워드 |
| **Pure Virtual Function** | 순수가상함수 → 인터페이스 역할 | `= 0` |
| **Abstract Class** | 직접 인스턴스화 불가 클래스 | 순수가상함수 ≥1개 |

---

## 3. 상속 핵심 구조 설계 포인트

### 3-1 기본 상속 구조
```cpp
class Animal {
public:
    virtual void speak() const = 0;
    virtual ~Animal() = default;
};

class Dog : public Animal {
public:
    void speak() const override { std::cout << "Woof!"; }
};
```

### 3-2 public vs protected vs private 상속
- public 상속: “is-a” 관계
- protected 상속: 내부 재사용
- private 상속: 구현을 구성요소로 활용

### 3-3 가상 상속과 다중 상속
- 다중 상속 시 Base 중복 → 다이아몬드 문제
- `virtual Base` 로 해결

```cpp
struct A { int x; };
struct B : virtual A {};
struct C : virtual A {};
struct D : B, C {};
```

---

## 4. 대표 예시: 패턴 & Idiom
| 패턴 | 핵심 아이디어 | 사례 |
|------|----------------|------|
| **Interface Class** | 순수가상함수로 역할만 제공 | `Drawable` |
| **NVI Idiom** | Non-Virtual Interface: 공통 부분 base에서 | `Base::run()` → `virtual impl()` |
| **CRTP** | 정적 다형성 | 정책 기반 설계 |

---

## 5. 상속 관련 비용 / 관리 포인트
```text
Virtual call: indirect call cost
Virtual inheritance: 메모리 & vptr 비용
vtable: 런타임 오버헤드
```

---

## 6. 흔한 실수 & Best Practice
- Base 클래스에는 반드시 virtual 소멸자 제공
- 다중 상속은 인터페이스용으로만 최소화
- 상속보다 합성을 먼저 고려
- 멤버 초기화 순서 Base→Member→Derived 주의

---

## 7. 더 읽어볼 것
- cppreference: [Inheritance](https://en.cppreference.com/w/cpp/language/derived_class)
- Effective C++, Item 14~17
- Herb Sutter, *Virtuality* series
