#include "ransac.hpp"
#include <random>
#include <vector>
using namespace std;
using namespace cv;
using cv::Point3d;

double RansacModelEstimator::estimateDeparture(Point3d& p)
{
	return fabs(p.dot(theta) / norm(Point2d(theta.x, theta.y)));
}

void RansacModelEstimator::estimateInliners(vector<int>& mask)
{
	mask.clear();
	for (size_t i = 0; i < point_set.size(); i++)
	{
		if (estimateDeparture(point_set[i]) < 0.3)
			mask.push_back(i);
	}
}

void RansacModelEstimator::estimateParm(vector<cv::Point3d>& initial_point)
{
	theta = initial_point[0].cross(initial_point[1]);
}

Mat RansacModelEstimator::estimateParm1(vector<cv::Point3d>& inliner_point)
{
	Mat constrains(inliner_point.size(), 3, CV_64F);
	Mat b(inliner_point.size(), 1, CV_64F);
	b.setTo(0);
	for (int i = 0; i<inliner_point.size(); i++)
	{
		constrains.at<double>(i, 0) = inliner_point[i].x;
		constrains.at<double>(i, 1) = inliner_point[i].y;
		constrains.at<double>(i, 2) = inliner_point[i].z;
	}
	Mat tconstrains;
	Mat result;

	cv::SVD::solveZ(constrains, result);
	return result;
}


int RansacModelEstimator::iterate(vector<int>& mask)
{
	static std::random_device rd;
	static std::default_random_engine e(rd());
	static std::uniform_int_distribution<> u(0, point_set.size() - 1);
	vector<cv::Point3d> initial_point;
	int last = -1;
	for (size_t i = 0; i < 2; i++)
	{
		int index = u(e);
		while (index == last)
			index = u(e);
		initial_point.push_back(point_set[index]);
		last = index;
	}
	estimateParm(initial_point);
	estimateInliners(mask);
	return mask.size();
}

Mat RansacModelEstimator::run(vector<cv::Point3d> point_set_)
{
	point_set = point_set_;
	vector<int> optimal_mask;
	vector<int> current_mask;
	int optimal_inliner_num = 0;
	int inliner_num;
	for (size_t i = 0; i < 300; i++)
	{
		inliner_num = iterate(current_mask);
		if (optimal_inliner_num < inliner_num)
		{
			optimal_mask = current_mask;
			optimal_inliner_num = inliner_num;
		}
	}
	vector<Point3d> inliners;
	for (size_t i = 0; i < optimal_inliner_num; i++)
	{
		inliners.push_back(point_set[optimal_mask[i]]);
	}
	return estimateParm1(inliners);
}
//int main()
//{
//	RansacModelEstimator est;
//	Mat result = est.run({ { 1,1,1 },{ 2,2,1 },{ 3,4,1 },{ 5,4,1 },{ 7,6.9,1 },{ 6,6.1,1 },{ 1,111,1 },{ 23,2,1 },{ 11.8,12.1,1 } });
//	std::cout << result << endl;
//	return 0;
//}