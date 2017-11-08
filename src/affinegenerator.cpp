#include <opencv2/opencv.hpp>
#include <vision_utils.h>
#include <random>
#include <affinegenerator.h>
#include <iostream>
#include <embedimg.h>

using cv::Mat;
using cv::imshow;
using cv::waitKey;
using std::cout;
using cv::Point2d;
using std::vector;
using std::pair;
using std::fstream;

Mat GenRoatationMatrix(double theta)
{
	Mat rot = Mat::eye({ 3,3 }, CV_64F);
	rot.at<double>(0, 0) = cos(theta);
	rot.at<double>(0, 1) = sin(theta);
	rot.at<double>(1, 0) = -sin(theta);
	rot.at<double>(1, 1) = cos(theta);
	return rot;
}

pair<Point2d,Point2d> BBox(vector<Point2d> pts)
{
	Point2d lu{ 1000, 1000 };
	Point2d rd{ -1, -1 };
	for (size_t i = 0; i < pts.size(); i++) {
		lu.x = lu.x < pts[i].x ? lu.x : pts[i].x;
		lu.y = lu.y < pts[i].y ? lu.y : pts[i].y;
		rd.x = rd.x > pts[i].x ? rd.x : pts[i].x;
		rd.y = rd.y > pts[i].y ? rd.y : pts[i].y;
	}
	return std::make_pair(lu, rd);
}

Mat GenAffine(Mat input, double theta, double phi, double lambda1,double lambda2, cv::Size sz)
{
	int height = input.rows;
	int width = input.cols;

	Mat T = Mat::eye({ 3,3 }, CV_64F);
	T.at<double>(0, 2) = -width /2;
	T.at<double>(1, 2) = -height/2;
	Mat iT = Mat::eye({ 3,3 }, CV_64F);
	iT.at<double>(0, 2) = sz.width / 2;
	iT.at<double>(1, 2) = sz.height / 2;

	Mat theta_mat = GenRoatationMatrix(theta);
	Mat phi_mat = GenRoatationMatrix(phi);
	Mat iphi_mat = GenRoatationMatrix(-phi);
	Mat lambda_mat = Mat::eye({3,3},CV_64F);
	lambda_mat.at<double>(0) = lambda1;
	lambda_mat.at<double>(1,1) = lambda2;

	Mat M = (iT)*(theta_mat)*(iphi_mat)*\
		(lambda_mat)*(phi_mat)*(T);
	Mat dst;
	vector<Point2d> vetexes{ {0.,0.},{0.,(double)height},{ (double)width,0.},{ (double)width,(double)height} };
	vector<Point2d> after;
	
	cv::perspectiveTransform(vetexes, after, M);
	auto bbox = BBox(after);
	cv::warpPerspective(input, dst, M, sz);

	return dst;
}

Mat GenAffine(Mat input, double theta, double phi, double lambda1, double lambda2,Mat& H)
{
	int height = input.rows;
	int width = input.cols;

	Mat T = Mat::eye({ 3,3 }, CV_64F);
	T.at<double>(0, 2) = -width / 2;
	T.at<double>(1, 2) = -height / 2;

	Mat theta_mat = GenRoatationMatrix(theta);
	Mat phi_mat = GenRoatationMatrix(phi);
	Mat iphi_mat = GenRoatationMatrix(-phi);
	Mat lambda_mat = Mat::eye({ 3,3 }, CV_64F);
	lambda_mat.at<double>(0) = lambda1;
	lambda_mat.at<double>(1, 1) = lambda2;


	Mat M = (theta_mat)*(iphi_mat)*\
		(lambda_mat)*(phi_mat)*(T);
	Mat dst;
	vector<Point2d> vetexes{ { 0.,0. },{ 0.,(double)height },{ (double)width,0. },{ (double)width,(double)height } };
	vector<Point2d> after;
	Mat iT = Mat::eye({ 3,3 }, CV_64F);

	cv::perspectiveTransform(vetexes, after, M);
	auto bbox = BBox(after);
	iT.at<double>(0,2) = -bbox.first.x;
	iT.at<double>(1,2) = -bbox.first.y;
	M = iT*M;
	width = bbox.second.x - bbox.first.x;
	height = bbox.second.y - bbox.first.y;
	cv::warpPerspective(input, dst, M, {width,height});
  H = M;
	return dst;
}

double Angle2Radian(double angle)
{
	return angle / 180 * M_PI;
}


Mat AffineGenerator::Generate(const Mat& img,Mat& H)
{
	std::random_device rd;
	static std::default_random_engine thetae(rd()),phie(rd()),lambdae1(rd()),lambdae2(rd());
	static std::uniform_real_distribution<> u1(mintheta, maxtheta),u2(minphi,maxphi),\
		u3(minlambda,maxlambda),u4(minlambda,maxlambda);
	double theta = u1(thetae);
	double phi = u2(phie);
	double lambda1 = u3(lambdae1);
	double lambda2 = u4(lambdae2);

	return  GenAffine(img, theta, phi, lambda1, lambda2,H);
}


void GenMutiViewImg(const Mat& img,int num)
{
	Mat groundTruth = Mat::zeros(480, 640, CV_8UC3);
	AffineGenerator affg;
    fstream f;
    f.open("../train_data/labels.txt",std::ios::out);
	for(int i=0;i<num;i++)
	{
		Mat tempH;
		Mat temp = affg.Generate(img,tempH);
		char filename[50];
		for (int j = 0; j < 9; ++j) 
		{
			f<<tempH.at<double>(j)<<" ";
		}
		f<<std::endl;
		std::cout<<i<<std::endl;
		int h = temp.rows < 480 ? temp.rows : 480;
		int w = temp.cols < 640 ? temp.cols : 640;
		auto patch = GetPatch(temp, { 0,0 }, w, h);
		sprintf(filename, "../train_data/%d.jpg", i);
		auto eimg = embed(groundTruth, patch, { 0,0 });
		cv::imwrite(filename,convertToGray(eimg));
		std::cout << i << std::endl;
	}
    f.close();
}


