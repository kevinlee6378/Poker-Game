#pragma once
#include "Card.h"
#include "Game.h"
#include "Poker.h"
#include <iostream>

class Game;
class SevenCardStud :public Game {
private:
protected:
	size_t dealer;
	Deck discard_deck;

public:
	SevenCardStud();
	virtual int turn1(Player & p);
	virtual int turn2(Player & p);
	virtual int turn3(Player & p);
	virtual int turn4(Player & p);
	virtual int turn5(Player & p);
	virtual int before_round();
	virtual int round();
	virtual int after_round();
};
void comb(int off, int a);
bool poker_rank3(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2);
