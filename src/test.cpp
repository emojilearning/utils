#include <opencv2/opencv.hpp>
#include <vision_utils.h>
#include <affinegenerator.h>
#include <noise_factory.h>
#include <embedimg.h>

using cv::Mat;
using cv::waitKey;

int main()
{
    Mat img = cv::imread("../resources/Marker.jpg");

    GenMutiViewImg(img,1000);


//	Mat img = cv::imread("../img.jpg");
//	GenMutiViewImg(img,1000);
//    Mat test = cv::imread("../resources/test.jpg");
//    auto patch = GetPatch(test,  {60,60 },  100,100 );

//	imshow("null", embed(img, patch, {16,16}));
    //SlidingWindows(img, { 64,64 }, { 16,16 },show);
    return 0;
}
