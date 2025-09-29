#include <iostream>
#include <initializer_list>

class A {
public:
    A(int x, double y) { std::cout << "A의 일반 생성자 호출!" << std::endl; }
    A(std::initializer_list<int> lst) {
        for (auto itr = lst.begin(); itr != lst.end(); ++itr) {
            std::cout << *itr << std::endl;
        }
    }
};

int main() {
    A a = {1,2,3,4,5};

    return 0;
}