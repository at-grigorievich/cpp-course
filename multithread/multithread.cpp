#include <iostream>
#include <chrono>
#include "VectorSumCalculator.h"

void FirstTaskExecutor();

int main() {
	setlocale(LC_ALL, "Russian");

	FirstTaskExecutor();

    return 0;
}

void FirstTaskExecutor() {
	using namespace FirstTask;

    const size_t VECTOR_SIZE = 100000000;
    const int NUM_THREADS = 4;

    VectorSumCalculator calculator(VECTOR_SIZE);

    std::cout << "\n--- Однопоточное вычисление ---\n";
    auto start_single = std::chrono::high_resolution_clock::now();
    long long sum_single = calculator.calculateSingleThreaded();
    auto end_single = std::chrono::high_resolution_clock::now();
    auto duration_single = std::chrono::duration_cast<std::chrono::milliseconds>(
        end_single - start_single);

    std::cout << "Сумма: " << sum_single << "\n";
    std::cout << "Время выполнения: " << duration_single.count() << " мс\n";

    std::cout << "\n--- Многопоточное вычисление (" << NUM_THREADS << " потоков) ---\n";
    auto start_multi = std::chrono::high_resolution_clock::now();
    long long sum_multi = calculator.calculateMultiThreaded(NUM_THREADS);
    auto end_multi = std::chrono::high_resolution_clock::now();
    auto duration_multi = std::chrono::duration_cast<std::chrono::milliseconds>(
        end_multi - start_multi);

    std::cout << "Сумма: " << sum_multi << "\n";
    std::cout << "Время выполнения: " << duration_multi.count() << " мс\n";

    std::cout << "\n--- Результаты сравнения ---\n";
    std::cout << "Результаты совпадают: " << (sum_single == sum_multi ? "Да" : "Нет") << "\n";

    if (duration_multi.count() > 0) {
        double speedup = static_cast<double>(duration_single.count()) / duration_multi.count();
        std::cout << "Ускорение: " << speedup << "x\n";
    }
}