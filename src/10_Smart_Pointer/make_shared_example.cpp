#include <iostream>
#include <memory>

class A : public std::enable_shared_from_this<A> {
    int* data;

public:
    A() {
        std::cout << "자원을 획득함!" << std::endl;
        data = new int[100];
    }
    ~A() {
        std::cout << "자원을 해제함!" << std::endl;
        delete[] data;
    }

    std::shared_ptr<A> get_shared_ptr() { return shared_from_this(); }
};

int main() {
    std::shared_ptr<A> pa1 = std::make_shared<A>();
    std::shared_ptr<A> pa2 = pa1->get_shared_ptr();

    std::cout << pa1.use_count() << std::endl;
    std::cout << pa2.use_count() << std::endl;

    return 0;
}