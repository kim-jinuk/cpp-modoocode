#include <iostream>

class A {
public:
    A(int x) { std::cout << "A의 생성자 호출!" << std::endl; }
};

int main() {
    A a(3.5);   // Narrow-conversion 가능!
    A b{3.5};   // Narrow-conversion 불가능!

    return 0;
}