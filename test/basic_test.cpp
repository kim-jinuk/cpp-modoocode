#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

void worker(int& result, std::mutex& m) {
    for (int i = 0; i < 10000; ++i) {
        std::lock_guard<std::mutex> lock(m);    // lock 생성 시에 m.lock() 수행된다
        result += 1;
    }
}

int main() {
    int counter = 0;

    std::vector<std::thread> workers;
    std::mutex m;

    for (int i = 0; i < 4; ++i) {
        workers.push_back(std::thread(worker, std::ref(counter), std::ref(m)));
    }

    for (int i = 0; i < 4; ++i) {
        workers[i].join();
    }

    std::cout << "최종 Counter 값 : " << counter << std::endl;

    return 0;
}