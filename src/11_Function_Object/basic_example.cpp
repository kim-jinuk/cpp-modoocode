#include <iostream>

struct S {
    void operator()(int a, int b) { std::cout << "S : a + b = " << a + b << std::endl; }
};

int main() {
    S some_obj;
    auto f = [](int a, int b) { std::cout << "f : a + b = " << a + b << std::endl; };
    
    some_obj(3, 5);
    f(3, 5);

    return 0;
}