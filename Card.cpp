#include "stdafx.h"
#include "Card.h"

Card::Card(Suit suit, Rank rank) {
	this->suit = suit;
	this->rank = rank;
}

bool operator<(const Card& a, const Card& b) {
	if (a.rank < b.rank) {
		return true;
	}
	else if (a.rank == b.rank) {
		return (a.suit < b.suit);
	}
	else {
		return false;
	}
}
bool operator==(const Card& a, const Card& b) {
	if ((a.rank == b.rank) && (a.suit == b.suit)) {
		return true;
	}
	else {
		return false;
	}
}