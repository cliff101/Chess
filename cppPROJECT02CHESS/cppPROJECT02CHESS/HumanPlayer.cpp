#include "HumanPlayer.h"

int* HumanPlayer::SelectChess(int playerid)
{
	int* pos = new int[2];
	cout << "(q): surrender  ";
	cout << "(s): save game  ";
	cout << "(u): undo  ";
	cout << "(r): redo  ";
	cout << "Player: " << playerid << "\n";
	HANDLE h;
	DWORD NumRead, fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT, fdwModeOld;
	h = GetStdHandle(STD_INPUT_HANDLE);
	GetConsoleMode(h, &fdwModeOld);
	SetConsoleMode(h, fdwMode);
	while (true) {
		INPUT_RECORD in;
		if (!ReadConsoleInput(h, &in, 1, &NumRead) || NumRead > 1) {
			continue;
		}
		if (in.EventType == KEY_EVENT && in.Event.KeyEvent.bKeyDown == false) {
			if (in.Event.KeyEvent.wVirtualKeyCode == 0x51) {
				pos[0] = 'q';
				SetConsoleMode(h, fdwModeOld);
				return pos;
			}
			else if (in.Event.KeyEvent.wVirtualKeyCode == 0x53) {
				pos[0] = 's';
				SetConsoleMode(h, fdwModeOld);
				return pos;
			}
			else if (in.Event.KeyEvent.wVirtualKeyCode == 0x55) {
				pos[0] = 'u';
				SetConsoleMode(h, fdwModeOld);
				return pos;
			}
			else if (in.Event.KeyEvent.wVirtualKeyCode == 0x52) {
				pos[0] = 'r';
				SetConsoleMode(h, fdwModeOld);
				return pos;
			}
		}
		else if (in.EventType == MOUSE_EVENT) {
			if (in.Event.MouseEvent.dwEventFlags == 0 && in.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
				pos[0] = floor(in.Event.MouseEvent.dwMousePosition.X / 13);
				pos[1] = floor(in.Event.MouseEvent.dwMousePosition.Y / 7);
				SetConsoleMode(h, fdwModeOld);
				return pos;
			}
		}
	}
}

int HumanPlayer::SelectMoveOption(vector<GameManager::movetype>& avail, int selectedchesstype)
{
	int selected_move_id;

	for (int i = 0; i < avail.size(); i++) {
		Viewer::printOneChess(3, avail[i].pos, 0, avail[i].type);
	}
	//GameManager::Printavail(avail);
	//cout << "Please select:";
	HANDLE h;
	DWORD NumRead, fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT, fdwModeOld;
	h = GetStdHandle(STD_INPUT_HANDLE);
	GetConsoleMode(h, &fdwModeOld);
	SetConsoleMode(h, fdwMode);
	while (true) {
		INPUT_RECORD in;
		ReadConsoleInput(h, &in, 1, &NumRead);
		if (in.EventType == MOUSE_EVENT) {
			if (in.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
				for (int i = 0; i < avail.size(); i++) {
					if (avail[i].pos[0] == floor(in.Event.MouseEvent.dwMousePosition.X / 13) && avail[i].pos[1] == floor(in.Event.MouseEvent.dwMousePosition.Y / 7)) {
						SetConsoleMode(h, fdwModeOld);
						return i;
					}
				}
			}
			else if (in.Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED) {
				SetConsoleMode(h, fdwModeOld);
				return 9999;
			}
		}
	}
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
	HANDLE h;
	DWORD NumRead, fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT, fdwModeOld;
	h = GetStdHandle(STD_INPUT_HANDLE);
	GetConsoleMode(h, &fdwModeOld);
	SetConsoleMode(h, fdwMode);
	while (true) {
		INPUT_RECORD in;
		ReadConsoleInput(h, &in, 1, &NumRead);
		if (in.EventType == KEY_EVENT && in.Event.KeyEvent.bKeyDown == false) {
			if (in.Event.KeyEvent.wVirtualKeyCode == 0x30) {
				SetConsoleMode(h, fdwModeOld);
				return 2;
			}
			else if (in.Event.KeyEvent.wVirtualKeyCode == 0x31) {
				SetConsoleMode(h, fdwModeOld);
				return 3;
			}
			else if (in.Event.KeyEvent.wVirtualKeyCode == 0x32) {
				SetConsoleMode(h, fdwModeOld);
				return 4;
			}
		}
	}
	cin >> selected;
	return selected + 2;
}