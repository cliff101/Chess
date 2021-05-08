#pragma once
#include "Board.h"

class Board;

using namespace std;

class Player {
public:
	virtual void OnMove(/*ex. Board& const board, Position& outFromPos,
Position& outToPos*/) = 0; // ��ܭn�q fromPos ���� toPos
	virtual void OnPromote(/*ex. Board& const board, Position& const
	pawnPos, PieceType& outType*/) = 0; // ��ܤɶ�����
private:
};