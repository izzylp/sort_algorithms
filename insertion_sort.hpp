#ifndef _INSERTION_SORT_HPP_
#define _INSERTION_SORT_HPP_

#include <cstdint>
#include <vector>
#include <algorithm>

void insertion_sort(std::vector<size_t>::iterator begin, std::vector<size_t>::iterator end)
{
	for (auto i = begin + 1; i != end; ++i) {
		auto x = *i;
		auto j = i;

		while (j >= 1 + begin && *(j - 1) > x) {
			*j = *(j - 1);
			--j;
		}

		*j = x;
	}
}

#endif
