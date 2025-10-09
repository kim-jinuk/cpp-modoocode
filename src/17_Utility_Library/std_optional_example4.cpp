// std::optional<T> 가 "없음" 일 때, 아예 T를 만들지 않기 때문에 T의 디폴트 생성자가 필요 없다.
// std::pair<bool, T>는 bool이 false여도 T를 항상 만든다.
// 이것이 std::optional<T>와 std::pair<T, bool>의 가장 큰 차이다. 
#include <iostream>
#include <utility>
#include <optional>

class A {
public:
    A() { std::cout << "디폴트 생성" << std::endl; }
    A(const A& a) { std::cout << "복사 생성" << std::endl; }
};

int main() {
    A a;

    std::cout << "Optional 객체 만듦 ---- \n"; 
    std::optional<A> maybe_a;

    std::cout << "maybe_a는 A 객체를 포함하고 있지 않기 때문에 디폴트 생성할 필요가 없다. \n";
    maybe_a = a;

    return 0;
}