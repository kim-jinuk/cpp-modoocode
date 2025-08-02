#include <iostream>

class A {
public:
    A() { std::cout << "A의 생성자 호출!" << std::endl; }
};

class B { 
public:
    B(A a) { std::cout << "B의 생성자 호출!" << std::endl; }
};

int main() {
    A a();      // 뭐가 출력될까?
    B b(A());   // 뭐가 출력될까?

    A c{};      

    return 0;
}