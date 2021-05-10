#pragma once
#include "Board.h"
#include <Windows.h>

class Board;

using namespace std;

class Viewer {
public:
	void print(Board::basechess** board);
	void printOneChess(int chesstype, const int pos[2], int turn);
private:
};