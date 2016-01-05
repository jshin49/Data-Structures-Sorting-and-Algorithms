#pragma once
#ifndef LINKEDLISTSINGLE_HPP
#define LINKEDLISTSINGLE_HPP

#include <vector>
#include <algorithm>

using namespace std;

class SingleLinkedList {

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

	/**
	* \brief Default constructor with new Head.
	*/
	SingleLinkedList() { 
		head_m = new Node;
		head_m->set_next(nil);
		size_m = 0;
	}

	/**
	* \brief Constructor with one head.
	*/
	SingleLinkedList(int elem) {
		head_m = new Node;
		head_m->set_elem(elem);
		head_m->set_next(nil);
		size_m = 1;
	}

	/**
	* \brief Constructs a list from a given input array
	*/
	SingleLinkedList(int vec[], int size) {
		Node* cur = new Node;
		head_m = cur;
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
		Node* cur = new Node;
		head_m = cur;
		size_m = vec.size();
		for (int i = 0; i < vec.size(); ++i) {
			cur->set_elem(vec[i]);
			if (i == vec.size() - 1)
				cur->set_next(nil);
			else {
				cur->set_next(new Node);
				cur = cur->next();
			}
		}
	}

	/**
	* \brief Destructs the entire list
	*/
	~SingleLinkedList() {
		while (head_m != nil) {
			Node* temp = head_m;
			head_m = head_m->next();
			delete temp;
		}
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
	* \brief Searches iteratively for all nodes with the given elem
	* \return The list of those node
	*/
	SingleLinkedList search_all(int elem) {
		Node* cur = head_m;
		SingleLinkedList res;

		while (cur != nil) {
			if (cur->elem() == elem)
				res.push_back(elem);
			cur = cur->next();
		}

		return res;
	}

	/**
	* \brief Gets the previous node of position via search_node, and inserts elem
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
	* \brief Pushes elem to the back
	*/
	void push_back(int elem) {
		++size_m;
	}
	
	/**
	* \brief Pushes elem to the front
	*/
	void push_front(int elem) {
		++size_m;

	}

	/**
	* \brief Pops the head
	*/
	int pop_back() {
		--size_m;

	}

	/**
	* \brief Pops the head
	*/
	int pop_front() {
		--size_m;

	}

	/**
	* \brief Gets the previous node of position via search_node, and deletes elem
	*/
	void delete_elem(int pos) {
		// Empty list
		if (size_m == 0) cerr << "ERROR: Empty List" << endl;

		// One element list
		else if (size_m == 1) delete head_m;

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

	void delete_list() { this->~SingleLinkedList(); }

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