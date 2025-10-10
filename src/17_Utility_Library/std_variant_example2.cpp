// variant가 아무 것도 들고 있지 않은 상태 (std::monostate 타입 사용)
#include <iostream>
#include <variant>

class A {
public:
    A(int n) {}
};

class B {
public:
    B(int n) {}
};

int main() {
    std::variant<A, B> v;

    return 0;
}