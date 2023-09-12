#include 	<iostream>
#include	<cstring>

#include 	"KeyNode.h"
#include 	"LeafNode.h"
#include 	"BPTree.h"
using namespace std;

void help_message(){
	cout<<"actions can be use"<<endl;
	cout<<"\t\"h\" for help"<<endl;
	cout<<"\t\"+ key, value\" for insert key with value in b+tree"<<endl;
	cout<<"\t\"- key\" for delete the key in the b+tree"<<endl;
	cout<<"\t\"$\" for print the tree"<<endl;
	cout<<"\t\"f key\" for find the value of key"<<endl;
	cout<<"\t\"r l, r\" for find the range from l key to r key"<<endl;
	cout<<"\t\"n l, r\" for find the range not in l key to r key"<<endl;
	cout<<"\t\"q\" for quit"<<endl;
}


int main(int argc, char **argv) {
	//freopen ("stderr","w",stderr);
	int order;
	char c, comma;
	int key;
	string s;
	cerr<<"please input the order of b+tree:"<<endl;
	while(cin>>order){
		if(order >= 1){break;}
		cerr<<"order shouldn't less than one"<<endl;
		cerr<<"please input the order of b+tree:"<<endl;
	}
	cout<<"set order to "<<order<<endl;

	BPTree bpt(order);		//initialize
	cerr<<"please input the reaction or h for help"<<endl;
	while(cin>>c){
		if(c == 'h'){
			help_message();
		}else if(c == '+'){
			cin>>key>>c>>s;
			if(c != ','){
				cout<<"input error"<<endl;
			}else{
				bpt.insert(key, s);
				cout<<"insert "<<key<<" OK!"<<endl;
			}
		}else if(c == '-'){
			cin>>key;
			if(bpt.erase(key) < 0){
				cout<<"delete error"<<endl;
			}else{
				cout<<"delete "<<key<<" OK!"<<endl;
			}
		}else if(c == '$'){
			cout<<"display the tree"<<endl;
			bpt.display();
		}else if(c == 'f'){
			cin>>key;
			cout<<"the value of key "<<key<<" is "<<bpt.find(key)<<endl;
		}else if(c == 'r'){
			int l, r;
			cin>>l>>c>>r;
			if(c != ','){
				cout<<"input error"<<endl;
			}else{
				vector<pair<int, string>> res = bpt.range_search(l, r);
				cout<<"search range from "<<l<<" to "<<r<<endl;
				for(auto e:res){
					cout<<"\t"<<e.first<<" : "<<e.second<<endl;
				}
			}
		}else if(c == 'n'){
			int l, r;
			cin>>l>>c>>r;
			if(c != ','){
				cout<<"input error"<<endl;
			}else{
				vector<pair<int, string>> res = bpt.range_search_not(l, r);
				cout<<"search range out of "<<l<<" to "<<r<<endl;
				for(auto e:res){
					cout<<"\t"<<e.first<<" : "<<e.second<<endl;
				}
			}
			
		}else if(c == 'q'){
			cout<<"Bye!"<<endl;
			break;
		}else{
			cout<<"input error"<<endl;
		}
		cerr<<"please input the reaction or h for help"<<endl;
	}
	
	bool flag = false;
	for(int i=0;i<argc;i++){
		if(strcmp(argv[i], "-b") == 0){
			flag = true;
		}
	}
	if(flag){
		//bulking loading example
		vector<pair<int, string>> input;
		input.emplace_back(2, "two");
		input.emplace_back(3, "three");
		input.emplace_back(5, "five");
		input.emplace_back(7, "seven");
		input.emplace_back(11, "eleven");
		input.emplace_back(17, "seventeen");
		input.emplace_back(19, "nineteen");
		input.emplace_back(31, "thirty-one");
		input.emplace_back(9, "nine");
		input.emplace_back(10, "ten");
		input.emplace_back(8, "eight");
		input.emplace_back(1, "one");
		input.emplace_back(4, "four");
		input.emplace_back(0, "zero");
		input.emplace_back(23, "twenty-three");
		input.emplace_back(29, "twenty-nine");
		input.emplace_back(2, "two");		//test the bulk loading with same key
		BPTree bpt2 = BPTree(2, input);		
		bpt2.display();
		int l = 5, r = 19;
		vector<pair<int, string>> res = bpt2.range_search(l, r);
		cout<<"search range from "<<l<<" to "<<r<<endl;
		for(auto e:res){
			cout<<"\t"<<e.first<<" : "<<e.second<<endl;
		}
		cout<<"BYE!"<<endl;
	}
	return 0;
}
