# 09. R-Value and Move Semantics

## 1. 목차
- **l-value** vs **r-value** 개념 차이
  - **주소값**을 취득할 수 있는지를 기준으로 구분
- **r-value reference(T&&)**의 의미
- **이동 생성자** & **이동 대입 연산자**
- **std::move**와 **std::forward**
- **Perfect Forwarding** 기초

---

## 2. 핵심 용어 & 분류
| 개념 | 정의 | 비고 |
|------|------|------|
| **l-value** | 이름이 있는 값, 주소 참조 가능한 값 | 변수, 객체 |
| **r-value** | 일시적인 값, 주소 참조 불가능한 값 | 리터럴, 임시 객체 |
| **r-value Reference** | T&& | 이동 의미론 핵심 |
| **Move Constructor** | 리소스 소유권 이전 | 복사보다 효율적 |
| **std::move** | 명시적 r-value 캐스팅 | |
| **Perfect Forwarding** | Universal Reference | 템플릿 인자 유지 |

---

## 3. 핵심 구조 설계 포인트

### 3-1 l-value vs r-value
```cpp
int x = 5;     // x: l-value, 5: r-value
int&& y = 10;  // 10: r-value
```

### 3-2 이동 생성자 & 이동 대입 연산자
```cpp
class Buffer {
  int* data;
  size_t size;
public:
  Buffer(size_t n) : data(new int[n]), size(n) {}
  ~Buffer() { delete[] data; }

  Buffer(Buffer&& other) noexcept
    : data(other.data), size(other.size) {
      other.data = nullptr; other.size = 0;
  }

  Buffer& operator=(Buffer&& other) noexcept {
    if (this != &other) {
      delete[] data;
      data = other.data;
      size = other.size;
      other.data = nullptr; other.size = 0;
    }
    return *this;
  }
};
```

### 3-3 std::move / std::forward
```cpp
std::string s = "hello";
std::string t = std::move(s); // s는 비워짐

template<typename T>
void wrapper(T&& arg) {
  func(std::forward<T>(arg));
}
```

---

## 4. 대표 예시: 패턴 & Idiom
| 패턴 | 핵심 아이디어 | 사례 |
|------|----------------|------|
| **Rule of 5** | 복사 + 이동 + 소멸자 세트 관리 | 자원 직접 관리 클래스 |
| **Move-only Type** | 복사 금지, 이동만 허용 | unique_ptr |
| **Perfect Forwarding** | 인자 원형 유지 | emplace_back |

---

## 5. 비용 / 관리 포인트
```text
이동은 얕은 복사 + 원본 무효화 → 비용↓
std::move는 단순 캐스팅, 실질 이동은 아님
Perfect Forwarding은 Universal Reference(== Forwarding Reference)만
```

---

## 6. 흔한 실수 & Best Practice
- **std::move** 후 원본 객체 사용 X (dangling)
- **Rule of 5** 지켜서 move/copy 일관성 유지
- **noexcept**로 **이동 연산자 최적화**
- vector, map 등 **emplace** 사용으로 **불필요한 복사 방지** (vec.push_back(A(1,2,3)) --> vec.emplace_back(1,2,3))

---

## 7. 더 읽어볼 것
- cppreference: [Move Semantics](https://en.cppreference.com/w/cpp/language/move_constructor)
- Effective Modern C++, Item 23~27
- Scott Meyers, Universal References & Perfect Forwarding
