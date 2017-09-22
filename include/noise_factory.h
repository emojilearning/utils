#ifndef UTILS_NOISE_FACTORY_H
#define UTILS_NOISE_FACTORY_H

#include <opencv2/opencv.hpp>
cv::Mat AddWhiteNoise(const cv::Mat& src,int lv = 0);
cv::Mat AddGaussiaNoise(const cv::Mat& src,int lv = 0);

#endif