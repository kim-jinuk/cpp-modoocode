#include <iostream>

class A {
public:
    A(int x, double y) { std::cout << "A의 생성자 호출!" << std::endl; }
};

A func() { 
    return {1, 2.3};    // A(1, 2.3) 과 동일
}

int main() {
    func();

    return 0;
}