#ifndef _TRIE_
#define _TRIE_

#include<string>
#include<unordered_map>
#include<vector>
#include<iostream>

using namespace std;

class TrieNode{
    public:
        unordered_map<string,int> data;
        //first: file name; second: frequency

        TrieNode* child[38];
        //26 aplhabet + 10 number + $ + #
        //every node has 38 children

        bool isExist = false;

        void trieTranverse(TrieNode* head);
};

class Trie{
    private:
        TrieNode* root = nullptr;
    public:
        vector<pair<string, int>> search(string keyword);
        //search anf rank based on keywords
        //first: filename , second// frequency

        void build(string key, unordered_map<string,int> data);

        void save(string filename);

        void load(string filename);

        bool isEmpty();

        void trieTranverse();

};


#endif