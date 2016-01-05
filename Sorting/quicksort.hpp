#include <vector>
#include <algorithm>

//// Quick Sort

//int median3(int a, int b, int c) {
//	return max(min(a, b), min(max(a, b), c));
//}
//
//int choosePivot(int l, int r) {
//	return r / 2;// median3(l, r, (l + r) / 2);
//}
//
//int partition(vector<int>& vec, int l, int r) {
//	int pi = choosePivot(l, r);
//	int pivot = vec[pi];
//	
//	// swap pivot with the beginning
//	swap(vec[pi], vec[l]); 
//
//	// beginning index of the right side of the pivot (larger than the pivot)
//	int i = l + 1;
//
//	// partition around the pivot
//	for (int j = l+1; j <= r; ++j) {
//		if (vec[j] <= pivot) {
//			swap(vec[i], vec[j]);
//			++i;
//		}
//	}
//
//	// swap pivot back to its position
//	swap(vec[l], vec[i - 1]);
//
//	// return pivot position
//	return i - 1;
//}
//
//void quicksort(vector<int>& vec, int l, int r, int& count) {
//	if (l < r) {
//		count += r - l;
//		int p = partition(vec, l, r);
//		quicksort(vec, l, p - 1, count);
//		quicksort(vec, p + 1, r, count);
//	}
//}