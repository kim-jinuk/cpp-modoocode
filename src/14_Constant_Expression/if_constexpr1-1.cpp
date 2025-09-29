#include <iostream>

template <typename T>
void show_value(T t) {
    std::cout << "포인터가 아니다 : " << t << std::endl;
}

template <typename T>
void show_value(T* t) {
    std::cout << "포인터다 : " << *t << std::endl;
}

int main() {
    int x = 3;
    show_value(x);

    int* p = &x;
    show_value(p);

    return 0;
}