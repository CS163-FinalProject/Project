#ifndef _QUERY_
#define _QUERY_
#include"Trie.h"
#include"Tool.h"

#include<string>
#include<queue>
#include<fstream>
#include<unordered_map>
#include<iostream>
#include<algorithm>
#include<sstream>
#include"Trie.h"

using namespace std;



void wildCardOperator(int ast, string key, unordered_map<string, Trie>& imap);

void inTitle_Search(unordered_map<string, Trie>& map1,  string key);

void minus_Search(unordered_map<string, Trie>& imap,  string key);

void intitle_filetype_Operator(unordered_map<string, Trie>& imap, string key);

void Synonyms_Search(string key, unordered_map<string, Trie>& imap, unordered_map<string, Trie>& omap, unordered_map<string, int>& tableKey, unordered_multimap<int, string>& synonyms);



void andOperator(string key, unordered_map<string, Trie>& imap);

void orOperator(unordered_map<string, Trie> data, unordered_map<string, Trie>& imap, unordered_map<string, Trie>& omap);

void checkOperator(string query, unordered_map<string, Trie> data, unordered_map<string, Trie>& imap, unordered_map<string, Trie>& omap);


#endif