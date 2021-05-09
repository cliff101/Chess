#pragma once
#include <string>
#include <vector>
#include <map>
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
		int type = 0;//0 = normal  1 = eat  2 = castling  3 = soldier first move  4 = passeat
		int pos[2] = {-2,-2};//x , y
		static map<int, string> typeint2str;
		static map<string, int> typestr2int;
	private:
	};
	void StartGame();
	vector<movetype> RequestAvaliStep(int req_player,int pos[2], movetype prevplayermovetype);
	static void Printavail(vector<movetype>& in);
private:
	Player* players[2];
	int current_player;
	Board board;
	Viewer viewer;

	int gameturn;//0 = player0  1 = player1
	int state;//0 = move chess  1 = promote  2 = checkmate  3 = nextplayer
	void Lobby();
	void MainGame();
	void Result();

	//void checkpromote(movetype prevplayermovetype);
};