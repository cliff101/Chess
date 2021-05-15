#include "HumanPlayer.h"
#include <chrono>

int* HumanPlayer::SelectChess(Board& const board, int playerid, GameManager::movetype prevplayermovetype)
{
	int* pos = new int[2];
	std::cout << "(q): surrender  ";
	std::cout << "(s): save game  ";
	std::cout << "(u): undo  ";
	std::cout << "(r): redo  ";
	std::cout << "(f): fresh  ";
	std::cout << "Player: " << playerid << "\n";
	HANDLE h;
	DWORD NumRead, fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT, fdwModeOld;
	h = GetStdHandle(STD_INPUT_HANDLE);
	GetConsoleMode(h, &fdwModeOld);
	SetConsoleMode(h, fdwMode);
	auto start = std::chrono::system_clock::now();
	long long timeleft, timeleftold = 0;
	while (true) {
		INPUT_RECORD in;
		GetNumberOfConsoleInputEvents(h, &NumRead);

		timeleft = 60 - (std::chrono::system_clock::now() - start).count() / 10000000;
		if (timeleft != timeleftold) {
			std::cout << "(我是棋鐘)Time Left:" << timeleft << "\t\t\t\t\t\t";
		}
		if (NumRead > 0) {
			ReadConsoleInput(h, &in, 1, &NumRead);
			if (in.EventType == KEY_EVENT && in.Event.KeyEvent.bKeyDown == false) {
				if (in.Event.KeyEvent.wVirtualKeyCode == 0x51) {
					pos[0] = 'q';
					std::cout << "\r";
					SetConsoleMode(h, fdwModeOld);
					return pos;
				}
				else if (in.Event.KeyEvent.wVirtualKeyCode == 0x53) {
					pos[0] = 's';
					std::cout << "\r";
					SetConsoleMode(h, fdwModeOld);
					return pos;
				}
				else if (in.Event.KeyEvent.wVirtualKeyCode == 0x55) {
					pos[0] = 'u';
					std::cout << "\r";
					SetConsoleMode(h, fdwModeOld);
					return pos;
				}
				else if (in.Event.KeyEvent.wVirtualKeyCode == 0x52) {
					pos[0] = 'r';
					SetConsoleMode(h, fdwModeOld);
					std::cout << "\r";
					return pos;
				}
				else if (in.Event.KeyEvent.wVirtualKeyCode == 0x46) {
					pos[0] = 'f';
					std::cout << "\r";
					SetConsoleMode(h, fdwModeOld);
					return pos;
				}
			}
			else if (in.EventType == MOUSE_EVENT) {
				if (in.Event.MouseEvent.dwEventFlags == 0 && in.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
					pos[0] = floor(in.Event.MouseEvent.dwMousePosition.X / 13);
					pos[1] = floor(in.Event.MouseEvent.dwMousePosition.Y / 7);
					std::cout << "\r";
					if (pos[0] > 7 || pos[0] < 0 || pos[1]>7 || pos[1] < 0) {
						continue;
					}
					SetConsoleMode(h, fdwModeOld);
					return pos;
				}
			}
		}
		else if (timeleft <= 0) {
			pos[0] = 'q';
			std::cout << "\r";
			std::cout << '\n';
			SetConsoleMode(h, fdwModeOld);
			return pos;
		}
		if (timeleft != timeleftold) {
			std::cout << "\r";
			timeleftold = timeleft;
		}
		Sleep(10);
	}
}

int HumanPlayer::SelectMoveOption(std::vector<GameManager::movetype>& avail, int selectedchesstype)
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

int HumanPlayer::SelectPromote(Board& const board, int Pos[2])
{
	int selected;
	for (int i = 2; i < 6; i++) {
		std::cout << i - 2 << ". " << board.typeint2str[i] << "\t\t\t\t\t\t" << std::endl;
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
	std::cin >> selected;
	return selected + 2;
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