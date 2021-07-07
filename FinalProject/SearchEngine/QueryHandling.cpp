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
	query = query + " END!";
	//cout << query << endl;
	stringstream ss(query); //coffee OR tea
	string tmp;
	
	while (ss >> tmp) {
		string get; get = tmp.substr(0, 8);
		if (tmp == "AND") {// AND
			continue;
		}
		else if (tmp == "OR" || tmp == "END!") {// OR
			orOperator(data, imap, omap);
			if (tmp == "END!") {
				imap.clear();
				imap = omap;
			}
		}
		else if (get == "intitle:") { //intitle:
			string left = tmp.substr(8);
			string key = query.substr(query.find(tmp) + 8);
			
			inTitle_Search(imap, key);
			break;
		}
		else if (tmp[0] == '-') { //exclude "-"
			string key = tmp.substr(1);

			minus_Search(imap, key);
		}
		else {// '$' '#' ' '
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
	imap.clear();
	imap = tmpmap;
	tmpmap.clear();

}


void intitle_filetype_Search(unordered_map<string, Trie> & data, unordered_map<string, Trie> & map1, string key) {
	for (auto itr : data) {
		string title = itr.first;
		if (title.find(key) != string::npos) {
			map1.insert(make_pair(itr.first, itr.second));
		}
	}
}

void inTitle_Search(unordered_map<string, Trie>& imap, string key) {
	unordered_map<string, Trie> tmpmap;
	stringstream ss(key);
	string tmp;
	while (ss >> tmp){
		for (auto itr : imap) {
			string title = itr.first;
			if (title.find(tmp) != string::npos) {
				tmpmap.insert(make_pair(itr.first, itr.second));
			}

		}
	}

	imap.clear();
	imap = tmpmap;
}

void minus_Search(unordered_map<string, Trie>& imap, string key) {
	unordered_map<string, Trie> tmpmap;
	for (auto itr : imap) {
		if (!searchWord(itr.second.root, key, false)) {
			tmpmap.insert(make_pair(itr.first, itr.second));
		}
	}
	
	imap.clear();
	imap = tmpmap;
	tmpmap.clear();

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


