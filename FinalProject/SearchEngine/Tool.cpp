#include"Tool.h"

#include<iostream>
#include<unordered_map>
#include<vector>

using namespace std;

int get_index(char key){
    if('0' <= key && key <= '9'){
        return key - '0';
    }else if('a' <= key && key <= 'z'){
        return key - 'a' +10;
    }else if('A' <= key && key <= 'Z'){
        return key -'A' + 10;
    }else if( key == '$'){
        return 36;
    }else if(key == '#'){
        return 37;
    }

    return -1;
}

vector<pair<string,int>> to_vector(unordered_map<string, int> map){
    vector<pair<string,int>> ret;

    for(auto it : map){
        ret.push_back(it);
    }
    return ret;
}