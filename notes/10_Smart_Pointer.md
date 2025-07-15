# 10. Smart Pointer

## 1. 목차
- 스마트 포인터 도입 이유
- unique_ptr / shared_ptr / weak_ptr 구조
- std::make_unique, std::make_shared
- 순환 참조 문제와 해결법
- Best Practice

---

## 2. 핵심 용어 & 분류
| 개념 | 정의 | 비고 |
|------|------|------|
| **unique_ptr** | 단일 소유권, 이동만 가능 | 가장 가볍고 안전 |
| **shared_ptr** | 참조 카운트 기반 공유 소유권 | 비용 있음 |
| **weak_ptr** | shared_ptr 순환 참조 방지 | 참조 카운트 증가 X |
| **make_unique** | 안전한 생성자 | new 직접 호출 대체 |
| **make_shared** | shared_ptr + 객체 + 컨트롤 블록 할당 | 캐시 효율적 |
| **use_count** | shared_ptr 참조 횟수 | 디버깅 시 사용 |

---

## 3. 스마트 포인터 구조 설계 포인트

### 3-1 unique_ptr
```cpp
std::unique_ptr<int> p = std::make_unique<int>(10);
auto p2 = std::move(p);
```
- 복사 불가, 이동만 가능
- reset(), release()로 소유권 제어

### 3-2 shared_ptr
```cpp
std::shared_ptr<int> sp1 = std::make_shared<int>(5);
std::shared_ptr<int> sp2 = sp1;
```
- 컨트롤 블록 관리
- 참조 카운트 0 되면 해제

### 3-3 weak_ptr
```cpp
std::weak_ptr<int> wp = sp1;
if (auto spt = wp.lock()) {
  // 유효 시 shared_ptr 획득
}
```

### 3-4 make_unique, make_shared
```cpp
auto up = std::make_unique<MyClass>();
auto sp = std::make_shared<MyClass>();
```

---

## 4. 대표 예시: 패턴 & Idiom
| 패턴 | 핵심 아이디어 | 사례 |
|------|----------------|------|
| **RAII** | 객체 수명과 리소스 해제 연계 | 모든 스마트 포인터 |
| **Pimpl** | 구현 숨김 시 unique_ptr | |
| **Observer Pattern** | weak_ptr로 관찰자 참조 | |

---

## 5. 비용 / 관리 포인트
```text
unique_ptr    단일 소유권, 오버헤드 최소
shared_ptr    atomic 연산 비용↑
weak_ptr      순환 참조 방지
```

---

## 6. 흔한 실수 & Best Practice
- new/delete 직접 호출 금지, make 계열 함수 사용
- shared_ptr 순환 참조는 weak_ptr로 끊기
- unique_ptr noexcept 이동 연산자 활용
- raw pointer와 혼용 금지

---

## 7. 더 읽어볼 것
- cppreference: [Smart Pointers](https://en.cppreference.com/w/cpp/memory)
- Effective Modern C++, Item 18~21
- Herb Sutter: Resource Management & RAII
