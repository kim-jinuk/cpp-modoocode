#include <iostream>
#include <cstring>
#include <vector>

class MyString {
    char* string_content;
    int string_length;
    int memory_capacity;

public:
    MyString();
    MyString(const char* str);
    MyString(const MyString& str);
    MyString(MyString&& str);
    ~MyString();
};

MyString::MyString() {
    std::cout << "생성자 호출!" << std::endl;
    string_content = nullptr;
    string_length = 0;
    memory_capacity = 0;
}

MyString::MyString(const char* str) {
    std::cout << "생성자 호출!" << std::endl;
    string_length = strlen(str);
    memory_capacity = string_length;
    string_content = new char[string_length];

    for (int i = 0; i < string_length; ++i) string_content[i] = str[i];
}

MyString::MyString(const MyString& str) {
    std::cout << "복사생성자 호출!" << std::endl;
    string_length = str.string_length;
    string_content = new char[string_length];

    for (int i = 0; i < string_length; ++i) string_content[i] = str.string_content[i];
}

MyString::MyString(MyString&& str) {
    std::cout << "이동생성자 호출!" << std::endl;
    string_length = str.string_length;
    string_content = str.string_content;
    memory_capacity = str.memory_capacity;

    // 임시 객체 소멸 시에 메모리를 해제하지 못하게 한다.
    str.string_content = nullptr;
}

MyString::~MyString() {
    if (string_content) delete[] string_content;
}

int main() {
    MyString s("abc");
    std::vector<MyString> vec;
    vec.resize(0);

    std::cout << "첫 번째 추가 ---" << std::endl;
    vec.push_back(s);
    std::cout << "두 번째 추가 ---" << std::endl;
    vec.push_back(s);
    std::cout << "세 번째 추가 ---" << std::endl;
    vec.push_back(s);

    return 0;
}