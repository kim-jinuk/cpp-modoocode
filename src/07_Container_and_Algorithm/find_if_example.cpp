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
        current = std::find_if(current, vec.end(), [](int i){ return i % 3 == 2; });
        if (current == vec.end()) break;
        std::cout << "3으로 나눈 나머지가 2인 원소는 : " << *current << std::endl;
        current++;
    }

    return 0;
}