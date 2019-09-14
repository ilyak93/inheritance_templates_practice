#ifndef PLAYERS_H
#define PLAYERS_H

#include "CardDeck.h"

class Player{
public:
	enum PlayerState{IN = 5,STAND, OUT};
	enum ResultLstGm{LOSE = 8,EVEN, WIN};
	enum Strategy{CASINO, CALCULATED};
private:
	int _id;
	int _budget;
	CardDeck _pdeck;
	unsigned int _value;
	Strategy _strgy;
	ResultLstGm _result;
	PlayerState _state;
	unsigned int _bet;
public:
	Player(int id, int budget, Strategy strgy)
			:_id(id), _budget(budget),_value(0),_strgy(strgy), _result(EVEN),
			 _state(IN), _bet(strgy == CASINO ? 1 : 20){}
	Player(const Player&) = default;
	virtual ~Player(){}
	Player& operator=(const Player&) = default;
	virtual void hitOrStand(const Card&, const Card&) = 0;
	virtual void makeBet() = 0;
	void addCard(const Card&);
	int getId() const;
	CardDeck& getDeck();
	CardDeck& getDeck() const;
	unsigned int getValue() const;
	int getBudget() const;
	int getBet() const;
	Strategy getStrgy() const;
	ResultLstGm getResult() const;
	PlayerState getState() const;
	void setState(PlayerState);
	void setResult(ResultLstGm);
	void setBudget(int);
	void setBet(int);
	void setValue(int);
};

class CasinoP : public Player{
public:
	CasinoP(int id, int budget, Strategy strgy)
	:Player(id, budget, strgy){}
	CasinoP(const CasinoP&) = default;
	virtual ~CasinoP() = default;
	CasinoP& operator=(const CasinoP&) = default;
	virtual void hitOrStand(const Card&, const Card&);
	virtual void makeBet();
	};

class CalculatedP : public Player{
private:
	bool _ace_valued_11;
	void strgyAce11In(const Card&, const Card&, int);
	void strgyAce11NotIn(const Card&, const Card&, int);
public:
	CalculatedP(int id, int budget, Strategy strgy)
	:Player(id, budget, strgy),_ace_valued_11(false){}
	CalculatedP(const CalculatedP&) = default;
	virtual ~CalculatedP() = default;
	CalculatedP& operator=(const CalculatedP&) = default;
	virtual void hitOrStand(const Card&, const Card&);
	virtual void makeBet();
	void resetAce11();
	};

#endif // PLAYERS_H
