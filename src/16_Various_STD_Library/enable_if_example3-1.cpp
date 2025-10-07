#include <iostream>
#include <type_traits>

template <typename T, typename = decltype(std::declval<T>().func())>
void test(const T& t) {
    std::cout << "t.func() : " << t.func() << std::endl;
}

struct A {
    int func() const { return 1; }
};

struct B {};

int main() {
    test(A{});
    //test(B{});  // error!

    return 0;
}