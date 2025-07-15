# 15. decltype

## 1. 목차
- decltype의 기본 역할과 auto 차이
- 선언 타입 vs 표현식 타입
- decltype(auto)로 완벽 추론
- forwarding 참조와 decltype
- Best Practice

---

## 2. 핵심 용어 & 분류
| 개념 | 정의 | 비고 |
|------|------|------|
| **decltype** | 표현식 타입 추론 | 정적 검사 |
| **auto** | 초기화 값 기반 타입 | 값에 따라 다름 |
| **decltype(auto)** | 값+참조 모두 보존 | 완벽 추론 |
| **Forwarding Ref** | universal reference | T&& |
| **Unevaluated Context** | 표현식 평가 X 타입만 | decltype |

---

## 3. decltype 설계 포인트

### 3-1 decltype 기본
```cpp
int x = 3;
decltype(x) y = x;
```

### 3-2 표현식에 따른 참조 여부
```cpp
int i = 42;
int& ri = i;

decltype(i) a;    // int
decltype((i)) b = i; // int&
decltype(ri) c = i;  // int&
```

### 3-3 decltype(auto)
```cpp
auto f1() { int x=3; return x; }
decltype(auto) f2() { int x=3; return (x); }
```

### 3-4 Forwarding과 decltype
```cpp
template<typename T>
decltype(auto) forwarder(T&& val) {
  return std::forward<T>(val);
}
```

---

## 4. 대표 예시: 패턴 & Idiom
| 패턴 | 핵심 아이디어 | 사례 |
|------|----------------|------|
| **decltype(auto)** | 참조+값 완벽 추론 | 함수 반환 |
| **Perfect Forwarding** | universal ref + decltype | forwarding |
| **Unevaluated Context** | 표현식 평가 없이 타입만 | decltype(expr) |

---

## 5. 비용 / 관리 포인트
```text
decltype는 런타임 비용 X
괄호 유무에 따라 참조 달라짐
auto는 값 타입만 → 참조 유지 X
```

---

## 6. 흔한 실수 & Best Practice
- decltype((var))와 decltype(var) 차이 주의
- decltype(auto)로 함수 반환 시 참조 유지
- Perfect Forwarding 시 std::forward 함께
- 긴 타입은 별칭으로 가독성 ↑

---

## 7. 더 읽어볼 것
- cppreference: [decltype](https://en.cppreference.com/w/cpp/language/decltype)
- Effective Modern C++, Item 2~3
- Scott Meyers, auto vs decltype 비교
