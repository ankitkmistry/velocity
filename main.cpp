#include <iostream>
#include <mutex>
#include <thread>

std::mutex mtx;

void printBlock(int n, char c) {
    mtx.lock();
    for (int i = 0; i < n; ++i) {
        std::cout << c;
    }
    std::cout << '\n';
    mtx.unlock();
}

int main() {
    std::ios::sync_with_stdio(false);
    std::thread t1{printBlock,50,'*'};
    std::thread t2{printBlock, 50, '$'};

    t1.join();
    t2.join();
    return 0;
}
