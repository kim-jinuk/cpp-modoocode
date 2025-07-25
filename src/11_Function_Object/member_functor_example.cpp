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
    std::function<size_t(const vector<int>&)> sz_func = &vector<int>::size;
    std::transform(container.begin(), container.end(), size_vec.begin(), sz_func);

    for (auto it = size_vec.begin(); it != size_vec.end(); ++it) {
        std::cout << "벡터의 크기: " << *it << std::endl;
    }

    return 0;
}