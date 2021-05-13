#include "AIPlayer.h"
#include <chrono>

int* AIPlayer::SelectChess(Board& const board, int playerid)
{
	srand(time(NULL));
	while (true) {
		int* pos = new int[2]{ rand() % 8,rand() % 8 };
		if (board.plot[pos[1]][pos[0]].turn == playerid) {
			return pos;
		}
	}
}

int AIPlayer::SelectMoveOption(std::vector<GameManager::movetype>& avail, int selectedchesstype)
{
	srand(time(NULL));
	int selected_move_id = rand()%avail.size();
	return selected_move_id;
}

int AIPlayer::SelectPromote(Board& const board, int Pos[2])
{
	srand(time(NULL));
	int selected = rand() % 3;
	return selected + 2;
}

void AIPlayer::OnMove(Board& const board, int* frompos, GameManager::movetype to)
{
	if (GameManager::movetype::typeint2str[to.type] == "passeat") {
		board.RemoveChess(new int[2]{ to.pos[0],frompos[1] });
	}
	if (GameManager::movetype::typeint2str[to.type] == "castling") {
		if (to.pos[0] == 6) {//短易位
			board.MoveChess(new int[2]{ 7,frompos[1] }, new int[2]{ 5,frompos[1] });
		}
		else {//長易位
			board.MoveChess(new int[2]{ 0,frompos[1] }, new int[2]{ 3,frompos[1] });
		}

	}
	board.MoveChess(frompos, to.pos);
}

void AIPlayer::OnPromote(Board& const board, int Pos[2], Board::basechess outchess)
{
	board.PlaceChess(Pos, outchess);
}