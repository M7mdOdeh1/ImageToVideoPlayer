#pragma once

#include <chrono>

class FPSCalculator {
public:
    FPSCalculator();

    // Method for calculating real-time FPS
    double calculateRealTimeFPS();

    // Method for counting FPS over one second
    void countFrame();
    int getFpsCount();

private:
    // Real-time FPS calculation variables
    std::chrono::high_resolution_clock::time_point lastFrameTime;

    // Frame count method variables
    int frameCount;
    int fpsCount;
    std::chrono::high_resolution_clock::time_point lastSecondTime;
};