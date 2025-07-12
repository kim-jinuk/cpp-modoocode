#include <iostream>
#include <map>
#include <string>

template <typename K, typename V>
void print_map(const std::multimap<K, V>& m) {
    for (const auto& kv : m) {
        std::cout << kv.first << " " << kv.second << std::endl;
    }
}

int main() {
    std::multimap<int, std::string> m;

    m.insert(std::make_pair(1, "hello"));
    m.insert(std::make_pair(2, "hi"));
    m.insert(std::make_pair(1, "ahihi"));
    m.insert(std::make_pair(2, "bye"));
    m.insert(std::make_pair(1, "baba"));

    print_map(m);

    std::cout << "--------------" << std::endl;
    std::cout << m.find(1)->second << std::endl;

    auto range = m.equal_range(1);
    for (auto itr = range.first; itr != range.second; ++itr) {
        std::cout << itr->first << " : " << itr->second << std::endl;
    }

    return 0;
}