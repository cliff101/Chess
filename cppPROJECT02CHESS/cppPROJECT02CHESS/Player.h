#pragma once
#include "Board.h"
#include "GameManager.h"

class Board;


class Player {
public:
	virtual void OnMove(Board& const board, int* from, GameManager::movetype to) = 0; // ��ܭn�q fromPos ���� toPos
	virtual void OnPromote(Board& const board, int Pos[2], Board::basechess outchess) = 0; // �ɶ��B�z
	virtual int SelectMoveOption(std::vector<GameManager::movetype>& avail, int selectedchesstype) = 0; // ��ܭn���
	virtual int* SelectChess(Board& const board, int playerid) = 0; // ��ܭn�ʭ���chess
	virtual int SelectPromote(Board& const board, int Pos[2]) = 0; // ��ܤɶ�����
private:
};