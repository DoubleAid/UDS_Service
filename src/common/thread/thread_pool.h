//
// Created by guanggang.bian on 2023/5/8.
//

#pragma once

#include <atomic>
#include <condition_variable>
#include <functional>
#include <future>
#include <queue>
#include <thread>
#include <vector>


namespace guanggang {
namespace common {

    class ThreadPool {
    public:
        using Ids = std::vector<std::thread::id>;

        ThreadPool(std::size_t thread_count = std::thread::hardware_concurrency());
        ThreadPool(const ThreadPool&) = delete;
        ThreadPool& operator=(const ThreadPool&) = delete;

        ~ThreadPool();

        template <typename Func, typename... Args>
        auto enqueue(Func&& func, Args&&... args)
            -> std::future<typename std::result_of<Func(Args...)>::type>;

        std::size_t threadCount() const;

        std::size_t jobsWaiting() const;

        std::size_t jobsTotal() const;

        Ids ids() const;

        // clear currently queued jobs (jobs which are not currently running)
        void clear();

        void wait(int64_t interval = 500);
    private:
        using Job = std::function<void()>;

        static void threadTask(ThreadPool* pool);

        std::queue<Job> jobs_;
        mutable std::mutex jobs_mutex_;

        std::condition_variable jobs_available_;

        std::vector<std::thread> threads_;
        std::atomic<std::size_t> jobs_count_;

        std::atomic<bool> terminate_;
    };

    // future type must stay with definition
    template <typename Func, typename... Args>
    auto ThreadPool::enqueue(Func&& func, Args&&... args)
    -> std::future<typename std::result_of<Func(Args...)>::type> {
        using PackedTask = std::packaged_task<typename std::result_of<Func(Args...)>::type()>;
        jobs_count_.fetch_add(1);

        auto task = std::make_shared<PackedTask>(std::bind(std::forward<Func>(func), std::forward<Args>(args)...));

        auto ret = task->get_future();

        {
            std::lock_guard<std::mutex> lock{jobs_mutex_};
            jobs_.emplace([task]() { (*task)(); });
        }

        jobs_available_.notify_one();
        return ret;
    }


}
}
