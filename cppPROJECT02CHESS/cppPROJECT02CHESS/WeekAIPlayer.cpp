#include "WeekAIPlayer.h"
#include <chrono>

bool WeekAIPlayer::checkcheck(Board& inboard, int which_player) {
	int* kingpos = getkingpos(inboard, which_player);
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (inboard.plot[i][j].turn == (1 - which_player)) {
				int* temppos = new int[2]{ j,i };
				std::vector<GameManager::movetype> avail = GameManager::RequestAvaliStep(inboard, (1 - which_player), temppos, GameManager::movetype{}, false);
				delete[] temppos;
				for (int k = 0; k < avail.size(); k++) {
					if (GameManager::movetype::typeint2str[avail[k].type] == "eat" && avail[k].pos[0] == kingpos[0] && avail[k].pos[1] == kingpos[1]) {
						return true;
					}
				}
			}
		}
	}
	return false;
}
int* WeekAIPlayer::getkingpos(Board& inboard, int which_player)
{
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (inboard.plot[i][j].turn == which_player && inboard.typeint2str[inboard.plot[i][j].type] == "king") {
				return new int[2]{ j,i };
			}
		}
	}
}
bool WeekAIPlayer::checkdie(Board& inboard, int playerid, GameManager::movetype prevplayermovetype, int pos[2]) {
	bool die = false;
	for (int a = 0; !die && a < 8; a++) {
		for (int b = 0; !die && b < 8; b++) {
			if (inboard.plot[a][b].turn!=3 && inboard.plot[a][b].turn != playerid) {
				int* temppos = new int[2]{ b,a };
				auto testavail = GameManager::RequestAvaliStep(inboard, 1 - playerid, temppos, prevplayermovetype, true);
				delete[] temppos;
				for (int c = 0; c < testavail.size(); c++) {
					if (testavail[c].pos[0] == pos[0] && testavail[c].pos[1] == pos[1]) {
						die = true;
						break;
					}
				}
			}
		}
	}
	//if (die) {
	//	std::cout << pos[0]<<" "<<pos[1];
	//}
	return die;
}

