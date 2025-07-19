#include <iostream>

class A {
    int data_;

public:
    A(int data) : data_(data) { std::cout << "일반생성자 호출!" << std::endl; }

    A(const A& a) : data_(a.data_) { std::cout << "복사생성자 호출!" << std::endl; }
};

int main() {
    A a(1);
    A b(a);

    A c(A(2));  // 컴파일러가 알아서 A(2) 자체를 c로 만들어 복사생성자를 생략해버린다.

    return 0;
}