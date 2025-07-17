// Raw string 문법은 아래와 같다.
// R"/* delimiter */( /* 문자열*/ )/* delimiter */" 
#include <iostream>
#include <string>

int main() {
    std::string str1 = R"(asdfasdf
이 안에는
어떤 것들이 와도
    // 이런 것도 되고
    #define haksenlfkans
    \n\n <--- Escape 안 해도 됨
    )";

    std::string str2 = R"foo(
)"; <--- 무시됨
)foo";

    std::cout << "======== str1 은 아래와 같음 ========" << std::endl << str1 << std::endl << std::endl;
    std::cout << "======== str2 은 아래와 같음 ========" << std::endl << str2;

    return 0;
}