#pragma once
#include "stdafx.h"
#include "Card.h"
#include "Hand.h"
#include "Deck.h"
#include <string>
#include <iostream>
#include <fstream>	 

struct Player {
	std::string name;
	Hand hand;
	unsigned int won;
	unsigned int lost;
	unsigned int chips;
	unsigned int current_bet;
	bool hasFolded;
	Player(std::string s);

};
std::ostream& operator<<(std::ostream& out, const Player& p);