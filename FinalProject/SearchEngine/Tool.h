#ifndef _TOOL_
#define _TOOL_

#include<iostream>
using namespace std;

int get_index(char key);

vector<pair<string,int>> to_vector(unordered_map<string, int> map);

string get_dir(string folder, string filename);

int string_to_int(string str);

#endif