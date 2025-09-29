#include <iostream>

template <int N>
struct Factorial {
    static const int value = N * Factorial<N-1>::value;
};

template <>
struct Factorial<0> {
    static const int value = 1;
};

template <int N>
struct A {
    int operator()() { return N; }
};

int main() {
    A<Factorial<10>::value> a;
    std::cout << a() << std::endl;

    return 0;
}