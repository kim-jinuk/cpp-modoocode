#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <string>

template <typename Iter>
void print(Iter begin, Iter end) {
    while (begin != end) {
        std::cout << *begin << " ";
        begin++;
    }
    std::cout << std::endl;
}

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

    std::cout << "std::remove 직후 상태 ----" << std::endl;
    auto itr = std::remove(vec.begin(), vec.end(), 3);
    print(vec.begin(), vec.end());

    std::cout << "벡터에서 값이 3인 원소 제거 ----" << std::endl;
    vec.erase(itr, vec.end());
    print(vec.begin(), vec.end());

    return 0;
}