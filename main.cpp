/* Compile and run: g++ -std=c++11 -W -Wall -O3 -o main main.cpp && ./main
 */

#include <iostream>
#include <cstdint>
#include <vector>
#include <algorithm>
#include <random>
#include <string>
#include <utility>
#include <chrono>

#include "selection_sort.hpp"
#include "insertion_sort.hpp"
#include "shell_sort.hpp"
#include "heap_sort.hpp"
#include "merge_sort.hpp"
#include "quick_sort.hpp"

std::vector<size_t> generate_unsorted_array(size_t n)
{
	std::vector<size_t> ret;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(1, 10 * n);

	for (size_t i = 0; i < n; ++i) {
		ret.push_back(dis(gen));
	}

	return ret;
}

std::vector<size_t> generate_sorted_asc_array(size_t n)
{
	std::vector<size_t> ret;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(1, 10 * n);

	for (size_t i = 0; i < n; ++i) {
		ret.push_back(dis(gen));
	}

	std::sort(ret.begin(), ret.end());

	return ret;
}

std::vector<size_t> generate_sorted_desc_array(size_t n)
{
	std::vector<size_t> ret;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(1, 10 * n);

	for (size_t i = 0; i < n; ++i) {
		ret.push_back(dis(gen));
	}

	std::sort(ret.rbegin(), ret.rend());

	return ret;
}

double run_time(size_t m, 
		void (*sort_function)(std::vector<size_t>::iterator, std::vector<size_t>::iterator), 
		std::vector<size_t>::iterator begin, 
		std::vector<size_t>::iterator end)
{
	double mean_time = 0.0;

	std::vector<size_t> input(begin, end);

	for (size_t i = 0; i < m; ++i) {
		std::vector<size_t> input_copy(input);
		std::chrono::time_point<std::chrono::steady_clock> t_start = std::chrono::steady_clock::now();
		//std::make_heap(input_copy.begin(), input_copy.end());
		sort_function(input_copy.begin(), input_copy.end());
		std::chrono::time_point<std::chrono::steady_clock> t_end = std::chrono::steady_clock::now();
		std::chrono::duration<double> elapsed_seconds = t_end - t_start;
		mean_time += elapsed_seconds.count();

		//if (!std::is_sorted(input_copy.begin(), input_copy.end())) {
		//	return -1;
		//}
	}

	mean_time /= m;
	return mean_time;
}

int main()
{
	const size_t m = 1000;
	const size_t n = 1000;

	std::vector<std::pair<std::string, std::vector<size_t> (*)(size_t)>> test;
	test.push_back(std::make_pair<std::string, std::vector<size_t> (*)(size_t)>("unsorted array", generate_unsorted_array));
	test.push_back(std::make_pair<std::string, std::vector<size_t> (*)(size_t)>("sorted asc array", generate_sorted_asc_array));
	test.push_back(std::make_pair<std::string, std::vector<size_t> (*)(size_t)>("sorted desc array", generate_sorted_desc_array));

	std::vector<std::pair<std::string, void (*)(std::vector<size_t>::iterator, std::vector<size_t>::iterator)>> sort_function;
	sort_function.push_back(std::make_pair<std::string, void (*)(std::vector<size_t>::iterator, std::vector<size_t>::iterator)>("selection_sort", selection_sort));
	sort_function.push_back(std::make_pair<std::string, void (*)(std::vector<size_t>::iterator, std::vector<size_t>::iterator)>("insertion_sort", insertion_sort));
	sort_function.push_back(std::make_pair<std::string, void (*)(std::vector<size_t>::iterator, std::vector<size_t>::iterator)>("shell_sort", shell_sort));
	sort_function.push_back(std::make_pair<std::string, void (*)(std::vector<size_t>::iterator, std::vector<size_t>::iterator)>("heap_sort", heap_sort));
	sort_function.push_back(std::make_pair<std::string, void (*)(std::vector<size_t>::iterator, std::vector<size_t>::iterator)>("merge_sort", merge_sort));
	sort_function.push_back(std::make_pair<std::string, void (*)(std::vector<size_t>::iterator, std::vector<size_t>::iterator)>("quick_sort", quick_sort));
	sort_function.push_back(std::make_pair<std::string, void (*)(std::vector<size_t>::iterator, std::vector<size_t>::iterator)>("std::sort", std::sort));
	sort_function.push_back(std::make_pair<std::string, void (*)(std::vector<size_t>::iterator, std::vector<size_t>::iterator)>("std::stable_sort", std::stable_sort));
	//sort_function.push_back(std::make_pair<std::string, void (*)(std::vector<size_t>::iterator, std::vector<size_t>::iterator)>("std::sort_heap", std::sort_heap));

	std::cout << n << "\n";
	for (size_t i = 0; i < test.size(); ++i) {
		std::vector<size_t> input = test[i].second(n);
		std::cout << test[i].first << std::endl;
		for (size_t j = 0; j < sort_function.size(); ++j) {
			//std::cout << sort_function[j].first << " ";
			double mean_time = run_time(m, sort_function[j].second, input.begin(), input.end());
			std::cout << mean_time << " ";
		}
		std::cout << std::endl;
	}

	return 0;
}
