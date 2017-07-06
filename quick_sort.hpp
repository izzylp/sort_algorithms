#ifndef _QUICK_SORT_HPP_
#define _QUICK_SORT_HPP_

#include <cstdint>
#include <vector>
#include <algorithm>

/* Baseado no Sedgewick */
std::vector<size_t>::iterator partition_(std::vector<size_t>::iterator lo, std::vector<size_t>::iterator hi)
{
	auto i = lo;
	auto j = hi + 1;

	for (;;) {
		while (*(++i) < *lo) {
			if (i == hi) {
				break;
			}
		}

		while (*lo < *(--j));

		if (i - j >= 0) {
			break;
		}
		std::swap(*i, *j);
	}
	std::swap(*lo, *j);

	return j;
}

void quick_sort_(std::vector<size_t>::iterator lo, std::vector<size_t>::iterator hi)
{
	if (hi - lo <= 0) {
		return;
	}

	auto j = partition_(lo, hi);

	quick_sort_(lo, j - 1);
	quick_sort_(j + 1, hi);
}

/* In place quick sort */
void quick_sort(std::vector<size_t>::iterator begin, std::vector<size_t>::iterator end)
{
	quick_sort_(begin, end - 1);
}

#endif
