#include <iostream>
#include <map>
#include <string>

template <typename K, typename V>
void print_map(const std::map<K, V>& m) {
    for (const auto& kv : m) {
        std::cout << kv.first << " " << kv.second << std::endl;
    }
}

int main() {
    std::map<std::string, double> pitcher_list;

    pitcher_list.insert(std::make_pair("박세웅", 2.23));
    pitcher_list.insert(std::make_pair("박세웅", 2.93));
    pitcher_list["박세웅"] = 2.5;
    
    print_map(pitcher_list);

    return 0;
}