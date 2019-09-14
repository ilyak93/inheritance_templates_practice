/*
 * BlackJack.cpp
 *
 *  Created on: Jan 17, 2016
 *      Author: Ilya
 */
#include <iostream>
#include <algorithm>
#include "BlackJack.h"
#include "Exceptions.h"

using std::map;
using std::pair;
using mtm::PlayerDoesNotExistException;
using mtm::PlayerAlreadytExistException;
using mtm::NoPlayersException;
using mtm::NotEnoughCardsException;
using std::find_if;
using std::begin;
using std::end;

//const incompitble wit erase
vector<Player*>::iterator BlackJack::findPlayer(int id){
		vector<Player*>::iterator found
		= find_if(begin(this->_players_in), end(this->_players_in),
				[id] (Player* player) {
	        return player->getId() == id;
	    });
	   return found;
	}

bool BlackJack::isPlayerIn(int id) const{
	map<int, Player*>::const_iterator found =
			find_if(begin(this->_players_pool),
			end(this->_players_pool), [id] (pair<int, Player*> found) {
		return found.second->getId() == id;
	});
	return found != end(this->_players_pool);
}

bool BlackJack::allPlayersIn(const vector<int>& ids) const{
	for(vector<int>::const_iterator cur_id = ids.begin();
			cur_id != ids.end(); ++cur_id){
		if(!this->isPlayerIn(*cur_id)){
			return false;
		}
	}
	return true;
}

void BlackJack::BJCheck(int& players_in_count) {
	for (vector<Player*>::const_iterator it = this->_players_in.begin();
	it != this->_players_in.end(); ++it) {
		Player* cur_player = *it;
			if (cur_player->getDeck().haveBJ()) {
				cur_player->setResult(Player::WIN);
				cur_player->setBudget(cur_player->getBudget()+
						((int)(cur_player->getBet()*1.5)));
				cur_player->setState(Player::OUT);
				players_in_count--;
			}
	}
}

void BlackJack::firstTwoCardsDeal(Card& dler_card){
	this->_dler.clear();
	this->_dler_value = 0;
	for (int i = 0; i < 2; i++) {
		for (vector<Player*>::const_iterator it = this->_players_in.begin();
		it != this->_players_in.end(); ++it) {
			Player* cur_player = *it;
			if (i == 0) {
				cur_player->makeBet();
				if (cur_player->getStrgy() == Player::Strategy::CALCULATED) {
					((CalculatedP*)cur_player)->resetAce11();
				}
				cur_player->setState(Player::IN);
				cur_player->getDeck().clear();

			}
			cur_player->addCard(this->_game_deck.draw());
			cur_player->setValue(cur_player->getDeck().value());
		}
		if (i == 0) {
			dler_card = this->_game_deck.top();
		}
		this->_dler += this->_game_deck.draw();
		this->_dler_value = this->_dler.value();
	}
}

static void endRoundDlerBJ(vector<Player*>& players_in){
	for(vector<Player*>::iterator it = players_in.begin();
			it != players_in.end();++it){
		Player* cur_player = *it;
		if(cur_player->getState() != Player::OUT){
			if (!cur_player->getDeck().haveBJ()) {
				cur_player->setBudget(cur_player->getBudget() -
						cur_player->getBet());
				cur_player->setResult(Player::LOSE);
			}
			else {
				cur_player->setResult(Player::EVEN);
			}
		}
	}
}

void BlackJack::playersDeal(int& players_in_count, const Card& dler_card) {
	bool someone_is_in = true;
	while (someone_is_in) {
		someone_is_in = false;
		for (vector<Player*>::const_iterator it = this->_players_in.begin();
		it != this->_players_in.end(); ++it) {
			Player* cur_player = *it;
			if (cur_player->getState() == Player::IN) {
				someone_is_in = true;
				cur_player->hitOrStand(this->_game_deck.top(), dler_card);
				Player::PlayerState cur_state = cur_player->getState();
				if (cur_state != Player::STAND) {
					this->_game_deck.draw();
					if (cur_state == Player::OUT) {
						players_in_count--;
					}
				}
			}
		}
	}
}

void BlackJack::dlerDeal(){
	while(this->_dler_value < 17){
		this->_dler += this->_game_deck.draw();
		this->_dler_value = this->_dler.value();
		if(this->_dler_value > 21){
			return;
		}
	}
}

