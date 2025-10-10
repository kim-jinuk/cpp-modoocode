// 디렉토리 안의 모든 파일들 순회하기 (std::filesystem::directory_iterator 객체 사용)
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

int main() {
    // fs::directory_iterator itr(fs::current_path() / "build");       // operator/ 오버로딩 되어 있음
    // while (itr != fs::end(itr)) {
    //     const fs::directory_entry& entry = *itr;
    //     std::cout << entry.path() << '\n';
    //     ++itr;
    // }

    return 0;
}