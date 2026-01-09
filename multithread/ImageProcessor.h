#pragma once

#include <vector>

namespace ThirdTask {
    class ImageProcessor {
    private:
        std::vector<std::vector<int>> image;
        std::vector<std::vector<int>> result;
        int width;
        int height;

        int blurPixel(int x, int y);

    public:
        ImageProcessor(int w, int h);

        void applyFilterSingleThread();
        void applyFilterMultiThread(int numThreads);

        void printAverageBrightness() const;
    };
}