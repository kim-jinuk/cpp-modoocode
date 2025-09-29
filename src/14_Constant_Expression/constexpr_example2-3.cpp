#include <iostream>

constexpr int Factorial(int n) {
    int total = 1;
    for (int i = 1; i <= n; ++i) {
        total *= i;
    }

    return total;
}

int main() {
    int num;
    std::cin >> num;
    std::cout << Factorial(num) << std::endl;

    return 0;
}