#pragma once
#ifndef LINKEDLISTDOUBLE_HPP
#define LINKEDLISTDOUBLE_HPP

#include <vector>
#include <algorithm>

using namespace std;

class DoubleLinkedList {

	class Node {

	public:
		// Getter
		Node* next() { return next_m; }
		int elem() { return elem_m; }

		// Setter
		void set_next(Node* next) { next_m = next; }
		void set_elem(int elem) { elem_m = elem; }

	private:
		Node* next_m;
		int elem_m;
	};

	// Sentinel Node
	class Nil : public Node {};

public:
	
private:

};

#endif /* LINKEDLISTDOUBLE_HPP */