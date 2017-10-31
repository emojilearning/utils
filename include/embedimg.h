//Author:emojilearning
//data:2017.9.22

#ifndef VISION_UTILS_EMBEDIMG_H
#define VISION_UTILS_EMBEDIMG_H

#include <opencv2/opencv.hpp>
cv::Mat embed(cv::Mat src, cv::Mat patch, cv::Point2i pt);
#endif