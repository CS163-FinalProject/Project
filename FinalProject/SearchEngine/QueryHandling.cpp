#include"QueryHandling.h"

#include<string>
#include<queue>
#include<fstream>
#include<unordered_map>
#include<iostream>
#include<algorithm>
#include<sstream>

using namespace std;

int checkOperator(string query) {
	stringstream ss(query);
	string tmp;
	while (ss >> tmp) {
		string get; get = tmp.substr(0, 8);
		if (tmp == "AND") return 1;
		if(tmp == "OR") return 2;
		if (get == "intitle:") return 3;
		if (tmp[0] == '-') return 4;
		//if(tmp)

	}
}