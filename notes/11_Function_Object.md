# 11. Function Object (Functor)

## 1. 목차
- 함수 객체(Functor)의 개념과 필요성
- 함수 포인터 vs Functor
- std::function과 람다
- 커스텀 비교자 / 조건자 패턴
- Best Practice

---

## 2. 핵심 용어 & 분류
| 개념 | 정의 | 비고 |
|------|------|------|
| **Functor** | operator() 오버로딩 객체 | 상태 저장 가능 |
| **Function Pointer** | 함수의 주소 | 상태 저장 X |
| **std::function** | 일반화된 호출자 래퍼 | 타입 소거 |
| **Lambda** | 익명 함수 객체 | 상태 캡쳐 가능 |
| **Predicate** | 조건자 | 비교 함수 등 |

---

## 3. Functor 설계 포인트

### 3-1 Functor 기본 구조
```cpp
struct Adder {
  int operator()(int a, int b) const {
    return a + b;
  }
};
Adder add;
int result = add(1, 2); // 3
```

### 3-2 함수 포인터 vs Functor vs 람다
```cpp
void func() { /* ... */ }
void (*fptr)() = func;
fptr();

auto lambda = [](int x) { return x * 2; };
lambda(3); // 6
```

### 3-3 std::function
```cpp
std::function<int(int)> f = [](int x) { return x * 2; };
f(5); // 10
```

### 3-4 커스텀 비교자/조건자
```cpp
struct Compare {
  bool operator()(int a, int b) const {
    return a > b;
  }
};
std::priority_queue<int, std::vector<int>, Compare> pq;
```

---

## 4. 대표 예시: 패턴 & Idiom
| 패턴 | 핵심 아이디어 | 사례 |
|------|----------------|------|
| **STL Predicate** | 조건자 전달 | find_if, sort |
| **Stateful Functor** | 내부 상태 유지 | 횟수 카운트 등 |
| **Lambda Capture** | 지역 변수 캡쳐 | [&](x) { ... } |

---

## 5. 비용 / 관리 포인트
```text
Functor      인라인 최적화 유리
std::function 타입 소거 → 오버헤드 有
Lambda       가볍고 캡쳐로 편리
```

---

## 6. 흔한 실수 & Best Practice
- std::function 지나친 남발은 성능↓
- Functor는 상태 변경 시 불변성 고려
- STL 조건자는 반환 bool 요구
- 비교 Functor는 strict weak ordering 만족해야 함

---

## 7. 더 읽어볼 것
- cppreference: [Function Object](https://en.cppreference.com/w/cpp/utility/functional)
- Effective STL, Item 46~50
- Scott Meyers, Modern C++ 람다 챕터
