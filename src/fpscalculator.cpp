#include "../include/fpscalculator.h"

FPSCalculator::FPSCalculator()
    : frameCount(0), fpsCount(0)
{
    lastFrameTime = std::chrono::high_resolution_clock::now();
    lastSecondTime = std::chrono::high_resolution_clock::now();
}


// calculate the real-time FPS by measuring the time between two frames
double FPSCalculator::calculateRealTimeFPS() {
    auto currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsedTime = currentTime - lastFrameTime;
    lastFrameTime = currentTime;
    return 1.0 / elapsedTime.count();
}


// count the number of frames in one second
void FPSCalculator::countFrame() {
    frameCount++;
    auto currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsedTime = currentTime - lastSecondTime;

    if (elapsedTime.count() >= 1.0) {
        fpsCount = frameCount;
        frameCount = 0;
        lastSecondTime = currentTime;
    }
}

// return the calculated FPS
int FPSCalculator::getFpsCount() {
    return fpsCount;
}
