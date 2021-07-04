#include"Trie.h"
#include"Tool.h"

#include<string>
#include<unordered_map>
#include<iostream>

using namespace std;

void Trie::build(string filename, unordered_map<string,int> data){
    if(data.size() == 0) return;

    TrieNode* root = this->root;

    for(auto it = data.begin(); it != data.end(); it++){
        string key = it->first;
        if(!root){
            root = new TrieNode;
        }
        TrieNode* roottmp = root;
        for(int i = 0; i < key.length(); i++){
            int tmp = get_index(key[i]);
            if(tmp == -1){
                continue;
            }
            if(!root->child[tmp]) roottmp->child[tmp] = new TrieNode;
            roottmp = roottmp->child[tmp];
        }

    }

    if(!this->root) this->root = root;
}
