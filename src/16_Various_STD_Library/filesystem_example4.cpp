// 디렉토리 생성하기 (std::filesystem::create_directory 함수 사용)
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

int main() {
    fs::path p("./a/c");
    std::cout << "Does " << p << "exist? [" << std::boolalpha << fs::exists(p) << "]\n";

    fs::create_directories(p);
    std::cout << "Does " << p << "exist? [" << fs::exists(p) << "]\n";
    std::cout << "Is " << p << " directory? [" << fs::is_directory(p) << "]\n";

    return 0;
}