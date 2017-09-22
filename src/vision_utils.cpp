#include <vision_utils.h>
#include <opencv2/opencv.hpp>
#include <functional>

using cv::Mat;
using cv::Point2d;
using cv::Size;
using std::function;

Mat GetPatch(const Mat& img, const Point2d& center, const Size& r)
{
	return img.rowRange(center.y - r.height, center.y + r.height).colRange(center.x - r.width, center.x + r.width);
}


Mat GetPatch(const Mat& img, const Point2d& center, int r)
{
	return img.rowRange(center.y - r, center.y + r).colRange(center.x - r, center.x + r);
}

Mat SlidingWindows(const Mat& img,Size size, Size step, std::function<void(cv::Mat)> f)
{
	for (size_t j = size.height / 2; j < img.rows - size.height / 2; j += step.height)
	{
		for (size_t i = size.width / 2; i < img.cols - size.width / 2; i += step.width)
		{
			Mat patch = GetPatch(img, { i*1.0,(double)j }, size / 2);
			f(patch);
		}
	}
	return {};
}