#ifndef _SHELL_SORT_HPP_
#define _SHELL_SORT_HPP_

#include <cstdint>
#include <vector>

void shell_sort(std::vector<size_t>::iterator begin, std::vector<size_t>::iterator end)
{
	ssize_t h = 1;

	while (h < end - begin) {
		h = 3 * h + 1;
	}

	h /= 3;

	while (h > 0) {
		for (auto i = begin + h; i != end; ++i) {
			auto x = *i;
			auto j = i;

			while (j >= h + begin && *(j - h) > x) {
				*j = *(j - h);
				j -= h;
			}

			*j = x;
		}
		h /= 3;
	}
}

#endif
