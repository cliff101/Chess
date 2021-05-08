#pragma once
#include "Player.h"
#include "Viewer.h"
#include "Board.h"

class Viewer;
class Player;
class Board;

using namespace std;

class GameManager {
public:
	void StartGame();
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
};