#include <iostream>
#include <cstdlib>
#include <new>
#include <cstring>
#include <string>
#include <cassert>
#include <cmath>
#include "Card.h"
#include "Exceptions.h"

using std::string;
using std::istream;
using std::ostream;
using std::cin;
using std::cout;
using std::stoi;
using std::to_string;
using std::ceil;
using std::endl;
using namespace mtm;

const int major_value = 10;
const int ace_low_value = 1;
const int ace_high_value = 11;
const int devider = 21;

bool cardSuitCorrect(Card::Suit suit) {
	if (suit < Card::Heart || suit > Card::Spade) {
		return false;
	}
	return true;
}

bool cardSuitInputCorrect(char suit) {
	return (suit == 'H' || suit == 'D' || suit == 'C' || suit == 'S');
}

Card::Suit charToSuit(char suit) {
	suit = toupper(suit);
	switch (suit) {
	case 'H':
		return Card::Heart;
	case 'D':
		return Card::Diamond;
	case 'C':
		return Card::Club;
	case 'S':
		return Card::Spade;
	}
	throw CardWrongArgsException();
}

 char suitToChar(Card::Suit suit) {
	 int int_suit = (int)suit;
	switch (int_suit) {
	case 0:
		return 'H';
	case 1:
		return 'D';
	case 2:
		return 'C';
	}
	return 'S';
}

bool cardValueCorrect(int value) {
	if (!(value > 0 && value < 11)) {
		return false;
	}
	return true;
}

bool cardIdentierCorrect(char identier) {
	identier = toupper(identier);
	if (identier == 'A' || identier == 'J' ||
		identier == 'Q' || identier == 'K') {
		return true;
	}
	return false;
}



Card strToCardOrExc(const string& str) {
	int len = str.size();
	if (!(len == 2 || len == 3)) {
		throw CardWrongArgsException();
	}
	char suit_c = str.at(len - 1);
	Card::Suit suit = charToSuit(suit_c);
	string val = str;
	val.resize(len - 1);
	char tmp_identier = toupper(val.at(0));
	Card new_card;
	if (cardIdentierCorrect(tmp_identier)) {
		new_card = Card(suit, tmp_identier);
	}
	else{
		int tmp_value = 0;
		try {
			tmp_value = stoi(val);
		}
		catch (...) { throw CardWrongArgsException(); }
		new_card = Card(suit, tmp_value);
	}
	return new_card;
}

inline Card::Card() {
	_suit = Club;
	_value = 0;
	_identier = 'D';
}



inline Card::Card(Suit suit, int value) {
	if (!cardSuitCorrect(suit) || !cardValueCorrect(value)) {
		throw CardWrongArgsException();
	}
	this->_suit = suit;
	if (value == 1) {
		this->_identier = 'A';
		this->_value = 0;
	}
	else {
		this->_value = value;
		this->_identier = '!';
	}
}

inline Card::Card(Suit suit, char identier) {
	if (!cardSuitCorrect(suit) || !cardIdentierCorrect(identier)) {
		throw CardWrongArgsException();
	}
	this->_suit = suit;
	this->_identier = toupper(identier);
	this->_value = 0;
}

bool operator==(const Card& card1, const Card& card2) {
	return ((card1._suit == card2._suit) && card1._value == card2._value &&
		card1._identier == card2._identier);
}

bool operator!=(const Card& card1, const Card& card2) {
	return !(card1 == card2);
}

istream& operator>>(istream& is, Card& card) {
	string str;
	is >> str;
	card = strToCardOrExc(str);
	return is;
}

ostream& operator<<(ostream& os, const Card& card) {
	string str;
	if(cardValueCorrect(card._value)){
		str += std::to_string((long long int)card._value);
	} else {
		str += card._identier;
	}
	str += suitToChar(card._suit);
	return os << str;
}

const unsigned int Card::getValueOfCard(unsigned int cur_value) const{
	assert(!(this->_identier == '!' && this->_value == 0));
	if (this->_identier == 'A' || this->_value == 1) {
		return ceil((cur_value + ace_low_value) / devider) <
				ceil((cur_value + ace_high_value) / devider)
				? ace_low_value : ace_high_value;
	} else if(this->_identier == '!'){
		return this->_value;
	}
	return major_value;
}
