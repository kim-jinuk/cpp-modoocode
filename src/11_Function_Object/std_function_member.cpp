#include <iostream>
#include <functional>

class A {
    int c;

public:
    A(int c) : c(c) {}

    int some_func() {
        std::cout << "비상수 함수: " << ++c << std::endl;
        return c;
    }
    
    int some_const_func() const {
        std::cout << "상수 함수" << c << std::endl;
        return c;
    }

    static void st() {}
};

int main() {
    A a(5);

    std::function<int(A&)> f1 = &A::some_func;
    std::function<int(const A&)> f2 = &A::some_const_func;

    f1(a);
    f2(a);

    return 0;
}