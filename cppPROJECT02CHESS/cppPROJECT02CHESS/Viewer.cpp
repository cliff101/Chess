#include "Viewer.h"

void SetColor(int color = 7)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

void gotoxy(int x, int y) {
	COORD coord;
	coord.X = x; coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	return;
}

void Viewer::print(Board::basechess** board) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			int p[2]; p[0] = i; p[1] = j;
			printOneChess(board[i][j].type, p, board[i][j].turn);
		}
	}
	gotoxy(0, 56);
}
void Viewer::printOneChess(int chesstype, const int pos[2], int turn) {
	int color[7][13];
	int bgcolor, playercolor;
	if ((pos[0] + pos[1]) % 2 == 0) {
		bgcolor = 130;
	}
	else {
		bgcolor = 120;
	}
	if (turn == 0) {
		playercolor = 255;
	}
	else {
		playercolor = 1;
	}
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 13; j++) {
			color[i][j] = bgcolor;
		}
	}
	if (chesstype == 1) {
		color[1][4] = playercolor; color[1][6] = playercolor; color[1][8] = playercolor;
		color[2][3] = playercolor; color[2][5] = playercolor; color[2][6] = playercolor; color[2][7] = playercolor; color[2][9] = playercolor;
		color[3][4] = playercolor; color[3][6] = playercolor; color[3][8] = playercolor;
		color[4][4] = playercolor; color[4][5] = playercolor; color[4][6] = playercolor; color[4][7] = playercolor; color[4][8] = playercolor;
		color[5][3] = playercolor; color[5][4] = playercolor; color[5][5] = playercolor; color[5][6] = playercolor; color[5][7] = playercolor; color[5][8] = playercolor; color[5][9] = playercolor;
	}
	else if (chesstype == 2) {
		color[1][3] = playercolor; color[1][5] = playercolor; color[1][7] = playercolor; color[1][9] = playercolor;
		color[2][4] = playercolor; color[2][6] = playercolor; color[2][8] = playercolor;
		color[3][5] = playercolor; color[3][6] = playercolor; color[3][7] = playercolor;
		color[4][4] = playercolor; color[4][5] = playercolor; color[4][6] = playercolor; color[4][7] = playercolor; color[4][8] = playercolor;
		color[5][3] = playercolor; color[5][4] = playercolor; color[5][5] = playercolor; color[5][6] = playercolor; color[5][7] = playercolor; color[5][8] = playercolor; color[5][9] = playercolor;
	}
	else if (chesstype == 3) {
		color[1][4] = playercolor; color[1][6] = playercolor; color[1][8] = playercolor;
		color[2][4] = playercolor; color[2][5] = playercolor; color[2][6] = playercolor; color[2][7] = playercolor; color[2][8] = playercolor;
		color[3][5] = playercolor; color[3][6] = playercolor; color[3][7] = playercolor;
		color[4][4] = playercolor; color[4][5] = playercolor; color[4][6] = playercolor; color[4][7] = playercolor; color[4][8] = playercolor;
		color[5][3] = playercolor; color[5][4] = playercolor; color[5][5] = playercolor; color[5][6] = playercolor; color[5][7] = playercolor; color[5][8] = playercolor; color[5][9] = playercolor;
	}
	else if (chesstype == 4) {
		color[1][6] = playercolor;
		color[2][5] = playercolor; color[2][6] = playercolor; color[2][7] = playercolor;
		color[3][4] = playercolor; color[3][5] = playercolor; color[3][6] = playercolor; color[3][7] = playercolor; color[3][9] = playercolor;
		color[4][5] = playercolor; color[4][6] = playercolor; color[4][7] = playercolor; color[4][8] = playercolor;
		color[5][3] = playercolor; color[5][4] = playercolor; color[5][5] = playercolor; color[5][6] = playercolor; color[5][7] = playercolor; color[5][8] = playercolor; color[5][9] = playercolor;
	}
	else if (chesstype == 5) {
		color[1][4] = playercolor; color[1][5] = playercolor; color[1][6] = playercolor; color[1][7] = playercolor; color[1][8] = playercolor;
		color[2][3] = playercolor; color[2][4] = playercolor; color[2][6] = playercolor; color[2][7] = playercolor; color[2][8] = playercolor; color[2][9] = playercolor;
		color[3][5] = playercolor; color[3][6] = playercolor; color[3][7] = playercolor; color[3][8] = playercolor; color[3][9] = playercolor;
		color[4][4] = playercolor; color[4][5] = playercolor; color[4][6] = playercolor; color[4][7] = playercolor; color[4][8] = playercolor;
		color[5][3] = playercolor; color[5][4] = playercolor; color[5][5] = playercolor; color[5][6] = playercolor; color[5][7] = playercolor; color[5][8] = playercolor; color[5][9] = playercolor;
	}
	else if (chesstype == 6) {
		color[2][5] = playercolor; color[2][6] = playercolor; color[2][7] = playercolor;
		color[3][4] = playercolor; color[3][5] = playercolor; color[3][6] = playercolor; color[3][7] = playercolor; color[3][8] = playercolor;
		color[4][5] = playercolor; color[4][6] = playercolor; color[4][7] = playercolor;
		color[5][3] = playercolor; color[5][4] = playercolor; color[5][5] = playercolor; color[5][6] = playercolor; color[5][7] = playercolor; color[5][8] = playercolor; color[5][9] = playercolor;
	}

	gotoxy(pos[1] * 13, pos[0] * 7);
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 13; j++) {
			SetColor(color[i][j]);
			cout << " ";
		}
		gotoxy(pos[1] * 13, pos[0] * 7 + i + 1);
	}
	SetColor();
}