# 07. Container and Algorithm

## 1. 목차
- STL 컨테이너·알고리즘이 해결하는 문제
- 컨테이너 유형별 특징
- 대표 알고리즘 & iterator 요구 조건
- iterator invalidation과 안전한 사용
- Best Practice

---

## 2. 핵심 용어 & 분류
| 범주 | 대표 예 | 특징 키워드 |
|------|---------|-------------|
| **Sequence** | `vector`, `deque`, `list` | 순서 보장, index/iterator 기반 |
| **Associative** | `set`, `map`, `multiset` | O(log n) 균형 트리 |
| **Unordered** | `unordered_set`, `unordered_map` | 해시 기반 O(1) 평균 |
| **Container Adapter** | `stack`, `queue`, `priority_queue` | 내부 컨테이너 래핑 |

* **Iterator Category** : Input / Forward / Bidirectional / Random-access / Contiguous

---

## 3. 컨테이너 설계 포인트

### 3-1 `vector`
```cpp
std::vector<int> v = {1,2,3};
v.push_back(4);
```

### 3-2 `deque`
```cpp
std::deque<int> d;
d.push_front(1);
d.push_back(2);
```

### 3-3 `map` vs `unordered_map`
```cpp
std::map<std::string,int> m;
std::unordered_map<std::string,int> um;
```

---

## 4. 표준 알고리즘 분류
| 카테고리 | 알고리즘 | 요구 iterator |
|----------|----------|---------------|
| Non-modifying | `for_each`, `count` | Input |
| Modifying | `copy`, `transform` | Forward |
| Sorting | `sort`, `stable_sort` | Random-access |
| Numeric | `accumulate` | Input |

```cpp
std::vector<int> v = {1,2,3};
std::for_each(v.begin(), v.end(), [](int& x){ x*=2; });
```

---

## 5. 시간 복잡도 칠트 시트
```text
vector::push_back O(1)
set::find O(log n)
unordered_map::find Avg O(1)
```

---

## 6. 흔한 실수 & Best Practice
- Iterator 무효화 주의
- erase-remove idiom
- 컨테이너 선택 기준

---

## 7. 더 읽어볼 것
- cppreference: [Containers](https://en.cppreference.com/w/cpp/container)
- Effective STL
