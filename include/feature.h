//Author:emojilearning
//data:2017.9.22
#ifndef VISION_UTILS_FEATURE_H
#define VISION_UTILS_FEATURE_H

#include <opencv2/opencv.hpp>
void MarkMarker(const Mat& left, Mat& out2, const Mat& H, Scalar s = Scalar(0, 255, 0));
void OrbMatchByKnn(cv::Mat& desp_m, cv::Mat& desp_i, std::vector<cv::DMatch>& matches);

#endif
