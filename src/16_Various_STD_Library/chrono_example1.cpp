#include <iostream>
#include <iomanip>
#include <vector>
#include <random>
#include <chrono>

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 1000);

    for (int i = 1; i <= 1000000; i *= 10) {
        std::vector<int> random_numbers;
        random_numbers.reserve(i);

        std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();
        for (int j = 0; j < i; ++j) {
            random_numbers.push_back(dis(gen));
        }
        std::chrono::time_point<std::chrono::high_resolution_clock> end = std::chrono::high_resolution_clock::now();

        auto diff = end - start;
        std::cout << std::setw(7) << i << "개 난수 생성 시 틱 횟수 : " << diff.count() << '\n';
    }

    return 0;
}