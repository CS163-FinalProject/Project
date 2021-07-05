#include"Trie.h"
#include"Tool.h"
#include"InputManager.h"

#include<string>
#include<queue>
#include<fstream>
#include<unordered_map>
#include<iostream>
#include<algorithm>
#include<sstream>

void InputFile(string filename, unordered_map<string, Trie>& data){
    ifstream in;
    in.open("dataset\\" + filename);
    string sen;
    if(in.is_open()){
        while(!in.eof()){
            getline(in ,sen);
            cout << sen << endl;
            TrieNode* tmp = new TrieNode;
            data[filename].insert(tmp, sen, 0, false);
        }
    }
    in.close();
}

void InputListFile(string filename, unordered_map<string, Trie> &data){
    ifstream fin;
    fin.open(filename);
    
    string line;
    if(fin.is_open()){
        
            getline(fin, line);
            //cout << "YES";
            InputFile(line, data);
        
    }
    else {
        cout << "Cant open file";
    }
    fin.close();

}