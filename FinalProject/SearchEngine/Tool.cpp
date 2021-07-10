#include"Tool.h"
#include<stdio.h>
#include<conio.h>
using namespace std;

int get_index(char key){
    if('0' <= key && key <= '9'){
        return key - '0';
    }else if('a' <= key && key <= 'z'){
        return key - 'a' +10;
    }else if('A' <= key && key <= 'Z'){
        return key -'A' + 10;
    }else if( key == '@'){
        return 36;
    }else if(key == '_'){
        return 37;
    }else if(key == '$'){
        return 38;
    }else if(key == '%'){
        return 39;
    }else if(key == '#'){
        return 40;
    }else if(key == '-'){
        return 41;
    }

    return -1;
}

string get_dir(string folder, string filename){
    return folder + "\\" + filename + ".txt"; 
}

int string_to_int(string str){
    int ans = 0;
    for(int i = 0; i < str.length(); i++){
        ans = ans*10 +(str[i] - '0');
    }
    return ans;
}

vector<pair<string,int>> to_vector(unordered_map<string, int> map){
    vector<pair<string,int>> ret;

    for(auto it : map){
        ret.push_back(it);
    }
    return ret;
}

int binarySearch(int x, vector<int> a, int l, int r) {
    if (l <= r) {
        int mid = (l + r) / 2;
        if (a[mid] == x) {
            return mid;
        }
        else if (a[mid] < x) {
            return binarySearch(x, a, mid+1, r);
        }
        else if (a[mid] > x) {
            return binarySearch(x, a, l, mid-1);
        }
    }
    else {
        return -1;
    }
}

void TextColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}