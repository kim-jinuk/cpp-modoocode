#include <iostream>
#include <future>
#include <thread>

int do_work(int x) {
    std::this_thread::sleep_for(std::chrono::seconds(3));
    return x;
}

void do_work_parallel() {
    auto f1 = std::async([]() { do_work(3); });
    auto f2 = std::async([]() { do_work(3); });
    do_work(3);

    f1.get();
    f2.get();
}

void do_work_sequantial() {
    do_work(3);
    do_work(3);
    do_work(3);
}

int main() { do_work_parallel(); }