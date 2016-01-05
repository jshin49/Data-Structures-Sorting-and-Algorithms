#pragma once
#ifndef HEAP_HPP
#define HEAP_HPP

#include <vector>
#include <algorithm>

using namespace std;

typedef vector<int> Array;

class Heap {
public:
	Heap() { cerr << "No input array" << endl; }
	Heap(Array& input) : arr_m(input), size_m(input.size()) { }

	/**
	* \brief builds a max heap from unsorted array arr_m
	* \return Max Heap
	*/
	Array build_max_heap() {
		for (int i = parent(size_m-1); i >= 0; --i)
			max_heapify(i, size_m - 1);
		return arr_m;
	}

	/**
	* \brief builds a min heap from an unsorted array arr_m
	* \return Min Heap
	*/
	Array build_min_heap() {
		for (int i = parent(size_m - 1); i >= 0; --i)
			min_heapify(i, size_m - 1);
		return arr_m;
	}


	// Priority Queue Implementations

	/**
	* \brief inserts element key into arr_m
	*/
	void insert(int key) {
		arr_m.push_back(numeric_limits<int>::min());
		increase_key(size_m, key);
		++size_m;
	}

	/**
	* \brief increases key value
	*/
	void increase_key(int i, int key) {
		if (key < arr_m[i]) cerr << "new key is smaller than current key" << endl;
		arr_m[i] = key;
		while (i > 0 && arr_m[parent(i)] < arr_m[i]) {
			swap(arr_m[i], arr_m[parent(i)]);
			if (parent(i) == 0 && arr_m[parent(i)] < arr_m[i])
				swap(arr_m[i], arr_m[parent(i)]);
			i = parent(i);
		}
	}

	/**
	* \brief pops max of arr_m
	*/
	int pop_max() {
		int maximum = max();
		--size_m;
		arr_m[0] = arr_m[size_m];
		max_heapify(0, size_m);
		return maximum;
	}

	/**
	* \brief pops min of arr_m
	*/
	int pop_min() {
		int minimum = min();
		--size_m;
		arr_m[0] = arr_m[size_m];
		min_heapify(0, size_m);
		return minimum;
	}

	/**
	* \brief returns max of arr_m
	*/
	int max() {
		if (size_m == 0) cerr << "Heap underflow" << endl;
		return arr_m[0];
	}

	/**
	* \brief returns min of arr_m
	*/
	int min() {
		if (size_m == 0) cerr << "Heap underflow" << endl;
		return arr_m[0];
	}


	// Heapsort

	/**
	* \brief heapsorts in an ascending order using max heap property
	*/
	Array sort() {
		build_max_heap();
		for (int i = size_m - 1; i > 0; --i) {
			swap(arr_m[0], arr_m[i]);
			max_heapify(0, i - 1);
		}
		return arr_m;
	}

	/**
	* \brief heapsorts in a descending order using min heap property
	*/
	Array sort_desc() {
		build_min_heap();
		for (int i = size_m - 1; i > 0; --i) {
			swap(arr_m[0], arr_m[i]);
			min_heapify(0, i - 1);
		}
		return arr_m;
	}

	void print_heap(std::ostream& os = std::cout) {
		if (size_m == 0) {
			os << "ERROR: Empty Heap" << endl;
			return;
		}
		for (int i = 0; i < size_m; ++i)
			os << arr_m[i] << " ";
		os << endl;
	}

private:
	// Members
	Array arr_m;
	int size_m;


	// Heapify

	/**
	* \brief Max heapifies the tree rooted at arr_m[i]
	*/
	void max_heapify(int i, int n) {
		int l = left(i);
		int r = right(i);
		int largest;

		if (l <= n && arr_m[l] > arr_m[i])
			largest = l;
		else
			largest = i;

		if (r <= n && arr_m[r] > arr_m[largest])
			largest = r;

		if (largest != i)	{
			swap(arr_m[i], arr_m[largest]);
			max_heapify(largest, n);
		}
	}

	/**
	* \brief Min heapifies the tree rooted at arr_m[i]
	*/
	void min_heapify(int i, int n) {
		int l = left(i);
		int r = right(i);
		int smallest;

		if (l <= n && arr_m[l] < arr_m[i])
			smallest = l;
		else
			smallest = i;

		if (r <= n && arr_m[r] < arr_m[smallest])
			smallest = r;

		if (smallest != i) {
			swap(arr_m[i], arr_m[smallest]);
			min_heapify(smallest, n);
		}
	}


	// Helper functions
	int left(int i) { return 2 * i + 1; }
	int right(int i) { return 2 * i + 2; }
	bool isEven(int i) { return (i % 2 == 0); }

	int parent(int i) {
		if (i > 2) return isEven(i) ? i / 2 - 1 : i / 2;
		else return 0;
	}

};
#endif /* HEAP_HPP */