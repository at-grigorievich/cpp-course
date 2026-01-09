#pragma once

namespace FourthTask {
    class PiCalculator {
    public:
        double calculatePiPortion(int totalPoints);
        double calculatePiParallel(int totalPoints, int numTasks);
    };
}
