#include "../include/frameprocessor.h"
#include <opencv2/opencv.hpp>
#include <vector>

FrameProcessor::FrameProcessor() {}

cv::Mat FrameProcessor::processFrame(const cv::Mat& frame, bool grayscale, bool redChannel, double rotationAngle) {
    cv::Mat processedFrame = frame.clone();

    if (grayscale) {
        processedFrame = applyGrayscale(processedFrame);
    }

    if (redChannel) {
        processedFrame = applyRedChannel(processedFrame);
    }

    if (rotationAngle != 0.0) {
        processedFrame = rotateFrame(processedFrame, rotationAngle);
    }

    return processedFrame;
}

cv::Mat FrameProcessor::applyGrayscale(const cv::Mat& frame) {
    cv::Mat grayFrame;
    cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);
    cv::cvtColor(grayFrame, grayFrame, cv::COLOR_GRAY2BGR); // Convert back to 3 channels
    return grayFrame;
}

cv::Mat FrameProcessor::applyRedChannel(const cv::Mat& frame) {
    std::vector<cv::Mat> channels;
    cv::split(frame, channels);
    channels[0] = cv::Mat::zeros(channels[0].size(), CV_8UC1); // Remove Blue channel
    channels[1] = cv::Mat::zeros(channels[1].size(), CV_8UC1); // Remove Green channel
    cv::Mat redFrame;
    cv::merge(channels, redFrame);
    return redFrame;
}

cv::Mat FrameProcessor::rotateFrame(const cv::Mat& frame, double angle) {
    cv::Point2f center(frame.cols / 2.0, frame.rows / 2.0);
    cv::Mat rotationMatrix = cv::getRotationMatrix2D(center, angle, 1.0);
    cv::Mat rotatedFrame;
    cv::warpAffine(frame, rotatedFrame, rotationMatrix, frame.size());
    return rotatedFrame;
}
