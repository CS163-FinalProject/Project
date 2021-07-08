#include"QueryHandling.h"
#include"Trie.h"
#include"Tool.h"

#include<string>
#include<queue>
#include<fstream>
#include<unordered_map>
#include<iostream>
#include<algorithm>
#include<sstream>

using namespace std;
typedef unordered_multimap<int, string>::iterator umit;


void checkOperator(string query,unordered_map<string,Trie> data, unordered_map<string,Trie> &imap, unordered_map<string, Trie> &omap) {
	query = query + " END!";
	//cout << query << endl;
	stringstream ss(query); //coffee OR tea
	string tmp;

	while (ss >> tmp) {
		string get = tmp.substr(0, 8);
		string get2 = tmp.substr(0, 9);
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
			string key = tmp.substr(8);
			inTitle_Search(imap, key);
		}
		else if (tmp[0] == '-') { //exclude "-"
			string key = tmp.substr(1);
			minus_Search(imap, key);
		}
		else if (get2 == "filetype:") { // filetype:
			string key = tmp.substr(9);
			intitle_filetype_Operator(imap, key);
		}
		else if (tmp[0] == '"') {
			int ast = 0;
			string key = "";

			//case "* building" * at the first pos is the same as searching "building" alone
			if (tmp.substr(1) != "*") {
				key += tmp.substr(1);
			}
			//get word in between "tallest * building"
			while (tmp.back() != '"') {
				ss >> tmp;
				if (tmp == "*") {
					++ast;
					continue;
				}
				key = key + " " + tmp;
			}
			key.pop_back();
			//case "building *" * at the final pos is the same as searching "building" alone
			if (key.back() == '*') {
				key.pop_back();
			}
			//

			wildCardOperator(ast, key, imap);
			
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



void intitle_filetype_Operator(unordered_map<string, Trie>& imap, string key) {
	unordered_map<string, Trie> tmpmap;
	for (auto itr : imap) {
		string title = itr.first;
		string type = title.substr(title.find(".") + 1);
		if (type == key) {
			tmpmap.insert(make_pair(itr.first, itr.second));
		}
	}

	imap.clear();
	imap = tmpmap;
}

void inTitle_Search(unordered_map<string, Trie>& imap, string key) {
	unordered_map<string, Trie> tmpmap;
	
	for (auto itr : imap) {
		string title = itr.first;
		if (title.find(key) != string::npos) {
			tmpmap.insert(make_pair(itr.first, itr.second));
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

void wildCardOperator(int ast, string key, unordered_map<string, Trie>& imap) {
	unordered_map<string, Trie> tmpmap;
	
	unordered_map<string, vector<vector<int>>> wordpos;

	stringstream ss(key);

	vector<string> line;

	string tmp; bool accept; int num = 0;

	while (ss >> tmp) {// filter all files contain all the words in " "
		line.push_back(tmp);
	}


	for (auto it : imap) {
		accept = true;
		for (string str : line) {
			if (!searchWord(it.second.root, str, false)) {
				accept = false;
				break;
			}
			else {
				wordpos[it.first].push_back(searchWordpos(it.second.root, str));
				num++;
			}
		}
		if (accept) {
			tmpmap.insert(make_pair(it.first, it.second));
		}
		else {
			wordpos[it.first].clear();
		}
	}
	imap.clear();
	imap = tmpmap;
	tmpmap.clear();
	
	for (auto it : wordpos) {
		int i = 0; int j = 0; int lvl = 0;
		if (it.second.size() != 0) {
			while (i < it.second.size() - 1 && lvl < it.second[0].size()) {
				int u = it.second[i][j];
				int mid = binarySearch(u + 1, it.second[i + 1], 0, it.second[i + 1].size() - 1);
				if (mid != -1) {
					i++;
					j = mid;
				}
				else {
					i = 0;
					++lvl;
					j = lvl;
				}
			}
			if (i == it.second.size() - 1) {
				tmpmap[it.first] = imap[it.first];
			}
		}
	}

	imap.clear();
	imap = tmpmap;
	tmpmap.clear();

}

void Synonyms_Search(string key, unordered_map<string, Trie>& imap, unordered_map<string, Trie>& omap, unordered_map<string, int>& tableKey, unordered_multimap<int, string>& synonyms) {
	//umit is unordered_multimap iterator
	//equal_range return the begin and end iterators for the synonyms list
	pair<umit, umit> itr = synonyms.equal_range(tableKey[key]);
	umit i = itr.first;

	while (i != itr.second) {
		string synonym_word = i->second;
		for (auto k : imap) {
			if (searchWord(k.second.root, synonym_word, false)) {
				omap.insert(make_pair(k.first, k.second));
			}
		}
		++i;
	}

	imap.swap(omap);
	omap.clear();
}


