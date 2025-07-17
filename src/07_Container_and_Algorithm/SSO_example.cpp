// SSO -> Short String Optimization
#include <iostream>
#include <string>

// 이와 같이 new를 전역 함수로 정의하면 모든 new 연산자를 오버로딩 해버린다.
// (어떤 클래스의 멤버 함수로 정의하면 해당 클래스의 new만 오버로딩됨)
void* operator new(std::size_t count) {
    std::cout << count << " bytes 할당" << std::endl;
    return malloc(count);
}

int main() {
    std::cout << "s1 생성 ---" << std::endl;
    std::string s1 = "this is a pretty long sentence!!";
    std::cout << "s1 크기 : " << sizeof(s1) << std::endl;

    std::cout << "s2 생성 ---" << std::endl;
    std::string s2 = "short sentence";
    std::cout << "s2 크기 : " << sizeof(s2) << std::endl;

    return 0;
}