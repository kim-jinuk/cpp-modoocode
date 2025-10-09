#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

int main() {
    fs::path p("./some_file.txt");

    std::cout << "내 현재 경로 : " << fs::current_path() << '\n';
    std::cout << "상대 경로 : " << p.relative_path() << '\n';
    std::cout << "절대 경로 : " << fs::absolute(p) << '\n';
    std::cout << "공식적인 절대 경로 : " << fs::canonical(p) << '\n';

    return 0;
}