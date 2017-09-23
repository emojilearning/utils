#include <vision_utils.h>
#include <opencv2/opencv.hpp>
#include <functional>

using cv::Mat;
using cv::Point2d;
using cv::Size;
using std::function;

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
{
	return img.rowRange(center.y - r.height, center.y + r.height).colRange(center.x - r.width, center.x + r.width);
}


Mat GetPatch(const Mat& img, const Point2d& center, int r)
{
	return img.rowRange(center.y - r, center.y + r).colRange(center.x - r, center.x + r);
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
    Mat pad(origin + padsize*2,CV_8U);
    img.copyTo(pad.colRange(padsize.width,img.cols+padsize.width).rowRange(padsize.height,padsize.height+img.rows));
    return pad;
}
