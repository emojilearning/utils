#ifndef VISION_UTILS_NONVISIONALG_H
#define VISION_UTILS_NONVISIONALG_H
#include <vector>
class SubSetGenrator
{
public:
	SubSetGenrator(int dimonsion, int range) :dimonsion_(dimonsion), range_(range) {};
	std::vector<std::vector<int>> subsets;
	void ndpick(std::vector<int> subset, int d)
	{
		if (d >= dimonsion_)
		{
			subsets.push_back(subset);
			return;
		}
		for (size_t i = 0; i < range_; i++)
		{
			std::vector<int> s(subset);
			s.push_back(i);
			ndpick(s, d + 1);
		}
	}

	void generate()
	{
		std::vector<int> initial;
		ndpick(initial, 0);
	}
private:
	int dimonsion_;
	int range_;
};

#endif // !VISION_UTILS_NONVISIONALG_H
