#pragma once
#include <map>
#include <string>
#include <iostream>

using namespace std;

class Board {
public:
	class basechess {
	public:
		int type = 0;//define in typestr2int
		int turn = 3;//0 = player0's chess  1 = player1's chess  3 = no one
	private:
	};
	Board();
	void InitBoard();
	void PrintBoard();
	void MoveChess(int frompos[2],int topos[2], basechess bc);
	void RemoveChess(int pos[2]);
	void PlaceChess(int pos[2], basechess bc);
	basechess GetChess(int pos[2]);
	basechess** plot;//player0 的棋子在下面
	map<string, int> typestr2int;
	map<int, string> typeint2str;
private:
};