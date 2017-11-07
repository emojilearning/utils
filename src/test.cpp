#include <opencv2/opencv.hpp>
#include <vision_utils.h>
#include <affinegenerator.h>
#include <noise_factory.h>
#include <embedimg.h>

using cv::Mat;
using cv::waitKey;

int main()
{
    Mat img = cv::imread("../resources/img.jpg");

//    GenMutiViewImg(img,1000);

    Mat groundTruth = Mat::zeros(480,640,CV_8UC3);
    for (int i = 0; i < 1000; ++i) {
        char filename[50];
        sprintf(filename,"train_%d.jpg",i);
        Mat img = cv::imread(filename);
        int h = img.rows < 480? img.rows:480;
        int w = img.cols < 640? img.cols:640;
        auto patch = GetPatch(img,  {0,0 },  w,h );
        sprintf(filename,"../train_data/%d.jpg",i);
        auto eimg = embed(groundTruth, patch, {0,0});
        cv::imwrite(filename,eimg);
        std::cout<<i<<std::endl;
    }
//	Mat img = cv::imread("../img.jpg");
//	GenMutiViewImg(img,1000);
//    Mat test = cv::imread("../resources/test.jpg");
//    auto patch = GetPatch(test,  {60,60 },  100,100 );

//	imshow("null", embed(img, patch, {16,16}));
    //SlidingWindows(img, { 64,64 }, { 16,16 },show);
    return 0;
}
