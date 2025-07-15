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

struct is_odd {
    int count;

    is_odd() : count(0) {}

    bool operator()(const int& i) {
        if (count >= 2) return false;
        if (i % 2 == 1) {
            count++;
            return true;
        }
        return false;
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
    // 잘못된 사용!! std::remove_if 내부 구현 상 함수 객체 is_odd()가 여러 번 복사되어서 사용될 수 있기 떄문에
    // std::remove_if에 전달되는 함수 객체 안에 멤버 변수를 넣는 것은 원칙상 안 된다.
    // 즉, 함수 객체에는 절대로 특정 상태를 저장해서 이에 따라 결과가 달라지는 루틴을 짜면 안 된다.
    vec.erase(std::remove_if(vec.begin(), vec.end(), is_odd()), vec.end());
    print(vec.begin(), vec.end());

    return 0;
}