#pragma once
#ifndef STACK_HPP
#define STACK_HPP

#include <vector>

using namespace std;

class Stack {
protected:
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
		Node* next_m;
		int elem_m;
	};

	// Sentinel Node
	class Nil : public Node {};


public:
	// Constructors

	/**
	* \brief Default Constructor - Empty Queue
	*/
	Stack() {
		top_m = new Node(nil);
		size_m = 0;
	}

	/**
	* \brief Construct with one head.
	*/
	Stack(int elem) {
		top_m = new Node(elem, nil);
		size_m = 1;
	}

	/**
	* \brief Constructs a stack from a given input array
	*/
	Stack(int vec[], int size) {
		top_m = new Node;
		Node* cur = top_m;
		size_m = size;
		for (int i = 0; i < size; ++i) {
			cur->set_elem(vec[i]);
			if (i == size - 1)
				cur->set_next(nil);
			else {
				cur->set_next(new Node);
				cur = cur->next();
			}
		}
	}

	/**
	* \brief Constructs a stack from a given input vector
	*/
	Stack(vector<int>& vec) {
		top_m = new Node;
		Node* cur = top_m;
		size_m = vec.size();
		for (int i = 0; i < vec.size(); ++i) {
			cur->set_elem(vec[i]);
			if (i == vec.size() - 1)
				cur->set_next(nil); // end of list
			else {
				cur->set_next(new Node);
				cur = cur->next();
			}
		}
	}

	~Stack() {
		while (top_m != nil) {
			Node* temp = top_m;
			top_m = top_m->next();
			delete temp;
		}
		size_m = 0;
	}

	/**
	* \brief Pushes elem to the top
	*/
	void push(int elem) {
		Node* new_top = new Node(elem, top_m);
		top_m = new_top;
		++size_m;
	}

	/**
	* \brief Pops the top elem
	*/
	int pop() {
		int res = top_m->elem();
		Node* new_top = top_m->next();
		delete top_m;
		top_m = new_top;
		--size_m;
		return res;
	}

	/**
	* \brief Returns the element in the stack at the given position (starting from 1)
	*/
	int search(int pos) {
		Node* cur = top_m;
		while (pos > 1 && cur != nil && size_m > 0) {
			cur = cur->next();
			--pos;
		}
		return cur->elem();
	}

	/**
	* \brief Checks whether the stack is empty
	*/
	bool is_empty() { return size_m == 0; }

	/**
	* \brief Deletes the entire stack
	*/
	void delete_stack() { this->~Stack(); }

	/**
	* \brief Iteratively prints the top_m. Print nil if empty or end of top_m
	*/
	void print_stack(std::ostream& os = std::cout) {
		Node* cur = top_m;
		while (cur != nil) {
			os << cur->elem() << " -> ";
			cur = cur->next();
		}
		os << "nil" << endl;
	}

	/**
	* \brief Get stack size
	*/
	int size() { return size_m; }

	/**
	* \brief Get top element
	*/
	int top() { return top_m->elem(); }

private:
	// Members
	Node* top_m;
	Nil* nil;
	int size_m;

};

#endif /* STACK_HPP */