#include "ImageProcessor.h"

#include <cstdlib>
#include <ctime>
#include <thread>
#include <iostream>

namespace ThirdTask {
    ImageProcessor::ImageProcessor(int w, int h)
        : width(w), height(h)
    {
        std::srand((unsigned)std::time(nullptr));

        image.resize(height, std::vector<int>(width));
        result.resize(height, std::vector<int>(width));

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                image[y][x] = std::rand() % 256;
            }
        }
    }

    int ImageProcessor::blurPixel(int x, int y) {
        int sum = 0;
        int count = 0;

        for (int dy = -1; dy <= 1; dy++) {
            for (int dx = -1; dx <= 1; dx++) {
                int nx = x + dx;
                int ny = y + dy;

                if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                    sum += image[ny][nx];
                    count++;
                }
            }
        }

        return sum / count;
    }

    void ImageProcessor::applyFilterSingleThread() {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                result[y][x] = blurPixel(x, y);
            }
        }
    }

    void ImageProcessor::applyFilterMultiThread(int numThreads) {
        std::vector<std::thread> threads;
        int rowsPerThread = height / numThreads;

        auto worker = [&](int startY, int endY) {
            for (int y = startY; y < endY; y++) {
                for (int x = 0; x < width; x++) {
                    result[y][x] = blurPixel(x, y);
                }
            }
            };

        int currentY = 0;
        for (int i = 0; i < numThreads; i++) {
            int startY = currentY;
            int endY = (i == numThreads - 1)
                ? height
                : startY + rowsPerThread;

            threads.emplace_back(worker, startY, endY);
            currentY = endY;
        }

        for (auto& t : threads) {
            t.join();
        }
    }

    void ImageProcessor::printAverageBrightness() const {
        long long sum = 0;

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                sum += result[y][x];
            }
        }

        double avg = (double)sum / (width * height);
        std::cout << "Average brightness: " << avg << std::endl;
    }
}