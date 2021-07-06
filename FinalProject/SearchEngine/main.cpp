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
    cout << "Building..." << endl;
    begin = clock();
    unordered_map<string,Trie> data;
    InputListFile("dataset\\___index.txt", data);
    end = clock();

    data["053.txt"].score = 0;
    data["Data8.txt"].score = 1;
    cout << "Completed in " << (end - begin) / CLOCKS_PER_SEC << " s." << endl;

   
    cout << "------------------------------------------------------------------" << endl;
    cout << "Please input a key to find: ";
    string key = "";
    getline(cin, key);
    OuputResult(key, data);

    destructor(data);
}