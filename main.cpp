#include <iostream>
#include <vector>
#include <fstream>
#include "linkedlistsingle.hpp"
#include "heap.hpp"
#include "heapsort.hpp"

using namespace std;

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

	vector<int> test = { 1, 2, 3, 4, 5 };
	vector<int> test1 = { 5, 14, 10, 8, 7, 9, 3, 2, 4, 1 };
	vector<int> test2 = { 4, 1, 3, 2, 16, 9, 10, 14, 8, 7 };
	vector<int> test3 = { 12, 8, 5, 6, 7, 1, 0, 4, 1, 3 };
	vector<int> test4 = { 9, 8, 5, 6, 7, 1, 0, 4, 1, 3 };

	// List Test
	cout << "List Tests" << endl;
	cout << "Initialization and print: " << endl;
	SingleLinkedList slist(test);
	slist.print_list();
	cout << endl;
	cout << "Delete all and print: " << endl;
	slist.delete_list();
	slist.print_list();
	cout << endl;

	// Heap Test
	cout << "Heap Tests" << endl;
	Heap heap3(test3);
	heap3.insert(10);
	Heap heap4(test4);
	int heap4max = heap4.pop_max();
	cout << endl;

	// Sorting Test
	cout << "Sorting Tests" << endl;
	//heapsort(vec2);
	//heapsort_desc(test);
	//heapsort_desc(test2);


	return 0;
}