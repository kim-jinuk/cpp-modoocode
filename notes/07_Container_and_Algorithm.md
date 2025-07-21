# 07. Container and Algorithm

## 1. 목차
- STL 컨테이너·알고리즘이 주는 가장 핵심적인 장점
    - 컨테이너와 알고리즘을 분리함으로써 데이터 구조와 로직을 단숨에 갈아 끼울 수 있게 해준다 -> 한 줄로 실험해보고 성능-메모리 트레이드오프 즉시 확인 가능
    - 템플릿으로 구현되어 컴파일 타임에 타입이 확정된다 -> 캐스팅 지옥 없이도 C 코드만큼 빠른 바이너리
    - "이터레이터 + `[first, last)`" 규악으로 커스텀 컨테이너도 STL 알고리즘에 그냥 꽂힌다 -> 코드 의존성 최소화 = 유지보수 비용 절감
    - 벡터의 reserve, list.splice() 처럼 STL 내부의 최적화 활용만 해도 손코딩 대비 퍼포먼스가 좋다
    - C++20 ranges::filter | views::transform 로 파이프라인을 이어 붙여도 비용은 인라인 최적화 수준 -> 깔끔한 선언형 코드 쓰고도 ‘0‑cost abstraction’ 유지
- 컨테이너 유형별 특징
    - Sequence, Associative, Unordered, Container Adapter
- 대표 알고리즘 & iterator 요구 조건
    - sort, stable_sort, partial_sort, remove, remove_if, accumulate 등 알고리즘
    - input, output, forward, bidirectional, random-access 등 Iterator 요구 조건
- iterator invalidation과 안전한 사용
- Best Practice
앗, 바로 파일을 만들어 첨부하려다 포맷 오류로 실패했네요. 😅
대신 아래에 **그대로 복붙해 쓸 수 있는 `.md` 원본**을 통째로 넣어 드립니다. 로컬에서 `07_container_algorithm.md` 같은 이름으로 저장하면 바로 사용 가능합니다!

````markdown
# 07. Container and Algorithm

## 1. 목차
- **STL 컨테이너·알고리즘이 주는 핵심 장점**
  - **자료구조 ↔ 로직 분리**  
    컨테이너와 알고리즘을 분리함으로써 데이터 구조와 로직을 단숨에 갈아 끼울 수 있게 해준다 -> 한 줄로 실험해보고 성능-메모리 트레이드오프 즉시 확인 가능
  - **컴파일‑타임 최적화**  
    템플릿으로 구현되어 컴파일 타임에 타입이 확정된다 -> 캐스팅 지옥 없이도 C 코드만큼 빠른 바이너리
  - **`이터레이터 + [first, last)` 규약**  
    "이터레이터 + `[first, last)`" 규악으로 커스텀 컨테이너도 STL 알고리즘에 그냥 꽂힌다 -> 코드 의존성 최소화 = 유지보수 비용 ↓
  - **내장 최적화**  
    `vector::reserve`, `list::splice` 처럼 STL 내부의 최적화 활용만 해도 손코딩 대비 퍼포먼스가 좋다
  - **C++20 `<ranges>` 파이프라인**  
    C++20 `views::filter | views::transform` 로 파이프라인을 이어 붙여도 비용은 인라인 최적화 수준 -> 깔끔한 선언형 코드 쓰고도 ‘0‑cost abstraction’ 유지
- **컨테이너 유형별 특징**
  - Sequence, Associative, Unordered, Container Adapter
- **대표 알고리즘 & Iterator 요구 조건**
  - 정렬`(sort, stable_sort, partial_sort)`·제거`(remove, remove_if)`·누적`(accumulate)` 계열 + input/forward/bidirectional/random‑access iterator
- **Iterator 무효화와 안전한 사용**
- **Best Practice**

---

## 2. STL 컨테이너 분류

| 범주 | 대표 예 | 특징 키워드 |
|------|---------|-------------|
| **Sequence** | `vector`, `deque`, `list`, `array` | 순서 보장, 인덱스/이터레이터 기반 |
| **Associative** | `set`, `map`, `multiset`, `multimap` | O(log n) 균형 트리 |
| **Unordered** | `unordered_set`, `unordered_map`, … | 해시 기반 *평균* O(1) |
| **Container Adapter** | `stack`, `queue`, `priority_queue` | 내부 컨테이너 래핑 |

> **Iterator Category** : input → output → forward → bidirectional → random‑access → contiguous (C++17)

---

## 3. 컨테이너 설계 포인트 & 최소 예제

### 3‑1 `vector`
```cpp
std::vector<int> v = {1, 2, 3};
v.reserve(8);        // 재할당 최소화
v.push_back(4);
````

### 3‑2 `deque`

```cpp
std::deque<int> d;
d.push_front(1);     // O(1)
d.push_back(2);      // O(1)
```

### 3‑3 `map` vs `unordered_map`

```cpp
std::map<std::string, int>           m;  // 정렬·범위 조회
std::unordered_map<std::string, int> um; // 평균 O(1) 조회
```

---

## 4. 대표 알고리즘 & 요구 Iterator

| 카테고리               | 알고리즘                                                 | 최소 Iterator       |
| ------------------ | ---------------------------------------------------- | ----------------- |
| Non‑modifying      | `for_each`, `count`, `find`                          | **Input**         |
| Modifying          | `copy`, `transform`, `remove`                        | **Forward**       |
| Sorting            | `sort`, `stable_sort`, `nth_element`, `partial_sort` | **Random‑access** |
| Remove‑erase idiom | `remove`, `remove_if` + `container.erase()`          | Forward           |
| Numeric            | `accumulate`, `reduce`                               | Input             |

```cpp
std::vector<int> v = {1,2,3};
std::ranges::for_each(v, [](int& x){ x *= 2; });
```

---

## 5. 시간 복잡도 치트 시트

```text
vector::push_back          Amortized O(1)
vector::insert(pos, n)     O(N)   (pos == end → O(n))
deque::push_front/back     O(1)
list::insert/erase         O(1)   (노드 위치 이미 알고 있을 때)
set/map::find              O(log n)
unordered_map::find        Avg O(1), Worst O(n)
sort (Introsort)           Avg O(n log n)
stable_sort (Merge)        O(n log n) + O(n) extra mem
remove + erase             O(n)
```

---

## 6. 흔한 실수 & Best Practice

| 실수                                | 대안 / 체크                                                      |
| --------------------------------- | ------------------------------------------------------------ |
| 반복 중 `erase`로 iterator 무효화        | `auto it = container.erase(it);` 반환값 사용                      |
| `std::remove_if` 후 `size()` 안 줄어듦 | **erase‑remove idiom** 필수                                    |
| 작은 데이터에 무조건 `vector` → `sort`     | 100 k 미만 랜덤 삽입/삭제면 `list`‑`splice` 가 유리                      |
| 해시 컨테이너에서 열쇠 큰 구조체 직접 사용          | `struct Key { …; bool operator==(...); };` + `std::hash` 특수화 |

---

## 7. 더 읽어볼 것

* cppreference: **[Containers](https://en.cppreference.com/w/cpp/container)**
* *Effective STL* – Scott Meyers
* *Ranges — the STL to the Next Level* (Conference slides)

---

```
```
