#pragma once
#ifndef LINKEDLISTDOUBLE_HPP
#define LINKEDLISTDOUBLE_HPP

#include <vector>

using namespace std;

class DoubleLinkedList {
protected:
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

	/**
	* \brief Default Constructor - Empty list
	*/
	DoubleLinkedList() {
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
	DoubleLinkedList(int elem) {
		head_m = new Node(elem, nil, nil);
		size_m = 1;
	}

	/**
	* \brief Constructs a list from a given input vector
	*/
	DoubleLinkedList(vector<int>& vec) {
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
	
	/**
	* \brief Constructs a list from a given input array
	*/
	DoubleLinkedList(int vec[], int size) {
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
	* \brief Destructor
	*/
	~DoubleLinkedList() {
		while (head_m != nil) {
			Node* temp = head_m;
			head_m = head_m->next();
			delete temp;
		}
		size_m = 0;
	}

	/**
	* \brief Searches iteratively for the first node with the given elem
	* \return The position of that node (starts from 1)
	*/
	int search_elem(int elem) {
		int pos = 1;
		Node* cur = head_m;

		while (cur->elem() != elem && cur != nil) {
			++pos;
			cur = cur->next();
		}

		return pos;
	}

	/**
	* \brief Searches iteratively for the given position
	* \return The elem of that position
	*/
	int search_pos(int pos) { return search_node(pos)->elem(); }

	/**
	* \brief Inserts elem at pos
	*/
	void insert_elem(int elem, int pos) {
		// Empty list
		if (size_m == 0) DoubleLinkedList(elem);

		// At the head
		else if (pos == 1) push_front(elem);

		// At the end
		else if (pos == size_m) push_back(elem);

		// General case (in middle)
		else {
			Node* cur = search_node(pos);
			Node* new_node = new Node(elem, cur, cur->next());
			cur->set_next(new_node);
			cur->next()->set_prev(new_node);
			++size_m;
		}
	}

	/**
	* \brief Gets the node of position via search_node, and deletes elem
	*/
	void delete_elem(int pos = 1) {
		// Empty list
		if (size_m == 0) cerr << "ERROR: Empty List" << endl;

		// At the head
		else if (pos == 1) pop_front();

		// At the end
		else if (pos == size_m) pop_back();

		// General case (in middle)
		else {
			Node* cur = search_node(pos);
			cur->prev()->set_next(cur->next());
			cur->next()->set_prev(cur->prev());
			delete cur;
			--size_m;
		}
	}

	/**
	* \brief Deletes the entire list
	*/
	void delete_list() {
		this->~DoubleLinkedList();
		if (head_m != NULL) delete head_m;}

	/**
	* \brief Pushes elem to the front
	*/
	void push_front(int elem) {
		Node* new_head = new Node(elem, nil, head_m);
		nil->set_next(new_head);
		head_m->set_prev(new_head);
		head_m = new_head;
		++size_m;
	}

	/**
	* \brief Pushes elem to the back
	*/
	void push_back(int elem) {
		Node* tail = nil->prev();
		Node* new_tail = new Node(elem, tail, nil);
		tail->set_next(new_tail);
		nil->set_prev(new_tail);
		++size_m;
	}

	/**
	* \brief Pops the head
	*/
	int pop_front() {
		int res = head_m->elem();

		// One element list
		if (size_m == 1) {
			delete head_m;
			head_m = nil;
		}

		else {
			Node* new_head = head_m->next();
			nil->set_next(new_head);
			new_head->set_prev(nil);
			delete head_m;
			head_m = new_head;
		}

		--size_m;

		return res;
	}

	/**
	* \brief Pops the tail
	*/
	int pop_back() {
		Node* tail = nil->prev();
		Node* new_tail = tail->prev();
		int res = tail->elem();

		nil->set_prev(new_tail);
		new_tail->set_next(nil);

		delete tail;
		--size_m;

		return res;
	}

	/**
	* \brief Iteratively prints the list. Print nil if empty or end of list
	*/
	void print_list(std::ostream& os = std::cout) {
		Node* cur = head_m;
		while (cur != nil) {
			os << cur->elem() << " <-> ";
			cur = cur->next();
		}
		os << "nil <-> head" << endl;
	}

	/**
	* \brief Get list size
	*/
	int size() { return size_m; }

	/**
	* \brief Get head element
	*/
	int head() { return head_m->elem(); }

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