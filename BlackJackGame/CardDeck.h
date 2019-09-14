#ifndef CARD_DECK_H
#define CARD_DECK_H

#include <iostream>
#include "Card.h"
#include <vector>
#include "Exceptions.h"

using std::vector;



class CardDeck {
public:
	vector<Card> _Deck;
public:
	CardDeck() = default;
	CardDeck(const CardDeck&) = default;
	CardDeck(const Card&);
	~CardDeck() = default;
	Card draw();
	const Card& top() const ;
	unsigned int size() const;
	bool isEmpty() const;
	void clear();
	unsigned int value() const;
	static CardDeck getFullDeck();
	bool aceIsIn() const;
	bool haveBJ() const;
	CardDeck& operator=(const CardDeck&) = default;
	CardDeck& operator+=(const CardDeck&);
	friend bool operator<=(const CardDeck&, const CardDeck&);
	friend bool operator==(const CardDeck&, const CardDeck&);
	friend istream& operator>>(istream&, CardDeck&);
	friend ostream& operator<<(ostream&, const CardDeck&);

};
bool operator<=(const CardDeck&, const CardDeck&);
CardDeck operator+(const CardDeck&, const CardDeck&);
CardDeck operator*(const CardDeck&, const int);
inline CardDeck operator*(const int multier, const CardDeck& deck)
{return deck * multier;}
bool operator!=(const CardDeck&, const CardDeck&);
bool operator>=(const CardDeck&, const CardDeck&);
bool operator<(const CardDeck&, const CardDeck&);
bool operator>(const CardDeck&, const CardDeck&);


#endif // CARD_DECK_H
