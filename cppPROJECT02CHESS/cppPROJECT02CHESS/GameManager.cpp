#include "GameManager.h"
#include "Player.h"
#include "HumanPlayer.h"

map<int, string> GameManager::movetype::typeint2str = { {0,"normal"},{1,"eat"},{2,"castling"},{3,"soldier1stmove"},{4,"passeat"} };
map<string, int> GameManager::movetype::typestr2int = { {"normal",0},{"eat",1},{"castling",2},{"soldier1stmove",3},{"passeat",4} };


vector<GameManager::movetype> GameManager::RequestAvaliStep(int req_player, int pos[2], GameManager::movetype prevplayermovetype)
{
	vector<movetype> avali;
	Board::basechess selected = board.plot[pos[1]][pos[0]];
	if (selected.turn != req_player) {
		return avali;
	}
	else {
		if (board.typeint2str[selected.type] == "soldier") {
			if (pos[1] == 6 && req_player == 0 || pos[1] == 1 && req_player == 1) {
				if (board.plot[pos[1] + 2 * (req_player == 0 ? -1 : 1)][pos[0]].turn == 3) {
					avali.push_back(movetype{ 3,{pos[0],pos[1] + 2 * (req_player == 0 ? -1 : 1) } });
				}
				if (board.plot[pos[1] + 1 * (req_player == 0 ? -1 : 1)][pos[0]].turn == 3) {
					avali.push_back(movetype{ 3,{pos[0],pos[1] + 1 * (req_player == 0 ? -1 : 1) } });
				}
			}
			else {
				if (board.plot[pos[1] + 1 * (req_player == 0 ? -1 : 1)][pos[0]].turn == 3) {
					avali.push_back(movetype{ 0,{pos[0],pos[1] + 1 * (req_player == 0 ? -1 : 1) } });
				}
				if (prevplayermovetype.type == 3) {
					if (pos[1] == prevplayermovetype.pos[1] && abs(prevplayermovetype.pos[0] - pos[0]) == 1) {
						avali.push_back(movetype{ 4,{pos[0] + prevplayermovetype.pos[0] - pos[0],pos[1] + 1 * (req_player == 0 ? -1 : 1) } });
					}
				}
			}
			if (pos[0] > 0 && board.plot[pos[1] + 1 * (req_player == 0 ? -1 : 1)][pos[0] - 1].turn == (1 - req_player)) {
				avali.push_back(movetype{ 1,{pos[0] - 1,pos[1] + 1 * (req_player == 0 ? -1 : 1) } });
			}
			if (pos[0] < 6 && board.plot[pos[1] + 1 * (req_player == 0 ? -1 : 1)][pos[0] + 1].turn == (1-req_player)) {
				avali.push_back(movetype{ 1,{pos[0] + 1,pos[1] + 1 * (req_player == 0 ? -1 : 1) } });
			}
		}
		else if (board.typeint2str[selected.type] == "horse") {

		}
		else if (board.typeint2str[selected.type] == "elephant") {

		}
		else if (board.typeint2str[selected.type] == "car") {

		}
		else if (board.typeint2str[selected.type] == "queen") {

		}
		else if (board.typeint2str[selected.type] == "king") {

		}
	}
	return avali;
}


void GameManager::StartGame()
{
	Lobby();
}

void GameManager::Lobby()
{
	while (true) {
		string input="1";
		/*system("cls");
		cout << "Welcome to CONSOLE CHESS!!" << endl;
		cout << "1. Play\n2. Exit\nPlease Enter: ";
		getline(cin, input);
		*/
		if (input == "1") {
			MainGame();
		}
		else if(input=="2"){
			break;
		}
	}
}

void GameManager::MainGame()
{
	board.InitBoard();
	current_player = 0;
	state = 0;
	int selected_move_id;
	int* selectedpos;
	movetype prevmove;
	players[0] = new HumanPlayer{};
	players[1] = new HumanPlayer{};
	//board.PrintBoard();
	//vector<movetype> temp = RequestAvaliStep(1, new int[2]{ 1,2 }, movetype{ 3,{0,2} });
	//Printavali(temp);
	while (true) {
		system("cls");
		board.PrintBoard();//maybe call viewer
		selectedpos = players[current_player]->SelectChess(current_player);
		vector<movetype> avail = RequestAvaliStep(current_player, new int[2]{ selectedpos[0],selectedpos[1] }, prevmove);
		if (avail.size() > 0) {
			selected_move_id = players[current_player]->SelectMoveOption(avail);
			if (selected_move_id < avail.size()) {
				players[current_player]->OnMove(board, selectedpos,avail[selected_move_id]);
				current_player = 1 - current_player;
				prevmove = avail[selected_move_id];
			}
			else {
				continue;
			}
		}
		else {
			continue;
		}
	}
}

void GameManager::Result()
{
}

void GameManager::Printavail(vector<movetype>& in)
{
	for (int i = 0; i < in.size(); i++) {
		cout << to_string(i)+".  X: " << in[i].pos[0] << "  Y: " << in[i].pos[1] << "  Type: " << movetype::typeint2str[in[i].type] << endl;
	}
}