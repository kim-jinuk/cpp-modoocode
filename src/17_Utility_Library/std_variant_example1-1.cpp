// C++ 17 이상 - <variant>
#include <iostream>
#include <memory>

class Data {};
class A : public Data {};
class B : public Data {};

std::unique_ptr<Data> GetDataFromDB(bool is_a) {
    if (is_a) return std::make_unique<A>();
    return std::make_unique<B>();
}

int main() {
    auto a = GetDataFromDB(true);

    return 0;
}