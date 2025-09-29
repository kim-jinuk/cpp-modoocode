#include <iostream>
#include <type_traits>

template <typename T>
void show_value(T t) {
    if constexpr (std::is_pointer_v<T>) {
        std::cout << "포인터이다 : " << *t << std::endl;
    } else {
        std::cout << "포인터가 아니다 : " << t << std::endl;
    }
}

int main() {
    int x = 3;
    show_value(x);

    int* p = &x;
    show_value(p);

    return 0;
}