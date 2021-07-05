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
#include<time.h>

using namespace std;

int main(){
    clock_t begin, end;

    begin = clock();
    unordered_map<string,Trie> data;
    InputListFile("dataset\\___index.txt", data);
    end = clock();

    cout << "Build Time: " << (end - begin) / CLOCKS_PER_SEC << endl;

    //Trie tree;
    //tree.getNode();
    string filename = "0.txt";
    cout << "Please input a key" << endl;
    string key = "";
    getline(cin, key);
    OuputResult(key, data);
}