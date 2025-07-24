#include <iostream>
#include <vector>
#include <memory>

class A {
    int* data;

public:
    A(int i) {
        std::cout << "자원을 획득함!" << std::endl;
        data = new int[100];
        data[0] = i;
    }
    ~A() {
        std::cout << "자원을 해제함!" << std::endl;
        delete[] data;
    }

    void some() {  std::cout << "값: " << data[0] << std::endl; }
};

int main() {
    std::vector<std::unique_ptr<A>> vec;
    std::unique_ptr<A> pa(new A(1));

    vec.push_back(std::move(pa));
    vec.back()->some();

    vec.emplace_back(new A(2));
    vec.back()->some();

    return 0;
}