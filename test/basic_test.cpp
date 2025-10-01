#include <iostream>

template <typename T>
struct is_void {
    static constexpr bool value = false;
};

template <>
struct is_void<void> {
    static constexpr bool value = true;
};

template <typename T>
void tell_type() {
    if (is_void<T>::value) {
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