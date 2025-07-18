#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <string>

template <typename Iter>
void print(Iter begin, Iter end) {
    while (begin != end) {
        std::cout << "[" << *begin << "] ";
        begin++;
    }
    std::cout << std::endl;
}

struct User {
    int age;
    std::string name;

    User(std::string name, int age) : age(age), name(name) {}

    bool operator<(const User& u) const { return age < u.age; }
};

std::ostream& operator<<(std::ostream& o, const User& u) {
    o << u.name << " , " << u.age;
    return o;
}

int main() {
    std::vector<User> vec;
    for (int i = 0; i < 100; ++i) {
        std::string name = "";
        name.push_back('a' + i / 26);
        name.push_back('a' + i % 26);
        vec.push_back(User(name, static_cast<int>(rand() % 10)));
    }

    std::vector<User> vec2 = vec;

    std::cout << "정렬 전 ----" << std::endl;
    print(vec.begin(), vec.end());

    std::sort(vec.begin(), vec.end());

    std::cout << "정렬 후 ----" << std::endl;
    print(vec.begin(), vec.end());

    std::cout << "stable_sort의 경우 ----" << std::endl;
    std::stable_sort(vec2.begin(), vec2.end());
    print(vec2.begin(), vec2.end());

    return 0;
}