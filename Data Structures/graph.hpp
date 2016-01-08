#pragma once
#ifndef GRAPH_HPP 
#define GRAPH_HPP 

#include <vector>
#include <fstream>

using namespace std;

class Graph {
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
		void set_explored() { is_explored = true; }

	private:
		Node* next_m;
		int elem_m;
		bool is_explored = false;
	};

	// Sentinel Node
	class Nil : public Node {};

public:
	Graph() {}
	Graph(string filename, bool direction = false) {
		is_directed = direction;
		ifstream infile(filename);
		int first, second;
		int i = 0;
		while (!infile.eof()) {
			if (i % 2 == 1) {
				++i;
				continue;
			}
			else {
				infile >> first;
				infile >> second;
				Node edge(first, new Node(second, nil));
				vector_m.push_back(edge);
				++i;
			}
		}
	}
	~Graph(){}


private:
	// Members
	vector<Node> vector_m;
	Nil* nil;
	bool is_directed;

};

#endif /* GRAPH_HPP */