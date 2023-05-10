//
// Created by guanggang.bian on 2023/5/9.
//

#pragma once

#include <condition_variable>
#include <queue>
#include <memory>
#include <mutex>
#include <thread>

namespace guanggang {
namespace common {
namespace thread {

template <typename T>
class ThreadSafeQueue {
public:
    ThreadSafeQueue() = default;

    void push(T new_val);

    // safe pop, wait until queue has item val
    void waitAndPop(T& val);

    // safe pop, wait until queue has item
    std::shared_ptr<T> waitAndPop();

    // immediate pop
    bool tryPop(T &val);

    // immediate pop
    std::shared_ptr<T> tryPop();

    bool empty() const;

    size_t size() const;

private:
    mutable std::mutex mutex_;
    std::queue<std::shared_ptr<T>> data_queue_;
    std::condition_variable data_cond_;
};

template <typename T>
void ThreadSafeQueue<T>::push(T new_val) {
    std::shared_ptr<T> data(std::make_shared<T>(std::move(new_val)));
    std::lock_guard<std::mutex> lock{mutex_};
    data_queue_.push(data);
    data_cond_.notify_one();
}

template <typename T>
void ThreadSafeQueue<T>::waitAndPop(T& val) {
    std::unique_lock<std::mutex> lock{mutex_};
    data_cond_.wait(lock, [this]{ return !data_queue_.empty(); });
    val = std::move(*data_queue_.front());
    data_queue_.pop();
}

template <typename T>
std::shared_ptr<T> ThreadSafeQueue<T>::waitAndPop() {
    std::unique_lock<std::mutex> lock{mutex_};
    data_cond_.wait(lock, [this]{ return !data_queue_.empty(); });
    std::shared_ptr<T> res = data_queue_.front();
    data_queue_.pop();
    return res;
}

template <typename T>
bool ThreadSafeQueue<T>::tryPop(T &val) {
    std::lock_guard<std::mutex> lock{mutex_};
    if (data_queue_.empty()) {
        return false;
    }
    val = std::move(*data_queue_.front());
    data_queue_.pop();
    return true;
}

template <typename T>
std::shared_ptr<T> ThreadSafeQueue<T>::tryPop() {
    std::lock_guard<std::mutex> lock{mutex_};
    if (data_queue_.empty()) {
        return std::shared_ptr<T>();
    }
    std::shared_ptr<T> res = data_queue_.front();
    data_queue_.pop();
    return res;
}

template <typename T>
bool ThreadSafeQueue<T>::empty() const {
    std::lock_guard<std::mutex> lock{mutex_};
    return data_queue_.empty();
}

template <typename T>
size_t ThreadSafeQueue<T>::size() const {
    std::lock_guard<std::mutex> lock{mutex_};
    return data_queue_.size();
}

} // thread
} // common
} // guanggang
