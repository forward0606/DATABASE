#include 	<iostream>

#include 	"KeyNode.h"
#include 	"LeafNode.h"
#include 	"BPTree.h"
using namespace std;


int main() {
	freopen ("stderr","w",stderr);
	BPTree bpt(4);
	bpt.insert(1, "one");
	bpt.erase(1);
	//bulking loading example
	vector<pair<int, string>> input;
	input.emplace_back(9, "nine");
	input.emplace_back(10, "ten");
	input.emplace_back(8, "eight");
	input.emplace_back(1, "one");
	input.emplace_back(4, "four");
	input.emplace_back(0, "zero");
	input.emplace_back(23, "twenty-three");
	input.emplace_back(29, "twenty-nine");
	BPTree bpt2 = BPTree(2, input);
	bpt.display();
	bpt2.display();
	cout<<bpt2.find(9)<<endl;
	cout<<bpt2.find_smallest()<<endl;
	auto res = bpt2.get_all_data();
	for(auto e:res){
		cout<<e.first<<":"<<e.second<<endl;
	}
	cout<<"range search"<<endl;
	res = bpt2.range_search(4, 8);
	for(auto e:res){
		cout<<e.first<<":"<<e.second<<endl;
	}
	cout<<"range search not"<<endl;
	res = bpt2.range_search_not(4, 8);
	for(auto e:res){
		cout<<e.first<<":"<<e.second<<endl;
	}
	return 0;
}
