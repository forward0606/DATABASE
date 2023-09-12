#include	"BPTree.h"

BPTree::BPTree(int ord): root(nullptr){
	if(ord < 1){
		cerr<<"we can't set the order less than one."<<endl;
		cerr<<"set the order to default value 1."<<endl;
		ord = 1;
	}
	order = ord;
}


BPTree::BPTree(int ord, vector<pair<int, string>> input){
	if(ord < 1){
		cerr<<"we can't set the order less than one."<<endl;
		cerr<<"set the order to default value 1."<<endl;
		ord = 1;
	}
	order = ord;

	//bulk loading
	
	// sort and remove the same
	sort(input.begin(), input.end());
	int cnt = 1;
	for(int i=1;i<input.size();i++){
		if(input[i] != input[cnt-1]){
			input[cnt] = input[i];
			++cnt;
		}
	}
	
	input.resize(cnt);

	vector<int> key;
	vector<string> value;
	vector<int> node_key;
	vector<Node *> nodes;
	int idx = 0;
	LeafNode *last = nullptr;
	while(idx < input.size()){
		for(int i=0;i<order && idx<input.size();i++, idx++){
			key.emplace_back(input[idx].first);
			value.emplace_back(input[idx].second);
		}
		LeafNode* l = new LeafNode(key, value);
		if(last != nullptr){
			//linked list
			l -> next = last -> next;
			last -> next -> prev = l;
			last -> next = l;
			l -> prev = last;
		}
		nodes.emplace_back(l);
		node_key.emplace_back(key[0]);
		key.clear();
		value.clear();
		last = l;
	}
	root = _make_index(node_key, nodes);
}


KeyNode *BPTree::_make_index(vector<int> node_key, vector<Node *> nodes){
	if(nodes.size() == 1 && nodes[0] -> is_leaf == false){
		return static_cast<KeyNode *>(nodes[0]);
	}
	if(node_key.size() <= order){
		node_key.erase(node_key.begin());
		return new KeyNode(node_key, nodes);
	}
	vector<int> key;
	vector<Node *> value;
	vector<int> next_key;
	vector<Node *> next_idx;
	int idx = 0;
	while(idx < node_key.size()){
		next_key.emplace_back(node_key[idx]);
		for(int i=0;i<=order && idx<node_key.size();i++, idx++){
			if(i != 0)key.emplace_back(node_key[idx]);
			value.emplace_back(nodes[idx]);
		}
		KeyNode* k = new KeyNode(key, value);
		next_idx.emplace_back(k);
		key.clear();
		value.clear();
	}
	return _make_index(next_key, next_idx);
}



int BPTree::insert(int key, string s) {
	//cerr << "B+ tree insert: key = " << key << ", s = " << s << endl;
	if (root == nullptr) {
		LeafNode* p = new LeafNode();
		p -> insert(key, s, order);
		root = new KeyNode();
		root -> insert(key, p, order);
		return 0;
	}
	if(find(key) != ""){
		//already has a key in tree
		return -1;
	}
	//change root -> height++
	pair<int, Node *> p = _insert(root, key, s);
	if( p.second != nullptr) {
		KeyNode *new_r = new KeyNode();
		new_r -> insert(0, root, order);
		new_r -> insert(p.first, p.second, order);
		root = new_r;
	}
	return 0;
}

pair<int, Node *>BPTree::_insert(Node* node, int key, string s) {
	//cerr<<"BPTree::_insert() : "<<'\n';
	if (node -> is_leaf) {
		LeafNode *tmp = static_cast<LeafNode *>(node);
		return tmp -> insert(key, s, order);
	}

	//go down update(change data)
	bool flag = true;
	pair<int, Node *> p;
	KeyNode *tmp = static_cast<KeyNode *>(node);
	for(int i=0;i<node->keys.size();i++){
		if(key < node->keys[i]){
			//go to i node
			flag = false;
			p = _insert(tmp->get_pointer(i), key, s);
			break;
		}
	}
	if(flag){
		//go to the last
		p = _insert(tmp->get_pointer(node -> keys.size()), key, s);
	}

	//go up update 
	if(p.second != nullptr){
		return tmp -> insert(p.first, p.second, order);
	}
	return {0, nullptr};
}


void BPTree::display(){
	//cerr<<"BPTree::display()"<<endl;
	if(root == nullptr){
		cout<<"The tree is empty now!"<<endl;
		return;
	}
	_print(root, "1", 0);
}

void BPTree::_print(Node *node, string s, int depth){
	//cerr<<"BPTree::print()"<<s<<" "<<depth<<'\n';
	for(int i=0;i<depth;i++){cout<<'\t';};
	cout<<s<<":";
	node -> print(depth);
	if (node -> is_leaf) {
		return;
	}
	string t = s + ".";
	KeyNode *tmp = static_cast<KeyNode *>(node);
	for(int i=0;i<node -> keys.size()+1;i++){
		s = t;
		s += to_string(i+1);	//generator node id	
		_print(tmp->get_pointer(i), s, depth+1);
	}
}

