#include "GameManager.h"
#include "Player.h"
#include "HumanPlayer.h"

map<int, string> GameManager::movetype::typeint2str = { {0,"normal"},{1,"eat"},{2,"castling"},{3,"soldier1stmove"},{4,"passeat"} };
map<string, int> GameManager::movetype::typestr2int = { {"normal",0},{"eat",1},{"castling",2},{"soldier1stmove",3},{"passeat",4} };


vector<GameManager::movetype> GameManager::RequestAvaliStep(Board& inboard, int req_player, int pos[2], GameManager::movetype prevplayermovetype, bool kingcheck)
{
	vector<movetype> avail;
	Board::basechess selected = inboard.plot[pos[1]][pos[0]];
	if (selected.turn != req_player || req_player != 0 && req_player != 1) {
		return avail;
	}
	else if (inboard.typeint2str[selected.type] == "soldier") {
		if (!selected.moved) {
			if (inboard.plot[pos[1] + 2 * (req_player == 0 ? -1 : 1)][pos[0]].type == 0) {
				avail.push_back(movetype{ 3,{pos[0],pos[1] + 2 * (req_player == 0 ? -1 : 1) } });
			}
			if (inboard.plot[pos[1] + 1 * (req_player == 0 ? -1 : 1)][pos[0]].type == 0) {
				avail.push_back(movetype{ 3,{pos[0],pos[1] + 1 * (req_player == 0 ? -1 : 1) } });
			}
		}
		else {
			if (inboard.plot[pos[1] + 1 * (req_player == 0 ? -1 : 1)][pos[0]].type == 0) {
				avail.push_back(movetype{ 0,{pos[0],pos[1] + 1 * (req_player == 0 ? -1 : 1) },req_player == 0 ? pos[1] + 1 * (req_player == 0 ? -1 : 1) == 0 : pos[1] + 1 * (req_player == 0 ? -1 : 1) == 7 });
			}
			if (prevplayermovetype.type == 3) {
				if (pos[1] == prevplayermovetype.pos[1] && abs(prevplayermovetype.pos[0] - pos[0]) == 1) {
					avail.push_back(movetype{ 4,{pos[0] + prevplayermovetype.pos[0] - pos[0],pos[1] + 1 * (req_player == 0 ? -1 : 1) } });
				}
			}
		}
		if (pos[0] > 0 && inboard.plot[pos[1] + 1 * (req_player == 0 ? -1 : 1)][pos[0] - 1].turn == (1 - req_player)) {
			avail.push_back(movetype{ 1,{pos[0] - 1,pos[1] + 1 * (req_player == 0 ? -1 : 1) },req_player == 0 ? pos[1] + 1 * (req_player == 0 ? -1 : 1) == 0 : pos[1] + 1 * (req_player == 0 ? -1 : 1) == 7 });
		}
		if (pos[0] < 7 && inboard.plot[pos[1] + 1 * (req_player == 0 ? -1 : 1)][pos[0] + 1].turn == (1 - req_player)) {
			avail.push_back(movetype{ 1,{pos[0] + 1,pos[1] + 1 * (req_player == 0 ? -1 : 1) },req_player == 0 ? pos[1] + 1 * (req_player == 0 ? -1 : 1) == 0 : pos[1] + 1 * (req_player == 0 ? -1 : 1) == 7 });
		}
	}
	else if (inboard.typeint2str[selected.type] == "horse") {
		int x, y, temp;
		for (int i = 0; i < 8; i++) {
			if (i == 0) {
				x = 1;
				y = 2;
			}
			else if (i == 4) {
				x = 2;
				y = 1;
			}
			temp = -x;
			x = y;
			y = temp;
			if (pos[0] + x <= 7 && pos[1] + y <= 7 && pos[0] + x >= 0 && pos[1] + y >= 0) {
				if (inboard.plot[pos[1] + y][pos[0] + x].type == 0) {
					avail.push_back(movetype{ 0,pos[0] + x,pos[1] + y });
				}
				else if (inboard.plot[pos[1] + y][pos[0] + x].turn != req_player) {
					avail.push_back(movetype{ 1,pos[0] + x,pos[1] + y });
				}
			}
		}
	}
	else if (inboard.typeint2str[selected.type] == "elep") {
		int x = 1, y = 1, temp;
		for (int i = 0; i < 4; i++) {
			int k = 1;
			while (true) {
				if (pos[0] + x * k <= 7 && pos[0] + x * k >= 0 && pos[1] + y * k >= 0 && pos[1] + y * k <= 7) {
					if (inboard.plot[pos[1] + y * k][pos[0] + x * k].type == 0) {
						avail.push_back(movetype{ 0,pos[0] + x * k,pos[1] + y * k });
					}
					else if (inboard.plot[pos[1] + y * k][pos[0] + x * k].turn != req_player) {
						avail.push_back(movetype{ 1,pos[0] + x * k,pos[1] + y * k });
						break;
					}
					else {
						break;
					}
				}
				else {
					break;
				}
				k++;
			}
			temp = -x;
			x = y;
			y = temp;
		}
	}
	else if (inboard.typeint2str[selected.type] == "car") {
		int x = 1, y = 0, temp;
		for (int i = 0; i < 4; i++) {
			int k = 1;
			while (true) {
				if (pos[0] + x * k <= 7 && pos[0] + x * k >= 0 && pos[1] + y * k >= 0 && pos[1] + y * k <= 7) {
					if (inboard.plot[pos[1] + y * k][pos[0] + x * k].type == 0) {
						avail.push_back(movetype{ 0,pos[0] + x * k,pos[1] + y * k });
					}
					else if (inboard.plot[pos[1] + y * k][pos[0] + x * k].turn != req_player) {
						avail.push_back(movetype{ 1,pos[0] + x * k,pos[1] + y * k });
						break;
					}
					else {
						break;
					}
				}
				else {
					break;
				}
				k++;
			}
			temp = -x;
			x = y;
			y = temp;
		}
	}
	else if (inboard.typeint2str[selected.type] == "queen") {
		int x, y, temp;
		for (int i = 0; i < 8; i++) {
			if (i == 0) {
				x = 1;
				y = 1;
			}
			else if (i == 4) {
				x = 1;
				y = 0;
			}
			int k = 1;
			while (true) {
				if (pos[0] + x * k <= 7 && pos[0] + x * k >= 0 && pos[1] + y * k >= 0 && pos[1] + y * k <= 7) {
					if (inboard.plot[pos[1] + y * k][pos[0] + x * k].type == 0) {
						avail.push_back(movetype{ 0,pos[0] + x * k,pos[1] + y * k });
					}
					else if (inboard.plot[pos[1] + y * k][pos[0] + x * k].turn != req_player) {
						avail.push_back(movetype{ 1,pos[0] + x * k,pos[1] + y * k });
						break;
					}
					else {
						break;
					}
				}
				else {
					break;
				}
				k++;
			}
			temp = -x;
			x = y;
			y = temp;
		}
	}
	else if (inboard.typeint2str[selected.type] == "king") {
		int x, y, temp;
		for (int i = 0; i < 8; i++) {
			if (i == 0) {
				x = 1;
				y = 1;
			}
			else if (i == 4) {
				x = 1;
				y = 0;
			}
			if (pos[0] + x <= 7 && pos[0] + x >= 0 && pos[1] + y >= 0 && pos[1] + y <= 7) {
				if (inboard.plot[pos[1] + y][pos[0] + x].type == 0) {
					avail.push_back(movetype{ 0,pos[0] + x,pos[1] + y });
				}
				else if (inboard.plot[pos[1] + y][pos[0] + x].turn != req_player) {
					avail.push_back(movetype{ 1,pos[0] + x,pos[1] + y });
				}
			}
			temp = -x;
			x = y;
			y = temp;
		}
		if (kingcheck && !checkcheck(inboard, req_player) && !selected.moved) {
			if (!inboard.plot[(req_player == 0 ? 7 : 0)][0].moved) {//長易位
				bool cancas = true;
				for (int i = 0; i < 3; i++) {
					if (inboard.plot[(req_player == 0 ? 7 : 0)][i + 1].type != 0) {
						cancas = false;
						break;
					}
				}
				for (int i = 0; cancas && i < 2; i++) {
					Board temp2 = inboard.SimulteMove(pos, new int[2]{ 2 + i,(req_player == 0 ? 7 : 0) });
					if (checkcheck(temp2, req_player)) {
						cancas = false;
						break;
					}
				}
				if (cancas) {
					avail.push_back(movetype{ 2,{2,(req_player == 0 ? 7 : 0)} });
				}
			}
			if (!inboard.plot[(req_player == 0 ? 7 : 0)][7].moved) {//短易位
				bool cancas = true;
				for (int i = 0; i < 2; i++) {
					if (inboard.plot[(req_player == 0 ? 7 : 0)][i + 5].type != 0) {
						cancas = false;
						break;
					}
				}
				for (int i = 0; cancas && i < 2; i++) {
					Board temp2 = inboard.SimulteMove(pos, new int[2]{ 5 + i,(req_player == 0 ? 7 : 0) });
					if (checkcheck(temp2, req_player)) {
						cancas = false;
						break;
					}
				}
				if (cancas) {
					avail.push_back(movetype{ 2,{6,(req_player == 0 ? 7 : 0)} });
				}
			}
		}
	}
	if (kingcheck) {
		for (int i = 0; i < avail.size(); i++) {//如果移動後被將軍，不可動
			Board temp2 = inboard.SimulteMove(pos, avail[i].pos);
			if (checkcheck(temp2, req_player)) {
				avail.erase(avail.begin() + i);
				i--;
				continue;
			}
		}
	}
	return avail;
}


