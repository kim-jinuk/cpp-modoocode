#include <iostream>
#include <vector>
#include <thread>

using std::vector;
using std::thread;

void worker(int& counter) {
    for (int i = 0; i < 10000; ++i) {
        counter += 1;
    }
}

int main() {
    int counter = 0;

    vector<thread> workers;
    for (int i = 0; i < 4; ++i) {
        // 레퍼런스로 전달하려면 ref함수로 감싸야 한다. (지난 강좌의 bind 함수 참조)
        // counter를 여러 쓰레드가 접근해서 수정하기 때문에 race condition이 발생한다.
        workers.push_back(thread(worker, std::ref(counter)));
    }

    for (int i = 0; i < 4; ++i) {
        workers[i].join();
    }

    std::cout << "Counter 최종 값 : " << counter << std::endl;

    return 0;
}