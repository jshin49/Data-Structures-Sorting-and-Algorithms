#pragma once
#ifndef BSTMAP_HPP
#define BSTMAP_HPP

#include <utility>
#include <cstddef>
#include <iterator>
#include <iostream>
#include <cassert>
#include <stdexcept>

using namespace std;

/**
* \class bstmap
* \brief A template class, which implements a binary search
*        tree dictionary following the STL idiom
*/
template <class Key, class T>
class bstmap // binary search tree map
{
	friend class my_iterator;
	typedef bstmap<Key, T>     Self;

public:
	typedef Key                key_type;
	typedef T                  data_type;
	typedef pair<const Key, T> value_type;
	typedef unsigned int       size_type;
	typedef int                difference_type;

	// members
protected:
	/**
	* \class Node
	* \brief Holds value_type (keypair). Has two child, left and right
	*        but also points to the parent for easier implementation
	*/
	class Node {
	public:
		Node(value_type val, Node* parent = NULL, Node* left = NULL, Node* right = NULL) :
			value_m(val), parent_m(parent), left_m(left), right_m(right) {}

		// Destructor sets to NULL to prevent OS to reuse garbage
		~Node() {
			parent_m = NULL;
			left_m = NULL;
			right_m = NULL;
		}

		value_type value_m;
		Node* left_m;
		Node* right_m;
		Node* parent_m;
	};

	Node*	root_m;

public:
	// iterator
	// template for iterator and const_iterator
	template <class _T>
	class my_iterator {
		friend class bstmap;

	public:
		typedef _T									 value_type;
		typedef int									 difference_type;
		typedef value_type*						 pointer;
		typedef value_type&						 reference;

		Node* node_m;

		my_iterator(Node* n = NULL) : node_m(n) {}
		my_iterator(const my_iterator& x) : node_m(x.node_m) {}

		my_iterator& operator=(const my_iterator& x) {
			node_m = x.node_m;
			return *this;
		}
		reference operator*() {
			return node_m->value_m;
		}
		pointer operator->() {
			return &(node_m->value_m);
		}
		bool operator==(const my_iterator& x) {
			return (node_m == x.node_m);
		}
		bool operator!=(const my_iterator& x) {
			return (node_m != x.node_m);
		}
		my_iterator& operator++() { // prefix notation
			node_m = successor(node_m);
			return *this;
		}
		my_iterator operator++(int) { // postfix notation
			my_iterator temp = *this;
			++(*this); 
			return temp;
		}
	};

	typedef my_iterator<value_type>				iterator;
	typedef my_iterator<const value_type> const_iterator; // or is it <value_type const>

public:
	// default constructor to create an empty map
	bstmap() : root_m(NULL) {}
	// overload copy constructor to do a deep copy
	bstmap(const Self& x) {
		root_m = x.root_m;
	}
	// destructor, deallocates all the nodes in the tree */
	~bstmap() { clear(); }
	// overloads assignment to do a deep copy
	Self& operator=(const Self& x) {
		// prevent self assignment
		if (this == &x)
			return *this;
		clear(); // clear original map and replace
		for (const_iterator i = x.begin(); i != x.end(); i++)
			insert(*i);
	}

	// accessors:
	iterator begin() {
		return iterator(left_most(root_m));
	}
	const_iterator begin() const {
		return const_iterator(left_most(root_m));
	}
	iterator end() {
		if (empty()) return begin();
		else				 return iterator(NULL);
	}
	const_iterator end() const {
		if (empty()) return begin();
		else				 return const_iterator(NULL);
	}
	bool empty() const { return root_m == NULL; }
	size_type size() const {
		return _size(root_m);
	}

