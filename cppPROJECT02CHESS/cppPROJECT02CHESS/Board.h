#pragma once
#include <map>
#include <string>
#include <iostream>


class Viewer;

class Board {
public:
	class basechess {
	public:
		int type = 0;//define in typestr2int
		int turn = 3;//0 = player0's chess  1 = player1's chess  3 = no one
		bool moved = false;//是否曾經移動過
	private:
	};
	Board();
	Board(const Board&);
	Board operator=(const Board &);
	void InitBoard();
	void PrintBoard();
	void MoveChess(int frompos[2],int topos[2],bool animation = true);
	void RemoveChess(int pos[2]);
	void PlaceChess(int pos[2], basechess bc);
	basechess GetChess(int pos[2]);
	basechess** plot;//player0 的棋子在下面
	std::map<std::string, int> typestr2int;
	std::map<int, std::string> typeint2str;
	Board SimulteMove(int frompos[2], int topos[2]);
private:
};