int BPTree::erase(int key){
	//cerr<<"BPTree:: erase("<<key<<")"<<endl;
	if(root == nullptr) return -1;	//error
	int status = _erase(root, key);
	if( status == notdone){
		delete root;
		root = nullptr;
		status = done;
		return done;
	}
	if(root -> keys.size() == 0 && root -> get_pointer() -> is_leaf == false){
		KeyNode *p = root;
		root = static_cast<KeyNode *>(root -> get_pointer(0));
		p -> set_pointer(0, nullptr);
		delete p;
	}
	return status;
}

int BPTree::_erase(Node *node, int key){
	if(node -> is_leaf){
		LeafNode *tmp = static_cast<LeafNode *>(node);
		return tmp -> erase(key);
	}
	int go_in = -1;
	int status = 0;
	KeyNode *tmp = static_cast<KeyNode *>(node);
	for(int i=0;i<node->keys.size();i++){
		if(key < node->keys[i]){
			go_in = i;
			//go to i node
			status = _erase(tmp->get_pointer(i), key);
			break;
		}
	}
	if(go_in == -1){
		//go to the last node
		go_in = node -> keys.size();
		status = _erase(tmp->get_pointer(), key);
	}
	if(status == notdone){
		return tmp -> erase(go_in);
	}
	return status;
}


BPTree::~BPTree(){
	//cerr<<"destruct BPTree"<<endl;
	delete root;
}

LeafNode* BPTree::_find(Node *node, int key){
	if(node -> is_leaf){
		return static_cast<LeafNode *>(node);
	}
	KeyNode *tmp = static_cast<KeyNode *>(node);
	for(int i=0;i<tmp -> keys.size();i++){
		if(key < tmp->keys[i]){
			return _find(tmp->get_pointer(i), key);
		}
	}
	return _find(tmp->get_pointer(), key);
}

string BPTree::find(int key){
	if(root == nullptr)	return "";	//not found
	LeafNode *p = _find(root, key);
	for(int i=0;i<p->keys.size();i++){
		if(p->keys[i] == key){
			return p -> get_data(i);
		}
	}
	return "";		//key is not in tree
}


LeafNode* BPTree::_find_smallest(Node *node){
	if(node -> is_leaf){
		return static_cast<LeafNode *>(node);
	}
	KeyNode *tmp = static_cast<KeyNode *>(node);
	return _find_smallest(tmp->get_pointer(0));
}

string BPTree::find_smallest(){
	if(root == nullptr)	return "";
	LeafNode *p = _find_smallest(root);
	return p->get_data(0);		//return the first value(smallest)
}



vector<pair<int, string>> BPTree::get_all_data(){
	//cerr<<"BPTree::get_all()"<<endl;
	if(root == nullptr){
		cout<<"the tree is empty!";
	}
	vector<pair<int, string>> res;
	LeafNode *p = _find_smallest(root);
	LeafNode *tmp = p->next;
	for(int i=0;i<p->keys.size();i++){
		res.emplace_back(p->keys[i], p->get_data(i));
	}
	while(tmp != p){
		for(int i=0;i<tmp->keys.size();i++){
			res.emplace_back(tmp->keys[i], tmp->get_data(i));
		}
		tmp = tmp -> next;
	}
	return res;
}

vector<pair<int, string>> BPTree::range_search(int lkey, int rkey){
	vector<pair<int, string>> res;
	if(lkey > rkey)	return res;
	LeafNode *tmp1 = _find(root, lkey);
	LeafNode *tmp2 = _find(root, rkey);
	for(int i=0;i<tmp1->keys.size();i++){
		if(tmp1->keys[i] >= lkey && tmp1->keys[i] <= rkey){
			res.emplace_back(tmp1->keys[i], tmp1->get_data(i));
		}
	}
	if(tmp1 == tmp2){
		return res;
	}
	tmp1 = tmp1 -> next;
	while(tmp1 != tmp2){
		for(int i=0;i<tmp1->keys.size();i++){
			res.emplace_back(tmp1->keys[i], tmp1->get_data(i));
		}
		tmp1 = tmp1->next;
	}
	for(int i=0;i<tmp1->keys.size();i++){
		if(tmp1->keys[i] <= rkey){
			res.emplace_back(tmp1->keys[i], tmp1->get_data(i));
		}
	}
	return res;
}


vector<pair<int, string>> BPTree::range_search_not
						(int lkey, int rkey){
	vector<pair<int, string>> res;
	if(lkey > rkey)	return res;
	LeafNode *tmp1 = _find(root, lkey);
	LeafNode *tmp2 = _find(root, rkey);
	for(int i=0;i<tmp2->keys.size();i++){
		if(tmp2->keys[i] < lkey || tmp2->keys[i] > rkey){
			res.emplace_back(tmp2->keys[i], tmp2->get_data(i));
		}
	}
	if(tmp1 == tmp2)tmp1 = tmp1 -> prev;
	tmp2 = tmp2 -> next;
	while(tmp1 != tmp2){
		for(int i=0;i<tmp2->keys.size();i++){
			res.emplace_back(tmp2->keys[i], tmp2->get_data(i));
		}
		tmp2 = tmp2->next;
	}
	for(int i=0;i<tmp1->keys.size();i++){
		if(tmp1->keys[i] < lkey){
			res.emplace_back(tmp1->keys[i], tmp1->get_data(i));
		}
	}
	return res;
}