void GameManager::StartGame()
{
	Lobby();
}

void GameManager::Lobby()
{
	while (true) {
		string input = "1";
		///*
		system("cls");
		cout << "Welcome to CONSOLE CHESS!!" << endl;
		cout << "1. Play\n2. Load\ne. Exit\nPlease Enter: ";
		getline(cin, input);
		//*/
		if (input == "1") {
			MainGame();
		}
		else if (input == "2") {
			string filename;
			cout << "load filename:";
			cin >> filename;
			MainGame(filename);
		}
		else if (input == "e") {
			break;
		}
	}
}

void GameManager::MainGame(string filename)
{
	board.InitBoard();
	current_player = 0;
	state = 0;
	int selected_move_id,//傳入之avail的index
		selected_promote_id;//選擇要promote的棋
	int* selectedpos;
	movetype prevmove;
	players[0] = new HumanPlayer{};
	players[1] = new HumanPlayer{};

	int current_step = 0;
	gamerecord.push_back(gamelog(board, current_player));

	if (filename != "") {
		ifstream ifile(filename);
		gamelog gl;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				ifile.read((char*)&board.plot[i][j], sizeof(board.plot[i][j]));
			}
		}
		ifile.read((char*)&gl.current_player, sizeof(gl.current_player));
		ifile.close();
	}
	while (true) {
		system("cls");
		//board.PrintBoard();//maybe call viewer
		viewer.print(board.plot);
		state = 0;
		if (checkcheck(board, current_player)) {
			state = 1;
			cout << "You have been Checked!"<<endl;
			bool found = false;
			for (int i = 0; !found && i < 8; i++) {
				for (int j = 0; !found && j < 8; j++) {
					if (board.plot[i][j].turn == current_player) {
						vector<movetype> avail = RequestAvaliStep(board, current_player, new int[2]{ j,i }, movetype{});
						for (int k = 0; k < avail.size(); k++) {
							Board temp2 = board.SimulteMove(new int[2]{ j,i }, avail[k].pos);
							if (!checkcheck(temp2, current_player)) {
								found = true;
								break;
							}
						}
					}
				}
			}
			if (!found) {
				break;
			}
		}
		bool find = false;
		for (int i = 0; !find && i < 8; i++) {
			for (int j = 0; !find && j < 8; j++) {
				if (RequestAvaliStep(board, current_player, new int[2]{ j,i }, movetype{}).size() > 0) {
					find = true;
					break;
				}
			}
		}
		if (!find) {
			current_player = -1;
			break;
		}
		selectedpos = players[current_player]->SelectChess(current_player);
		if (selectedpos[0] == -1) {
			break;
		}
		else if (selectedpos[0] == 's') {
			string filename;
			cout << "save filename:";
			cin >> filename;
			ofstream ofile(filename);
			gamelog gl{ board,current_player };
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					ofile.write((char*)&board.plot[i][j], sizeof(board.plot[i][j]));
				}
			}
			ofile.write((char*)&gl.current_player, sizeof(gl.current_player));
			ofile.close();
			continue;
		}
		else if (selectedpos[0] == 'r') {
			if (current_step != gamerecord.size()-1) {
				current_step++;
				board = gamerecord[current_step].board;
				current_player = gamerecord[current_step].current_player;
			}
			continue;
		}
		else if (selectedpos[0] == 'u') {
			if (current_step != 0) {
				current_step--;
				board = gamerecord[current_step].board;
				current_player = gamerecord[current_step].current_player;
			}
			continue;
		}
		vector<movetype> avail = RequestAvaliStep(board, current_player, new int[2]{ selectedpos[0],selectedpos[1] }, prevmove);
		if (avail.size() > 0) {
			selected_move_id = players[current_player]->SelectMoveOption(avail);
			if (selected_move_id < avail.size()) {
				players[current_player]->OnMove(board, selectedpos, avail[selected_move_id]);
				if (avail[selected_move_id].will_promote) {
					selected_promote_id = players[current_player]->SelectPromote(board, avail[selected_move_id].pos);
					players[current_player]->OnPromote(board, avail[selected_move_id].pos, Board::basechess{ selected_promote_id, current_player });
				}
				current_player = 1 - current_player;
				prevmove = avail[selected_move_id];

				//clear 多出來的gamerecord
				while (gamerecord.size() > current_step+1) {
					gamerecord.pop_back();
				}
				//save gamelog to gamerecord
				gamerecord.push_back(gamelog(board,current_player));
				current_step++;
			}
			else {
				continue;
			}
		}
		else {
			continue;
		}
	}
	Result();
}

