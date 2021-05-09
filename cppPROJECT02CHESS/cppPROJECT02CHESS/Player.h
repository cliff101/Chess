#pragma once
#include "Board.h"
#include "GameManager.h"

class Board;

using namespace std;

class Player {
public:
	virtual void OnMove(Board& const board, int* from, GameManager::movetype to) = 0; // 選擇要從 fromPos 走到 toPos
	virtual void OnPromote(Board& const board, int Pos[2], Board::basechess outchess) = 0; // 選擇升階類型
	virtual int SelectMoveOption(vector<GameManager::movetype>& avail) = 0; // 選擇要怎麼走
	virtual int* SelectChess(int playerid) = 0; // 選擇要動哪個chess
private:
};