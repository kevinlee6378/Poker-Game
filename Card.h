#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;
enum Suit { Clubs, Diamonds, Hearts, Spades };
enum Rank { Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King, Ace };
struct Card {
public:

	Card(Suit suit, Rank rank);

	Suit suit;
	Rank rank;

};
bool operator==(const Card& a, const Card& b);
bool operator<(const Card& a, const Card& b);