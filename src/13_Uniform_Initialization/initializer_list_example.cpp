#include <iostream>
#include <string>
#include <initializer_list>

class A {
public:
    A(int x, double y) { std::cout << "일반 생성자" << std::endl; }
    A(std::initializer_list<std::string> lst) { std::cout << "초기화자 생성자" << std::endl; }
};

int main() {
    A a(1, 3.5);
    A b{1, 3.5};
    A c{"abc", "def"};

    return 0;
}