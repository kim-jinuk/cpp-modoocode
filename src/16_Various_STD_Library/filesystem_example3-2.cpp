// 디렉토리 안의 모든 파일들 순회하기2 (std::filesystem::directory_iterator 객체 사용)
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

int main() {
    // for (const fs::directory_entry& entry : fs::directory_iterator(fs::current_path() / "build")) {
    //     std::cout << entry.path() << '\n';
    // }

    return 0;
}