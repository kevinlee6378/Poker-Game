#include "stdafx.h"
#include "Deck.h"
#include "Card.h"
#include "Poker.h"
#include <fstream>
#include <string>
#include <random>
#include <algorithm>
#include <chrono>

Deck::Deck(const char* &filename) {
	int loadError = load(filename);
	if (loadError == 1) {
		throw loadError;
	}
}
int Deck::load(const char* &filename) {
	string line;
	ifstream ifs;
	ifs.open(filename);
	if (!ifs.is_open()) {
		cout << "Error" << endl;
		return 1;
	}
	else {
		ifs >> ws;
		while (getline(ifs, line)) {
			istringstream iss(line);
			char* suit = nullptr;
			char* rank = nullptr;
			//int cardsInHand = 0;
			string current;
			while (iss >> current) {
				int size = static_cast<int>(current.length());
				if (size == 2) {
					rank = &current[0];
					suit = &current[1];
					//cout << *rank << endl;
					//cout << *suit << endl;
				}
				else if (size == 3) {
					rank = &current[0];
					if (current[1] != '0') {
						rank = suit;
					}
					suit = &current[2];
					//cout << *rank << endl;
					//cout << *suit << endl;
				}
				else {
				}
				if (*suit == '/' || *rank == '/') {
					break;
				}
				if (valid_suit(suit) && valid_rank(rank)) {
					this->cards.push_back(Card(char_to_suit(suit), char_to_rank(rank)));
					//cardsInHand++;
					//cout << cardsInHand << endl;
				}
				else {
					cout << "Not Valid Card Format " << current << endl;
				}
			}

		}
		ifs.close();
		return 0;
	}
}

void Deck::shuffle() {
	//auto engine = std::default_random_engine{};
	//std::shuffle(this->cards.begin(), this->cards.end(), engine);
	std::random_device seed;
	std::mt19937 rng(seed());
	std::shuffle(this->cards.begin(), this->cards.end(), rng);
}
int Deck::size() const {
	return this->cards.size();
}
void Deck::add_card(Card c)
{
	this->cards.push_back(c);
}
std::ostream & operator<<(std::ostream & output, const Deck & deck) {
	for (int i = 0; i < (static_cast<int>(deck.cards.size())); ++i) {
		output << rank_to_string(deck.cards[i].rank) << suit_to_string(deck.cards[i].suit) << endl;
	}
	return output;
}
void Deck::collect_cards(const std::vector<Card> & c) {

	std::copy(c.begin(), c.end(), std::back_inserter(this->cards));
	//c.erase(c.begin(), c.end());
}

const std::vector<Card> Deck::getCards() const
{
	return this->cards;
}
void Deck::clear_deck()
{
	this->cards.erase(this->cards.begin(), this->cards.end());
}
