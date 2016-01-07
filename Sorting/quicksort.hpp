#include <vector>
#include <cmath>
#include <algorithm>
#include <stdlib.h>
#include <time.h>

// Quick Sort
using namespace std;

int median3(int a, int b, int c, int ai, int bi, int ci) {
	int median = max(min(a, b), min(max(a, b), c));
	if (median == a) return ai;
	else if (median == b) return bi;
	else return ci;
}

int choosePivot(vector<int>& vec, int l, int r) {
	// random choose median 3
	//srand(time(NULL));
	//int rand1 = rand() % (r - l) + l;
	//int rand2 = rand() % (r - l) + l;
	//int rand3 = rand() % (r - l) + l;

	//return median3(rand1, rand2, rand3);
	int mid = (r + l) / 2;
	return median3(vec[l], vec[r], vec[mid], l, r, mid);
}

int partition(vector<int>& vec, int l, int r) {
	int pi = choosePivot(vec, l, r);
	int pivot = vec[pi];
	
	// swap pivot with the beginning
	swap(vec[pi], vec[l]); 

	// beginning index of the right side of the pivot (larger than the pivot)
	int i = l + 1;

	// partition around the pivot
	for (int j = l+1; j <= r; ++j) {
		if (vec[j] <= pivot) {
			swap(vec[i], vec[j]);
			++i;
		}
	}

	// swap pivot back to its position
	swap(vec[l], vec[i - 1]);

	// return pivot position
	return i - 1;
}

int quicksort(vector<int>& vec, int l, int r, int& count) {
	// cutoff to insertion sort

	// general case
	if (l < r) {
		count += r - l;
		int p = partition(vec, l, r);
		quicksort(vec, l, p - 1, count);
		quicksort(vec, p + 1, r, count);
	}
	return count;
}