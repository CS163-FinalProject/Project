#include"QueryHandling.h"
#include"Trie.h"

#include<string>
#include<queue>
#include<fstream>
#include<unordered_map>
#include<iostream>
#include<algorithm>
#include<sstream>

using namespace std;

int checkOperator(string query) {
	stringstream ss(query);
	string tmp;
	while (ss >> tmp) {
		string get; get = tmp.substr(0, 8);
		if (tmp == "AND") return 1;
		if(tmp == "OR") return 2;
		if (get == "intitle:") return 3;
		if (tmp[0] == '-') return 4;
		//if(tmp)

	}
}

void inTitle_Search(unordered_map<string, Trie>& data, unordered_map<string, Trie>& map1, unordered_map<string, Trie>& map2, string key) {
	for (auto itr : data) {
		string title = itr.first;
		if (title.find(key) != string::npos) {
			map1.insert(make_pair(itr.first, itr.second));
		}
	}

	int i = 1;
	for (auto itr : map1) {
		cout <<"[" << i << "] " << itr.first << endl;
		++i;
	}
}

void minus_Search(unordered_map<string, Trie>& map1, unordered_map<string, Trie>& map2, string key) {
	for (auto itr : map1) {
		if (!searchWord(itr.second.root, key, false)) {
			map2.insert(make_pair(itr.first, itr.second));
		}
	}
	map1.swap(map2);

	int i = 1;
	for (auto itr : map1) {
		cout << "[" << i << "] " << itr.first << endl;
		++i;
	}
}