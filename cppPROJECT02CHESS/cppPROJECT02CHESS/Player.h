#pragma once
#include "Board.h"
#include "GameManager.h"

class Board;


class Player {
public:
	virtual void OnMove(Board& const board, int* from, GameManager::movetype to) = 0; // 選擇要從 fromPos 走到 toPos
	virtual void OnPromote(Board& const board, int Pos[2], Board::basechess outchess) = 0; // 升階處理
	virtual int SelectMoveOption(std::vector<GameManager::movetype>& avail, int selectedchesstype) = 0; // 選擇要怎麼走
	virtual int* SelectChess(Board& const board, int playerid) = 0; // 選擇要動哪個chess
	virtual int SelectPromote(Board& const board, int Pos[2]) = 0; // 選擇升階類型
private:
};