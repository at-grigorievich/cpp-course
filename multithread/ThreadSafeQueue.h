#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>

namespace SecondTask {
    template<typename T>
    class ThreadSafeQueue {
    private:
        std::queue<T> queue;
        std::mutex mtx;
        std::condition_variable cv;
        bool isClosed = false;

    public:
        void push(const T& value) {
            std::lock_guard<std::mutex> lock(mtx);
            queue.push(value);
            cv.notify_one();
        }

        bool pop(T& value) {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [this]() {
                return isClosed || !queue.empty();
                });

            if (queue.empty())
                return false;

            value = queue.front();
            queue.pop();
            return true;
        }

        void shutdown() {
            std::lock_guard<std::mutex> lock(mtx);
            isClosed = true;
            cv.notify_all();
        }
    };

    void producer(ThreadSafeQueue<int>& queue, int count);
    void consumer(ThreadSafeQueue<int>& queue, int id);
}