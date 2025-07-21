#include <iostream>
#include <vector>

template <typename T>
void wrapper(T& u) {
    std::cout << "T&로 추론됨" << std::endl;
    g(u);
}

template <typename T>
void wrapper(const T& u) {
    std::cout << "const T&로 추론됨" << std::endl;
    g(u);
}

class A {};

void g(A& a) { std::cout << "좌측값 레퍼런스 호출" << std::endl; }
void g(const A& a) { std::cout << "좌측값 상수 레퍼런스 호출" << std::endl; }
void g(A&& a) { std::cout << "우측값 레퍼런스 호출" << std::endl; }

int main() {
    A a;
    const A ca;

    std::cout << "원본 ---------------" << std::endl;
    g(a);
    g(ca);
    g(A());

    std::cout << "Wrapper ------------" << std::endl;
    wrapper(a);
    wrapper(ca);
    wrapper(A());

    return 0;
}