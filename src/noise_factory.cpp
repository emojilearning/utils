#include <noise_factory.h>
#include <random>
#include <cstdint>
#include <opencv2/opencv.hpp>

using cv::Mat;

Mat AddWhiteNoise(const Mat& src,int lv )
{
    Mat img = src.clone();
    std::random_device rd;
    static std::default_random_engine noise(rd());
    static std::uniform_int_distribution<> u(-lv, lv);

    for (int i = 0; i < img.size().height*img.size().width; ++i) {
        int n = u(noise);
        if(n + img.at<uint8_t>(i)>255)
            img.at<uint8_t>(i) = 255;
        else if (n + img.at<char>(i)<0)
            img.at<uint8_t>(i) = 0;
        else
            img.at<uint8_t>(i) += n;
    }
    return std::move(img);
}

Mat AddGaussiaNoise(const Mat& src,int lv)
{
    Mat img = src.clone();
    std::random_device rd;
    static std::default_random_engine noise(rd());
    static std::normal_distribution<> u;

    for (int i = 0; i < img.size().height*img.size().width; ++i) {
        int n = (int) (u(noise)*lv);
        if(n + img.at<uint8_t>(i)>255)
            img.at<uint8_t>(i) = 255;
        else if (n + img.at<uint8_t>(i)<0)
            img.at<uint8_t>(i) = 0;
        else
            img.at<uint8_t>(i) += n;
    }
    return std::move(img);
}
