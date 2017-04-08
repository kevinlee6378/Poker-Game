#include "stdafx.h"
#include "Player.h"

Player::Player(std::string s)
{
	this->name = s;
	this->hand = Hand();
	this->won = 0;
	this->lost = 0;
	this->chips = 20;

	std::string file_input_string = s + ".txt";
	std::string	file_input[] = {"", "-1", "-1", "-1"};
	std::ifstream player_file(file_input_string);
	if (!player_file.is_open()) {
	}
	else {
		std::string temp;
		int i = 0;
		
		while (i < 4 && player_file >> temp) {
			file_input[i] = temp;
			i++;
		}
		player_file.close();
	}
	if (file_input[0] == s && std::stoi(file_input[1]) >= 0 && std::stoi(file_input[2]) >= 0 && std::stoi(file_input[3]) >= 0) {
		this->name = file_input[0];
		this->won = std::stoi(file_input[1]);
		this->lost = std::stoi(file_input[2]);
		this->chips = std::stoi(file_input[3]);
	}
}

std::ostream & operator<<(std::ostream & out, const Player & p)
{
	out <<  p.name << " " << p.won  << " "<< p.lost << " " << p.chips;
	return out;
}
