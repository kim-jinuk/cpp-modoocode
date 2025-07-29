// 문제 1. std::atomic 을 이용해서 lock(), unlock() 을 만들어 보아라.

#include <iostream>
#include <atomic>
#include <thread>
#include <vector>

class SpinLock {
    // 현재 락이 걸려있는 지 여부
    // locked == false : 락이 걸려있지 않다.
    //        == true  : 누군가 락을 이미 소유하고 있음.
    std::atomic<bool> locked = {false};

public:
    void lock() {
        bool expected = false;
        
        // compare_exchange_(weak or strong) 함수는 아래와 같이 생겼다.
        // bool compare_exchange_strong(T& expected, T desired, std::memory_order order = std::memory_order_seq_cst);
        // 여기서 atomic 객체의 값이 expected 와 같다면 desired 로 바꾸고 true 반환, 다르다면 expected 에 객체 값 넣고 false 반환.
        while (!locked.compare_exchange_weak(expected, true, std::memory_order_acquire)) {
            expected = false;
            std::this_thread::yield();      // 과도한 CPU 소모 방지
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