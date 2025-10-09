// 파일과 폴더 복사/삭제하기 (std::filesystem::copy 함수 사용)
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

int main() {
    fs::path from("./a");
    fs::path to("./c");

    fs::create_directories(fs::path("./c"));
    fs::create_directories(fs::path("./a/a.txt"));
    fs::create_directories(fs::path("./a/b/c.txt"));

    fs::copy(from, to, fs::copy_options::recursive);

    return 0;
}