#pragma once
#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <vector>
#include <algorithm>

class Queue {

	class Node {
	public:
		// Constructors
		Node(){}
		Node(int elem, Node* prev, Node* next) : elem_m(elem), prev_m(prev), next_m(next){}

		// Getter
		Node* prev() { return prev_m; }
		Node* next() { return next_m; }
		int elem() { return elem_m; }

		// Setter
		void set_prev(Node* prev) { prev_m = prev; }
		void set_next(Node* next) { next_m = next; }
		void set_elem(int elem) { elem_m = elem; }

	private:
		// Members
		Node* prev_m;
		Node* next_m;
		int elem_m;
	};

	// Sentinel Node
	class Nil : public Node {
	public:
		Nil() {
			NULL;
		}
	};

public:
	// Constructors

	/**
	* \brief Default Constructor - Empty Queue
	*/
	Queue() {
		head_m = new Node;
		nil = new Nil;
		head_m->set_next(nil);
		head_m->set_prev(nil);
		nil->set_next(head_m);
		nil->set_prev(head_m);

		size_m = 0;
	}

	/**
	* \brief Construct with one head.
	*/
	Queue(int elem) {
		head_m = new Node(elem, nil, nil);
		size_m = 1;
	}

	/**
	* \brief Constructs a list from a given input array
	*/
	Queue(int vec[], int size) {
		head_m = new Node;
		nil = new Nil;
		head_m->set_prev(nil);
		nil->set_next(head_m);
		Node* cur = head_m;

		size_m = size;

		for (int i = 0; i < size; ++i) {
			cur->set_elem(vec[i]);
			if (i == size - 1) {
				cur->set_next(nil);
				nil->set_prev(cur);
			}
			else {
				cur->set_next(new Node);
				cur->next()->set_prev(cur);
				cur = cur->next();
			}
		}
	}

	/**
	* \brief Constructs a list from a given input vector
	*/
	Queue(vector<int>& vec) {
		head_m = new Node;
		nil = new Nil;
		head_m->set_prev(nil);
		nil->set_next(head_m);
		Node* cur = head_m;

		size_m = vec.size();

		for (int i = 0; i < vec.size(); ++i) {
			cur->set_elem(vec[i]);
			if (i == vec.size() - 1) {
				cur->set_next(nil);
				nil->set_prev(cur);
			}
			else {
				cur->set_next(new Node);
				cur->next()->set_prev(cur);
				cur = cur->next();
			}
		}
	}

	~Queue() {
		while (head_m != nil) {
			Node* temp = head_m;
			head_m = head_m->next();
			delete temp;
		}
		size_m = 0;
	}

	/**
	* \brief Inserts elem into the queue
	*/
	void enqueue(int elem) {
		Node* tail = nil->prev();
		Node* new_tail = new Node(elem, tail, nil);
		tail->set_next(new_tail);
		nil->set_prev(new_tail);
	}

	/**
	* \brief Deletes the head
	*/
	int dequeue() {
		int res = head_m->elem();
		Node* new_head = head_m->next();
		nil->set_next(new_head);
		new_head->set_prev(nil);
		delete head_m;
		head_m = new_head;
		return res;
	}

	void delete_queue() { this->~Queue(); }

	/**
	* \brief Returns the element in the queue at the given position (starting from 1)
	*/
	int search(int pos) {
		Node* cur = head_m;
		while (pos > 1 && cur != nil && size_m > 0) {
			cur = cur->next();
			--pos;
		}
		return cur->elem();
	}

	/**
	* \brief checks whether the queue is empty
	*/
	bool is_empty() { return size_m == 0; }

	/**
	* \brief Iteratively prints the list. Print nil if empty or end of list
	*/
	void print_queue(std::ostream& os = std::cout) {
		Node* cur = head_m;
		while (cur != nil) {
			os << cur->elem() << " <-> ";
			cur = cur->next();
		}
		os << "nil <-> head" << endl;
	}

private:
	// Members
	Node* head_m;
	Nil* nil;
	int size_m;

};


#endif /* QUEUE_HPP */