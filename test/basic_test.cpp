#include <iostream>

int foo() noexcept {}

int bar() noexcept { throw 1; }

int main() {
    // noexcept 함수 bar()에서 예외가 발생하면 예외가 제대로 처리되지 않고 프로그램이 종료됨.
    // 하지만 noexcept를 사용하는 이유는, 프로그래머가 컴파일러에게 어떤 함수가 절대로 예외를 발생시키지 않는다는 힌트를 줌으로써 추가적인 최적화를 수행하기 위함이다.
    // 대표적인 예로, C++11 이후로 소멸자들은 기본적으로 noexcept 이다.
    /*
    try {
        bar();
    } catch (int x) {
        std::cout << "Error : " << x << std::endl;
    }
    */

    return 0;
}