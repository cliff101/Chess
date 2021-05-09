#include "HumanPlayer.h"

int* HumanPlayer::SelectChess(int playerid)
{
	int* pos = new int[2];
	cout << "Player: " << playerid << "  Please select a chess x y:";
	cin >> pos[0] >> pos[1];
	return pos;
}

int HumanPlayer::SelectMoveOption(vector<GameManager::movetype>& avail)
{
	int selected_move_id;
	GameManager::Printavail(avail);
	cout << "Please select:";
	cin >> selected_move_id;
	return selected_move_id;
}

void HumanPlayer::OnMove(Board& const board, int* frompos, GameManager::movetype to)
{
	if (GameManager::movetype::typeint2str[to.type] == "passeat") {
		board.RemoveChess(new int[2]{ to.pos[0],frompos[1] });
	}
	board.MoveChess(frompos, to.pos, board.GetChess(frompos));
}

void HumanPlayer::OnPromote(Board& const board, int Pos[2], Board::basechess outchess)
{
}