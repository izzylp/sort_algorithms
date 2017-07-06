#ifndef _MERGE_SORT_HPP_
#define _MERGE_SORT_HPP_

#include <cstdint>
#include <vector>
#include <algorithm>

/* Baseado no Sedgewick */
static void merge_(size_t *aux, std::vector<size_t>::iterator lo, std::vector<size_t>::iterator mid, std::vector<size_t>::iterator hi)
{
	if (*mid <= *(mid + 1)) {
		return;
	}

	for (ssize_t k = 0; k < hi - lo + 1; ++k) {
		aux[k] = *(lo + k);
	}

	auto i = lo;
	auto j = mid + 1;
	for (ssize_t k = 0; k <= hi - lo; ++k) {
		if (i - lo > mid - lo) {
			*(lo + k) = aux[j++ - lo];
		} else if (j - lo > hi - lo) {
			*(lo + k) = aux[i++ - lo];
		} else if (aux[j - lo] < aux[i - lo]) {
			*(lo + k) = aux[j++ - lo];
		} else {
			*(lo + k) = aux[i++ - lo];
		}
	}
}

/* 
 * Tentativa de in-place mergesort 
 * Pessima performance 
 */
static void merge__(std::vector<size_t>::iterator lo, std::vector<size_t>::iterator mid, std::vector<size_t>::iterator hi)
{
	auto lo_2 = mid + 1;

	if (*mid <= *(lo_2)) {
		return;
	}

	while (lo != lo_2) {
		if ((lo_2 != hi + 1) && (*lo > *(lo_2))) {
			auto lo_prev = *lo;
			*lo = *lo_2;
			++lo_2;
			/* Rellocate lo values */
			for (auto i = lo + 1; i != lo_2; ++i) {
				std::swap(*i, lo_prev);
			}
		}
		++lo;
	}
}

static void merge_sort_(size_t *aux, std::vector<size_t>::iterator lo, std::vector<size_t>::iterator hi)
{
	if (lo == hi) {
		return;
	}

	auto mid = lo + (hi - lo) / 2;

	merge_sort_(aux, lo, mid);
	merge_sort_(aux, mid + 1, hi);
	merge_(aux, lo, mid, hi);
}

void merge_sort(std::vector<size_t>::iterator begin, std::vector<size_t>::iterator end)
{
	size_t *aux = new size_t[end - begin];
	merge_sort_(aux, begin, end - 1);
	delete[] aux;
}

#endif
