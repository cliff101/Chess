#pragma once
#include "Player.h"
#include "GameManager.h"
#include "Board.h"

class WeekAIPlayer :public Player {
public:
	virtual int* SelectChess(Board& const board, int playerid, GameManager::movetype prevplayermovetype) override;
	virtual int SelectMoveOption(std::vector<GameManager::movetype>& avail, int selectedchesstype) override;
	virtual void OnMove(Board& const board, int* frompos, GameManager::movetype to) override;
	virtual void OnPromote(Board& const board, int Pos[2], Board::basechess outchess) override;
	virtual int SelectPromote(Board& const board, int Pos[2]) override;
private:
	bool checkdie(Board& inboard, int playerid, GameManager::movetype prevplayermovetype, int pos[2]);
	int* getkingpos(Board& inboard, int which_player);
	bool checkcheck(Board& inboard, int which_player);
	int selectedk=0;
};