void BlackJack::Result(){
	for(vector<Player*>::iterator it = this->_players_in.begin();
			it != this->_players_in.end();++it){
		Player* cur_player = *it;
		Player::PlayerState cur_player_state = cur_player->getState();
		if(cur_player_state == Player::STAND){
			if(this->_dler_value > 21 ||
					cur_player->getValue() > this->_dler.value()){
				cur_player->setResult(Player::WIN);
				cur_player->setBudget(cur_player->getBudget()
						+ cur_player->getBet());
			} else if(cur_player->getValue() < this->_dler.value()){
				cur_player->setResult(Player::LOSE);
				cur_player->setBudget(cur_player->getBudget() -
						cur_player->getBet());
			} else {
				cur_player->setResult(Player::EVEN);
			}
		}
	}
}



	BlackJack::~BlackJack() {
		for (map<int, Player*>::iterator it = this->_players_pool.begin();
		it != this->_players_pool.end(); ++it) {
			delete it->second;
		}
	}

	void BlackJack::addPlayer(int id, PlayerStrategy strategy, int budget){
		Player *player = nullptr;
		if (this->isPlayerIn(id)) {
			throw PlayerAlreadytExistException();
		}
		if(strategy == CASINO){
			player = new CasinoP(id, budget, Player::Strategy::CASINO);
		} else {
			player = new CalculatedP(id, budget, Player::Strategy::CALCULATED);
		}
		this->_players_pool.insert(pair<int, Player*>(id, player));
	}

	void BlackJack::joinGame(int player){
		vector<int> players(1, player);
		BlackJack::joinGame(players);
	}

	void BlackJack::joinGame(const vector<int>& players){
		if(this->allPlayersIn(players)){
			for(vector<int>::const_iterator cur_id = players.begin();
							cur_id != players.end(); ++cur_id){
				if(this->findPlayer(*cur_id) == end(this->_players_in)) {
					Player* cur_player = this->_players_pool[*cur_id];
					if(cur_player->getStrgy() == Player::Strategy::CASINO) {
						cur_player->setBet(1);
						cur_player->setResult(Player::EVEN);
					}
					this->_players_in.push_back(cur_player);
					this->_players_in_count++;
				}
			}
		} else {
			throw PlayerDoesNotExistException();
		}
	}

	void BlackJack::leaveGame(int player){
		vector<int> players(1, player);
		leaveGame(players);
	}

	void BlackJack::leaveGame(const vector<int>& players){
		if(this->allPlayersIn(players)){
			for(vector<int>::const_iterator cur_id = players.begin();
					cur_id != players.end(); ++cur_id){
				vector<Player *>::iterator found =
						this->findPlayer(*cur_id);
				if(found != end(this->_players_in)){
					this->_players_in.erase(found);
					this->_players_in_count--;
				}
			}
		} else {
			throw PlayerDoesNotExistException();
		}
	}

	void BlackJack::playRound(){
		if(!(CardDeck::getFullDeck() <= this->_game_deck)){
			throw NotEnoughCardsException();
		} else if(this->_players_in_count){
			int players_stand = this->_players_in_count;
			Card dler_first_card;
			this->firstTwoCardsDeal(dler_first_card);
			if(this->_dler.haveBJ()){
				endRoundDlerBJ(this->_players_in);
				return;
			} else {
				this->BJCheck(players_stand);
				this->playersDeal(players_stand, dler_first_card);
				if(players_stand){
					this->dlerDeal();
				}
				this->Result();
			}
		}
	}


	void BlackJack::reloadDeck(const CardDeck& newDeck){
		this->_game_deck = newDeck;
	}


	int BlackJack::getBalance(int id) const{
		for(map<int, Player*>::const_iterator it = this->_players_pool.begin();
				it != this->_players_pool.end(); ++it){
			Player* cur_player = (*it).second;
			if(cur_player->getId() == id){
				return cur_player->getBudget();
			}
		}
		throw PlayerDoesNotExistException();
	}

	int BlackJack::getRichest() const{
		if(this->_players_pool.begin() == this->_players_pool.end()){
			throw NoPlayersException();
		}
		int richest = (*(this->_players_pool.begin())).second->getId();
		int max_budget = (*(this->_players_pool.begin())).second->getBudget();
		for(map<int, Player*>::const_iterator it = this->_players_pool.begin();
				it != this->_players_pool.end(); ++it){
			int cur_budget = (*it).second->getBudget();
			if(cur_budget > max_budget){
				max_budget = cur_budget;
				richest = (*it).second->getId();
			} else if(cur_budget == max_budget){
				int cur_id = (*it).second->getId();
				richest = cur_id < richest ? cur_id : richest;
			}
		}
		return richest;
	}
