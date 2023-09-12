#ifndef __BPTREE_H
#define __BPTREE_H

#include <algorithm>
#include <iostream>
#include <string>
#include <typeinfo>

#include "KeyNode.h"
#include "LeafNode.h"
#include "Node.h"
using namespace std;

class BPTree {
	KeyNode *root;
	int order;
	pair<int, Node *> _insert(Node *, int, string);
	void _print(Node *node, string s, int depth);
	int _erase(Node *node, int key);
	LeafNode *_find(Node *, int key);
	LeafNode *_find_smallest(Node *);
	KeyNode *_make_index(vector<int>, vector<Node *>);

	public:
	BPTree(int);
	BPTree(int, vector<pair<int, string>>);
	int insert(int, string);
	int erase(int);  // erase with key
	string find(int);
	string find_smallest();
	void display(void);  // print the whole tree
	vector<pair<int, string>> get_all_data();
	vector<pair<int, string>> range_search(int, int);
	vector<pair<int, string>> range_search_not(int, int);
	~BPTree();
};

#endif
