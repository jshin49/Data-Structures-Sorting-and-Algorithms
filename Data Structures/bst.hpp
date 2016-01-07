#pragma once
#ifndef BST_HPP
#define BST_HPP

#include <vector>
#include <cmath>

using namespace std;

class BinarySearchTree {
protected:
	class Node {
	public:
		// Constructors
		Node(){}
		Node(int elem, Node* right, Node* left) {
			set_node(elem, right, left);
		}

		// Getters
		Node* right() { return right_m; }
		Node* left() { return left_m; }
		int elem() { return elem_m; }

		// Setters
		void set_node(int elem, Node* right, Node* left) {
			set_elem(elem);
			set_right(right);
			set_left(left);
		}
		void set_right(Node* right) { right_m = right; }
		void set_left(Node* left) { left_m = left; }
		void set_elem(int elem) { elem_m = elem; }

	private:
		// Members
		Node* right_m;
		Node* left_m;
		int elem_m;
	};

	// Sentinel Node
	class Nil : public Node {};

public:
	// Constructors
	BinarySearchTree() {
		root_m = new Node;
		size_m = 0;
	}

	BinarySearchTree(int elem) {
		root_m = new Node(elem, nil, nil);
		size_m = 1;
	}

	BinarySearchTree(vector<int>& vec) {
		int median3 = vec.front() + vec.back() + vec[vec.size() / 2];
		int root = vec.front();
		int root_index = 0;
		for (int i = 0; i < vec.size(); ++i) {
			int diff1 = abs(vec[i] - median3);
			int diff2 = abs(root - median3);
			if (diff1 < diff2) {
				root = vec[i];
				root_index = i;
			}
		}

		for (int i = 0; i < vec.size(); ++i) {

		}
	}

	BinarySearchTree(int vec[], int size) {

	}

	// Insert

	// Remove

	// Search

	// Print

	// Successor

	// Predecessor


private:
	// Members
	Node* root_m;
	Nil* nil;
	int size_m;
};

#endif /* BST_HPP */