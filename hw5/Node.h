#ifndef __Node_H
#define __Node_H
#include <iostream>
#include <vector>
using namespace std;

const int done = 0;
const int notdone = 1;

class Node {
public:
	bool is_leaf;						// node have two derivated class: KeyNode and LeafNode
	vector<int> keys;
	Node(bool);							//is_leaf or not
	Node(const vector<int>&, bool);		//key and is_leaf or not
	virtual ~Node(){};
	virtual void print(int) = 0;		//print the node value
	virtual int erase(int) = 0;			//delete the contain in node
};

#endif
