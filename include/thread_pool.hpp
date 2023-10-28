#pragma once

/**
 * @file thread_pool.hpp
 * @brief Definition and implementation of the `thread_pool` class.
 */

#include <condition_variable>
#include <mutex>
#include <thread>

#include <functional>
#include <future>
#include <type_traits>

#include <queue>
#include <vector>

/// @brief The thread_pool class represents a pool of threads for executing asynchronous tasks.
class thread_pool
{
public:
    explicit thread_pool(unsigned thread_count = 0);

    ~thread_pool();

public:
    template <class F>
    auto submit(F function)->std::future<decltype(function())>;

private:
    std::queue<std::function<void()>> tasks_;
    std::vector<std::thread> threads_;
    std::mutex mutex_;
    std::condition_variable condition_;
    bool stop_;
};

inline thread_pool::thread_pool(unsigned thread_count)
    : stop_{ false }
{
    if (thread_count == 0) {
        thread_count = std::thread::hardware_concurrency();
    }
    for (auto i = 0; i < thread_count; ++i) {
        threads_.emplace_back([this] {
            while (true) {
                std::function<void()> tsk;
                {
                    std::unique_lock<std::mutex> lock(mutex_);
                    while (!stop_ && tasks_.empty()) {
                        condition_.wait(lock);
                    }
                    if (stop_ && tasks_.empty()) {
                        return;
                    }
                    tsk = std::move(tasks_.front());
                    tasks_.pop();
                }
                tsk();
            }
            });
    }
}

inline thread_pool::~thread_pool()
{
    {
        std::unique_lock<std::mutex> lock(mutex_);
        stop_ = true;
    }
    condition_.notify_all();
    for (auto& iter : threads_) {
        iter.join();
    }
}

template <class F>
inline auto thread_pool::submit(F function) -> std::future<decltype(function())>
{
    if (stop_) {
        throw std::runtime_error("schedule on destroyed scheduler");
    }
    using result_type = decltype(function());
    auto task = std::make_shared<std::packaged_task<result_type()>>(function);
    std::future<result_type> result(task->get_future());
    {
        std::unique_lock<std::mutex> lock(mutex_);
        if (stop_) {
            throw std::runtime_error("enqueue on stopped ThreadPool");
        }

        tasks_.emplace([task]() {
            (*task)();
        });
    }
    condition_.notify_one();
    return result;
}