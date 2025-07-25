#include <iostream>
#include <functional>

void add(int x, int y) {
    std::cout << x << " + " << y << " = " << x + y << std::endl;
}

void substract(int x, int y) {
    std::cout << x << " - " << y << " = " << x - y << std::endl;
}

int main() {
    auto add_with_2 = std::bind(add, 2, std::placeholders::_1);
    add_with_2(3);
    add_with_2(3, 4);   // 두 번째 인자는 무시된다

    auto substract_with_2 = std::bind(substract, std::placeholders::_1, 2);
    auto negate = std::bind(substract, std::placeholders::_2, std::placeholders::_1);

    substract_with_2(3);
    negate(4, 2);

    return 0;
}