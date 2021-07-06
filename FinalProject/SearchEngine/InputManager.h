#ifndef _INPUT_
#define _INPUT_

#include"Trie.h"

#include<string>
#include<unordered_map>
#include<vector>
#include<iostream>

struct cmp {
    bool operator()(pair<string, Trie> one, pair<string, Trie> other) {
        return one.second.score < other.second.score;
    }
};

vector<string> SenFilter(string sen);

void InputFile(string filename, unordered_map<string, Trie>& data);

void InputListFile(string filename, unordered_map<string, Trie> &data);

void OuputResult(string key, unordered_map<string, Trie> data);

void destructor(unordered_map<string, Trie>& data);
    

#endif