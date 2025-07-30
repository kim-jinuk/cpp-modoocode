#include <exception>
#include <future>
#include <string>
#include <iostream>
#include <thread>

void worker(std::promise<std::string>* p) {
    try {
        throw std::runtime_error("Some Error!");
    } catch (...) {
        p->set_exception(std::current_exception());
    }
}

int main() {
    std::promise<std::string> p;
    std::future<std::string> data = p.get_future();

    std::thread t(worker, &p);

    data.wait();

    try {
        data.get();
    } catch (const std::exception& e) {
        std::cout << "예외 : " << e.what() << std::endl;
    }

    t.join();

    return 0;
}