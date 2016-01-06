#pragma once
#ifndef LINKEDLISTSINGLE_HPP
#define LINKEDLISTSINGLE_HPP

#include <vector>
#include <algorithm>

using namespace std;

class SingleLinkedList {

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

	/**
	* \brief Default Constructor - Empty list
	*/
	SingleLinkedList() { 
		head_m = new Node(nil);
		size_m = 0;
	}

	/**
	* \brief Construct with one head.
	*/
	SingleLinkedList(int elem) {
		head_m = new Node(elem, nil);
		size_m = 1;
	}

	/**
	* \brief Constructs a list from a given input array
	*/
	SingleLinkedList(int vec[], int size) {
		head_m = new Node;
		Node* cur = head_m;
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
	* \brief Constructs a list from a given input vector
	*/
	SingleLinkedList(vector<int>& vec) {
		head_m = new Node;
		Node* cur = head_m;
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

	/**
	* \brief Destructor
	*/
	~SingleLinkedList() {
		while (head_m != nil) {
			Node* temp = head_m;
			head_m = head_m->next();
			delete temp;
		}
		size_m = 0;
	}

	// Search, Insert, Delete

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
		if (size_m == 0) SingleLinkedList(elem);

		// At the head
		else if (pos == 1) push_front(elem);

		// At the end
		else if (pos == size_m) push_back(elem);

		// General case (in middle)
		else {
			Node* prev = search_prev_node(pos);
			Node* cur = new Node;
			cur->set_elem(elem);
			cur->set_next(prev->next());
			prev->set_next(cur);
			++size_m;
		}
	}

	/**
	* \brief Gets the previous node of position via search_node, and deletes elem
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
			Node* prev = search_prev_node(pos);
			Node* cur = prev->next();
			prev->set_next(cur->next());
			delete cur;
			--size_m;
		}
	}

	/**
	* \brief Deletes the entire list
	*/
	void delete_list() { this->~SingleLinkedList(); }

	/**
	* \brief Pushes elem to the front
	*/
	void push_front(int elem) {
		++size_m;
		Node* new_head = new Node;
		new_head->set_elem(elem);
		new_head->set_next(head_m);
		head_m = new_head;
	}

	/**
	* \brief Pushes elem to the back
	*/
	void push_back(int elem) {
		Node* tail = search_node(size_m);
		Node* new_tail = new Node;
		new_tail->set_elem(elem);
		new_tail->set_next(nil);
		tail->set_next(new_tail);
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
		Node* new_tail = search_prev_node(size_m);
		Node* tail = new_tail->next();
		new_tail->set_next(nil);
		int res = tail->elem();
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
			os << cur->elem() << " -> ";
			cur = cur->next();
		}
		os << "nil" << endl;
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

	/**
	* \brief Searches iteratively for the node at the given position (starts from 1)
	* \return The preceding node
	*/
	Node* search_prev_node(int pos) {
		Node* res = head_m;
		while (pos > 2 && res != nil) {
			--pos;
			res = res->next();
		}
		return res;
	}

};

#endif /* LINKEDLISTSINGLE_HPP */