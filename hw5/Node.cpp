#include    "Node.h"


Node::Node(bool leaf):is_leaf(leaf){};

Node::Node(const vector<int> & _keys, bool leaf)
	:keys(_keys), is_leaf(leaf){};

