#ifndef KEYNODE_H
#define KEYNODE_H
#include "Node.h"

class KeyNode : public Node {
	vector<Node *> node_pointer;
	pair<int, KeyNode *> spilt(int);//split key node to two node

	public:
	KeyNode():Node(false){};	//isn't leaf
	KeyNode(const vector<int> &, const vector<Node *> &);//key and node_pointer
	Node* get_pointer(int = -1);//get node pointer, -1 is last element
	void set_pointer(int, Node *);// set node_pointer[idx] to p
	pair<int, Node *> insert(int, Node *, int);// insert into KeyNode the last int is to check whether overpage or not
	int erase(int);//delete the idx
	void print(int=0);//print the node(overwrite Node.print)
	~KeyNode();
};

#endif
