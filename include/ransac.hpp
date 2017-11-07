#include <opencv2/opencv.hpp>
class RansacModelEstimator
{
public:
	RansacModelEstimator() {};
	cv::Mat run(std::vector<cv::Point3d> point_set);
	int iterate(std::vector<int>& mask);
	void estimateParm(std::vector<cv::Point3d>& initial_point);
	void estimateInliners(std::vector<int>& mask);
	cv::Mat estimateParm1(std::vector<cv::Point3d>& initial_point);
	double estimateDeparture(cv::Point3d& p);

private:
	std::vector<cv::Point3d> point_set;
	cv::Point3d theta;
	std::vector<int> rand_index;
};
