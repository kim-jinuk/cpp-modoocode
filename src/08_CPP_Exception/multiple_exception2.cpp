#include <iostream>
#include <stdexcept>

class parent : public std::exception {
public:
    virtual const char* what() const noexcept override { return "Parent!\n"; }
};

class child : public parent {
public:
    virtual const char* what() const noexcept override { return "Child!\n"; }
};

int func(int c) {
    if (c == 1) throw parent();
    else if (c == 2) throw child();
    return 0;
}

int main() {
    int c;
    std::cin >> c;
    
    // 상속의 경우에 예외를 처리할 때는, 파생 클래스를 상위 catch에 먼저 작성한다.
    try {
        func(c);
    } /*catch (parent& p) {
        std::cout << "Parent Catch!" << std::endl;
        std::cout << p.what();
    } catch (child& c) {
        std::cout << "Child Catch!" << std::endl;
        std::cout << c.what();
    }*/ catch (child& c) {
        std::cout << "Child Catch!" << std::endl;
        std::cout << c.what();
    } catch (parent& p) {
        std::cout << "Parent Catch!" << std::endl;
        std::cout << p.what();
    }
    
    return 0;
}