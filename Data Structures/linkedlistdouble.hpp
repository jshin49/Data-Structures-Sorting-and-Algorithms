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
		Node* prev() { return prev_m; }
		Node* next() { return next_m; }
		int elem() { return elem_m; }

		// Setter
		void set_prev(Node* prev) { prev_m = prev; }
		void set_next(Node* next) { next_m = next; }
		void set_elem(int elem) { elem_m = elem; }

	private:
		Node* prev_m;
		Node* next_m;
		int elem_m;
	};

	// Sentinel Node
	class Nil : public Node {};

public:

	/**
	* \brief Iteratively prints the list. Print nil if empty or end of list
	*/
	void print_list(std::ostream& os = std::cout) {
		Node* cur = head_m;
		while (cur != nil) {
			os << cur->elem() << " -> ";
			cur = cur->next();
		}
		os << "nil" << endl;
	}

private:
	// Members
	Node* head_m;
	Nil* nil;
	int size_m;

	// Helpers

	/**
	* \brief Searches iteratively for the node at the given position (starts from 1)
	* \return The node at the given position
	*/
	Node* search_node(int pos) {
		Node* res = head_m;
		while (pos > 1 && res != nil) {
			--pos;
			res = res->next();
		}
		return res;
	}
};

#endif /* LINKEDLISTDOUBLE_HPP */