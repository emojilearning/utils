//Author:emojilearning
//data:2017.9.22

#ifndef BASIC_OP_VISION_UTILS
#define BASIC_OP_VISION_UTILS
#include <opencv2/opencv.hpp>
#include <functional>


//note : it's reference to origin image
cv::Mat GetPatch(const cv::Mat& img, const cv::Point2d& center, const cv::Size& r = cv::Size{ 32,32 });
cv::Mat GetPatch(const cv::Mat& img, const cv::Point2d& lt, const int width,const int height);

void SlidingWindows(const cv::Mat& img, cv::Size size, cv::Size step,std::function<void(cv::Mat)> f);
cv::Mat convertToGray(const cv::Mat& img);
cv::Mat padding(const cv::Mat& img,cv::Size padsize);


#endif // !BASIC_OP_UTILS
