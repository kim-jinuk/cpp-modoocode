#include <iostream>

class A {
public:
    A() { std::cout << "A의 생성자 호출!" << std::endl; }
};

int main() {
    A a{};      // 균일한 초기화 (Uniform Initialization)

    return 0;
}