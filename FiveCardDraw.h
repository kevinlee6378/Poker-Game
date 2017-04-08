#pragma once
#include "Card.h"
#include "Game.h"
#include <iostream>

class Game;
class FiveCardDraw :public Game{
private:
protected:
	size_t dealer;
	Deck discard_deck;

public:
	FiveCardDraw();
	virtual int before_turn(Player & p);
	virtual int turn(Player & p);
	//virtual int after_turn(Player & p);
	virtual int before_round();
	virtual int round();
	virtual int after_round();
};
bool poker_rank2(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2);
