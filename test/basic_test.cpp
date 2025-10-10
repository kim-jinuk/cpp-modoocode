// variant가 아무 것도 들고 있지 않은 상태 (std::monostate 타입 사용)
#include <iostream>
#include <variant>

class A {
public:
    A(int n) {}
};

class B {
public:
    B(int n) {}
};

class C {};

int main() {
    // std::variant<A, B> v;   // 해당 variant 객체 v에 값을 주지 않을 때, 첫 번째 타입인 A의 디폴트 생성자가 없기 때문에 에러가 난다!
    // std::variant<A, C> v;   // std::variant<A, B> 에서 에러가 나는 것과 같은 이유로 에러가 남!
    std::variant<C, A> v;       // 그러나, 첫 번 째 타입이 디폴트 생성자가 있으면 괜찮음.
    std::variant<std::monostate, A, B> v;       // 이를 고려하지 않으려면 std::monostate를 사용한다.

    return 0;
}