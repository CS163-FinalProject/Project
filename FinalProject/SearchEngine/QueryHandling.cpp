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

void checkOperator(string query,unordered_map<string,Trie> data, unordered_map<string,Trie> &imap, unordered_map<string, Trie> &omap) {
	query + " __END__";
	stringstream ss(query); //coffee OR tea
	string tmp;
	int checkOR = false;
	while (ss >> tmp) {
		if (tmp == "AND") {// AND
			continue;
		}
		else if (tmp == "OR") {// OR
			checkOR = true;
			orOperator(data, imap, omap);
		}

		else if (tmp.substr(0, 8) == "intitle:") {
			string key = tmp.substr(8);
			intitle_filetype_Operator(data, omap, key);
			break;	//just 1 time
		}
		else if (tmp.substr(0, 9) == "filetype:") {
			string key = tmp.substr(9);
			intitle_filetype_Operator(data, omap, key);
			break;	//just 1 time
		}
		else if (tmp[0] == '-') {
			string key = tmp.substr(1);
			minus_Search(imap, omap, key);
			break;	//just 1 time
		}

		else if (tmp == "__END__") {
			if (checkOR) {
				orOperator(data, imap, omap);
				imap.clear();
				imap = omap;
			}
		}
		else {// ' '
			andOperator(tmp, imap);
		}

	}
}

void andOperator(string key, unordered_map<string, Trie> &imap) {
	unordered_map<string, Trie> tmpmap;
	for (auto it : imap) {
		if (searchWord(it.second.root, key, false)) {
			tmpmap.insert(make_pair(it.first, it.second));
		}
	}

}

void intitle_filetype_Operator(unordered_map<string, Trie>& data, unordered_map<string, Trie>& map1, string key) {
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


void orOperator(unordered_map<string, Trie> data, unordered_map<string, Trie>& imap, unordered_map<string, Trie>& omap) {
	for (auto it : imap) {
		if (omap.find(it.first) == omap.end()) {
			omap.insert(make_pair(it.first, it.second));
		}
	}
	imap.clear();
	imap = data;


}
