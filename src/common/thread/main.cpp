//
// Created by guanggang.bian on 2023/5/9.
//
#include <iostream>
#include <random>

#include "src/common/thread/thread_pool.h"

std::random_device rd;
std::mt19937 mt(rd());
std::uniform_int_distribution<int> dist(-1000, 1000);
auto rnd = std::bind(dist, mt);

void sleepTask() {
    std::this_thread::sleep_for(std::chrono::milliseconds(2000 + rnd()));
}

int sumTask(int a, int b) {
    sleepTask();
    std::cout << __PRETTY_FUNCTION__ << " a + b = " << a + b << std::endl;
    return a + b;
}

int multiTask(int a, int b) {
    sleepTask();
    std::cout << __PRETTY_FUNCTION__ << " a * b = " << a * b << std::endl;
    return a * b;
}


int main(int, char**) {
    std::cout << "Testing thread pool" << std::endl;

    guanggang::common::ThreadPool pool;
    for (size_t i = 0; i < 100; i++) {
        if (i % 2) {
            pool.enqueue(sumTask, 5, 6);
        } else {
            pool.enqueue(multiTask, 5, 6);
        }
    }
    std::cout << "This line should be before task being finished --------------" << std::endl;
    pool.wait();
    std::cout << "This line should be after task being finished --------------" << std::endl;
    return 0;
}