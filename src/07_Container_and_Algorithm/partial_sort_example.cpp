#include <iostream>
#include <vector>
#include <algorithm>

template <typename Iter>
void print(Iter begin, Iter end) {
    while (begin != end) {
        std::cout << *begin << " ";
        begin++;
    }
    std::cout << std::endl;
}

template <typename T>
struct Compare {
    bool operator()(const T& a, const T& b) {
        return a > b;
    }
};

int main() {
    std::vector<int> vec;
    vec.push_back(5);
    vec.push_back(3);
    vec.push_back(1);
    vec.push_back(6);
    vec.push_back(4);
    vec.push_back(7);
    vec.push_back(2);

    std::cout << "정렬전----" << std::endl;
    print(vec.begin(), vec.end());

    std::partial_sort(vec.begin(), vec.begin() + 3, vec.end(), [](int a, int b){return a < b;});

    std::cout << "정렬후----" << std::endl;
    print(vec.begin(), vec.end());

    return 0;
}