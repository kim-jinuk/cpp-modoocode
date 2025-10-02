#include <iostream>
#include <type_traits>

namespace detail {
template <typename T>
char test(int T::*);

struct two {
    char c[2];
};

template <typename T>
two test(...);
}   // namespace detail

template <typename T>
struct is_class : std::integral_constant<bool, sizeof(detail::test<T>(0)) == 1 && !std::is_union<T>::value> {};

template <typename T>
void only_class(const T& t) {
    static_assert(is_class<T>::value);
    std::cout << "T is an class \n";
}

class A {
public:
    int n;

    A(int n) : n(n) {}
};

int main() {
    int A::*p_n = &A::n;

    A a(3);
    std::cout << "a.n : " << a.n << std::endl;
    std::cout << "a.*p_n : " << a.*p_n << std::endl;
    
    only_class(a);

    return 0;
}