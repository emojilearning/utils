#include <opencv2/opencv.hpp>
#include <vision_utils.h>
#include <affinegenerator.h>
#include <noise_factory.h>
#include <embedimg.h>

using cv::Mat;
using cv::waitKey;
int i = 0;
void show(Mat p)
{
    imshow("null", p);
    i++;
    waitKey(1);
}

int main()
{
	Mat img = cv::imread("../resources/img.jpg");
	Mat test = cv::imread("../resources/test.jpg");
	auto patch = GetPatch(test, { 160,160 }, { 100,100 });
	imshow("null", embed(img, patch, {16,16}));
    waitKey(0);
    //SlidingWindows(img, { 64,64 }, { 16,16 },show);
    return 0;
}