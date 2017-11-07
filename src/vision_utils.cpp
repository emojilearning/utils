#include <vision_utils.h>
#include <opencv2/opencv.hpp>
#include <functional>

using cv::Mat;
using cv::Point2d;
using cv::Size;
using std::function;
using cv::Rect;

Mat convertToGray(const Mat& img)
{
    Mat out;
    if (img.channels() == 4)
        cv::cvtColor(img, out, CV_RGBA2GRAY);
    else if (img.channels() == 3)
        cv::cvtColor(img, out, CV_BGR2GRAY);
    else if (img.channels() == 1)
        out = img.clone();
    return  out;
}

Mat GetPatch(const Mat& img, const Point2d& center, const Size& r)
//return a reference
{
	return img(Rect(center.y - r.height/2, center.y + r.height/2,r.width,r.width));
}

Mat GetPatch(const Mat& img, const Point2d& lt, const int width,const int height)
//return a reference
{
    return img(Rect(lt.x, lt.y,width, height));
}


void SlidingWindows(const Mat& img,Size size, Size step, std::function<void(cv::Mat)> f)
{
	for (int j = size.height / 2; j < img.rows - size.height / 2; j += step.height)
	{
		for (int i = size.width / 2; i < img.cols - size.width / 2; i += step.width)
		{
			Mat patch = GetPatch(img, { i*1.0,(double)j }, size / 2);
			f(patch);
		}
	}
}

Mat padding(const Mat& img,Size padsize)
{
    Size origin = img.size();
    Mat pad(origin + padsize*2,img.type());
    img.copyTo(pad.colRange(padsize.width,img.cols+padsize.width).rowRange(padsize.height,padsize.height+img.rows));
    return pad;
}
