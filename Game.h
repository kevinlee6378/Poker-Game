#pragma once

#include "stdafx.h"
#include <memory>
#include "Deck.h"
#include <vector>
#include "Player.h"


class Game {
protected:
	static std::shared_ptr<Game>game;
	Deck main_deck;
	std::vector<std::shared_ptr<Player>> players;
	unsigned int pot;
	unsigned int minimum_bet;
	unsigned int counter; // for keeping track of whether everyone has called most recent bet

public:
	static std::shared_ptr<Game> instance();
	static void start_game(const std::string s);
	void stop_game();
	void add_player(std::string s);
	void remove_player(const char * name);
	std::shared_ptr<Player> find_player(std::string s);
	virtual ~Game();
	int size();
	virtual int before_turn(Player & p) { return 0; }
	virtual int turn(Player & p) { return 0; }
	virtual int after_turn(Player & p) { return 0; }
	virtual int before_round() { return 0; }
	virtual int round() { return 0; }
	virtual int after_round() { return 0; }
};