#include <chrono>
#include <exception>
#include <future>
#include <iostream>
#include <thread>

void worker(std::promise<void>* p) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    p->set_value();
}

int main() {
    std::promise<void> p;
    std::future<void> data = p.get_future();

    std::thread t(worker, &p);

    while (true) {
        std::future_status status = data.wait_for(std::chrono::milliseconds(1));

        if (status == std::future_status::timeout) {
            std::cerr << ">";
        } else if (status == std::future_status::ready) {
            break;
        }
    }

    t.join();

    return 0;
}