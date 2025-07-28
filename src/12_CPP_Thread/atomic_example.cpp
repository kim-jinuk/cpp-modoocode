#include <iostream>
#include <atomic>
#include <vector>
#include <thread>

void worker(std::atomic<int>& counter) {
    for (int i = 0; i < 10000; ++i) {
        counter++;
    }
}

int main() {
    std::atomic<int> counter(0);
    std::cout << "Is lock free ? : " << std::boolalpha << counter.is_lock_free() << std::endl;
    std::vector<std::thread> workers;

    for (int i = 0; i < 4; ++i) {
        workers.push_back(std::thread(worker, std::ref(counter)));
    }

    for (int i = 0; i < 4; ++i) {
        workers[i].join();
    }

    std::cout << "Counter 최종 값 : " << counter << std::endl;

    return 0;
}