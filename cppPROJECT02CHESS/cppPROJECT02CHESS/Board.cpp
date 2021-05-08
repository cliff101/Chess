#include "Board.h"

Board::Board()
{
	plot = new int* [8];
	for (int i = 0; i < 8; i++) {
		plot[i] = new int[8];
	}
	typestr2int["king"] = 0;
	typestr2int["queen"] = 1;
	typestr2int["car"] = 2;
	typestr2int["elephant"] = 3;
	typestr2int["horse"] = 4;
	typestr2int["soldier"] = 5;

	typeint2str[0] = "king";
	typeint2str[1] = "queen";
	typeint2str[2] = "car";
	typeint2str[3] = "elephant";
	typeint2str[4] = "horse";
	typeint2str[5] = "soldier";

}