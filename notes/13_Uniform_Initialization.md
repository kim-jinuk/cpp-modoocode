# 13. Uniform Initialization

## 1. 목차
- 통일 초기화 문법 {}의 도입 배경
- Brace Initializer vs () vs =
- Narrowing Conversion 방지
- 초기화 순서: 멤버 이니셜라이저 리스트
- initializer_list와 범위 기반 for

---

## 2. 핵심 용어 & 분류
| 개념 | 정의 | 비고 |
|------|------|------|
| **Uniform Initialization** | 모든 타입에 {} 사용 | C++11 |
| **Brace Initializer** | 중괄호 초기화 | narrowing 방지 |
| **Narrowing** | 타입 축소로 손실 | 컴파일 오류 |
| **initializer_list** | {}로 다중 값 전달 | vector 등 |
| **Delegating Constructor** | 다른 생성자 호출 | 멤버 초기화 |

---

## 3. 설계 포인트

### 3-1 기본 구조
```cpp
int x{5};
std::vector<int> v{1, 2, 3};
```

### 3-2 Narrowing Conversion
```cpp
double d = 3.14;
int x1 = d;  // OK
int x2{d};   // Error!
```

### 3-3 멤버 이니셜라이저 리스트
```cpp
class Point {
  int x, y;
public:
  Point(int a, int b) : x{a}, y{b} {}
};
```

### 3-4 initializer_list & for
```cpp
std::vector<int> v = {1, 2, 3};
for (auto x : v) std::cout << x;
```

---

## 4. 대표 예시: 패턴 & Idiom
| 패턴 | 핵심 아이디어 | 사례 |
|------|----------------|------|
| **Uniform Init** | 모든 타입 {} | int, class |
| **No Narrowing** | 손실 방지 | int{3.14} 오류 |
| **Delegating Ctor** | 생성자 재사용 | Point(int) : Point(int,int) |

---

## 5. 비용 / 관리 포인트
```text
{} 안전: narrowing 방지
()는 허용 → 의도적 사용
initializer_list 복사 발생 가능
```

---

## 6. 흔한 실수 & Best Practice
- {}와 () 혼용 시 의미 구분
- 초기화 순서는 선언 순서 우선
- vector v{size} → initializer_list → v(size)로
- 멤버 초기화는 이니셜라이저 리스트

---

## 7. 더 읽어볼 것
- cppreference: [List Initialization](https://en.cppreference.com/w/cpp/language/list_initialization)
- Effective Modern C++, Item 7~8
- Scott Meyers, Brace vs Paren 초기화
