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

using namespace std;

int main(){
    unordered_map<string,Trie> data;
    InputListFile("dataset\\___index.txt", data);

    //Trie tree;
    //tree.getNode();
    string filename = "0.txt";
    cout << "Please input a key";
    string key = "";
    getline(cin, key);
    OuputResult(key, data);
}