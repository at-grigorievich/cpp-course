#include "VectorSumCalculator.h"

#include <random>
#include <iostream>

namespace FirstTask {
    VectorSumCalculator::VectorSumCalculator(size_t size) {
        data.resize(size);

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 100);

        for (size_t i = 0; i < size; i++) {
            data[i] = dis(gen);
        }

        std::cout << "Вектор из " << size << " элементов создан\n";
    }

    long long VectorSumCalculator::calculateSingleThreaded() {
        long long sum = 0;
        for (size_t i = 0; i < data.size(); i++) {
            sum += data[i];
        }
        return sum;
    }

    void VectorSumCalculator::threadWork(size_t start, size_t end, long long& total_sum) {
        long long local_sum = 0;

        for (size_t i = start; i < end; i++) {
            local_sum += data[i];
        }

        sum_mutex.lock();
        total_sum += local_sum;
        sum_mutex.unlock();
    }

    long long VectorSumCalculator::calculateMultiThreaded(int num_threads) {
        long long total_sum = 0;
        std::vector<std::thread> threads;

        size_t chunk_size = data.size() / num_threads;

        for (int i = 0; i < num_threads; i++) {
            size_t start = i * chunk_size;
            size_t end;

            if (i == num_threads - 1) {
                end = data.size();
            }
            else {
                end = start + chunk_size;
            }

            threads.push_back(std::thread(&VectorSumCalculator::threadWork,
                this, start, end, std::ref(total_sum)));
        }

        for (auto& t : threads) {
            t.join();
        }
        return total_sum;
    }
}