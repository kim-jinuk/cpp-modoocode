#include <iostream>
#include <vector>
#include <map>
#include <string>

template <typename T>
void print_vec(const std::vector<T>& vec) {
    std::cout << "[";
    for (const auto& v : vec) {
        std::cout << v << " ";
    }
    std::cout << "]";
}

template <typename K, typename V>
void print_map(const std::map<K, V>& m) {
    for (const auto& kv : m) {
        std::cout << kv.first << " : " << kv.second << std::endl;
    }
}

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    print_vec(vec);

    std::cout << "-----------------------" << std::endl;

    std::map<std::string, int> m = {{"abc", 1}, {"hi", 3}, {"hello", 5}, {"c++", 2}, {"java", 6}};
    print_map(m);

    return 0;
}