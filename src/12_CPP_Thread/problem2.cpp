// 문제 2. problem 1에서 std::atomic_flag 의 test_and_set 함수를 이용해서 SpinLock 을 구현하라.

#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

class SpinLock {
    std::atomic_flag flag = ATOMIC_FLAG_INIT;

public:
    void lock() {
        while (flag.test_and_set(std::memory_order_acquire)) {
            std::this_thread::yield();  // busy waiting 회피
        }
    }

    void unlock() {
        flag.clear(std::memory_order_release);
    }
};

SpinLock spin;
int data = 0;

void worker1() {
    for (int i = 0; i < 10000; ++i) {
        spin.lock();        // 논리적으로 이후의 모든 연산이 lock 이후에 실행되게 하기 위해 std::memory_order_acquire 지정.
        ++data;
        spin.unlock();      // 논리적으로 이전의 모든 연산이 unlock 이전에 실행되게 하기 위해 std::memory_order_release 지정.
    }
}

int main() {
    std::vector<std::thread> vec;

    for (int i = 0; i < 5; ++i) {
        vec.push_back(std::thread(worker1));
    }

    for (int i = 0; i < 5; ++i) {
        vec[i].join();
    }

    std::cout << "data : " << data << std::endl;

    return 0;
}