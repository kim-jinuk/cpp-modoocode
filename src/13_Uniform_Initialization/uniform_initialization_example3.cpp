#include <iostream>

class A {
public:
    A(std::initializer_list<int> l) {
        for (auto itr = l.begin(); itr != l.end(); ++itr) {
            std::cout << *itr << std::endl;
        }
    }
};

int main() {
    A a = {1, 2, 3, 4, 5};  // ()를 사용해서 생성자를 호출한다면 initializer_list 가 생성되지 않는다!

    return 0;
}