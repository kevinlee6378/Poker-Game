#include "stdafx.h"
#include "FiveCardDraw.h"
#include "Poker.h"

FiveCardDraw::FiveCardDraw()
{
	this->dealer = 0;
	for (int suit = 0; suit <= 3; suit++) {
		for (int rank = 0; rank <= 12; rank++) {
			Suit s = (Suit)suit;
			Rank r = (Rank)rank;
			Card c = Card(s, r);

			main_deck.add_card(c);

		}
	}
	main_deck.shuffle();
}

int FiveCardDraw::before_turn(Player & p)
{
	++counter;
	if (p.hasFolded || p.chips == 0) {
		return 0;
	}
	else {
		std::cout << "Current bet is at: " << minimum_bet << " You have bet " << p.current_bet << " You have " << p.chips << " chips\n" << std::endl;
		if (p.current_bet != minimum_bet) {
			while (true) {
				std::cout << p.name << " Type call to call, fold to fold, and 1 or 2 to raise\n" << std::endl;
				unsigned int raise_amount = 0;
				std::string response;
				std::cin >> response;
				if (response == "call") {
					unsigned int needToMatch = minimum_bet - p.current_bet;
					if (p.chips >= needToMatch) {
						pot += needToMatch;
						p.chips -= needToMatch;
						p.current_bet += needToMatch;
						return 0;
					}
					else {
						p.current_bet += p.chips;
						pot += p.chips;
						p.chips = 0;
						return 0;
					}
				}
				else if (response != "fold") {
					try {
						raise_amount = stoi(response);
						unsigned int needToMatch = minimum_bet - p.current_bet;
						if (0 < raise_amount && raise_amount < 3 && raise_amount <= p.chips) {
							minimum_bet += raise_amount;
							pot += raise_amount + needToMatch;
							p.chips -= raise_amount + needToMatch;
							p.current_bet += raise_amount + needToMatch;
							counter = 1;
							return 0;
						}
						else {
							throw 1;
						}
					}
					catch (...) {
						std::cout << "You must call, fold, or raise by \"1\" or \"2\"\n" << std::endl;
					}
				}
				else {
					p.hasFolded = true;
					return 0;
				}
			}
		}


		else {
			while (true) {
				std::cout << p.name << "Type \"check\" to check and 1 or 2 to raise\n" << std::endl;
				unsigned raise_amount = 0;
				std::string response;
				std::cin >> response;
				if (response == "check") {
					return 0;
				}
				else {
					try {
						raise_amount = stoi(response);
						if (0 < raise_amount && raise_amount < 3 && raise_amount <= p.chips) {
							minimum_bet += raise_amount;
							pot += raise_amount;
							p.chips -= raise_amount;
							p.current_bet += raise_amount;
							counter = 1;
							return 0;
						}
						else {
							throw 1;
						}
					}
					catch (...) {
						std::cout << "Please type the number of chips (1 or 2) to raise or check to check\n" << std::endl;

					}
				}
			}
		}
	}
}
int FiveCardDraw::turn(Player & p) {
	++counter;
	if (p.hasFolded || p.chips == 0) {
		return 0;
	}
	else {
		std::cout << p.name << "You have: " << p.hand << std::endl;
		std::cout << "Current bet is at: " << minimum_bet << " You have bet " << p.current_bet << " You have " << p.chips << " chips\n" << std::endl;
		if (p.current_bet != minimum_bet) {
			while (true) {
				std::cout << p.name << " Type call to call, fold to fold, and 1 or 2 to raise\n" << std::endl;
				unsigned int raise_amount = 0;
				std::string response;
				std::cin >> response;
				if (response == "call") {
					unsigned int needToMatch = minimum_bet - p.current_bet;
					if (p.chips >= needToMatch) {
						pot += needToMatch;
						p.chips -= needToMatch;
						p.current_bet += needToMatch;
						return 0;
					}
					else {
						p.current_bet += p.chips;
						pot += p.chips;
						p.chips = 0;
						return 0;
					}
				}
				else if (response != "fold") {
					try {
						raise_amount = stoi(response);
						unsigned int needToMatch = minimum_bet - p.current_bet;
						if (0 < raise_amount && raise_amount < 3 && raise_amount <= p.chips) {
							minimum_bet += raise_amount;
							pot += raise_amount + needToMatch;
							p.chips -= raise_amount + needToMatch;
							p.current_bet += raise_amount + needToMatch;
							counter = 1;
							return 0;
						}
						else {
							throw 1;
						}
					}
					catch (...) {
						std::cout << "You must call, fold, or raise by \"1\" or \"2\"\n" << std::endl;
					}
				}
				else {
					p.hasFolded = true;
					return 0;
				}
			}
		}


		else {
			while (true) {
				std::cout << p.name << "Type \"check\" to check and 1 or 2 to raise\n" << std::endl;
				unsigned raise_amount = 0;
				std::string response;
				std::cin >> response;
				if (response == "check") {
					return 0;
				}
				else {
					try {
						raise_amount = stoi(response);
						if (0 < raise_amount && raise_amount < 3 && raise_amount <= p.chips) {
							minimum_bet += raise_amount;
							pot += raise_amount;
							p.chips -= raise_amount;
							p.current_bet += raise_amount;
							counter = 1;
							return 0;
						}
						else {
							throw 1;
						}
					}
					catch (...) {
						std::cout << "Please type the number of chips (1 or 2) to raise or check to check\n" << std::endl;

					}
				}
			}
		}
	}
}
/*
int FiveCardDraw::after_turn(Player & p)
{
	std::cout << std::endl << p.name << " you have " << p.hand << std::endl;
	return 0;
}
*/

