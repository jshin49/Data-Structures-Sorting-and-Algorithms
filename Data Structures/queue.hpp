#pragma once
#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <vector>
#include <algorithm>

class Queue {

	class Node {
	public:
		//Constructors
		Node(){}
		Node(Node* next) : next_m(next){}
		Node(int elem, Node* next) : elem_m(elem), next_m(next){}

		// Getter
		Node* next() { return next_m; }
		int elem() { return elem_m; }

		// Setter
		void set_next(Node* next) { next_m = next; }
		void set_elem(int elem) { elem_m = elem; }

	private:
		// Members
		Node* next_m;
		int elem_m;
	};

	// Sentinel Node
	class Nil : public Node {};

public:
	// Constructors
	Queue() {
		head_m = new Node;
		size_m = 0;
	}
	Queue(vector<int>& vec) {}
	~Queue() {}

	// Insert

	// Remove

	// is_empty

private:
	// Members
	Node* head_m;
	int size_m;

};


#endif /* QUEUE_HPP */