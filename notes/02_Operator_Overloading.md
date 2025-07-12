# 02. Operator Overloading

## 1. 목차
- 연산자 오버로딩의 목적과 원칙
- 멤버 함수 vs 전역 함수
- 주의할 연산자 / 오버로딩 금지 연산자
- 암시적 변환 주의

---

## 2. 핵심 용어 & 분류
| 개념 | 정의 | 비고 |
|------|------|------|
| **Operator Overloading** | 사용자 정의 타입에 연산자 기능 부여 | `+`, `==` 등 |
| **멤버 vs 비멤버** | 피연산자 위치에 따라 결정 | 좌항 수정 필요 시 멤버 |
| **암시적 변환** | 단일 매개변수 생성자 → 자동 타입 변환 | `explicit`로 방지 |
| **Comparison Operators** | 동치·대소 비교 | C++20: `operator<=>` |
| **Stream Operators** | `<<`, `>>` 입력 출력 | 보통 비멤버 + friend |

---

## 3. 연산자 오버로딩 핵심 설계 포인트

### 3-1 연산자 작성 규칙
- 대입 `operator=` 는 멤버 함수로만 가능
- `operator+` / `operator-` : 값 반환 → 비멤버 함수 권장
- `operator[]` : 배열 인덱싱 → 멤버 함수
- `operator()` : 함수 호출 연산자 → functor 객체

### 3-2 멤버 vs 전역 함수
- 좌항 객체를 수정해야 하면 멤버 함수 필수
- 양쪽 피연산자 타입이 다를 수 있으면 비멤버 함수 + `friend` 사용

### 3-3 암시적 변환과 explicit
```cpp
class Rational {
public:
    explicit Rational(int num, int denom = 1);
    Rational operator+(const Rational&) const;
};
Rational r = 1 + Rational(3,4); // int → Rational 암시 변환 방지됨
```

---

## 4. 대표 예시: 패턴 & Idiom
| 패턴 | 핵심 아이디어 | 사례 |
|------|----------------|------|
| **Swap Idiom** | 예외 안전한 대입 연산자 | Copy-and-Swap |
| **Streaming** | I/O 연산자 friend로 정의 | `std::ostream& operator<<(...)` |
| **Equality** | 비교 연산자 쌍으로 정의 | C++20 `<=>` |
| **CRTP for Operators** | 반복되는 연산자 템플릿화 | Boost.Operator |

---

## 5. 연산자 오버로딩 관련 비용/주의
```text
operator=            Deep copy cost O(n)
operator+            Return by value → RVO 최적화
operator<<           Stream 버퍼 비용 고려
암시적 변환           성능·버그 위험 (explicit로 제어)
```

---

## 6. 흔한 실수 & Best Practice
- 불필요한 연산자 오버로딩 지양 (`++`, `--`는 정말 필요할 때만)
- Rule of 3: 대입 연산자/복사 생성자/소멸자는 세트로 관리
- `operator<<`는 friend로 정의하고, std::ostream 반환
- 암시적 변환은 explicit로 통제

---

## 7. 더 읽어볼 것
- cppreference: [Operator Overloading](https://en.cppreference.com/w/cpp/language/operators)
- Scott Meyers, *Effective C++*
- Herb Sutter, *GotW* 시리즈
