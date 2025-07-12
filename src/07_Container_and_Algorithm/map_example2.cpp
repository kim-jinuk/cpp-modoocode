#include <iostream>
#include <map>
#include <string>

template <typename K, typename V>
void print_map(std::map<K, V>& m) {
    for (const auto& kv : m) {
        std::cout << kv.first << " " << kv.second << std::endl;
    }
}

template <typename K, typename V>
void search_and_print(std::map<K, V>& m, K k) {
    if (m.find(k) != m.end()) { std::cout << k << "--->" << m[k] << std::endl; }
    else { std::cout << "No key in map"; }
}

int main() {
    std::map<std::string, double> pitcher_list;
    pitcher_list["오승환"] = 3.58;
    print_map(pitcher_list);
    std::cout << "-----------------" << std::endl;
    search_and_print(pitcher_list, std::string("오승환"));
    search_and_print(pitcher_list, std::string("류현진"));

    return 0;
}