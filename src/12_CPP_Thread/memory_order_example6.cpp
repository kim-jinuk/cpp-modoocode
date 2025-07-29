#include <iostream>
#include <atomic>
#include <thread>

using std::thread;
using std::memory_order_seq_cst;

std::atomic<bool> x(false);
std::atomic<bool> y(false);
std::atomic<int> z(0);

void write_x() {
    x.store(true, memory_order_seq_cst);
}

void write_y() {
    y.store(true, memory_order_seq_cst);
}

void read_x_then_y() {
    while (!x.load(memory_order_seq_cst)) {}
    if (y.load(memory_order_seq_cst)) {
        ++z;
    }
}

void read_y_then_x() {
    while (!y.load(memory_order_seq_cst)) {}
    if (x.load(memory_order_seq_cst)) {
        ++z;
    }
}

int main() {
    thread a(write_x);
    thread b(write_y);
    thread c(read_x_then_y);
    thread d(read_y_then_x);

    a.join();
    b.join();
    c.join();
    d.join();

    std::cout << "z : " << z << std::endl;

    return 0;
}