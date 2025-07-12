#include <iostream>
#include <unordered_set>
#include <string>

template <typename K>
void print_unordered_set(const std::unordered_set<K>& us) {
    for (const auto& elem : us) {
        std::cout << elem << std::endl;
    }
}

template <typename K>
void is_exist(const std::unordered_set<K>& us, const K& k) {
    if (us.find(k) != us.end()) {
        std::cout << k << "가 존재!" << std::endl;
    } else {
        std::cout << k << "가 없다!" << std::endl;
    }
}

int main() {
    std::unordered_set<std::string> s;

    s.insert("hi");
    s.insert("my");
    s.insert("name");
    s.insert("is");
    s.insert("psi");
    s.insert("welcome");
    s.insert("to");
    s.insert("c++");

    print_unordered_set(s);
    std::cout << "----------------" << std::endl;

    is_exist(s, std::string("c++"));
    is_exist(s, std::string("c"));
    std::cout << "----------------" << std::endl;

    std::cout << "'hi' 를삭제" << std::endl;
    s.erase(s.find("hi"));
    is_exist(s, std::string("hi"));

    return 0;
}