#pragma once
#include "stdafx.h"
#include "Deck.h"
#include "Card.h"
#include "Poker.h"
#include <vector>
class Deck;
class Hand {
	friend std::ostream& operator<<(std::ostream& out, const Hand& h);
	friend Hand& operator<<(Hand&h, Deck& d);
public:
	Hand() = default;
	Hand(const Hand& h) :cards(h.getCards()) {};
	Hand & operator=(const Hand & h);
	int size() const;
	bool operator==(Hand & h) const;
	bool operator<(const Hand & h);
	std::string asString() const;
	const std::vector<Card> getCards() const;
	Card & operator[](size_t i);
	void remove_card(size_t i);
	void clear_hand();
	void set_hand(std::vector<Card> v);
	Hand make_hand(int i);
	std::vector<Card> make_cards(int i);



private:
	std::vector<Card> cards;

};
std::ostream& operator<<(std::ostream&out, const Hand& h);
Hand& operator<<(Hand&h, Deck& d);