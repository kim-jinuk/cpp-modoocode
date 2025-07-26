#include <iostream>
#include <vector>
#include <thread>
#include <cstdio>

using std::vector;
using std::thread;

void worker(vector<int>::iterator start, vector<int>::iterator end, int* result) { 
    int sum = 0;
    for (auto itr = start; itr < end; ++itr) {
        sum += *itr;
    }

    *result = sum;
    thread::id this_id = std::this_thread::get_id();
    printf("쓰레드 %x에서 %d부터 %d까지 계산한 결과 : %d \n", this_id, *start, *(end - 1), sum);
}

int main() {
    vector<int> data(10000);
    for (int i = 0; i < 10000; ++i) {
        data[i] = i;
    }

    vector<int> partial_sum(4);
    vector<thread> workers(4);

    for (int i = 0; i < 4; ++i) {
        workers.push_back(thread(worker, data.begin() + i * 2500, data.begin() + (i + 1) * 2500, &partial_sum[i]));
    }

    for (int i = 0; i < 4; ++i) {
        workers[i].join();
    }

    int total = 0;
    for (int i = 0; i < 4; ++i) {
        total += partial_sum[i];
    }

    std::cout << "전체 합 : " << total << std::endl;

    return 0;
}