#include <iostream>
#include <type_traits>

class A {};

template <typename T>
void only_integer(const T& t) {
    // static_assert 는 키워드이다. 함수가 아니다.
    static_assert(std::is_integral<T>::value);
    std::cout << "T is an integer \n";
}

int main() {
    int n = 3;
    only_integer(n);        // ok

    A a;
    // A a()                // bad, 이것은 C++에서 함수 선언으로 해석된다.
    //only_integer(a);      // bad, static_assert로 인해 컴파일 에러 발생함.

    return 0;
}