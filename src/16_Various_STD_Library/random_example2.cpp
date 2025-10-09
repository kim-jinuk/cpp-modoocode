// 정규 분포 난수 생성 (std::normal_distribution 함수 사용)
#include <iostream>
#include <map>
#include <random>
#include <iomanip>

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> dist(/* 평균 */ 0, /* 표준 편차 */ 1);

    std::map<int, int> hist{};
    for (int i = 0; i < 10000; ++i) {
        ++hist[std::round(dist(gen))];
    }

    for (auto p : hist) {
        std::cout << std::setw(2) << p.first << ' ' << std::string(p.second / 100, '*') << " " << p.second << '\n'; 
    }

    return 0;
}