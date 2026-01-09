#include "PiCalculator.h"
#include <random>
#include <future>
#include <vector>
#include <iostream>

namespace FourthTask {

    double PiCalculator::calculatePiPortion(int totalPoints) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<double> dist(0.0, 1.0);

        int insideCircle = 0;

        for (int i = 0; i < totalPoints; i++) {
            double x = dist(gen);
            double y = dist(gen);

            if (x * x + y * y <= 1.0)
                insideCircle++;
        }

        return 4.0 * insideCircle / totalPoints;
    }

    double PiCalculator::calculatePiParallel(int totalPoints, int numTasks) {
        std::vector<std::future<double>> futures;
        int pointsPerTask = totalPoints / numTasks;

        for (int i = 0; i < numTasks; i++) {
            futures.push_back(
                std::async(
                    std::launch::async,
                    &PiCalculator::calculatePiPortion,
                    this,
                    pointsPerTask
                )
            );
        }

        double sum = 0.0;

        try {
            for (auto& f : futures) {
                sum += f.get();
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Error during calculation: " << e.what() << std::endl;
            return 0.0;
        }

        return sum / numTasks;
    }
}