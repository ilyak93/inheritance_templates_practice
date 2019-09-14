#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <cstring>
#include <string>

using std::istream;
using std::ostream;
using std::string;

class Card {
public:
	enum Suit { Heart, Diamond, Club, Spade };
private:
	Suit _suit;
	int _value;
	char _identier;
public:
	Card();
	Card(Suit suit, int value);
	Card(Suit suit, char identier);
	Card(const Card&) = default;
	~Card() = default;
	Card& operator=(const Card&) = default;
	friend bool operator==(const Card&, const Card&);
	friend istream& operator>>(istream& is, Card&);
	friend ostream& operator<<(ostream& os, const Card&);
	const unsigned int getValueOfCard(unsigned int) const;
};

bool operator!=(const Card& card1, const Card& card2);

#endif // CARD_H
