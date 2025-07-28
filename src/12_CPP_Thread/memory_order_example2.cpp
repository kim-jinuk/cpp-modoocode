#include <iostream>
#include <vector>
#include <atomic>
#include <thread>

using std::memory_order_relaxed;

void worker(std::atomic<int>* counter) {
    for (int i = 0; i < 10000; ++i) {
        // 다른 연산들 수행
        
        counter->fetch_add(1, memory_order_relaxed);
    }
}

int main() {
    std::vector<std::thread> workers;
    std::atomic<int> counter(0);

    for (int i = 0; i < 4; ++i) {
        workers.push_back(std::thread(worker, &counter));
    }

    for (int i = 0; i < 4; ++i) {
        workers[i].join();
    }

    std::cout << "Counter : " << counter << std::endl;

    return 0;
}