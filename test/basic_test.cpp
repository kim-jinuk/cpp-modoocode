#include <iostream>
#include <memory>

class A {
    int* data;

public:
    A() {
        data = new int[100];
        std::cout << "자원을 획득함!" << std::endl;
    }

    void some() { std::cout << "일반 포인터와 동일하게 사용 가능" << std::endl; }

    ~A() {
        std::cout << "자원을 해제함!" << std::endl;
        delete[] data;
    }
};

void do_something() {
    std::unique_ptr<A> pa(new A());
    std::cout << "pa : ";
    pa->some();

    // unique_ptr는 복사 생성자가 명시적으로 삭제되어 있음.
    // std::unique_ptr<A> pb = pa;     // Error : Attempting to reference a deleted function

    // 그러나 unique_ptr가 가지는 소유권 이전은 가능. (이동 생성자는 가능)
    std::unique_ptr<A> pb = std::move(pa);
    std::cout << "pb : ";
    pb->some();
}

int main() {
    do_something();
}