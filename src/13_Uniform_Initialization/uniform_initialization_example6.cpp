#include <initializer_list>
#include <string>
#include <iostream>

class A {
public:
    A(int x, double y) { std::cout << "일반 생성자 호출!" << std::endl; }
    A(std::initializer_list<std::string> lst) {
        std::cout << "초기화자 사용 생성자!" << std::endl;
    }
};

int main() {
    A a(3, 1.5);
    A b{3, 1.5};
    A c{"abc", "def"};

    return 0;
}