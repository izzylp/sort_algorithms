#ifndef _SELECTION_SORT_HPP_
#define _SELECTION_SORT_HPP_

#include <cstdint>
#include <vector>
#include <algorithm>

void selection_sort(std::vector<size_t>::iterator begin, std::vector<size_t>::iterator end)
{
	for (auto i = begin; i != end - 1; ++i) {
		auto menor = i;
		for (auto j = i + 1; j != end; ++j) {
			if (*j < *menor) {
				menor = j;
			}
		}
		std::iter_swap(i, menor);
	}
}

#endif
