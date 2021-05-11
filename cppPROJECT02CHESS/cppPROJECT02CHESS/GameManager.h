#pragma once
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include "Viewer.h"
#include "Board.h"

class Viewer;
class Player;
class Board;
class HumanPlayer;

using namespace std;

class GameManager {
public:
	class movetype {
	public:
		int type = 0;//0 = normal  1 = eat  2 = castling  3 = soldier first move  4 = passeat  10 = been checked
		int pos[2] = {-2,-2};//x , y
		bool will_promote = false;
		static map<int, string> typeint2str;
		static map<string, int> typestr2int;
	private:
	};
	class gamelog {//use a vector of this log, use the vector to simulate Undo Redo Save Load.
	public:
		gamelog() :board(Board{}),current_player(3) {}
		gamelog(Board b, int i) :board(b), current_player(i) {}
		Board board;
		int current_player;
	};

	void StartGame();
	vector<movetype> RequestAvaliStep(Board& inboard, int req_player,int pos[2], movetype prevplayermovetype,bool kingcheck = true);
	static void Printavail(vector<movetype>& in);
private:
	Player* players[2];
	int current_player;
	Board board;
	Viewer viewer;

	vector<gamelog> gamerecord;

	int gameturn;//0 = player0  1 = player1
	int state;//0 = move chess  1 = checkmate
	void Lobby();
	void MainGame(string filename = "");
	void Result();
	void Replay(string filename);

	bool checkcheck(Board& board,int which_player);
	int* getkingpos(Board& inboard, int which_player);
};