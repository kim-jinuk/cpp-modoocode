#include <iostream>
#include <stdexcept>

template <typename T>
class Vector {
private:
    size_t size_;
    T* data_;

public:
    Vector(size_t size) : size_(size) {
        data_ = new T[size_];
        for (int i = 0; i < size_; ++i) {
            data_[i] = 3;
        }
    }

    const T& at(size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("vector의 index가 범위를 초과하였습니다.");
        } 
        return data_[index];
    }

    ~Vector() {
        delete[] data_;
    }
};

int main() {
    Vector<int> vec(3);

    int index, data = 0;
    std::cin >> index;

    try {
        data = vec.at(index);
    } catch (std::out_of_range& e) {
        std::cout << "예외 발생!" << e.what() << std::endl;
    }
    std::cout << "읽은 데이터 : " << data << std::endl;

    return 0;
}