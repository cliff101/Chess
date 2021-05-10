#include "HumanPlayer.h"

int* HumanPlayer::SelectChess(int playerid)
{
	int* pos = new int[2];
	string temp;
	cout << "-1: surrender" << endl;
	cout << "s: save game" << endl;
	cout << "Player: " << playerid << "  Please select a chess x y:";
	cin >> temp;
	if (temp=="s") {
		pos[0] = temp[0];
		return pos;
	}

	pos[0] = stoi(temp);
	if (pos[0] == -1) {
		return pos;
	}
	cin >> pos[1];
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

void HumanPlayer::OnPromote(Board& const board, int Pos[2], Board::basechess outchess)
{
	board.PlaceChess(Pos, outchess);
}

int HumanPlayer::SelectPromote(Board& const board, int Pos[2])
{
	int selected;
	for (int i = 2; i < 6; i++) {
		cout << i - 2 << ". " << board.typeint2str[i] << endl;
	}
	cout << "Please select which to promote: ";
	cin >> selected;
	return selected + 2;
}