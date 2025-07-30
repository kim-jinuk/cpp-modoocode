#include <future>
#include <iostream>
#include <thread>
#include <string>
#include <chrono>

void runner(std::shared_future<void>* start) {
    start->get();
    std::cout << "출발!" << std::endl;
}

int main() {
    std::promise<void> p;
    std::shared_future<void> start = p.get_future();

    std::thread t1(runner, &start);
    std::thread t2(runner, &start);
    std::thread t3(runner, &start);
    std::thread t4(runner, &start);

    std::cout << "준비" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    std::cout << "땅" << std::endl;

    p.set_value();

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    return 0;
}