#include <iostream>
#include <vector>
#include <algorithm>

template <typename Iter>
void print(Iter begin, Iter end) {
    while (begin != end) {
        std::cout << "[" << *begin << "] ";
        begin++;
    }
    std::cout << std::endl;
}

// 클래스의 멤버 함수 내에서 람다를 사용할 때 멤버 변수들을 참조하려면, 아래처럼 this를 사용한다.
class SomeClass {
    std::vector<int> vec;
    int num_erased;

public:
    SomeClass() {
        vec.push_back(5);
        vec.push_back(3);
        vec.push_back(1);
        vec.push_back(2);
        vec.push_back(3);
        vec.push_back(4);

        num_erased = 0;
        vec.erase(std::remove_if(vec.begin(), vec.end(), [this](int i) {
            if (this->num_erased >= 2) return false;
            if (i % 2 == 1) {
                this->num_erased++;
                return true;
            }
            return false;
        }),
        vec.end());
    }
};

int main() {
    std::vector<int> vec;
    vec.push_back(5);
    vec.push_back(3);
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);

    std::cout << "처음 vec 상태 ----" << std::endl;
    print(vec.begin(), vec.end());

    std::cout << "벡터에서 홀수인 원소 2개만 제거 ----" << std::endl;
    int num_erased = 0;
    vec.erase(std::remove_if(vec.begin(), vec.end(), [&num_erased](int i){
        if (num_erased >= 2) return false;
        if (i % 2 == 1) {
            num_erased++;
            return true;
        }
        return false;
    }), vec.end());
    print(vec.begin(), vec.end());

    return 0;
}