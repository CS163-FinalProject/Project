#ifndef _QUERY_
#define _QUERY_

#include<string>
#include<queue>
#include<fstream>
#include<unordered_map>
#include<iostream>
#include<algorithm>
#include<sstream>
#include"Trie.h"

using namespace std;

int checkOperator(string query);
void inTitle_Search(unordered_map<string, Trie>& data, unordered_map<string, Trie>& map1, unordered_map<string, Trie>& map2, string key);
void minus_Search(unordered_map<string, Trie>& map1, unordered_map<string, Trie>& map2, string key);

#endif