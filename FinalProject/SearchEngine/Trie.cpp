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

TrieNode* Trie::getNode(){
    TrieNode* root = new TrieNode;
    if(root){
        root->isLeaf = false;
        root->isTitle = false;
        for(int i = 0; i < 42; i++) root->child[i] = false;
    }
    return root;
}

void Trie::insert(TrieNode* root, string key, int place, bool title){
    TrieNode* cur = root;
    int id;
    for(int i = 0; i < key.length(); ++i){
        id = get_index(key[i]);
        if(id == -1) continue;
        if(!cur->child[id]) cur->child[id] = new TrieNode;
        cur = cur->child[id];
    }

    cur->isLeaf = true;
}

TrieNode* Trie::search(TrieNode* root, string key, bool title){
    TrieNode* cur = root;
    int id;
    for(int i = 0; i < key.length(); i++){
        id = get_index(key[i]);
        if(id == -1) continue;
        if(!cur->child[id]) return nullptr;
        cur = cur->child[id];
    }
    if(cur){
        if(title && !cur->isTitle) return nullptr;
        if(cur->isLeaf) return cur;
    }
    return nullptr;
}