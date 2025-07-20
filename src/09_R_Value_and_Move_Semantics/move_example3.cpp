#include <iostream>
#include <utility>
#include <cstring>

class MyString {
    char* string_content;
    int string_length;
    int memory_capacity;

public:
    // 일반 생성자
    MyString();
    // 문자열로부터 생성
    MyString(const char* str);
    // 복사 생성자
    MyString(const MyString& str);
    // 이동 생성자
    MyString(MyString&& str);
    ~MyString();
    
    // 일반적인 대입 연산자
    MyString& operator=(const MyString& s);

    // 이동 대입 연산자
    MyString& operator=(MyString&& s);

    int length() const;

    void println();
};

MyString::MyString() {
    std::cout << "생성자 호출!" << std::endl;
    string_length = 0;
    memory_capacity = 0;
    string_content = nullptr;
}

MyString::MyString(const char* str) {
    std::cout << "생성자 호출!" << std::endl;
    string_length = strlen(str);
    memory_capacity = string_length;
    string_content = new char[string_length];

    for (int i = 0; i < string_length; ++i) string_content[i] = str[i];
}

MyString::MyString(const MyString& str) {
    std::cout << "복사 생성자 호출!" << std::endl;
    string_length = str.string_length;
    string_content = new char[string_length];

    for (int i = 0; i < string_length; ++i) string_content[i] = str.string_content[i];
}

MyString::MyString(MyString&& str) {
    std::cout << "이동 생성자 호출!" << std::endl;
    string_length = str.string_length;
    memory_capacity = str.memory_capacity;
    string_content = str.string_content;

    str.string_content = nullptr;
    str.string_length = 0;
    str.memory_capacity = 0;
}

MyString::~MyString() {
    if (string_content) delete[] string_content;
}

MyString& MyString::operator=(const MyString& s) {
    std::cout << "복사!" << std::endl;
    if (s.string_length > memory_capacity) {
        delete[] string_content;
        string_content = new char[s.string_length];
        memory_capacity = s.string_length;
    }
    string_length = s.string_length;

    for (int i = 0; i != string_length; ++i) {
        string_content[i] = s.string_content[i];
    }

    return *this;
}

MyString& MyString::operator=(MyString&& s) {
    std::cout << "이동!" << std::endl;
    string_content = s.string_content;
    memory_capacity = s.memory_capacity;
    string_length = s.string_length;

    s.string_content = nullptr;
    s.string_length = 0;
    s.memory_capacity = 0;

    return *this;
}

int MyString::length() const { return string_length; }

void MyString::println() {
    for (int i = 0; i != string_length; i++) std::cout << string_content[i];
    std::cout << std::endl;
}

template <typename T>
void my_swap(T& a, T& b) {
    T tmp(std::move(a));
    a = std::move(b);
    b = std::move(tmp);
}

int main() {
    MyString str1("abc");
    MyString str2("def");

    std::cout << "Swap 전-----" << std::endl;
    std::cout << "str1 : ";
    str1.println();
    std::cout << "str2 : ";
    str2.println();

    std::cout << "Swap 후-----" << std::endl;
    my_swap(str1, str2);
    std::cout << "str1 : ";
    str1.println();
    std::cout << "str2 : ";
    str2.println();

    return 0;
 }