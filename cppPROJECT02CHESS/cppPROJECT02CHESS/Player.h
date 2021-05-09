#pragma once
#include "Board.h"
#include "GameManager.h"

class Board;

using namespace std;

class Player {
public:
	virtual void OnMove(Board& const board, int* from, GameManager::movetype to) = 0; // ��ܭn�q fromPos ���� toPos
	virtual void OnPromote(Board& const board, int Pos[2], Board::basechess outchess) = 0; // ��ܤɶ�����
	virtual int SelectMoveOption(vector<GameManager::movetype>& avail) = 0; // ��ܭn���
	virtual int* SelectChess(int playerid) = 0; // ��ܭn�ʭ���chess
private:
};