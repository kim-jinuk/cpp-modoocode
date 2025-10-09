// C++ 17 이상 - <optional>
#include <iostream>
#include <map>
#include <string>
#include <utility>

std::pair<std::string, bool> GetValueFromMap(const std::map<int, std::string>& m, int key) {
    auto itr = m.find(key);
    if (itr != m.end()) {
        return std::make_pair(itr->second, true);
    }
    return std::make_pair(std::string(), false);
}

int main() {
    std::map<int, std::string> data = {{1, "hi"}, {2, "hello"}, {3, "hiroo"}};

    std::cout << "맵에서 2에 대응되는 값은? " << GetValueFromMap(data, 2).first << '\n';
    std::cout << "맵에 4는 존재하나요? " << GetValueFromMap(data, 4).second << '\n';

    return 0;
}