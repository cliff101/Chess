#pragma once
#include "Board.h"
#include <Windows.h>

using namespace std;

class Viewer {
public:
	static void print(Board::basechess** board);
	static void printOneChess(int chesstype, const int pos[2], int turn, int type = -1);
private:
};