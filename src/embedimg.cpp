#include <opencv2/opencv.hpp>

using cv::Mat;
using cv::Point2i;
using cv::Rect;

Mat embed(Mat src,Mat patch,Point2i pt)
{
	Mat temp = src.clone();
//	Mat imgROI = temp(Rect(pt.x, pt.y, patch.cols, patch.rows));
	patch.copyTo(temp(Rect(pt.x, pt.y, patch.cols, patch.rows)));

	return temp;
}


