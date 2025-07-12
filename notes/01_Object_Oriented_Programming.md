# 01. Object-Oriented Programming (OOP)

## 1. 목차
- 클래스와 객체의 개념 이해
- 캡슐화 / 상속 / 다형성 핵심 개념
- Rule of 0/3/5 / RAII 실천
- Composition vs Inheritance

---

## 2. 핵심 용어 & 분류
| 개념 | 정의 | 비고 |
|------|------|------|
| **Class / Object** | 사용자 정의 타입 / 그 인스턴스 | 기본 접근 `private` |
| **Encapsulation** | 데이터와 함수를 묶어 인터페이스만 노출 | `public` / `private` |
| **Inheritance** | 기존 타입을 확장해 새 타입 정의 | `public`·`protected`·`private` 상속 |
| **Polymorphism** | 동일 인터페이스, 다른 구현 선택 | 정적(O/L) · 동적(O/R) |
| **RAII** | 리소스 수명과 객체 수명 일치 | 스마트포인터, 파일 핸들 |
| **Rule of 0/3/5** | 복사·이동·소멸자 관리 원칙 | 복사/이동 필요 여부 가이드 |

---

## 3. OOP 핵심 구조 설계 포인트

### 3-1 클래스 구조
```cpp
class Point {
  int x_, y_;
public:
  Point(int x=0, int y=0) : x_(x), y_(y) {}
  int x() const { return x_; }
  void move(int dx, int dy) { x_ += dx; y_ += dy; }
};
```

- 멤버 변수는 `private`로, 행동은 `public` 메서드로
- 생성자/복사/소멸자/연산자 오버로딩 관리
- 멤버 이니셜라이저 리스트 사용

### 3-2 상속 & 가상함수
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

- 순수가상함수로 인터페이스 설계
- `override` / `final` 키워드로 실수 방지
- 동적 바인딩 vs 정적 바인딩 차이

### 3-3 Composition vs Inheritance
- “is-a” vs “has-a” 판단 기준
- 상속 남발의 위험성 (fragile base class 문제)
- PImpl idiom: 구현을 캡슐화하여 컴파일 의존성 줄이기

---

## 4. 대표 예시: 패턴 & Idiom
| 패턴 | 핵심 아이디어 | 사례 |
|------|----------------|------|
| **PImpl** | 구현 숨김, 컴파일 종속성 ↓ | 대형 클래스 API 안정화 |
| **RAII** | 리소스 소유권 = 객체 수명 | 파일 핸들, 스마트포인터 |
| **Rule of 0/3/5** | 복사/이동 연산자 관리 | 사용자 정의 여부 판단 |
| **CRTP** | 정적 다형성 | 정책 기반 설계 |

---

## 5. OOP 주요 연산 복잡도 / 관리 포인트
```text
Object copy ctor      Deep copy cost O(n)
Move ctor             Steal resource, O(1)
Virtual call          Indirect call cost
Shared_ptr refcount   Atomic inc/dec cost
```

---

## 6. 흔한 실수 & Best Practice
- Base 클래스에는 virtual 소멸자 반드시
- Rule of 0/3/5 준수
- 상속보다 합성을 먼저 고려
- 스마트포인터 사용으로 수명 관리

---

## 7. 더 읽어볼 것
- cppreference: [Classes](https://en.cppreference.com/w/cpp/language/classes)
- Effective C++ / More Effective C++
- Herb Sutter, *RAII Still Rules*
