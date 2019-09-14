#pragma once

#ifndef BLACK_JACK_H
#define BLACK_JACK_H

#include <vector>
#include <map>

#include "CardDeck.h"
#include "Players.h"

using std::vector;
using std::map;

class Player;
class BlackJack
{
private:
	CardDeck _game_deck;
	CardDeck _dler;
	unsigned int _dler_value;
	map<int, Player*> _players_pool;
	vector<Player*> _players_in;
	int _players_in_count;
	void firstTwoCardsDeal(Card&);
	void playersDeal(int&, const Card&);
	void dlerDeal();
	void Result();
	vector<Player*>::iterator findPlayer(int);
	bool isPlayerIn(int) const;
	bool allPlayersIn(const vector<int>&) const;
	void BJCheck(int&);
public:
	enum PlayerStrategy { CASINO, CALCULATED };

	BlackJack(const CardDeck& deck): _game_deck(deck), _dler_value(0),
			_players_in_count(0){}
	~BlackJack();

	void addPlayer(int id, PlayerStrategy strategy, int budget);
	void joinGame(int player);
	void joinGame(const vector<int>& players);
	void leaveGame(int player);
	void leaveGame(const vector<int>& players);
	void playRound();

	void reloadDeck(const CardDeck& newDeck);

	int getBalance(int id) const;
	int getRichest() const;
};

#endif // BLACK_JACK_H