	// insert/erase
	/**
	* \return pair<iterator, bool> iterator to node in tree, bool is
	*         true if an insertion has been done
	*/
	pair<iterator, bool> insert(const value_type& x) {
		pair<Node*, bool> res = _find(x.first, root_m);
		if (res.first == NULL){
			root_m = new Node (x); // head insertaion
			return make_pair(iterator(root_m), true);
		}
		else if (res.second) {  // already exists. return it's value
			return make_pair(iterator(res.first), false);
		}
		else {
			Node* new_node = new Node(x, res.first);
			if (x.first < (res.first->value_m).first) {
				res.first->left_m = new_node;
			}
			else {
				res.first->right_m = new_node;
			}
			return make_pair(iterator(new_node), true);
		}
	}
	void erase(iterator pos) { // erase by iterator position
		if (pos == NULL) {
			throw runtime_error("Cannot erase at a NULL position");
		}

		Node* n = pos.node_m;
		Node* parent = n->parent_m;
		Node* left = n->left_m;
		Node* right = n->right_m;
		if (n == NULL) {
			return;
		}
		// Case 3: x has 2 childs
		if (n->left_m != NULL && n->right_m != NULL) {
			Node* _successor = successor(n);
			
			// replace deleted node with successor
			delete n;
			n = new Node(_successor->value_m, parent, left, right);

			// delete original successor
			erase(iterator(_successor));
		}
		// Case 1: x is a leaf
		else if (n->left_m == NULL && n->right_m == NULL) {
			if (parent->left_m == n) {
				parent->left_m = NULL;
			}
			else {
				parent->right_m = NULL;
			}
			delete n;
		}
		// Case 2: x has exactly one child
		else {
			Node* child = n->left_m;
			if (child == NULL) {
				child = n->right_m;
			}

			// special case: deleting root
			if (n == root_m) {
				root_m = child; // move the root to the child
			}
			else {
				if (n == parent->left_m) {
					parent->left_m = child;
				}
				else {
					parent->right_m = child;
				}
			}
			child->parent_m = parent;
			delete n;
		}
		return;
	}
	size_type erase(const Key& x) {
		iterator it = find(x);
		if (it == end()) { // Key not found
			throw runtime_error("Cannot erase a nonexistent key");
		}
		erase(it);
		return 1; // since Key in maps are unique, can only be 1
	} // erase by key
	void clear() {
		_clear(root_m);
		root_m = NULL;
	}
	T& operator[](const key_type& k) {
		iterator it = find(k);		
		if (it != end()) {   // found key
			return (*it).second;
		}
		else {               // not found -> create empty node
			insert(value_type(k, NULL));
			return operator[](k);
		}
	}

	// map operations:
	iterator find(const key_type& x) {
		pair<Node*, bool> res = _find(x, root_m);
		if (res.second) { // found key
			return iterator(res.first);
		}
		return end();
	}
	const_iterator find(const key_type& x) const {
		pair<Node*, bool> res = _find(x, root_m);
		if (res.second) { // found key
			return const_iterator(res.first);
		}
		return end(); // return end if find fails
	}

	// since every key in the map is unique,
  // if the element is found return 1, otherwise return 0
	size_type count(const Key& x) const {
		if (find(x) != end()) {
			return 1;
		}
		return 0;
	}

private:
	/**
	*\return Node* nearest node to find
	*\return bool true if found
	*/
	pair<Node*, bool> _find(const key_type& key, Node* subtree, Node* parent = NULL) const {
		if (subtree == NULL) {
			return pair<Node*, bool>(parent, false);
		}
		if (subtree->value_m.first == key) {
			return pair<Node*, bool>(subtree, true);
		}
		else if (subtree->value_m.first > key) {
			return _find(key, subtree->left_m, subtree);
		}
		else {
			return _find(key, subtree->right_m, subtree);
		}
	}

// helper functions
private:
	static bool is_right_child(Node* n) {
		return n->parent_m && n->parent_m->right_m == n;
	}
	static bool is_left_child(Node* n) {
		return n->parent_m && n->parent_m->left_m == n;
	}
	static Node* left_most(Node* subtree) {  // minimum
		if (subtree) {
			while (subtree->left_m)
				subtree = subtree->left_m;
		}
		return subtree;
	}
	static Node* right_most(Node* subtree) {  // maximum
		if (subtree) {
			while (subtree->right_m)
				subtree = subtree->right_m;
		}
		return subtree;
	}
	static Node* successor(Node* n) {  // next node in in-order traverse
		if (n->right_m)					return left_most(n->right_m); // minimum of right subtree
		Node* pos = n;
		Node* pos_p = n->parent_m;
		while (pos_p && is_right_child(pos)) {
			pos = pos_p;
			pos_p = pos_p->parent_m;
		}
		return pos_p; // if left child, return parent
	}	
	static void _clear(Node* n) {
		if (n == NULL) {
			return;
		}

		_clear(n->right_m);
		_clear(n->left_m);
		
		delete n;
		n = NULL;
	}
	static size_type _size(Node* n) {
		if (n == NULL) {
			return 0;
		}
		return 1 + _size(n->left_m) + _size(n->right_m);
	}

};
#endif /* BSTMAP_HPP */