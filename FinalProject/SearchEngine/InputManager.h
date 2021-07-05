#ifndef _INPUT_
#define _INPUT_

#include"Trie.h"

#include<string>
#include<unordered_map>
#include<vector>
#include<iostream>


vector<string> SenFilter(string sen);

void InputFile(string filename, unordered_map<string, Trie>& data);

void InputListFile(string filename, unordered_map<string, Trie> &data);

void OuputResult(string key, unordered_map<string, Trie> data);
    

#endif