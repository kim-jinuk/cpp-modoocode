#include <iostream>

template <typename T>
class vector {
public:
    vector(size_t num, const T& e) {
        std::cout << e << "를" << num << "개 만들기" << std::endl;
    }

    template <typename Iterator>
    vector(Iterator start, Iterator end) {
        std::cout << "반복자를 이용한 생성자 호출" << std::endl;
    }
};

int main() {
    vector<int> v(10, 3);

    return 0;
}