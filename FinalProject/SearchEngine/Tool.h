#ifndef _TOOL_
#define _TOOL_

#include<iostream>
#include<vector>
#include<unordered_map>
#include <windows.h>
#include<stdio.h>
#include<conio.h>
using namespace std;

void TextColor(int color);

int get_index(char key);

vector<pair<string,int>> to_vector(unordered_map<string, int> map);

string get_dir(string folder, string filename);

int string_to_int(string str);

int binarySearch(int x, vector<int> a, int l, int r);

string WordFilter(string word);
#endif