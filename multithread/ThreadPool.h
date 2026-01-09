#pragma once

#include <thread>
#include <vector>
#include <queue>
#include <future>
#include <functional>
#include <mutex>
#include <condition_variable>

namespace FifthTask {
    class ThreadPool {
    private:
        std::vector<std::thread> workers;
        std::queue<std::function<void()>> tasks;

        std::mutex queueMutex;
        std::condition_variable condition;
        bool stop;

    public:
        ThreadPool(size_t numThreads);

        template<class F, class... Args>
        auto submit(F&& f, Args&&... args)
            -> std::future<decltype(f(args...))>
        {
            using ReturnType = decltype(f(args...));

            auto task = std::make_shared<std::packaged_task<ReturnType()>>(
                std::bind(std::forward<F>(f), std::forward<Args>(args)...)
            );

            std::future<ReturnType> result = task->get_future();

            {
                std::lock_guard<std::mutex> lock(queueMutex);
                tasks.emplace([task]() { (*task)(); });
            }

            condition.notify_one();
            return result;
        }

        ~ThreadPool();
    };

    unsigned long long factorial(int n);
}