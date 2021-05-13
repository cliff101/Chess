#pragma once
#include "Player.h"
#include "GameManager.h"
#include "Board.h"

class AIPlayer :public Player {
public:
	virtual int* SelectChess(Board& const board, int playerid) override;
	virtual int SelectMoveOption(std::vector<GameManager::movetype>& avail, int selectedchesstype) override;
	virtual void OnMove(Board& const board, int* frompos, GameManager::movetype to) override;
	virtual void OnPromote(Board& const board, int Pos[2], Board::basechess outchess) override;
	virtual int SelectPromote(Board& const board, int Pos[2]) override;
private:
};