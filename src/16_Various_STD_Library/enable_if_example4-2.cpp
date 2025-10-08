#include <iostream>
#include <type_traits>

template <typename Cont>
std::void_t<decltype(std::declval<Cont>().begin()),
            decltype(std::declval<Cont>().end())>
print(const Cont& container) {
    std::cout << "[ ";
    for (auto it = container.begin(); it != container.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "]\n";
}

struct Bad {
    void begin();
};

int main() {
    // print<Bad, void>(Bad{});     // error!

    return 0;
}