#include <iostream>
#include <vector>
#include <memory>

class A {
    int* data;

public:
    A() {
        std::cout << "자원을 획득함!" << std::endl;
        data = new int[100];
    }
    ~A() {
        std::cout << "자원을 해제함!" << std::endl;
        delete[] data;
    }
};

int main() {
    std::vector<std::shared_ptr<A>> vec;

    vec.push_back(std::shared_ptr<A>(new A()));
    vec.push_back(std::shared_ptr<A>(vec[0]));
    vec.push_back(std::shared_ptr<A>(vec[1]));

    // 벡터의 첫 번째 원소를 소멸시킨다.
    std::cout << "현재 A() 객체를 참조하는 스마트 포인터의 수 : " << vec[0].use_count() << std::endl;
    std::cout << "첫 번째 소멸!" << std::endl;
    vec.erase(vec.begin());

    // 벡터의 두 번째 원소를 소멸시킨다.
    std::cout << "현재 A() 객체를 참조하는 스마트 포인터의 수 : " << vec[0].use_count() << std::endl;
    std::cout << "두 번째 소멸!" << std::endl;
    vec.erase(vec.begin());

    // 벡터의 세 번째 원소를 소멸시킨다.
    std::cout << "현재 A() 객체를 참조하는 스마트 포인터의 수 : " << vec[0].use_count() << std::endl;
    std::cout << "세 번째 소멸!" << std::endl;
    vec.erase(vec.begin());

    return 0;
}