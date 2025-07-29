// std::atomic 을 이용해서 lock(), unlock() 을 만들어 보아라.
// 참고로 compare_exchange_strong 함수를 사용하는 것이 도움이 된다.
// bool compare_exchange_strong(T& expected, T desired, std::memory_order order = std::memory_order_seq_cst);

#include <iostream>
#include <atomic>
#include <thread>
#include <vector>

class SpinLock {
    // 현재 락이 걸려있는 지 여부
    // locked == false : 락이 걸려있지 않다
    //        == true  : 누군가 락을 이미 소유하고 있음
    std::atomic<bool> locked = {false};

public:
    void lock() {
        bool expected = false;
        while (!locked.compare_exchange_weak(expected, true, std::memory_order_acquire)) {
            expected = false;
            std::this_thread::yield();
        }
    }

    void unlock() {
        locked.store(false, std::memory_order_release);
    }
};

SpinLock spin;
int data = 0;

void worker1() {
    for (int i = 0; i < 10000; ++i) {
        spin.lock();
        ++data;
        spin.unlock();
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