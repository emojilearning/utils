//Author:emojilearning
//data:2017.9.22
#ifndef BASIC_OP_AFFINE_GENERATOR_H
#define BASIC_OP_AFFINE_GENERATOR_H
#include <math.h>

#include <opencv2/opencv.hpp>


class AffineGenerator
{
public:
	AffineGenerator(double mintheta_ = 0, double maxtheta_ = 2 * 3.1415926535,
		double minphi_ = 0, double maxphi_ = 3.1415926535,
		double minlambda_ = 0.5, double maxlambda_ = 1.5) :mintheta(mintheta_), maxtheta(maxtheta_),
		minphi(minphi_), maxphi(maxphi_), minlambda(minlambda_), maxlambda(maxlambda_) {}

	cv::Mat Generate(const cv::Mat& img,cv::Mat& H);
private:
	double mintheta = 0;
	double maxtheta = 2 * 3.1415926535;
	double minphi = 0;
	double maxphi = 3.1415926535;
	double minlambda = 0.5;
	double maxlambda = 1.5;

};

void GenMutiViewImg(const cv::Mat& img,int num);
#endif // !BASIC_OP_AFFINE_GENERATOR_H


