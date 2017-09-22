#include <opencv2/opencv.hpp>
#include <vision_utils.h>
#include <affinegenerator.h>
#include <noise_factory.h>

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
    auto patch = GetPatch(img, { 32,32 });
    //SlidingWindows(img, { 64,64 }, { 16,16 },show);
    AffineGenerator gr;
    while (true) {
        imshow("null", gr.Generate(AddGaussiaNoise(convertToGray(img),64 )));
        waitKey(0);
    }
    return 0;
}