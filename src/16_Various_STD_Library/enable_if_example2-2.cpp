#include <iostream>
#include <type_traits>
#include <iterator> // iterator_traits

// C++11용 void_t 대체
template <typename...>
using void_t = void;

// 기본: iterator 아님
template <typename T, typename = void>
struct is_iterator : std::false_type {};

// 특수화 : iterator_traits<T>::iterator_category 가 있으면 iterator로 간주
template <typename T>
struct is_iterator<T, void_t<typename std::iterator_traits<T>::iterator_category>> : std::true_type {};

template <typename T>
class vector {
public:
    vector(size_t num, int elements) {
        std::cout << elements << "를" << num << "개 만들기 \n";
    }

    template <typename Iterator, typename = typename std::enable_if<is_iterator<Iterator>::value>::type>
    vector(Iterator start, Iterator end) {
        std::cout << "반복자를 이용한 생성자 호출 \n";
    }
};

int main() {
    vector<int> v(10, 3);

    return 0;
}