int* WeekAIPlayer::SelectChess(Board& const board, int playerid, GameManager::movetype prevplayermovetype)
{
	srand(time(NULL));
	std::vector<std::vector<int>>posk(6, std::vector<int>(0));
	int* retrealpos;
	std::vector<int*> retpos;
	std::vector<int*> reteatpos;
	std::vector<int*> retnotdiepos;
	std::vector<int*> reteatnotdiepos;
	std::vector<int*> retcheckpos;
	std::vector<int*> retchecknotdiepos;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board.plot[i][j].turn == playerid) {
				int* temppos = new int[2]{ j,i };
				auto avail = GameManager::RequestAvaliStep(board, playerid, temppos, prevplayermovetype, true);
				delete[] temppos;
				for (int k = 0; k < avail.size(); k++) {
					int* temppos = new int[2]{ j,i };
					auto simboard = board.SimulteMove(temppos, avail[k].pos);
					delete[] temppos;

					bool die = checkdie(simboard, playerid, prevplayermovetype, avail[k].pos);
					if (checkcheck(simboard, playerid)) {
						if (!die) {
							retchecknotdiepos.push_back(new int[2]{ j,i });
							posk[5].push_back(k);
						}
						else {
							retcheckpos.push_back(new int[2]{ j,i });
							posk[4].push_back(k);
						}
					}
					else if (avail[k].type == 1 || avail[k].type == 4) {
						if (!die) {
							reteatnotdiepos.push_back(new int[2]{ j,i });
							posk[3].push_back(k);
						}
						else {
							reteatpos.push_back(new int[2]{ j,i });
							posk[1].push_back(k);
						}
					}
					else if (avail[k].type == 4) {
						if (!die) {
							retnotdiepos.push_back(new int[2]{ j,i });
							posk[2].push_back(k);
						}
						else {
							retpos.push_back(new int[2]{ j,i });
							posk[0].push_back(k);
						}
					}
					else if (avail[k].type == 3) {
						if (!die) {
							retnotdiepos.push_back(new int[2]{ j,i });
							posk[2].push_back(k);
						}
						else {
							retpos.push_back(new int[2]{ j,i });
							posk[0].push_back(k);
						}
					}
				}
			}
		}
	}

	if (retchecknotdiepos.size() != 0) {
		int selectrandmove = rand() % retchecknotdiepos.size();
		retrealpos = new int[2]{ retchecknotdiepos[selectrandmove][0], retchecknotdiepos[selectrandmove][1] };
		selectedk = posk[5][selectrandmove];
	}
	else if (retcheckpos.size() != 0) {
		int selectrandmove = rand() % retcheckpos.size();
		retrealpos = new int[2]{ retcheckpos[selectrandmove][0], retcheckpos[selectrandmove][1] };
		selectedk = posk[4][selectrandmove];
	}
	else if (reteatnotdiepos.size() != 0) {
		int selectrandmove = rand() % reteatnotdiepos.size();
		retrealpos = new int[2]{ reteatnotdiepos[selectrandmove][0], reteatnotdiepos[selectrandmove][1] };
		selectedk = posk[3][selectrandmove];
	}
	else if (retnotdiepos.size() != 0) {
		int selectrandmove = rand() % retnotdiepos.size();
		retrealpos = new int[2]{ retnotdiepos[selectrandmove][0], retnotdiepos[selectrandmove][1] };
		selectedk = posk[2][selectrandmove];
	}
	else if (reteatpos.size() != 0) {
		int selectrandmove = rand() % reteatpos.size();
		retrealpos = new int[2]{ reteatpos[selectrandmove][0], reteatpos[selectrandmove][1] };
		selectedk = posk[1][selectrandmove];
	}
	else if (retpos.size() != 0) {
		int selectrandmove = rand() % retpos.size();
		retrealpos = new int[2]{ retpos[selectrandmove][0], retpos[selectrandmove][1] };
		selectedk = posk[0][selectrandmove];
	}
	else {//防呆
		while (true) {
			int* pos = new int[2]{ rand() % 8,rand() % 8 };
			if (board.plot[pos[1]][pos[0]].turn == playerid) {
				auto avail = GameManager::RequestAvaliStep(board, playerid, pos, prevplayermovetype, true);
				if (avail.size() > 0) {
					selectedk = rand() % avail.size();
					retrealpos = pos;
					break;
				}
			}
		}
	}
	for (int i = 0; i < retchecknotdiepos.size(); i++) {
		delete[] retchecknotdiepos[i];
	}
	for (int i = 0; i < retcheckpos.size(); i++) {
		delete[] retcheckpos[i];
	}
	for (int i = 0; i < reteatnotdiepos.size(); i++) {
		delete[] reteatnotdiepos[i];
	}
	for (int i = 0; i < retnotdiepos.size(); i++) {
		delete[] retnotdiepos[i];
	}
	for (int i = 0; i < reteatpos.size(); i++) {
		delete[] reteatpos[i];
	}
	for (int i = 0; i < retpos.size(); i++) {
		delete[] retpos[i];
	}
	return retrealpos;
}

int WeekAIPlayer::SelectMoveOption(std::vector<GameManager::movetype>& avail, int selectedchesstype)
{
	return selectedk;
}

int WeekAIPlayer::SelectPromote(Board& const board, int Pos[2])
{
	srand(time(NULL));
	int selected = rand() % 3;
	return selected + 2;
}

void WeekAIPlayer::OnMove(Board& const board, int* frompos, GameManager::movetype to)
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

void WeekAIPlayer::OnPromote(Board& const board, int Pos[2], Board::basechess outchess)
{
	board.PlaceChess(Pos, outchess);
}