#include "ThreadSafeQueue.h"
#include <iostream>
#include <thread>
#include <chrono>

namespace SecondTask {
    void producer(ThreadSafeQueue<int>& queue, int count) {
        for (int i = 1; i <= count; i++) {
            queue.push(i);
            std::cout << "Producer added: " << i << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        queue.shutdown();
    }

    void consumer(ThreadSafeQueue<int>& queue, int id) {
        int value;

        while (queue.pop(value)) {
            std::cout << "Consumer " << id << " got value: " << value << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }

        std::cout << "Consumer " << id << " finished work" << std::endl;
    }
}