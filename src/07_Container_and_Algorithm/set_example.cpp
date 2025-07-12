#include <iostream>
#include <set>

template <typename T>
void print_set(const std::set<T>& s) {
    // 셋의 모든 원소 출력
    std::cout << "[";
    for (typename std::set<T>::iterator itr = s.cbegin(); itr != s.cend(); ++itr) {
        if (itr != s.cbegin()) std::cout << " ";
        std::cout << *itr;
    }
    std::cout << "]" << std::endl;
}

int main() {
    std::set<int> s;
    s.insert(10);
    s.insert(50);
    s.insert(20);
    s.insert(40);
    s.insert(30);

    std::cout << "순서대로 정렬되어서 나온다" << std::endl;
    print_set(s);

    std::cout << "20이 s의 원소인가요? :: ";
    auto itr = s.find(20);

    if (itr != s.end()) std::cout << "Yes" << std::endl;
    else std::cout << "No" << std::endl;

    std::cout << "25가 s의 원소인가요? :: ";
    itr = s.find(25);

    if (itr != s.end()) std::cout << "Yes" << std::endl;
    else std::cout << "No" << std::endl;

    return 0;
}