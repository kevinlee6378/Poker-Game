#include "stdafx.h"
#include "Poker.h"
#include "Hand.h"
#include "Deck.h"
#include "Card.h"
#include <vector>

bool poker_rank(const Hand & h1, const Hand & h2) {

	int hand1 = analyze_hand(h1.getCards());
	int hand2 = analyze_hand(h2.getCards());
	return hand1 < hand2;
}
bool valid_suit(char* c) {
	char validSuits[] = { 'C', 'c', 'D', 'd', 'H', 'h', 'S', 's' };
	bool valid = false;
	for (int i = 0; i < 8; i++) {
		if (*c == validSuits[i]) {
			valid = true;
			break;
		}
	}
	return valid;
}
bool valid_rank(char* c) {
	char validRanks[] = { '2', '3', '4', '5', '6', '7', '8', '9', '1', 'J', 'j', 'Q', 'q', 'K', 'k', 'A', 'a' };
	bool valid = false;
	for (int i = 0; i < 17; i++) {
		if (*c == validRanks[i]) {
			valid = true;
			break;
		}
	}
	return valid;
}
Suit char_to_suit(char* suit) {
	if (*suit == 'C' || *suit == 'c') {
		return Clubs;
	}
	if (*suit == 'D' || *suit == 'd') {
		return Diamonds;
	}
	if (*suit == 'H' || *suit == 'h') {
		return Hearts;
	}
	if (*suit == 'S' || *suit == 's') {
		return Spades;
	}
	else {
		return Clubs;
	}
}
Rank char_to_rank(char* rank) {
	if (*rank == '2') {
		return Two;
	}
	if (*rank == '3') {
		return Three;
	}
	if (*rank == '4') {
		return Four;
	}
	if (*rank == '5') {
		return Five;
	}
	if (*rank == '6') {
		return Six;
	}
	if (*rank == '7') {
		return Seven;
	}
	if (*rank == '8') {
		return Eight;
	}
	if (*rank == '9') {
		return Nine;
	}
	if (*rank == '1') {
		return Ten;
	}
	if (*rank == 'J' || *rank == 'j') {
		return Jack;
	}
	if (*rank == 'Q' || *rank == 'q') {
		return Queen;
	}
	if (*rank == 'K' || *rank == 'k') {
		return King;
	}
	if (*rank == 'A' || *rank == 'a') {
		return Ace;
	}
	else {
		return Two;
	}
}
int parse_file(vector<Card> & v, const char* s) {
	string line;
	ifstream ifs;
	ifs.open(s);
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
			int cardsInHand = 0;
			vector<Card> hand;
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
					hand.push_back(Card(char_to_suit(suit), char_to_rank(rank)));
					cardsInHand++;
					//cout << cardsInHand << endl;
				}
				else {
					cout << "Not Valid Card Format " << current << endl;
				}
			}
			if (cardsInHand == 5) {
				for (int i = 0; i < (static_cast<int>(hand.size())); ++i) {
					v.push_back(hand[i]);
				}
			}
			else {
				cout << "Hand doesn't have 5 cards" << endl;
			}
		}
		ifs.close();
		return 0;
	}
}
string suit_to_string(Suit suit) {
	if (suit == Clubs) {
		return "Clubs";
	}
	if (suit == Diamonds) {
		return "Diamonds";
	}
	if (suit == Hearts) {
		return "Hearts";
	}
	if (suit == Spades) {
		return "Spades";
	}
	else {
		return "Error";
	}
}
string rank_to_string(Rank rank) {
	if (rank == Two) {
		return "Two";
	}
	if (rank == Three) {
		return "Three";
	}
	if (rank == Four) {
		return "Four";
	}
	if (rank == Five) {
		return "Five";
	}
	if (rank == Six) {
		return "Six";
	}
	if (rank == Seven) {
		return "Seven";
	}
	if (rank == Eight) {
		return "Eight";
	}
	if (rank == Nine) {
		return "Nine";
	}
	if (rank == Ten) {
		return "Ten";
	}
	if (rank == Jack) {
		return "Jack";
	}
	if (rank == Queen) {
		return "Queen";
	}
	if (rank == King) {
		return "King";
	}
	if (rank == Ace) {
		return "Ace";
	}
	else {
		return "Error";
	}
}
//analyzes the 5 cards and returns an int representing which poker hand it is
int analyze_hand(const vector<Card> & v) {
	int numC = 0, numD = 0, numH = 0, numS = 0, numSame = 0, numConsecutive = 0;
	for (auto i = v.begin(); i != v.end(); ++i) {
		if (i->suit == Clubs) {
			numC++;
		}
		else if (i->suit == Diamonds) {
			numD++;
		}
		else if (i->suit == Hearts) {
			numH++;
		}
		else {
			numS++;
		}
		if (i != v.end() - 1) {
			if (i->rank == (i + 1)->rank) {
				numSame++;
			}
			else {
				if (i->rank + 1 == (i + 1)->rank) {
					numConsecutive++;
				}
			}
		}
	}
	if (numConsecutive == 4) {
		if (numC == 5 || numD == 5 || numH == 5 || numS == 5) {
			return 8;
			//straight flush
		}
		else {
			return 4;
			//straight
		}
	}
	else if (numSame == 3) {
		if (((v.begin() + 1)->rank == ((v.begin()) + 2)->rank) && ((v.begin() + 2)->rank == ((v.begin()) + 3)->rank)) {
			return 7;
			//four of a kind
		}
		else {
			return 6;
			//full house
		}
	}
	else if (numC == 5 || numD == 5 || numH == 5 || numS == 5) {
		return 5;
		//flush
	}
	else if (numSame == 2) {
		if (((v.begin()->rank) == ((v.begin()) + 2)->rank) || ((v.begin() + 1)->rank == ((v.begin()) + 3)->rank) || ((v.begin() + 2)->rank == ((v.begin()) + 4)->rank)) {
			return 3;
			//three of a kind
		}
		else {
			return 2;
			//two pairs
		}
	}
	else if (numSame == 1) {
		return 1;
		//one pair
	}
	else {
		return 0;
		//no rank
	}

}
//the below method will take the big vector of hands and split it up into vectors of size 5
//and analyze them each one by one. It will call upon the analyze_hand method which will return an int
//indicating which poker hand the 5 cards are. Then it will call on the print_hand_rank method to actually print
// the appropriate words based on what rank was previously determined.
int print_poker_hands(const vector<Card> & v) {

	vector<vector<Card>> hands;
	for (auto i = v.begin(); i != v.end(); i += 5) {
		vector<Card> hand;
		copy(i, i + 5, back_inserter(hand));
			(hand.begin(), hand.end());
		hands.push_back(hand);
	}
	for (auto i = hands.begin(); i != hands.end(); ++i) {
		//print_vector(*i);
		int whatRank = analyze_hand(*i);
		print_hand_rank(whatRank);
	}
	return 0;
}
char* get_hand_string(int r) {
	if (r == 0) {
		return "No Rank";
	}
	else if (r == 1) {
		return "One Pair";
	}
	else if (r == 2) {
		return "Two Pairs";
	}
	else if (r == 3) {
		return "Three of a Kind";
	}
	else if (r == 4) {
		return "Straight";
	}
	else if (r == 5) {
		return "Flush";
	}
	else if (r == 6) {
		return "Full House";
	}
	else if (r == 7) {
		return "Four of a Kind";
	}
	else {
		return "Straight Flush";
	}
}
// this method prints out based on the rank that is given to it.
void print_hand_rank(int r) {
	if (r == 0) {
		cout << "No Rank" << endl;
	}
	else if (r == 1) {
		cout << "One Pair" << endl;
	}
	else if (r == 2) {
		cout << "Two Pairs" << endl;
	}
	else if (r == 3) {
		cout << "Three of a Kind" << endl;
	}
	else if (r == 4) {
		cout << "Straight" << endl;
	}
	else if (r == 5) {
		cout << "Flush" << endl;
	}
	else if (r == 6) {
		cout << "Full House" << endl;
	}
	else if (r == 7) {
		cout << "Four of a Kind" << endl;
	}
	else {
		cout << "Straight Flush" << endl;
	}
}
//this method takes a vector of cards and prints out the card in words understandable
int print_vector(const vector<Card> & v) {
	try {
		for (int i = 0; i < (static_cast<int>(v.size())); ++i) {
			cout << rank_to_string(v[i].rank) << " of " << suit_to_string(v[i].suit) << endl;
		}
		return 0;
	}
	catch (int e) {
		cout << "Error" << e;
		return 1;
	}
}
//message displayed to user when the user does not enter parameters properly.
void usage_message(const char* name) {
	cout << name << "[-shuffle] filename" << endl;
}	
