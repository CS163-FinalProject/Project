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
#include<random>
#include<queue>

using namespace std;

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

void OpenFile(string key, unordered_map<string,Trie> data,  vector<string> line) {
    string folder = "dataset\\";
    string filename = folder + key;

    ifstream fin;
    fin.open(filename);
    string tmp; string word;

    vector<int> highlight;

    for (int i = 0; i < line.size(); i++) {
        vector<int> v = searchWordpos(data[key].root, line[i]);
        for (int i = 0; i < v.size(); i++) {
            highlight.push_back(v[i]);
        }
    }

    if (highlight.size() != 0) {
        sort(highlight.begin(), highlight.end());
        
        int cnt = 1; bool isNote = false; string preview = ""; int preview_cnt = 0;
        int stop_point = highlight[0] - 1;

        if (fin.is_open()) {
            while (!fin.eof()) {
                getline(fin, tmp);
                stringstream ss(tmp);
                while (ss >> word) {

                    if (cnt == stop_point) {
                        //cout << word;
                        isNote = true;
                    }

                    if (isNote) {
                        preview += (word + " ");
                        ++preview_cnt;
                    }

                    if (preview_cnt >= 100) {
                        break;
                    }
                    ++cnt;
                }
                if (preview_cnt >= 100) {
                    break;
                }

            }
        }fin.close();

        int i = 0;
        stringstream sss(preview); cout << "..";
        while (sss >> word) {
            bool hl = false;
            for (int i = 0; i < line.size(); i++) {
                if (word == line[i] || word == (line[i] + ":") || word == (line[i] + ",") || word == (line[i] + ".") || word == (line[i] + "!")) {
                    hl = true;
                }
            }
            if (hl) {
                TextColor(11);
                cout << word << " ";
            }
            else {
                TextColor(7);
                cout << word << " ";
            }
        }cout << ".." << endl;
    }
    else {
        cout << "....\n";
    }



    
}

void OuputResult(unordered_map<string, Trie> data, vector<string> line) {
    
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
            cout << "\n-Top 5 results:" << endl;
            cout << "------------------------------------------------------------------" << endl;
            while (!tmpq.empty() && n != 6) {
                cout << "[" << n << "] " << tmpq.top().first << endl;
                OpenFile(tmpq.top().first, data, line);
                tmpq.pop();
                n++;
            }
            
            cout << "------------------------------------------------------------------" << endl;
        }
        else if (choice == 2) {
            cout << "\n-All results:" << endl;
            cout << "------------------------------------------------------------------" << endl;
            while (!tmpq.empty()) {
                
                cout << "[" << n << "] " << tmpq.top().first;
                tmpq.pop();
                if (!tmpq.empty()) {
                    cout << '\t' << '\t' << '\t' << '\t' << '\t' << "[" << n + 1 << "] " << tmpq.top().first << endl;
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

void inputStopwordsFile(string filename, Trie& dataStopwords)
{
    ifstream fin;
    fin.open(filename);

    string word;
    int place = 1;
    dataStopwords.root = getNode();
    if (fin.is_open()) {
        while (!fin.eof()) 
        {
            getline(fin, word);
            insert(dataStopwords.root, word, place, false);
            ++place;
        }
    }
    else cout << "Can't open file !\n";

    fin.close();
}