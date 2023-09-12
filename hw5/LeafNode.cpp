#include "LeafNode.h"

LeafNode::LeafNode(const vector<int> &_keys, const vector<string> &p)
	: Node(_keys, true), data_pointer(p), next(this), prev(this){};

pair<int, Node *> LeafNode::insert(int key, const string &s, int order) {
	//cerr << "LeafNode : insert: " << key << endl;
	keys.push_back(key);
	data_pointer.push_back(s);
	for (int i = keys.size() - 1; i > 0; i--) {
		if (keys[i - 1] > keys[i]) {
			swap(keys[i - 1], keys[i]);
			swap(data_pointer[i-1], data_pointer[i]);
		} else {
			break;
		}
	}
	if (keys.size() > order * 2) {
		//overpage
		return spilt(order);
	}
	return {done, nullptr};
}

pair<int, Node *> LeafNode::spilt(int order) {
	//cerr << "LeafNode::spilt() in Leaf Node:" << endl;
	vector<int> key_tmp;
	vector<string> ptr_tmp;
	int spilt_key = keys[order];
	for (int i = order; i < keys.size(); i++) {
		key_tmp.push_back(keys[i]);
		ptr_tmp.push_back(data_pointer[i]);
	}
	keys.resize(order);
	data_pointer.resize(order);
	LeafNode *p = new LeafNode(key_tmp, ptr_tmp);
	p -> next = this -> next;
	this -> next -> prev = p;
	this -> next = p;
	p -> prev = this;
	return {spilt_key, p};
}

void LeafNode::print(int x) {
	//cerr << "print Leaf node" << endl;
	cout<< "["<<keys[0];
	for (int i = 1; i < keys.size(); i++) {
		cout << ", "<<keys[i];
	}
	cout<<"]"<<endl;
	for(int i=0;i<keys.size();i++){
		for(int j=0;j<=x;j++){cout<<"\t";}
		cout<<keys[i]<<": "<<data_pointer[i]<<endl;
	}
}

int LeafNode::erase(int key) {
	//cerr << "LeafNode : delete(" << key << ")" << endl;
	bool flag = false;
	for (int i = 0; i < keys.size(); i++) {
		if (key == keys[i]) {
			flag = true;
		}
		if (flag) {
			if (i < keys.size() - 1) {
				keys[i] = keys[i + 1];
				data_pointer[i] = data_pointer[i + 1];
			}
		}
	}
	if(!flag)	return -1;;	//not found
	data_pointer.pop_back();
	keys.pop_back();
	if (data_pointer.size() == 0) {
		// null
		this -> next -> prev = this -> prev;
		this -> prev -> next = this -> next;
		return notdone;
	}
	return done;
}

LeafNode::~LeafNode(){
	//cerr<<"destruct leaf node"<<endl;
}

string LeafNode::get_data(int index){
	return data_pointer[index];
}


