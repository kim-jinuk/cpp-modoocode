#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using std::vector;

int main() {
    vector<int> a(1);
    vector<int> b(2);
    vector<int> c(3);
    vector<int> d(4);

    vector<vector<int>> container;
    container.push_back(a);
    container.push_back(b);
    container.push_back(c);
    container.push_back(d);

    vector<int> size_vec(4);
    // 함수 객체를 std::function으로 만듦
    //std::function<size_t(const vector<int>&)> sz_func = &vector<int>::size;
    //std::transform(container.begin(), container.end(), size_vec.begin(), sz_func);

    // 함수 객체를 mem_fn 함수로 만듦
    // std::transform(container.begin(), container.end(), size_vec.begin(), std::mem_fn(&vector<int>::size));

    // mem_fn 대신 람다 함수로도 가능
    std::transform(container.begin(), container.end(), size_vec.begin(), [](const auto& v){ return v.size(); });

    for (auto it = size_vec.begin(); it != size_vec.end(); ++it) {
        std::cout << "벡터의 크기: " << *it << std::endl;
    }

    return 0;
}