#pragma once
#ifndef HEAPSORT_HPP
#define HEAPSORT_HPP

#include "heap.hpp"

void heapsort(vector<int>& vec) {
	Heap heap(vec);
	vec = heap.sort();
}

void heapsort_desc(vector<int>& vec) {
	Heap heap(vec);
	vec = heap.sort_desc();
}

#endif /* HEAPSORT_HPP */