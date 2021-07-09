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
#include<queue>

vector<string> SenFilter(string sen) {
    vector<string> v;
    string word;
    for (int i = 0; i < sen.length(); i++) {
        if (sen[i] == ' ') {
            v.push_back(word);
            word = "";
        }
        else {
            word = word + sen[i];
        }
    }
    return v;
}

void InputFile(string filename, unordered_map<string, Trie>& data){
    ifstream in;
    in.open("dataset\\" + filename);
    string sen;
    int place = 1;
    if(in.is_open()){
        while(!in.eof()){
            getline(in ,sen);
            vector<string> v = SenFilter(sen);
            if(!data[filename].root) data[filename].root = getNode();
            for (int i = 0; i < v.size(); i++) {
                //cout << v[i];
                insert(data[filename].root, v[i], place, false);
                ++place;
            }
               
        }
    }
    in.close();
}

void InputListFile(string filename, unordered_map<string, Trie> &data){
    ifstream fin;
    fin.open(filename);

    string line;
    int n = 0;
    if(fin.is_open()){
        while (n < 1001) {
            getline(fin, line);
            InputFile(line, data);
            n++;
        }
    }
    else {
        cout << "Cant open file";
    }
    fin.close();

}

void OpenFile(string key) {
    string folder = "dataset\\";
    string filename = folder + key;

    ifstream fin;
    fin.open(filename);



    fin.close();
}

void OuputResult(unordered_map<string, Trie> data) {
    
    priority_queue<pair<string, Trie>, vector<pair<string, Trie>>, cmp> pq;
    priority_queue<pair<string, Trie>, vector<pair<string, Trie>>, cmp> tmpq;
    for (auto it : data) {
        pq.push(it);
    }
    while (true) {
        int choice;
        int n = 1;
        tmpq = pq;
        cout << "[1] Get top 5 results (preview mode)" << endl;
        cout << "[2] Get all results (no preview mode)" << endl;
        cout << "[3] Quit and search another query" << endl;
        
        cout << "You choose mode (1,2,3): ";  cin >> choice;

        if (choice == 1) {
            cout << "\n-Top 5 results: \n" << endl;
            while (!tmpq.empty() && n != 6) {
                cout << "[" << n << "] " << tmpq.top().first << endl;
                tmpq.pop();
                n++;
            }
            cout << "------------------------------------------------------------------" << endl;
        }
        else if (choice == 2) {
            cout << "\n-All results: \n" << endl;
            while (!tmpq.empty()) {
                cout << "[" << n << "] " << tmpq.top().first;
                tmpq.pop();
                if (!tmpq.empty()) {
                    cout << '\t' << '\t' << "[" << n + 1 << "] " << tmpq.top().first << endl;
                    tmpq.pop();
                }
                else {
                    cout << endl;
                }
                n += 2;
            }
            cout << "------------------------------------------------------------------" << endl;
        }
        else if (choice == 3) {
            break;
        }
        else {
            cout << "Invalid choice, please try again\n" << endl;  
        }
    }
}

void destructor(unordered_map<string, Trie>& data) {
    for (auto it : data) {
        deleteTrie(it.second.root);
    }
}

void InputSynonymsFile(unordered_map<string, int>& tableKey, unordered_multimap<int, string>& synonyms) {
    fstream fin;
    fin.open("data.csv");

    while (!fin.eof())
    {
        string line;
        int i = 1;
        while (getline(fin, line))
        {
            stringstream s(line);
            string word;

            while (getline(s, word, ',') && word != "")
            {
                tableKey.insert(make_pair(word, i));
                synonyms.insert(make_pair(i, word));
            }
            ++i;
        }
    }

    fin.close();
}