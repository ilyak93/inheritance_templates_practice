/*
 * Players.cpp
 *
 *  Created on: Jan 21, 2016
 *      Author: Ilya
 */
#include "Players.h"



void CalculatedP::strgyAce11In(const Card& card, const Card& dler_card,
		int cur_value){
	int dler_card_value = dler_card.getValueOfCard(0);
		if(cur_value < 18 || (cur_value == 18 && (dler_card_value == 2 ||
				dler_card_value == 7 || dler_card_value == 8))){
			this->addCard(card);
			this->setValue(this->getDeck().value());
			int new_value = this->getValue();
			if(new_value > 21){
				this->setState(OUT);
				this->setBudget(this->getBudget() - this->getBet());
				return;
			}
		} else {
			this->setState(STAND);
		}
}

void CalculatedP::strgyAce11NotIn(const Card& card, const Card& dler_card,
		int cur_value){
	if(this->getValue() < 12){
		this->addCard(card);
		this->setValue(this->getDeck().value());
		if(this->getValue() > 21){
			this->setState(OUT);
			this->setBudget(this->getBudget() - this->getBet());
		} else if(card.getValueOfCard(this->getValue()) == 11){
			this->_ace_valued_11 = true;
		}
	} else {
		int dler_card_value = dler_card.getValueOfCard(0);
		if((cur_value == 12 &&
		  (dler_card_value == 4 || dler_card_value == 5|| dler_card_value == 6)) ||
				((cur_value >= 13 && cur_value <= 16)  &&
				(dler_card_value >= 2 || dler_card_value <= 6))
				|| cur_value >=17){
				this->setState(STAND);
			} else {
				this->addCard(card);
				this->setValue(this->getDeck().value());
			}
	}
}

void CasinoP::hitOrStand(const Card& card, const Card& dler_card){
		if(this->getValue() < 17){
			this->addCard(card);
			this->setValue(this->getDeck().value());
			if(this->getValue() > 21){
				this->setState(OUT);
				this->setBudget(this->getBudget() - this->getBet());
				return;
			}
		} else {
			this->setState(STAND);
		}
}

void CasinoP::makeBet(){
	ResultLstGm result = this->getResult();
	if(result == WIN){
		this->setBet(1);
	} else if(result == LOSE) {
		this->setBet(this->getBet()*2);
	}
}

void CalculatedP::hitOrStand(const Card& card, const Card& dler_card){
		int cur_value = this->getValue();
		if(this->_ace_valued_11){
			strgyAce11In(card, dler_card, cur_value);
		} else {
			strgyAce11NotIn(card, dler_card, cur_value);
		}
}

void CalculatedP::makeBet(){
	if(this->getResult() == WIN){
		this->setBet(this->getBet()+1);
	} else if(this->getResult() == LOSE){
		int cur_bet = this->getBet();
		if (cur_bet != 1) {
			this->setBet(this->getBet() - 1);
		}
	}
}

	void CalculatedP::resetAce11(){
		this->_ace_valued_11 = false;
	}

	void Player::addCard(const Card& card){
		this->_pdeck += card;
	}
	CardDeck& Player::getDeck(){
		return this->_pdeck;
	}
	int Player::getId() const{
		return this->_id;
	}
	unsigned int Player::getValue() const{
		return this->_value;
	}
	int Player::getBudget() const{
		return this->_budget;
	}
	Player::Strategy Player::getStrgy() const{
		return this->_strgy;
	}
	int Player::getBet() const{
		return this->_bet;
	}

	Player::ResultLstGm Player::getResult() const{
		return this->_result;
	}

	 Player::PlayerState Player::getState() const{
		return this->_state;
	}
	 void Player::setState(PlayerState state){
		 if(state == STAND){
			 this->_state = STAND;
		 } else if(state == OUT){
			 this->_state = OUT;
		 } else {
			 this->_state = IN;
		 }
	 }
	void Player::setResult(ResultLstGm result){
		this->_result = result;
	}
	void Player::setBet(int new_bet){
			this->_bet = new_bet;
	}
	void Player::setBudget(int new_budget){
		this->_budget = new_budget;
	}
	void Player::setValue(int new_value){
		this->_value = new_value;
	}


