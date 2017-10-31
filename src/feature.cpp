//Author:emojilearning
//data:2017.9.22
#ifndef VISION_UTIL_FEATURE_H


#include <feature.h>
using namespace cv;
using namespace std;
void OrbMatchByKnn(Mat& desp_m, Mat& desp_i, vector<DMatch>& matches)
{

	if (desp_i.rows == 0 || desp_m.rows == 0)
		return;
	auto knn_matcher = BFMatcher::create(NORM_HAMMING);
	vector<vector<DMatch>> knn_matches;
	knn_matcher->knnMatch(desp_m, desp_i, knn_matches, 2);
	int i = 0;
	for (auto m = knn_matches.begin(); m != knn_matches.end(); m++)
	{
		if (m->size() == 1)
			matches.push_back((*m)[0]);
		else if(m->size()==2&&( (*m)[0].distance / (*m)[1].distance <= 1.0 / 1.5))
		{
			matches.push_back((*m)[0]);
		}
	}
}

void MarkMarker(const Mat& left, Mat& out, const Mat& H,  Scalar s)
{
	std::vector<Point2d> vetexes(4);
	std::vector<Point2d> obj_corners(4);
	obj_corners[0] = Point2d(0, 0); obj_corners[1] = Point2d(left.cols, 0);
	obj_corners[2] = Point2d(left.cols, left.rows); obj_corners[3] = Point2d(0, left.rows);
	if (H.data)
	{
		perspectiveTransform(obj_corners, vetexes, H);
		line(out, vetexes[0], vetexes[1], s, 4);
		line(out, vetexes[1], vetexes[2], s, 4);
		line(out, vetexes[2], vetexes[3], s, 4);
		line(out, vetexes[3], vetexes[0], s, 4);
	}
}

#endif // !VISION_UTIL_FEATURE_H
