#include <iostream>
#include <utility>

template <typename T>
decltype(std::declval<T>().f()) call_f_and_return(T& t) {
    return t.f();
}

struct A {
    int f() { return 0; }
};

struct B {
    B(int x) {}
    int f() { return 0; }
};

int main() {
    A a;
    B b(1);
    // B c = std::declval<B>();    // Bad

    call_f_and_return(a);   // ok
    call_f_and_return(b);   // ok

    return 0;
}