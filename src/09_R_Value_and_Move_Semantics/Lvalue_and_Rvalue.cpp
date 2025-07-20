#include <iostream>

// func1은 좌측값 레퍼런스를 반환하고, 좌측값 레퍼런스도 좌측값이다.
int& func1(int& a) { return a; }

// func2은 우측값을 반환한다.
int func2(int b) { return b; }

int main() {
    int a = 3;
    func1(a) = 4;
    std::cout << &func1(a) << std::endl;    // 좌측값은 주소값을 취할 수 있는 값.

    int b = 2;
    a = func2(b);
    // func2(b) = 5;   // 우측값이 표현식 좌측에 오고 있으므로, 에러 발생
    // std::cout << &func2(b) << std::endl;    // 우측값은 주소값을 취할 수 없는 값.

    return 0;
}