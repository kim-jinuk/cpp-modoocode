#include <iostream>
#include <unordered_set>
#include <string>

template <typename K>
void print_unordered_set(const std::unordered_set<K>& us) {
    for (const auto& elem : us) {
        std::cout << elem << std::endl;
    }
}

int main() {
    std::unordered_set<std::string> s;

    s.insert("hi");
    s.insert("my");
    s.insert("hi");
    s.insert("name");
    s.insert("is");
    s.insert("psi");
    s.insert("welcome");
    s.insert("to");
    s.insert("c++");

    print_unordered_set(s);

    return 0;
}