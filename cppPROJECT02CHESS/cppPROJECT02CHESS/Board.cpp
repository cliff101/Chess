#include "Board.h"
#include "Viewer.h"

Board::Board()
{
	plot = new basechess * [8];
	for (int i = 0; i < 8; i++) {
		plot[i] = new basechess[8];
	}
	typestr2int[""] = 0;
	typestr2int["king"] = 1;
	typestr2int["queen"] = 2;
	typestr2int["car"] = 3;
	typestr2int["elep"] = 4;
	typestr2int["horse"] = 5;
	typestr2int["soldier"] = 6;

	typeint2str[0] = "";
	typeint2str[1] = "king";
	typeint2str[2] = "queen";
	typeint2str[3] = "car";
	typeint2str[4] = "elep";
	typeint2str[5] = "horse";
	typeint2str[6] = "soldier";

}

Board::Board(const Board& in)
{
	plot = new basechess * [8];
	for (int i = 0; i < 8; i++) {
		plot[i] = new basechess[8];
	}
	typestr2int[""] = 0;
	typestr2int["king"] = 1;
	typestr2int["queen"] = 2;
	typestr2int["car"] = 3;
	typestr2int["elep"] = 4;
	typestr2int["horse"] = 5;
	typestr2int["soldier"] = 6;

	typeint2str[0] = "";
	typeint2str[1] = "king";
	typeint2str[2] = "queen";
	typeint2str[3] = "car";
	typeint2str[4] = "elep";
	typeint2str[5] = "horse";
	typeint2str[6] = "soldier";
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			plot[i][j] = in.plot[i][j];
		}
	}
}

Board Board::operator=(const Board& in)
{
	plot = new basechess * [8];
	for (int i = 0; i < 8; i++) {
		plot[i] = new basechess[8];
	}
	typestr2int[""] = 0;
	typestr2int["king"] = 1;
	typestr2int["queen"] = 2;
	typestr2int["car"] = 3;
	typestr2int["elep"] = 4;
	typestr2int["horse"] = 5;
	typestr2int["soldier"] = 6;

	typeint2str[0] = "";
	typeint2str[1] = "king";
	typeint2str[2] = "queen";
	typeint2str[3] = "car";
	typeint2str[4] = "elep";
	typeint2str[5] = "horse";
	typeint2str[6] = "soldier";
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			plot[i][j] = in.plot[i][j];
		}
	}
	return *this;
}

void Board::InitBoard()
{
	plot = new basechess * [8];
	for (int i = 0; i < 8; i++) {
		plot[i] = new basechess[8];
	}
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 8; j++) {
			plot[(1 - i) * 5 + 1][j] = basechess{ typestr2int["soldier"],i};
		}
		plot[(1 - i) * 7][0] = basechess{ typestr2int["car"],i };
		plot[(1 - i) * 7][7] = basechess{ typestr2int["car"],i };
		plot[(1 - i) * 7][1] = basechess{ typestr2int["horse"],i };
		plot[(1 - i) * 7][6] = basechess{ typestr2int["horse"],i };
		plot[(1 - i) * 7][2] = basechess{ typestr2int["elep"],i };
		plot[(1 - i) * 7][5] = basechess{ typestr2int["elep"],i };
		plot[(1 - i) * 7][4] = basechess{ typestr2int["king"],i };
		plot[(1 - i) * 7][3] = basechess{ typestr2int["queen"],i };
	}
	//plot[2][0] = basechess{ typestr2int["soldier"],0 };
	//dplot[2][1] = basechess{ typestr2int["soldier"],1 };
}

void Board::PrintBoard()
{
	for (int i = 0; i < 9; i++) {
		if (i > 0) {
			cout << i - 1 << "\t\t";
		}
		else {
			cout << "\t\t";
		}
	}
	cout << endl;
	for (int i = 0; i < 8; i++) {
		cout << i << "\t\t";
		for (int j = 0; j < 8; j++) {
			cout << plot[i][j].turn<<"\t"<< typeint2str[plot[i][j].type]<<"\t";
		}
		cout << endl;
	}
}

void Board::MoveChess(int frompos[2], int topos[2],bool animation)
{
	basechess bc = plot[frompos[1]][frompos[0]];
	bc.moved = true;
	plot[frompos[1]][frompos[0]] = basechess{};
	if (animation) {
		Viewer::print(plot);
	}
	plot[topos[1]][topos[0]] = bc;
	if (animation) {
		Viewer::print(plot);
	}
}
Board Board::SimulteMove(int frompos[2], int topos[2])
{
	Board sim = *this;
	sim.MoveChess(frompos, topos,false);
	return sim;
}

void Board::RemoveChess(int pos[2])
{
	plot[pos[1]][pos[0]] = basechess{};
}
void Board::PlaceChess(int pos[2], basechess bc)
{
	plot[pos[1]][pos[0]] = bc;
}

Board::basechess Board::GetChess(int pos[2])
{
	return plot[pos[1]][pos[0]];
}
