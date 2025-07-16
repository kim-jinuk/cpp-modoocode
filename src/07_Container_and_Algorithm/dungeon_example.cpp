#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

struct User {
    std::string name;
    int level;

    User(std::string name, int level) : name(name), level(level) {}

    bool operator==(const User& user) const {
        return (name == user.name && level == user.level);
    }
};

class Party {
    std::vector<User> users;

public:
    bool add_user(std::string name, int level) {
        User user(name, level);
        auto result = std::find(users.begin(), users.end(), user);
        if (result != users.end()) return false;
        else {
            users.push_back(user);
            return true;
        }
    }

    bool can_join_dungeon() {
        return std::all_of(users.begin(), users.end(), [](User& u){ return u.level >= 15; });
    }

    bool can_use_special_item() {
        return std::any_of(users.begin(), users.end(), [](User& u){ return u.level >= 19; });
    }
};

int main() {
    Party party;
    party.add_user("철수", 15);
    party.add_user("영희", 18);
    party.add_user("민수", 12);
    party.add_user("수빈", 19);

    std::cout << std::boolalpha;
    std::cout << "던전 입장 가능? " << party.can_join_dungeon() << std::endl;
    std::cout << "특별 아이템 사용 가능? " << party.can_use_special_item() << std::endl;

    return 0;
}