#pragma once
#ifndef TEMPLATE_HASHTABLEMAP_HPP
#define TEMPLATE_HASHTABLEMAP_HPP

#include <list> // table type for collision
#include <vector> // table creation
#include <utility> // make_pair
#include <iostream>
#include <stdexcept>

using namespace std;

/**
* \class hashtablemap
* \brief A template class, which implements a
*        hash map dictionary following the STL idiom
*/
template <class Key, class T>
class hashtablemap
{
	typedef hashtablemap<Key, T>					 Self;

public:
	typedef Key											 key_type;
	typedef T						 					 data_type;
	typedef T											 mapped_type;
	typedef pair<Key, T>								 value_type;
	typedef unsigned int								 size_type;
	typedef int											 difference_type;
	typedef list<value_type>						 list_type;
	typedef vector<list<value_type>>				 table_type;

	// member variables
public:
	const int MAX_N; // max table size
	table_type vector_m;

	// iterator	: template class iterator and const_iterator
	template <class _T>
	class my_iterator {
		friend class hashtablemap;

	public:
		typedef _T										value_type;
		typedef int										difference_type;
		typedef value_type*							pointer;
		typedef value_type&							reference;

		typedef typename list_type::iterator	list_iterator;

		Self* hmap;
		int pos_v;
		list_iterator pos_l;

		my_iterator() {}
		my_iterator(Self* h, int v) {
			hmap = h;
			if (h == NULL) return;
			pos_v = v;
			if (pos_v == 0) {
				pos_v = hmap->get_next(-1);
				if (pos_v >= 0)
					pos_l = hmap->vector_m[pos_v].begin();
			}
		}
		my_iterator(Self* h, int v, const list_iterator& l) {
			hmap = h;
			pos_v = v;
			pos_l = l;
		}
		my_iterator(const my_iterator& x) {
			hmap = x.hmap;
			pos_l = x.pos_l;
			pos_v = x.pos_v;
		}
		my_iterator& operator= (const my_iterator& x) {
			hmap = x.hmap;
			pos_l = x.pos_l;
			pos_v = x.pos_v;
			return *this;
		}
		reference operator * () {
			return *pos_l;
		}
		pointer operator -> () {
			return &(*pos_l);
		}
		bool operator == (const my_iterator& x) {
			if (pos_v == x.pos_v) {
				if (pos_v == -1) return true;  // when both are end
				else return pos_l == x.pos_l;
			}
			else return false;
		}
		bool operator != (const my_iterator& x) {
			return &pos_l != &(x.pos_l) && pos_v != x.pos_v;
		}
		my_iterator& operator++() { // prefix notation
			++pos_l;
			if (pos_l == hmap->vector_m[pos_v].end()) {
				pos_v = hmap->get_next(pos_v);
				if (is_valid())
					pos_l = hmap->vector_m[pos_v].begin();
			}
			return *this;
		}
		my_iterator operator++(int) { // postfix notation
			my_iterator temp = *this;
			++(*this);
			return temp;
		}

		bool is_valid() {
			return pos_v >= 0;
		}

	};

	typedef my_iterator<value_type>				iterator;
	typedef my_iterator<value_type> const_iterator;
	//typedef my_iterator<const value_type> const_iterator; // causes error: don't know why.

public:
	// default constructor to create an empty map
	hashtablemap() : MAX_N(401) { // prime number 401 - fixed size
		vector_m.resize(MAX_N);
	}
	// overload copy constructor to do a deep copy
	hashtablemap(const Self& x) : MAX_N(401) {
		vector_m = x.vector_m;
	}
	~hashtablemap() { clear(); }
	// overload assignment to do a deep copy
	Self& operator= (Self& x) {
		if (this == &x) // prevent self assignment
			return *this;
		clear(); // clear original map and replace
		vector_m.resize(MAX_N);
		for (const_iterator i = x.begin(); i.is_valid(); ++i)
			insert(*i);
	}

	// accessors:
	iterator begin() {
		return iterator(this, 0);
	}
	//const_iterator begin() const {
	//	return const_iterator(this, 0);
	//}
	iterator end() {
		return iterator(this, -1);
	}
	//const_iterator end() const {
	//	return const_iterator(this, -1);
	//}
	bool empty() const { return get_next(-1) == -1;; }
	// return total number of elements
	size_type size() const { 
	int c = 0;
	for (int i = 0; i<MAX_N; i++)
		c += vector_m[i].size();
	return c;
}

	// insert/erase
	pair<iterator, bool> insert(const value_type& x) { // insert at list in ascending order
		key_type key = x.first;
		iterator it = find(key);
		if (it.is_valid()) {
			(*it).second = x.second;
			return make_pair(it, false);
		}
		int hash = hash_index(key);
		vector_m[hash].push_back(x);
		return make_pair(it, true);
	}

	void erase(iterator pos) {
		if (!pos.is_valid())
			throw runtime_error("Cannot erase an invalid key");
		key_type key = (*pos).first;
		int hash = hash_index(key);
		list_type::iterator it = locate(vector_m[hash].begin(), vector_m[hash].end(), key);
		if (it == vector_m[hash].end())
			throw runtime_error("Cannot erase a nonexistent key");
		else
			vector_m[hash].erase(it);
	}
	size_type erase(const Key& x) {
		iterator it = find(x);
		if (!it.is_valid()) { // Key not found
			throw runtime_error("Cannot erase a nonexistent key");
		}
		erase(it);
		return 1; // since Key in maps are unique, can only be 1
	} // erase by key
	void clear() {
		vector_m.clear();
	}

	// map operations:
	iterator find(const Key& x) {
		int hash = hash_index(x);
		list_type::iterator pos = locate(vector_m[hash].begin(), vector_m[hash].end(), x);
		if (pos == vector_m[hash].end())
			return end();
		return iterator(this, 0, pos);
	}
	//const_iterator find(const Key& x) const {
	//	int hash = hash_index(x);
	//	list_type::iterator pos = locate(vector_m[hash].begin(), vector_m[hash].end(), x);
	//	if (pos == vector_m[hash].end())
	//		return end();
	//	return const_iterator(this,hash,pos);
	//}

	// since every key in the map is unique, 
	// return 1 if found, otherwise return 0
	size_type count(const Key& x) {
		if (find(x).is_valid()) {
			return 1;
		}
		return 0;
	}
	T& operator[](const Key& k) {
		iterator it = find(k);
		if (it.is_valid()) {   // found key
			return (*it).second;
		}
		else {               // not found
			insert(value_type(k, NULL));
			return operator[](k);
		}
	}

	// helper functions
private:
	size_type hasher(const size_type& x) {
		size_type h = 1;
		h = h + 256 * x;
		return h;
	}
	size_type hasher(const string& x) { // special case: overloaded hasher function for strings
		size_type h = 1;
		int i = 0;
		for (auto a = x.begin(); a != x.end(); ++a) {
			h = h + 256 * (++i) * (*a);
		}
		return h;
	}
	size_type hash_index(const Key& x) {
		size_type h = hasher(x);
		return h % MAX_N;
	}
	int get_next(int i) const {
		do {
			++i;
			if (i == MAX_N) return -1;  // reached the end
		} while (vector_m[i].size() == 0);
		return i;
	}
	template<class IteratorT> // key locater
	IteratorT locate(IteratorT begin, IteratorT end, const Key& value) {
		while (begin != end && (*begin).first != value) {
			++begin;
		}
		return begin;
	}
};
#endif /* TEMPLATE_HASHTABLEMAP_HPP */