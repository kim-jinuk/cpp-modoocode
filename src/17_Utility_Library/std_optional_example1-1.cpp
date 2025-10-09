// C++ 17 이상 - <optional>
#include <iostream>
#include <map>
#include <string>

std::string GetValueFromMap(const std::map<int, std::string>& m, int key) {
    auto itr = m.find(key);
    if (itr != m.end()) {
        return itr->second;
    }
    return std::string();
}

int main() {
    std::map<int, std::string> data = {{1, "hi"}, {2, "hello"}, {3, "hiroo"}};

    std::cout << "맵에서 2에 대응되는 값은? " << GetValueFromMap(data, 2) << '\n';
    std::cout << "맵에서 4에 대응되는 값은? " << GetValueFromMap(data, 4) << '\n';

    return 0;
}