void GameManager::Result()
{
	string temp;
	if (current_player != -1) {
		cout << "Player" << (1 - current_player) << " WIN!!!" << endl << "Enter anything to continue:";
		getline(cin, temp);
		getline(cin, temp);
	}
	else {
		cout << "Draw!!" << endl << "Enter anything to continue:";
		getline(cin, temp);
		getline(cin, temp);
	}
}

void GameManager::Printavail(vector<movetype>& in)
{
	for (int i = 0; i < in.size(); i++) {
		cout << to_string(i) + ".  X: " << in[i].pos[0] << "  Y: " << in[i].pos[1] << "  Type: " << movetype::typeint2str[in[i].type] << endl;
	}
}

bool GameManager::checkcheck(Board& inboard, int which_player) {
	int* kingpos = getkingpos(inboard, which_player);
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (inboard.plot[i][j].turn == (1 - which_player)) {
				vector<movetype> avail = RequestAvaliStep(inboard, (1 - which_player), new int[2]{ j,i }, movetype{}, false);
				for (int k = 0; k < avail.size(); k++) {
					if (movetype::typeint2str[avail[k].type] == "eat" && avail[k].pos[0] == kingpos[0] && avail[k].pos[1] == kingpos[1]) {
						return true;
					}
				}
			}
		}
	}
	return false;
}
int* GameManager::getkingpos(Board& inboard, int which_player)
{
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (inboard.plot[i][j].turn == which_player && inboard.typeint2str[inboard.plot[i][j].type] == "king") {
				return new int[2]{ j,i };
			}
		}
	}
}