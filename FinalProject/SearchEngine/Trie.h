#ifndef _TRIE_
#define _TRIE_

#include<string>
#include<unordered_map>
#include<vector>
#include<iostream>

using namespace std;

class TrieNode{
    public:
        TrieNode* child[42]; //0-9: number, 10-35: character, 36: ' ', 37: '.', 38 '$' , 39 '%', 40 '#', 41 '-'
        bool isLeaf, isTitle;
        vector<int> order;
        
};

class Store{
    public:
        string filename;
        vector<int> pos;
        int point;
};

class Trie{
    public:
        TrieNode* getNode();

        void insert(TrieNode* root, string key, int place, bool title);

        TrieNode* search(TrieNode* root, string key, bool title);
};


#endif