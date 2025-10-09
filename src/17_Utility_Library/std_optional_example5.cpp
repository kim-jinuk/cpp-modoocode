// 레퍼런스를 가지는 std::optional (std::reference_wrapper 객체 사용)
#include <utility>
#include <optional>
#include <iostream>
#include <functional>

class A {
public:
    int data;
    A() { std::cout << "디폴트 생성" << std::endl; }
    A(const A& a) { std::cout << "복사 생성" << std::endl; }
};

int main() {
    A a;
    a.data = 5;
    // std::optional<A&> maybe_a = a;       // error!

    std::optional<std::reference_wrapper<A>> maybe_a = std::ref(a);
    maybe_a->get().data = 3;

    std::cout << "a.data : " << a.data << '\n';

    return 0;
}