#pragma once

#include <opencv2/opencv.hpp>

class FrameProcessor {
public:
    FrameProcessor();
    cv::Mat processFrame(const cv::Mat& frame, bool grayscale, bool redChannel, double rotationAngle);

private:
    cv::Mat applyGrayscale(const cv::Mat& frame);
    cv::Mat applyRedChannel(const cv::Mat& frame);
    cv::Mat rotateFrame(const cv::Mat& frame, double angle);
};