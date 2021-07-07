#include"Trie.h"
#include"Tool.h"
#include"QueryHandling.h"
#include"InputManager.h"
#include"QueryHandling.h"

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
    string query = "";
    getline(cin, query);
    


    /*vector<int> v;
    v = searchWordpos(data["000.txt"].root, "our");
    //OuputResult(key, data);
    for (int i = 0; i < v.size(); i++)
        cout << v[i] << " ";*/

    //Result Containers
    unordered_map<string, Trie> map1, map2;

    //Test
    //// Move to {void checkOperator}

/*    intitle_filetype_Operator(data, map1, key);
    string tmp;
    cout << "Word to eliminate: ";
    getline(cin, tmp);
    minus_Search(map1, map2, tmp); */   


    unordered_map<string, Trie> imap = data;
    unordered_map<string, Trie> omap;
    checkOperator(query, data, imap, omap);

    //vector<int> v;
    //v = searchWordpos(data["000.txt"].root, "our");
    OuputResult(imap);
    //for (int i = 0; i < v.size(); i++)
        //cout << v[i] << " ";

    destructor(data);
    //destructor(imap);
    //destructor(omap);
}