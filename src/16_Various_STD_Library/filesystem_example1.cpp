#include <iostream>
#include <filesystem>

int main() {
    std::filesystem::path p("./some_file");

    std::cout << "Does " << p << " exist? [" << std::boolalpha << std::filesystem::exists(p) << "]\n";
    std::cout << "Is " << p << " file? [" << std::boolalpha << std::filesystem::is_regular_file(p) << "]\n";
    std::cout << "Is " << p << " directory? [" << std::boolalpha << std::filesystem::is_directory(p) << "]\n";

    return 0;
}