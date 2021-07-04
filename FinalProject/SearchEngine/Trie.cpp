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
        roottmp->data[filename] += it->second;
    }

    if(!this->root) this->root = root;
}

void Trie::save(string filename){
    ofstream fout;
    fout.open(get_dir("dataset", filename), ios::app);

    queue<TrieNode*> mq;
    mq.push(root);

    while(!mq.empty()){
        TrieNode* u = mq.front();
        mq.pop();

        if(!u){
            fout << "0\n";
            continue;
        }

        unordered_map<string,int> tmp;

        for(auto& it : u->data){
            string strtmp = "";
            for(int j = 0; j < it.first.length(); j++){
                if(it.first[j] == ' ') strtmp += '@';
                else strtmp += it.first[j];
            }

            tmp[strtmp] = it.second;
            fout << strtmp << " " << it.second << " ";
        }
        u->data.clear();
        u->data = tmp;

        fout << "_END_ -1\n";

        for(int i = 0; i < 38; i++){
            mq.push(u->child[i]);
        }

    }
    fout.close();
}

void Trie::load(string filename){
    ifstream fin;
    fin.open(get_dir("dataset", filename));

    if(!root) root = new TrieNode;

    string line;
    getline(fin, line);

    queue<TrieNode*> mq;
    mq.push(root);

    while(!fin.eof()){
        if(mq.empty()) break;

        TrieNode* u = mq.front();
        mq.pop();

        for(int c = 0; c < 38; c++){
            getline(fin, line); // read a line

            if(line.length() == 0){
                break;
            }

            if(line == "0"){
                u->child[c] = nullptr;
                continue;
            }

            u->child[c] = new TrieNode;
            istringstream iss(line); // read per word in a line

            do{
                string word, num;
                iss >> word >> num;

                if(word == "_END_") break;

                for(int j = 0; j < word.length(); j++){
                    if(word[j] == '@'){
                        word[j] = ' ';
                    }
                }

                string file = word;
                int freq = string_to_int(num);

                root->child[c]->data[string(file)] = freq;

            }while(iss);

            mq.push(root->child[c]);
        }
    }
}

vector<pair<string,int>> Trie::search(string keyword){
    if(!root){
        return vector<pair<string,int>>(); //null
    }
    TrieNode* roottmp = root;
    for(int i = 0; i < keyword.length(); i++){
        if(!roottmp) return vector<pair<string,int>>();
        roottmp = roottmp->child[get_index(keyword[i])];
    }

    return to_vector(roottmp->data);
}
