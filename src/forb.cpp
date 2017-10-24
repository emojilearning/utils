#include <forb.h>

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