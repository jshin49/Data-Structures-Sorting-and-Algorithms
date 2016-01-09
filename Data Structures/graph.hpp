#pragma once
#ifndef GRAPH_HPP 
#define GRAPH_HPP 

#include <vector>
#include <fstream>
#include <unordered_map>

using namespace std;

class Graph {
protected:

	struct Node {
		Node() {}
		Node(int data, bool marked, bool explored = false) {
			this->data = data;
			this->marked = marked;
			this->explored = explored;
		}

		int data;
		bool marked = false;
		bool explored = false;
	};

public:
	Graph() {}
	Graph(string filename, int input_size, bool direction = false) {
		is_directed = direction;
		ifstream infile(filename);
		int key, value;
		map_m.reserve(input_size);

		int i = 0;
		while (!infile.eof()) {
			if (i % 2 == 1) {
				++i;
				continue;
			}
			else {
				infile >> key;
				infile >> value;

				if (is_directed && map_m.find(value) != map_m.end()) {
					auto it = find(map_m[value].begin(), map_m[value].end(), key);
					if (it != map_m[value].end()) {
						++i;
						continue;
					}
				}
				map_m[key].push_back(value);
				++i;
			}
		}
	}
	~Graph(){}

	vector<int>& operator[] (const int i) { return map_m.find(i)->second; }

	int BFS(int elem) {

	}

	int DFS(int elem) {

	}

private:
	// Members
	unordered_map<int, vector<int>> map_m;
	bool is_directed;

};

#endif /* GRAPH_HPP */