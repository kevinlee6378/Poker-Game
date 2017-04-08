#include "stdafx.h"
#include "Game.h"
#include "FiveCardDraw.h"
#include "SevenCardStud.h"

std::shared_ptr<Game> Game::game;
std::shared_ptr<Game> Game::instance()
{
	if (!game) {
		throw 1;
	}
	std::shared_ptr<Game> game_copy = game;
	return game_copy;
}

void Game::start_game(const std::string s)
{
	if (game) {
		throw game_already_started;
	}
	if (s.find("FiveCardDraw") == string::npos && s.find("SevenCardStud") == string::npos) {
		throw unknown_game;
	}
	if (s.find("FiveCardDraw") != string::npos) {

		game = std::static_pointer_cast<Game>(std::make_shared<FiveCardDraw>());
	}
	if (s.find("SevenCardStud") != string::npos) {

		game = std::static_pointer_cast<Game>(std::make_shared<SevenCardStud>());

	}

}
void Game::stop_game() {
	if (!game) {
		throw no_game_in_progress;
	}
	else {
		game.reset();
	}
}
void Game::add_player(std::string s) {
	if (find_player(s) != nullptr) {
		throw already_playing;
	}
	else {
		players.push_back(std::make_shared<Player>(s));
	}
}
void Game::remove_player(const char* name) {
	for (std::vector<std::shared_ptr<Player>>::iterator p = players.begin(); p != players.end(); ++p) {
		if ((*(*p)).name == name) {
			players.erase(p);
			return;
		}
	}
}

std::shared_ptr<Player> Game::find_player(std::string s) {
	for (std::vector<std::shared_ptr<Player>>::iterator p = players.begin(); p != players.end(); ++p) {
		if ((*p)->name == s) {
			return *p;
		}
	}
	std::shared_ptr<Player> not_found;
	return not_found;
}

Game::~Game()
{
}
int Game::size() {

	return players.size();

}
