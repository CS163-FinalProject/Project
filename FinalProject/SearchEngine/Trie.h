#ifndef _TRIE_
#define _TRIE_

#include<string>
#include<unordered_map>
#include<vector>
#include<iostream>

using namespace std;

struct TrieNode{
        TrieNode* child[42]; //0-9: number, 10-35: character, 36: '@', 37: '.', 38 '$' , 39 '%', 40 '#', 41 '-'
        bool isLeaf = false, isTitle;
        vector<int> order;
};

struct Store{
        string filename;
        vector<int> pos;
        int point;
};

struct Trie{
        TrieNode* root = nullptr;
        int score = 0;
};

TrieNode* getNode();

void insert(TrieNode* root, string key, int place, bool title);

TrieNode* searchWord(TrieNode* root, string key, bool title);

void deleteTrie(TrieNode*& root);

vector<int> searchWordpos(TrieNode* root, string key);






#endif