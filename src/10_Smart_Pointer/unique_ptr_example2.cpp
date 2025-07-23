#include <iostream>
#include <memory>

class A {
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

    void do_sth(int a) {
        std::cout << "무언가를 한다!" << std::endl;
        data[0] = a;
    }
};

// 올바르지 않은 전달 방식
// ptr이 레퍼런스이지만 적어도 do_something 함수 내부에서는 ptr도 객체 A()를 소유하게 된다 -> unique_ptr는 객체에 대해 유일한 소유권을 가진다는 원칙을 위배함!
// void do_something(std::unique_ptr<A>& ptr) { ptr->do_sth(3); }
void do_something(A* ptr) { ptr->do_sth(3); }

int main() {
    std::unique_ptr<A> pa(new A());
    // do_something(pa);
    do_something(pa.get());     // get() 함수는 실제 객체의 주소값을 리턴해준다
}