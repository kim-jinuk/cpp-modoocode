// async 를 사용해서 기존의 find 알고리즘을 더 빠르게 수행하는 함수를 만들어보세요.
#include <algorithm>
#include <future>
#include <thread>
#include <iostream>
#include <vector>
#include <iterator>

template <typename InputIterator, typename T>
InputIterator fast_find(InputIterator first, InputIterator last, const T& val) {
    if (first == last) return last;

    // 중간 지점 계산
    auto n = std::distance(first, last);
    InputIterator mid = first;
    std::advance(mid, n / 2);

    // 하위 절반 계산 [first, mid)
    auto lower_half_future = std::async(std::launch::async, [first, mid, val]() { return std::find(first, mid, val); });
    // 상위 절반 계산 [mid, last)
    auto upper_it = std::find(mid, last, val);

    auto lower_it = lower_half_future.get();

    if (upper_it != last) return upper_it;
    if (lower_it != mig) return lower_it;

    return last;    // 양쪽 다 못 찾은 경우
}

int main() {
    std::vector<int> vec;
    vec.reserve(10000);

    for (int i = 0; i < 10000; ++i) {
        vec.push_back(i + 1);
    }

    auto it = fast_find(vec.begin(), vec.end(), 9999);
    if (it != vec.end()) {
        std::cout << "Element found in myvector: " << *it << std::endl;
    } else {
        std::cout << "Element not found in myvector" << std::endl;
    }

    return 0;
}