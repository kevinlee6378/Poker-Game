#pragma once

#include "stdafx.h"
#include "Hand.h"
#include "Card.h"
#include "Deck.h"
#include<vector>
class Hand;
class Deck;

bool poker_rank(const Hand& h1, const Hand& h2);
bool valid_suit(char* c);
bool valid_rank(char* c);
Suit char_to_suit(char* suit);
Rank char_to_rank(char* rank);
string suit_to_string(Suit suit);
string rank_to_string(Rank rank);
int print_vector(const vector<Card> & v);
int parse_file(vector<Card>& v, const char* s);
int analyze_hand(const vector<Card> & v);
int print_poker_hands(const vector<Card>& v);
char* get_hand_string(int r);
void print_hand_rank(int r);
void usage_message(const char* name);

const int no_card_at_position = 1;
const int instance_not_availabe = 2;
const int game_already_started = 3;
const int unknown_game = 4;
const int no_game_in_progress = 5;
const int already_playing = 6;
const int not_valid_discard = 7;
const int no_more_cards = 8;