int FiveCardDraw::before_round()
{
	main_deck.shuffle();
	size_t player_index = (dealer + 1) % players.size();
	int deal_num = players.size() * 5;
	while(deal_num > 0){
		(players[player_index])->hand << main_deck;
		player_index = (player_index + 1) % players.size();
		--deal_num;
	}
	pot = 0;
	for (auto p = players.begin(); p != players.end(); p++) {
		(*(*p)).hasFolded = false;
		--(*(*p)).chips;
		(*(*p)).current_bet = 0;
		++pot;
	}
	counter = 0;
	minimum_bet = 0;
	while (counter < players.size()) {
		for (auto p = players.begin(); p != players.end(); p++) {
			if (counter >= players.size()) {
				break;
			}
			else {
				before_turn(*(*p));
			}	
		}
	}
	counter = 0;
	return 0;
}
//need to cast player.size()?
int FiveCardDraw::round()
{
	while (counter < players.size()) {
		for (auto p = players.begin(); p != players.end(); p++) {
			if (counter >= players.size()) {
				break;
			}
			else {
				turn(*(*p));
			}
		}
	}
	return 0;
}

int FiveCardDraw::after_round()
{
	std::vector<std::shared_ptr<Player>> players_copy = players;
	std::sort(players_copy.begin(), players_copy.end(), poker_rank2);
	bool hasPickedWinner = false;
	for (auto p = players_copy.begin(); p != players_copy.end(); ++p) {
		if (!(*(*p)).hasFolded && !hasPickedWinner){
			(*(*p)).won = (*(*p)).won + 1;
			(*(*p)).chips += pot;
			pot = 0;
			hasPickedWinner = true;
			std::cout << (*(*p)).name << " has " << (*(*p)).won << " wins " << (*(*p)).lost << " losses " << (*(*p)).chips << " chips and has " << (*(*p)).hand << std::endl;
			main_deck.collect_cards((*(*p)).hand.getCards());
			(*(*p)).hand.clear_hand();
		}
		else if ((*(*p)).hasFolded) {
			(*(*p)).lost = (*(*p)).lost + 1;
			std::cout << (*(*p)).name << " has " << (*(*p)).won << " wins " << (*(*p)).lost << " losses " << (*(*p)).chips << " chips and folded" << std::endl;
			main_deck.collect_cards((*(*p)).hand.getCards());
			(*(*p)).hand.clear_hand();
		}
		else {
			(*(*p)).lost = (*(*p)).lost + 1;
			std::cout << (*(*p)).name << " has " << (*(*p)).won << " wins " << (*(*p)).lost << " losses " << (*(*p)).chips << " chips and has " << (*(*p)).hand << std::endl;
			main_deck.collect_cards((*(*p)).hand.getCards());
			(*(*p)).hand.clear_hand();
		}
	}
	for (auto p = players_copy.begin(); p != players_copy.end(); ++p) {
		if ((*(*p)).chips == 0) {
			while (true) {
				std::cout << "reset or quit?" << std::endl;
				std::string response;
				std::cin >> response;
				if (response == "reset") {
					(*(*p)).chips = 20;
					break;
				}
				else if (response == "quit") {
					remove_player((*(*p)).name.c_str());
					break;
				}
				else {
					std::cout << "Please type reset or quit" << std::endl;
				}
			}
		}
	}
	
	main_deck.collect_cards(discard_deck.getCards());
	discard_deck.clear_deck();
	bool want_to_leave = true;
	while (want_to_leave) {
		std::cout << "Want to leave the game? y/n";
		char yes_or_no;
		std::cin >> yes_or_no;
		std::cin.ignore();
		if (yes_or_no == 'n') {
			want_to_leave = false;
		}
		else {
			std::cout << "Who wants to leave?";
			std::string player_name;
			std::getline(std::cin, player_name);
			std::shared_ptr<Player> p = find_player(player_name.c_str());
			if (p) {
				std::ofstream out;
				out.open(player_name);
				if (out.is_open()) {
					out << p;
					out.close();
				}
				remove_player(player_name.c_str());
			}
		}
		bool want_to_join = true;
		while (want_to_join) {
			std::cout << "Want to join the game? y/n";
			char yes_or_no;
			std::cin >> yes_or_no;
			std::cin.ignore();
			if (yes_or_no == 'n') {
				want_to_join = false;
			}
			else {
				std::cout << "Who wants to leave?";
				std::string player_name;
				std::getline(std::cin, player_name);
				try {
					add_player(player_name.c_str());
				}
				catch (...) {

				}
			}
			
		}
	}
	if (dealer != players.size() - 1) {
		dealer = 0;
	}
	else {
		dealer = dealer + 1;
	}
	return 0;
}

bool poker_rank2(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2)
{
	if (!p1) {
		return false;
	}
	else {
		if (!p2) {
			return true;
		}
		return poker_rank(p1->hand, p2->hand);
	}
}
