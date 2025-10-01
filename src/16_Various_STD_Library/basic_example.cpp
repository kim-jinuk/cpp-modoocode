#include <iostream>
#include <type_traits>

template <typename T>
void tell_type() {
    if (std::is_void<T>::value) {
        std::cout << "T는 void! \n";
    } else {
        std::cout << "T는 void가 아니다! \n";
    }
}

int main() {
    tell_type<int>();
    tell_type<void>();

    return 0;
}