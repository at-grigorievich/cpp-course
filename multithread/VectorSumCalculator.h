#pragma once
#include <vector>
#include <mutex>

namespace FirstTask {
    class VectorSumCalculator {
    private:
        std::vector<int> data;
        std::mutex sum_mutex;

        void threadWork(size_t start, size_t end, long long& total_sum);

    public:
        VectorSumCalculator(size_t size);

        long long calculateSingleThreaded();
        long long calculateMultiThreaded(int num_threads);
    };
}