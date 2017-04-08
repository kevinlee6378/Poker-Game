// Lab3.cpp : Defines the entry point for the console application.
//
//
#include "stdafx.h"
#include "Player.h"
#include "Game.h"
#include <iostream>

int main(int argc, char * argv[])
{
	/*
	std::vector<Card> cards; 
	cards.push_back(Card(Hearts, Ace));
	cards.push_back(Card(Hearts, Two));
	cards.push_back(Card(Hearts, Three));
	Hand h;
	h.set_hand(cards);
	Hand h2 = h.make_hand(2);
	std::cout << h2 << std::endl;
	return 0;
	*/

	char* program_name = argv[0];
	if (argc < 4) {
		std::cout << "Usage: " << program_name << "game_name player_name player2_name" << std::endl;
		return 1;
	}
	Game game;
	try {
		game.start_game(argv[1]);
	}
	catch (int e) {
		return e;
	}
	shared_ptr<Game> instance;
	try {
		instance = game.instance();
	}
	catch (int e) {
		return e;
	}
	int i = 2;
	while (i < argc) {
		try {
			instance->add_player(argv[i]);
			++i;
		}
		catch (int e) {
			return e;
		}
	}
	while (instance->size() >= 2) {
		try {
			if (int e = instance->before_round()) {
				return e;
			}
			if (int e = instance->round()) {
				return e;
			}
			if (int e = instance->after_round()) {
				return e;
			}

		}

		catch (int e) {
			game.stop_game();

			return e;
		}
	}
	game.stop_game();
	return 0;
}



