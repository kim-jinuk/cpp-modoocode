#include <iostream>
\
template <typename T>
struct is_void {
    // static constexpr이 붙는 이유에 대해 설명할 수 있어야 된다.
    // 먼저, 외부에서 value에 접근할 때 클래스 이름(is_void<T>::)으로 직접 접근하려면 해당 멤버가 정적(static)이어야 한다.
    // 즉, 객체가 생성되지 않았는데 해당 멤버에 접근하려면 해당 멤버가 정적이어야 한다.
    // 비정적(non-static) 멤버를 쓰려면 인스턴스가 필요하다.
    // 다음으로, constexpr을 붙이면 value가 컴파일 타임 상수 표현식(identifier expression)이 된다.
    // -> if constexpr (is_void<T>::value) 같은 컴파일 타임 분기가 가능하고, 템플릿 인자/배열 크기/부분 특수화 조건 등 정수 상수식이 필요한 곳에서도 바로 사용이 가능함.
    // constexpr 없이 static bool value 만으로도 접근은 가능하지만, 쓸 수 있는 곳이 줄고(런타임 변수), 최적화나 SFINAE 활용성이 떨어진다.
    static constexpr bool value = false;
};

template <>
struct is_void<void> {
    static constexpr bool value = true;
};

template <typename T>
void tell_type() {
    if (is_void<T>::value) {
        std::cout << "T는 void! \n";
    } else {
        std::cout << "T는 void가 아니다! \n";
    }
}

int main() {
    tell_type<int>();
    tell_type<void>();

    return 0;
}