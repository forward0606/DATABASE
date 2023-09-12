#ifndef __LeafNode_H
#define __LeafNode_H

#include "KeyNode.h"
#include "Node.h"


class LeafNode : public Node {
	vector<string> data_pointer;
public:
	LeafNode* next;
	LeafNode* prev;
	LeafNode():Node(true), next(this), prev(this){};
	LeafNode(const vector<int> &, const vector<string> &);
	string get_data(int index);
	pair<int, Node *> insert(int, const string &, int);
	int erase(int);
	pair<int, Node *> spilt(int);
	void print(int);
	~LeafNode();
};

#endif
