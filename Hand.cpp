#include "stdafx.h"
#include "Hand.h"
#include "Card.h"
#include <sstream>

Hand& Hand::operator=(const Hand& h) {
	if (this->cards == h.cards) {
		return *this;
	}
	else {
		this->cards.clear();
		std::copy(h.cards.begin(), h.cards.end(), std::back_inserter(this->cards));
		return *this;
	}
}
int Hand::size() const {
	return this->cards.size();
}
bool Hand::operator== (Hand& h) const {
	if (this->cards == h.cards) {
		return true;
	}
	else {
		return false;
	}
}
bool Hand::operator<(const Hand& h) {

	bool thisHasFewer = this->size() <= h.size();
	if (thisHasFewer) {
		int i = 0;
		while (i < (static_cast<int>(this->cards.size()))) {
			// returns true if this is found to have card that is smaller.
			if (this->cards[i] < h.cards[i]) {
				return true;
				break;
			}
			// returns true when it the cards are same up to last element and this has less elements so this should be less.
			else if ((this->cards[i] == h.cards[i]) && (i == (static_cast<int>(this->cards.size())) - 1)) {
				return true;
			}
			//continues in loop if cards are equal
			else if (this->cards[i] == h.cards[i]) {
			}
			//returns false when card in this is larger than card in h.
			else {
				return false;
				break;
			}
			i++;
		}
	}
	else {
		int i = 0;
		while (i < (static_cast<int>(h.cards.size()))) {
			if (this->cards[i] < h.cards[i]) {
				return true;
				break;
			}
			// this returns false this time because the shorter hand is h this time so it should be the smaller of the two in terms of ranking.
			else if ((this->cards[i] == h.cards[i]) && (i == (static_cast<int>(h.cards.size())) - 1)) {
				return false;
			}
			else if (this->cards[i] == h.cards[i]) {
			}
			else {
				return false;
				break;
			}
			i++;
		}
	}
}
std::string Hand::asString() const {

	std::stringstream stringReturn;
	for (int i = 0; i < (static_cast<int>(this->cards.size())); ++i) {
		stringReturn << rank_to_string(this->cards[i].rank) << suit_to_string(this->cards[i].suit) << " ";
	}
	return stringReturn.str();
}
const std::vector<Card> Hand::getCards() const
{
	return this->cards;
}
Card & Hand::operator[](size_t i)
{
	if (i < this->size()) {
		return this->cards[i];
	} 
	else {
		throw no_card_at_position;
	}
}
void Hand::remove_card(size_t i)
{
	if (i < this->size()) {
		this->cards.erase(this->cards.begin() + i);
	}
	else {
		throw no_card_at_position;
	}
}
void Hand::clear_hand()
{
	this->cards.erase(this->cards.begin(), this->cards.end());
}
void Hand::set_hand(std::vector<Card> v)
{
	this->cards = v;
}
Hand Hand::make_hand(int i)
{
	std::vector<Card> display;
	Hand h;
	for (auto a = this->cards.begin(); a != this->cards.begin() + i; a++) {
		display.push_back(*a);
	}
	h.set_hand(display);
	return h;
}

std::vector<Card> Hand::make_cards(int i)
{
	std::vector<Card> display;
	for (auto a = this->cards.begin(); a != this->cards.begin() + i; a++) {
		display.push_back(*a);
	}
	return display;
}
	

std::ostream& operator<<(std::ostream& output, const Hand& h) {
	output << h.asString();
	return output;
}
Hand& operator<<(Hand& h, Deck& d) {
	h.cards.push_back(d.cards.back());
	d.cards.pop_back();
	std::sort(h.cards.begin(), h.cards.end());
	return h;
}
