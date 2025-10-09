// C의 srand, rand 대신 C++의 random 라이브러리를 사용하여 난수 생성하기
// -- C의 srand, rand 를 사용하지 말아야 되는 이유 3가지 --
// 1. 현재 시간 초를 기준으로 시드를 생성할 경우, 시드 값이 너무 천천히 변한다.
// 2. 0부터 99까지 균등하게 난수를 생성하지 않는다.
// 3. 선형 합동 생성(Linear congruential generator) 알고리즘을 사용하기 때문에 품질이 좋은 난수를 생성할 수 없기에 일부 시뮬레이션에 사용하기 적합하지 않다.
#include <iostream>
#include <random>

int main() {
    // 시드 값을 얻기 위한 random_device 생성
    std::random_device rd;
    // random_device 객체를 통해 난수 생성 엔진을 초기화 한다.
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 99);

    for (int i = 0; i < 5; ++i) {
        std::cout << "난수 : " << dis(gen) << '\n';
    }

    return 0;
}