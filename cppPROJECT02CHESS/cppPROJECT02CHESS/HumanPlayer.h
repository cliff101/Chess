#pragma once
#include "Player.h"
#include "GameManager.h"
#include "Board.h"

class HumanPlayer :public Player {
public:
	virtual int* SelectChess(int playerid) override;
	virtual int SelectMoveOption(vector<GameManager::movetype>& avail) override;
	virtual void OnMove(Board& const board, int* frompos, GameManager::movetype to) override;
	virtual void OnPromote(Board& const board, int Pos[2], Board::basechess outchess) override;
	virtual int SelectPromote(Board& const board, int Pos[2]) override;
private:
};