#pragma once
#include <map>
#include <string>

using namespace std;

class Board {
public:
	Board();
	int** plot;
	map<string, int> typestr2int;
	map<int, string> typeint2str;
private:
};