#pragma once
#include "Player.h"

class HumanPlayer :public Player {
public:
	virtual void OnMove(/* parameters */) override;
	void OnPromote(/* parameters */) override;
private:
};