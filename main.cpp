#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include "linkedlistsingle.hpp"
#include "heap.hpp"
#include "heapsort.hpp"

using namespace std;
//// Quick Sort

int median3(int a, int b, int c) {
	return max(min(a, b), min(max(a, b), c));
}

int choosePivot(int l, int r) {
	return r / 2;// median3(l, r, (l + r) / 2);
}

int partition(vector<int>& vec, int l, int r) {
	int pi = choosePivot(l, r);
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

void quicksort(vector<int>& vec, int l, int r, int& count) {
	if (l < r) {
		count += r - l;
		int p = partition(vec, l, r);
		quicksort(vec, l, p - 1, count);
		quicksort(vec, p + 1, r, count);
	}
}

int main() {		
	ifstream infile("IntegerArray1-100000.txt"); 
	int a;
	vector<int> vec1;
	vec1.reserve(100000);
	while (infile >> a)
		vec1.push_back(a);

	ifstream infile2("IntegerArray1-10000.txt");
	vector<int> vec2;
	vec2.reserve(10000);
	while (infile >> a)
		vec2.push_back(a);

	vector<int> test = { 1,2,3,4,5 };
	vector<int> test1 = { 5, 14, 10, 8, 7, 9, 3, 2, 4, 1 };
	vector<int> test2 = { 4, 1, 3, 2, 16, 9, 10, 14, 8, 7 };
	vector<int> test3 = { 12, 8, 5, 6, 7, 1, 0, 4, 1, 3 };
	vector<int> test4 = { 9, 8, 5, 6, 7, 1, 0, 4, 1, 3 };
	//heapsort(vec2);
	//heapsort_desc(test);
	//heapsort_desc(test2);
	SingleLinkedList slist(test);
	slist.delete_list();
	Heap heap3(test3);
	heap3.insert(10);
	Heap heap4(test4);
	int heap4max = heap4.pop_max();

	return 0;
}