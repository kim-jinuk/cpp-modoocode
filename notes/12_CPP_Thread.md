# 12. C++ Thread

## 1. 목차
- C++ 표준 쓰레드 std::thread 기본 구조
- Thread Join vs Detach
- Race Condition과 Mutex
- std::lock_guard와 std::unique_lock
- Condition Variable
- Best Practice

---

## 2. 핵심 용어 & 분류
| 개념 | 정의 | 비고 |
|------|------|------|
| **std::thread** | 쓰레드 객체 | <thread> |
| **Join / Detach** | 쓰레드 동기화 방법 | Join은 blocking |
| **Race Condition** | 동시 접근 시 데이터 충돌 | |
| **Mutex** | 상호 배제 | std::mutex |
| **Lock Guard** | lock/unlock 자동 관리 | RAII |
| **Condition Variable** | 쓰레드간 조건 기반 통신 | notify/wait |

---

## 3. 쓰레드 설계 포인트

### 3-1 std::thread 기본 사용법
```cpp
#include <thread>
void task() { /* ... */ }

int main() {
  std::thread t(task);
  t.join();
}
```

### 3-2 Join vs Detach
```cpp
t.join();   // main이 t 끝날 때까지 대기
t.detach(); // 독립 실행 → main 끝나도 계속
```

### 3-3 Mutex & Lock Guard
```cpp
#include <mutex>
std::mutex mtx;

void safe() {
  std::lock_guard<std::mutex> lock(mtx);
  // 안전 접근
}
```

### 3-4 Condition Variable
```cpp
#include <condition_variable>
std::condition_variable cv;
std::mutex mtx;
bool ready = false;

void producer() {
  {
    std::lock_guard<std::mutex> lock(mtx);
    ready = true;
  }
  cv.notify_one();
}

void consumer() {
  std::unique_lock<std::mutex> lock(mtx);
  cv.wait(lock, []{ return ready; });
}
```

---

## 4. 대표 예시: 패턴 & Idiom
| 패턴 | 핵심 아이디어 | 사례 |
|------|----------------|------|
| **RAII Lock** | lock/unlock 자동 | lock_guard |
| **Producer-Consumer** | Condition Variable | 큐 처리 |
| **Atomic** | 경량 동기화 | std::atomic |

---

## 5. 비용 / 관리 포인트
```text
Thread 생성 비용 높음 → 풀 권장
Join 누락 시 terminate()
Mutex 과다 사용 시 데드락 위험
```

---

## 6. 흔한 실수 & Best Practice
- join/detach 반드시 선택
- 락은 RAII로 관리
- 불필요한 공유 데이터 피하기
- Condition Variable wait은 predicate 사용

---

## 7. 더 읽어볼 것
- cppreference: [std::thread](https://en.cppreference.com/w/cpp/thread/thread)
- Effective Modern C++, Item 40~42
- Herb Sutter, Prefer Lock Guards
