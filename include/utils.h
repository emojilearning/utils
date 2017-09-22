//Author:emojilearning
//data:2017.9.22

#include <opencv2\opencv.hpp>
#include <functional>
#ifndef BASIC_OP_UTILS
#define BASIC_OP_UTILS

//note : it's reference to origin image
cv::Mat GetPatch(cv::Mat img, cv::Point2d center, int r = 16);
cv::Mat SlidingWindows(cv::Mat img, cv::Size size, cv::Size step,std::function<void(cv::Mat)> f);

#endif // !BASIC_OP_UTILS
