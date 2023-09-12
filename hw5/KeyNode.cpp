#include "KeyNode.h"

KeyNode::KeyNode(const vector<int> &_keys, const vector<Node *> &p)
	: Node(_keys, false) {
		node_pointer = p;
	};

Node* KeyNode::get_pointer(int idx){
	if(idx == -1){
		return node_pointer.back();
	}
	return node_pointer[idx];
}

void KeyNode::set_pointer(int idx, Node *p){
	node_pointer[idx] = p;
}


pair<int, Node *> KeyNode::insert(int key, Node *p, int order) {
	//cerr << "KeyNode insert: " << key << endl;
	if(node_pointer.size() == 0){
		node_pointer.push_back(p);
		return {done, nullptr};
	}
	keys.push_back(key);
	node_pointer.push_back(p);
	for (int i = keys.size() - 1; i > 0; i--) {
		if (keys[i - 1] > keys[i]) {
			swap(keys[i - 1], keys[i]);
			swap(node_pointer[i], node_pointer[i+1]);
		} else {
			break;
		}
	}
	if (keys.size() > order * 2) {
		return spilt(order);
	}
	return {done, nullptr};
}

pair<int, KeyNode *> KeyNode::spilt(int order) {
	//cerr << "KeyNode::spilt()" << endl;
	vector<int> key_tmp;
	vector<Node *> ptr_tmp;
	int spilt_key = keys[order];
	for (int i = order+1; i < keys.size(); i++) {
		key_tmp.push_back(keys[i]);
		ptr_tmp.push_back(node_pointer[i]);
	}
	ptr_tmp.push_back(node_pointer.back());
	keys.resize(order);
	node_pointer.resize(order+1);
	KeyNode *p = new KeyNode(key_tmp, ptr_tmp);
	return {spilt_key, p};
}

void KeyNode::print(int) {
	//cerr << "print Key node" << endl;
	cout<<"[";
	if(keys.size() > 0)	cout<<keys[0];
	for (int i = 1; i < keys.size(); i++) {
		cout << ", "<<keys[i];
	}
	cout<<"]"<<endl;
}

int KeyNode::erase(int index) {
	// 3 7 9
	// 2 5 8 10
	// key is the last element in leaf node
	// for example delete 5
	// we delete 7
	
	//cerr << "KeyNode : delete(" << index << ")" << endl;
	if(node_pointer.size() < index) 	return -1;
	delete node_pointer[index];
	node_pointer[index] = nullptr;
	for (int i = index; i < keys.size(); i++) {
		if (i < keys.size() - 1) {
				keys[i] = keys[i + 1];
		}
		node_pointer[i] = node_pointer[i + 1];
	}
	node_pointer.pop_back();
	keys.pop_back();
	if (node_pointer.size() == 0) {
		// null
		return notdone;
	}
	return done;
}

KeyNode::~KeyNode(){
	//cerr<<"KeyNode::destruct key node"<<endl;
	for(auto p : node_pointer){
		delete p;
	}
}

