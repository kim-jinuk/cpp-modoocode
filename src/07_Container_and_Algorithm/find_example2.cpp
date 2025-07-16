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

int main() {
    std::vector<int> vec;
    vec.push_back(5);
    vec.push_back(3);
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);

    auto current = vec.begin();
    while (true) {
        current = std::find(current, vec.end(), 3);
        if (current == vec.end()) break;
        std::cout << "3은 " << std::distance(vec.begin(), current) + 1 << "번 째 원소" << std::endl;
        current++;
    }

    return 0;
}