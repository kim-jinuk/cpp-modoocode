// C++ 17 이상 - <variant>
#include <iostream>
#include <memory>
#include <variant>

class A {
public:
    void a() { std::cout << "I am A \n"; }
};

class B {
public:
    void b() { std::cout << "I am B \n"; }
};

std::variant<A, B> GetDataFromDB(bool is_a) {
    if (is_a) return A();
    return B();
}

int main() {
    auto v = GetDataFromDB(true);

    std::cout << v.index() << '\n';
    std::get<A>(v).a();

    return 0;
}