#include <iostream>
#include <condition_variable>
#include <mutex>
#include <string>
#include <thread>

std::mutex m;
std::condition_variable cv;
std::string info;
bool done = false;

void worker() {
    {
        std::lock_guard<std::mutex> lk(m);
        info = "some data";
        done = true;
    }
    cv.notify_all();
}

int main() {
    std::thread t(worker);

    std::unique_lock<std::mutex> lk(m);
    cv.wait(lk, [] { return done; });
    lk.unlock();

    std::cout << "받은 데이터 : " << info << std::endl;

    t.join();

    return 0;
}