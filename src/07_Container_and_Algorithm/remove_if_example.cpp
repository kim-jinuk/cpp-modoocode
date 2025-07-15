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
    bool operator()(const int& a) { return (a % 2 == 1); }
};

bool is_odd2(const int& a) { return (a % 2 == 1); }

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

    std::cout << "벡터에서 홀수인 원소 제거 ----" << std::endl;
    // 함수 객체(is_odd)를 전달하는 방법.
    vec.erase(std::remove_if(vec.begin(), vec.end(), is_odd()), vec.end());

    // 실제 함수(is_odd2)를 전달하는 방법. 아래 템플릿에서 Pred가 함수 포인터 타입이 됨.
    // template <typename Iter, typename Pred>
    // remove_if(Iter first, Iter last, Pred pred)
    // vec.erase(std::remove_if(vec.begin(), vec.end(), is_odd2), vec.end());
    
    print(vec.begin(), vec.end());

    return 0;
}