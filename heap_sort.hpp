#ifndef _HEAP_SORT_HPP_
#define _HEAP_SORT_HPP_

#include <cstdint>
#include <vector>

static void fix_down_heap(std::vector<size_t>::iterator begin, std::vector<size_t>::iterator end, std::vector<size_t>::iterator i)
{
	auto v = *i;
	auto j = 2 * (i - begin) + begin + 1;

	while (j - begin < end - begin) {
		if ((j != end - 1) && (*j < *(j + 1))) {
			++j;
		}

		if (v > *j) {
			break;
		}

		*((j - begin - 1) / 2 + begin) = *j;
		j = 2 * (j - begin) + begin + 1;
	}
	*((j - begin - 1) / 2 + begin) = v;
}

void heap_sort(std::vector<size_t>::iterator begin, std::vector<size_t>::iterator end)
{
	for (auto k = (end - begin) / 2 + begin - 1; k != begin; --k) {
		fix_down_heap(begin, end, k);
	}
	fix_down_heap(begin, end, begin);

	for (auto i = end - 1; i != begin; --i) {
		std::iter_swap(begin, i);
		fix_down_heap(begin, i, begin);
	}
}

#endif
