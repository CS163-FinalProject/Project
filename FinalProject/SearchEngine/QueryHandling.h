#ifndef _QUERY_
#define _QUERY_
#include"Trie.h"

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
void intitle_filetype_Operator(unordered_map<string, Trie>& data, unordered_map<string, Trie>& map1, string key);
void minus_Search(unordered_map<string, Trie>& map1, unordered_map<string, Trie>& map2, string key);


void andOperator(string key, unordered_map<string, Trie>& imap);

void orOperator(unordered_map<string, Trie> data, unordered_map<string, Trie>& imap, unordered_map<string, Trie>& omap);

void checkOperator(string query, unordered_map<string, Trie> data, unordered_map<string, Trie>& imap, unordered_map<string, Trie>& omap);


#endif