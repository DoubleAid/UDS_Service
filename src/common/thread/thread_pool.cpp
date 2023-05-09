//
// Created by guanggang.bian on 2023/5/8.
//

#include "thread_pool.h"
#include <algorithm>
#include <iterator>

namespace guanggang {
namespace common {


    ThreadPool::ThreadPool(std::size_t thread_count) : jobs_count_(0), terminate_(false) {
        threads_.reserve(thread_count);
        std::generate_n(std::back_inserter(threads_), thread_count, [this]() {
           return std::thread{threadTask, this};
        });
    }


    ThreadPool::~ThreadPool() {
        clear();

        terminate_ = true;
        jobs_available_.notify_all();

        for (auto& t : threads_) {
            if (t.joinable()) t.join();
        }
    }


    std::size_t ThreadPool::threadCount() const {
        return threads_.size();
    }


    std::size_t ThreadPool::jobsWaiting() const {
        auto jobs_total = jobs_count_.load();
        return jobs_total > threads_.size() ? jobs_total - threads_.size() : 0;
    }


    std::size_t ThreadPool::jobsTotal() const {
        return jobs_count_.load();
    }


    ThreadPool::Ids ThreadPool::ids() const {
        Ids ret(threads_.size());

        std::transform(threads_.begin(), threads_.end(), ret.begin(), [](auto& t) {
            return t.get_id();
        });

        return ret;
    }


    void ThreadPool::clear() {
        std::lock_guard<std::mutex> lock{jobs_mutex_};

        while (!jobs_.empty()) jobs_.pop();
    }


    void ThreadPool::wait(int64_t interval) {
        while (jobs_count_.load() != 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(interval));
        }
    }


    void ThreadPool::threadTask(guanggang::common::ThreadPool *pool) {
        while (true) {
            if (pool->terminate_) break;

            std::unique_lock<std::mutex> jobs_lock{pool->jobs_mutex_};

            if (pool->jobs_.empty()) {
                pool->jobs_available_.wait(jobs_lock, [&]() {
                    return pool->terminate_ || !(pool->jobs_.empty());
                });
            }

            if (pool->terminate_) break;

            auto job = std::move(pool->jobs_.front());
            pool->jobs_.pop();

            jobs_lock.unlock();

            job();

            pool->jobs_count_.fetch_add(-1);
        }
    }
}
}