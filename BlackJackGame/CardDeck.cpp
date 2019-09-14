#include <iostream>
#include <cstdlib>
#include <algorithm>
#include "CardDeck.h"
#include "Exceptions.h"


using namespace mtm;
using std::find;
using std::cout;
using std::endl;

const int major_value = 10;

CardDeck::CardDeck(const Card& card){
	this->_Deck.push_back(card);
}

CardDeck CardDeck::getFullDeck(){
	CardDeck full_deck;
	for(int suit = 0; suit <= 3; suit++){
		Card::Suit cur_suit = (Card::Suit)suit;
		for(int i = 1; i <= 10 ;i++){
			Card new_card = Card(cur_suit,i);
			full_deck._Deck.push_back(new_card); // func fillDeck
		}
		full_deck._Deck.push_back(Card(cur_suit,'J'));
		full_deck._Deck.push_back(Card(cur_suit,'Q'));
		full_deck._Deck.push_back(Card(cur_suit,'K'));
	}
	return full_deck;
}

Card CardDeck::draw(){
	if(this->_Deck.empty()){
		throw CardDeckIsEmptyException();
	}
	Card drawn = this->_Deck.back();
	this->_Deck.pop_back();
	return drawn;
}

const Card& CardDeck::top() const{
	if (this->_Deck.empty()) {
		throw CardDeckIsEmptyException();
	}
	return this->_Deck.back();
}

unsigned int CardDeck::size() const{
	return (unsigned)this->_Deck.size();
}

bool CardDeck::isEmpty() const{
	return this->_Deck.empty();
}

void CardDeck::clear(){
	this->_Deck.clear();
}

unsigned int CardDeck::value() const{
	unsigned int value = 0;
	for(vector<Card>::const_iterator cur_card = this->_Deck.begin();
				cur_card != this->_Deck.end(); ++cur_card) {
		value += (*cur_card).getValueOfCard(value);
	}
	return value;
}

CardDeck& CardDeck::operator+=(const CardDeck& deck){
	CardDeck deck_tmp = deck;
	for(vector<Card>::const_iterator cur_card = deck_tmp._Deck.begin();
			cur_card != deck_tmp._Deck.end(); ++cur_card) {
			this->_Deck.push_back(*cur_card);
	}
	return *this;
}

CardDeck operator+(const CardDeck& deck1, const CardDeck& deck2){
	CardDeck sum = deck1;
	sum += deck2;
	return sum;
}

CardDeck operator*(const CardDeck& deck, const int multier){
	CardDeck product;
	if(multier){
		for(int i = 0; i < multier; i++){
			product += deck;
		}
	}
	return product;
}

bool operator<=(const CardDeck& deck1, const CardDeck& deck2){
	if(deck1._Deck.size() > deck2._Deck.size()){
		return false;
	}
	for(vector<Card>::const_iterator cur_card = deck1._Deck.begin();
					cur_card != deck1._Deck.end(); ++cur_card) {
		int count_deck2 = count(deck2._Deck.begin(), deck2._Deck.end(), *cur_card);
		int count_deck1 = count(deck1._Deck.begin(), deck1._Deck.end(), *cur_card);
		if(!count_deck2 ||  count_deck1 > count_deck2){
			return false;
		}
	}
	return true;
}

bool operator>=(const CardDeck& deck1, const CardDeck& deck2){
	return deck2 <= deck1;
}

bool operator<(const CardDeck& deck1, const CardDeck& deck2){
	if(deck1 <= deck2 && !(deck2 <= deck1)){
		return true;
	}
	return false;
}

bool operator>(const CardDeck& deck1, const CardDeck& deck2){
	return deck2 < deck1;
}



bool operator==(const CardDeck& deck1, const CardDeck& deck2){
	if (deck1._Deck.size() != deck2._Deck.size()) {
		return false;
	}
	if(deck1._Deck == deck2._Deck){
		return true;
	}
	return false;
}

bool operator!=(const CardDeck& deck1, const CardDeck& deck2){
	return !(deck1 == deck2);
}

istream& operator>>(istream& is, CardDeck& ideck){
	int size = 0;
	is >> size;
	if(!ideck._Deck.size()){
		ideck._Deck.clear();
	}
	for(int i = 0; i < size; i++){
		Card cur_card;
		is >> cur_card;
		ideck._Deck.push_back(cur_card);
	}
	return is;
}

ostream& operator<<(ostream& os, const CardDeck& odeck){
	int deck_size = odeck._Deck.size();
	os << deck_size << ' ';
	for (int i = 0; i < deck_size-1; i++) {
		os << odeck._Deck[i] << ' ';
	}
	os << odeck._Deck[deck_size - 1];
	return os;
}

bool CardDeck::aceIsIn() const{
	if(find(this->_Deck.begin(), this->_Deck.end(), Card(Card::Spade, 1))
			!= this->_Deck.end()
		|| find(this->_Deck.begin(), this->_Deck.end(), Card(Card::Diamond, 1))
		!= this->_Deck.end()
		|| find(this->_Deck.begin(), this->_Deck.end(), Card(Card::Heart, 1))
		!= this->_Deck.end()
		|| find(this->_Deck.begin(), this->_Deck.end(), Card(Card::Club, 1))
		!= this->_Deck.end()){
			return true;
		}
		return false;
}

bool CardDeck::haveBJ()const {
	const CardDeck& pdeck = *this;
	int player_value = this->value();
	if (pdeck.aceIsIn() && (player_value == 11 || player_value == 21)) {
		return true;
	}
	return false;
}

