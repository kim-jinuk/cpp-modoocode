#include <iostream>

class A {
public:
    A(int x) { std::cout << "A의 생성자 호출!" << std::endl; }
};

int main() {
    // *** Narrowing 변환이란 데이터 손실이 있는 변환을 의미한다! ***
    A a(3.5);   // 암시적 변환 Narrow-conversion 가능! 
    // A b{3.5};   // 암시적 변환 Narrow-conversion 불가능!

    return 0;
}