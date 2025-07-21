#include <iostream>

// forwarding reference
template <typename T>
void wrapper(T&& u) {
    g(std::forward<T>(u));
}

class A {};

void g(A& a) { std::cout << "좌측값 레퍼런스 호출" << std::endl; }
void g(const A& a) { std::cout << "좌측값 상수 레퍼런스 호출" << std::endl;}
void g(A&& a) { std::cout << "우측값 레퍼런스 호출" << std::endl; }

int main() {
    A a;
    const A ca;

    std::cout << "원본 ---------------" << std::endl;
    g(a);
    g(ca);
    g(A());

    std::cout << "Wrapper ------------" << std::endl;
    wrapper(a);     // T& == A& -> (A&)& == A& -> T = A&
    wrapper(ca);    // T& == const A& -> (const A&)& == const A& -> T = const A&
    wrapper(A());   // T&& == A&& -> T = A

    return 0;
}