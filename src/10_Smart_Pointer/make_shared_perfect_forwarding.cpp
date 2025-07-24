#include <iostream>
#include <memory>
#include <utility>

struct A {
    A(int&  x)      { std::cout << "A(int& )  호출\n"; }   // lvalue
    A(int&& x)      { std::cout << "A(int&&)  호출\n"; }   // rvalue
};

int main() {
    int n = 10;

    auto p1 = std::make_shared<A>(n);      // lvalue 전달 → A(int&)
    auto p2 = std::make_shared<A>(20);     // rvalue 전달 → A(int&&)

    // make_shared 내부 구현(단순화):
    // template<class T, class... Args>
    // std::shared_ptr<T> make_shared(Args&&... args) {
    //     return std::shared_ptr<T>(new T(std::forward<Args>(args)...));
    // }
}
