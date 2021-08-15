#include"QueryHandling.h"
#include"Trie.h"
#include"Tool.h"

#include<iostream>
#include<algorithm>
#include<sstream>

using namespace std;
typedef unordered_multimap<int, string>::iterator umit;


void checkOperator(vector<string> &line,string query,unordered_map<string,Trie> data, unordered_map<string,Trie> &imap, 
	unordered_map<string, Trie> &omap, unordered_map<string, int>& tableKey, unordered_multimap<int, string>& synonyms) {
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
			line.push_back(key);
			inTitle_Search(imap, key);
		}
		else if (tmp[0] == '-') { //exclude "-"
			string key = tmp.substr(1);
			minus_Search(imap, key);
		}
		else if (get2 == "filetype:") { // filetype:
			string key = tmp.substr(9);
			filetypeOperator(imap, key);
		}
		else if (tmp[0] == '"') {
			int ast = 1; int pos = 0; int start = -1;
			string key = "";

			//case "* building" * at the first pos is the same as searching "building" alone
			if (tmp.size() != 1 && tmp.substr(1) != "*") {
				key += tmp.substr(1);
				if (key.back() == '"') key.pop_back();
				line.push_back(key);
				++pos;
			}
			//get word in between "tallest * building"
			while (tmp != "" && tmp.back() != '"') {
				ss >> tmp;
				if (tmp == "*") {
					if(start == -1) start = pos;
					++ast;
					continue;
				}
				++pos;
				if (tmp.back() == '"') {
					string tmp2 = tmp;
					tmp2.pop_back();
					line.push_back(tmp2);	
				}else line.push_back(tmp);

				key = key + " " + tmp;
			}
			if(key.back() == '"') key.pop_back();
			//case "building *" * at the final pos is the same as searching "building" alone
			if (key.back() == '*') {
				key.pop_back();
			}
			//
			
			wildCardOperator(start, ast, key, imap);
		}
		else if (tmp.find("..") != string::npos) {
			rangeOperator(imap, tmp, line);
		}
		else if (tmp[0] == '~') {
			string key = tmp.substr(1);

			Synonyms_Search(key, imap, tableKey, synonyms, line);
		}
		else {// '$' '#' ' '
			if (tmp[0] == '+') { //+
				tmp = tmp.substr(1);
			}
			line.push_back(tmp);
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


void filetypeOperator(unordered_map<string, Trie>& imap, string key) {
	unordered_map<string, Trie> tmpmap;
	for (auto itr : imap) {
		string title = itr.first;
		string type = title.substr(title.find(".") + 1);
		if (type == key)
			tmpmap.insert(make_pair(itr.first, itr.second));
		
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

void wildCardOperator(int start, int ast, string key, unordered_map<string, Trie>& imap) {
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
				if (start != -1 && i != start - 1) {
					ast = 1;
				}
				int u = it.second[i][j];
				int mid = binarySearch(u + ast, it.second[i + 1], 0, it.second[i + 1].size() - 1);
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

void Synonyms_Search(string key, unordered_map<string, Trie>& imap, unordered_map<string, int>& tableKey, unordered_multimap<int, string>& synonyms, vector<string> &line) {
	
	//umit is unordered_multimap iterator
	//equal_range return the begin and end iterators for the synonyms list
	
	pair<umit, umit> itr = synonyms.equal_range(tableKey[key]);
	umit i = itr.first;
	unordered_map<string, Trie> tmpmap;
	while (i != itr.second) {
		string synonym_word = i->second;
		line.push_back(synonym_word);
		for (auto k : imap) {
			if (searchWord(k.second.root, synonym_word, false)) {
				tmpmap.insert(make_pair(k.first, k.second));
			}
		}
		++i;
	}

	imap.clear();
	imap = tmpmap;
	tmpmap.clear();
}

void rangeOperator(unordered_map<string, Trie>& imap, string key, vector<string> &line)	//key is "$50..$100"
{
	int from, end;
	bool dollar;
	if (key[0] >= 48 && key[0] <= 57) {
		dollar = false;
		from = atoi(key.c_str());
	}
	else {
		dollar = true;
		from = atoi(key.substr(1).c_str());
	}
	
	string tmp;
	if (!dollar) tmp = key.substr(key.find('.') + 2);	//100
	else tmp = key.substr(key.find('.') + 3);
	end = atoi(tmp.c_str());

	unordered_map<string, Trie> tmpmap;

	for (int i = from; i <= end; ++i)
	{
		string val;
		if (!dollar) val = to_string(i);
		else val = key[0] + to_string(i);
		line.push_back(val);
		for (auto k : imap)
			if (searchWord(k.second.root, val, false))
				tmpmap.insert(make_pair(k.first, k.second));
	}

	imap.clear();
	imap = tmpmap;
}

string checkStopWord(string query, Trie dataStopWord) {
	stringstream ss(query);
	string tmp; string n_query = "";
	vector<string> str;
	while (ss >> tmp) {
		if (tmp == "AND" || tmp == "OR") {
			str.push_back(tmp);
			continue;
		}
		
		if (tmp[0] == '"') {
			if (searchWord(dataStopWord.root, tmp.substr(1), false)) {
				str.push_back("\"1");
				continue;
			}
		}
		if (tmp.back() == '"') {
			string key = tmp;
			key.pop_back();
			if (searchWord(dataStopWord.root, key, false)) {
				str.push_back("\"");
				continue;
			}
		}

		if (tmp.substr(0,8) == "intitle:") {
			if (searchWord(dataStopWord.root, tmp.substr(8), false)) {
				continue;
			}
		}

		if (tmp[0] == '-') {
			if (searchWord(dataStopWord.root, tmp.substr(1), false)) {
				continue;
			}
		}

		if (searchWord(dataStopWord.root, tmp, false)) {
			continue;
		}
		str.push_back(tmp);
	}
	int beg = 0; int end = str.size() - 1;
	
	while (beg < str.size() && (str[beg] == "AND" || str[beg] == "OR") ) {
		beg++;
	}
	
	while (end >= 0 && (str[end] == "AND" || str[end] == "OR") ) {
		end--;
	}
	if (beg <= end) {
		for (int i = beg; i <= end; i++) {
			if (str[i] == "\"1") {
				n_query += "\"";
			}
			else
				n_query += (str[i] + " ");
		}
	}
	return n_query;
}

//Use searchWord(dataStopwords.root, key, false); to check the StopWords to remove
//Move it to checkOperator before check AND, OR...
