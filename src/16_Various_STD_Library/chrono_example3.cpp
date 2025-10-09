// 현재 시간을 날짜로 출력하기
#include <iostream>
#include <ctime>
#include <chrono>
#include <iomanip>

int main() {
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::cout << "현재 시간은: " << std::put_time(std::localtime(&t), "%F %T %z") << '\n';

    return 0;
}