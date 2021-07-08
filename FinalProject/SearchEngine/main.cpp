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
#include<iterator>

using namespace std;

int main(){
    clock_t begin, end;
    cout << "Building..." << endl;
    begin = clock();

    unordered_map<string,Trie> data;
    InputListFile("dataset\\___index.txt", data);

    //Use for synonyms
    //Each word will have a special value stored in tableKey that use for search.
    //Synonyms words have the same value.
    //That value will be assign to list of synonyms words in the multimap.
    unordered_map<string, int> tableKey;  
    unordered_multimap<int, string> synonyms;
    InputSynonymsFile(tableKey, synonyms);

    end = clock();

    data["053.txt"].score = 0;
    data["Data8.txt"].score = 1;
    cout << "Completed in " << (end - begin) / CLOCKS_PER_SEC << " s." << endl;

   
    cout << "------------------------------------------------------------------" << endl;
    cout << " Welcome to our SUPER Search Engine " << endl;
    while (true) {
        
        int choice;

        cout << "Continue to search? if (yes) press 1 (no) press 0" << endl;

        cout << "You choose: "; cin >> choice; cin.ignore();
        cout << "------------------------------------------------------------------" << endl;
        if (choice == 1) {
            cout << "Queries:" << endl;
            cout << "[1] _ AND _ (FINISHED)" << endl;
            cout << "[2] _ OR _ (FINISHED)" << endl;
            cout << "[3] intitle: _ to the end. (FINISHED)" << endl;
            cout << "[4] filetype:txt (FINISHED)" << endl;
            cout << "[5] (exclude) -_ (FINISHED)" << endl;
            cout << "[6] exact word \"tallest bulding\" (FINISHED)" << endl;
            cout << "[7] wildcard \"tallest * building\" (FINISHED)" << endl;
            cout << "[6] (price) $ _ (FINISHED)" << endl;
            cout << "[7] (hashtag) # _ (FINISHED)" << endl;

            cout << "Please input to find: ";

            string query = "";
            getline(cin, query); cout << endl;
            
            unordered_map<string, Trie> map1, map2;
            
            unordered_map<string, Trie> imap = data;
            unordered_map<string, Trie> omap;
            checkOperator(query, data, imap, omap);
            //Synonyms_Search(query, imap, omap, tableKey, synonyms);
            
            OuputResult(imap); cout << endl;
            cout << "------------------------------------------------------------------" << endl;
        }
        else {
            break;
        }


    }
    cout << "Thank you for using!!!" << endl;

    


    destructor(data);
    //destructor(imap);
    //destructor(omap);
}