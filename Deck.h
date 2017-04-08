#pragma once
#include "stdafx.h"
#include "Card.h"
#include "Hand.h"
#include <vector>
#include <iostream>

class Hand;
class Deck {
	friend std::ostream& operator<<(std::ostream& output, const Deck& deck);
	friend Hand& operator<<(Hand&h, Deck& d);
public:
	Deck() = default;
	Deck(const char* &filename);
	int load(const char* &filename);
	void shuffle();
	int size() const;
	void add_card(Card c);
	void collect_cards(const std::vector<Card> & c);
	const std::vector<Card> getCards() const;
	void clear_deck();
private:

	std::vector<Card> cards;

};
std::ostream& operator<<(std::ostream& output, const Deck& deck);
