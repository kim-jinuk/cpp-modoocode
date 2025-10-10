// 디렉토리 삭제하기 (std::filesystem::remove 함수 사용)
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

int main() {
    // fs::path p("./c/b");

    // std::error_code err;
    // fs::remove(p, err);     // 실패!
    // std::cout << err.message() << std::endl;

    // fs::remove_all(p);      // 성공!

    return 0;
}