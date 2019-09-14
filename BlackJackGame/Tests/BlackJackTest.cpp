#include "BlackJack.h"
#include "Exceptions.h"
#include "MtmTst.h"
#include <algorithm>

using std::random_shuffle;

using mtm::PlayerAlreadytExistException;
using mtm::PlayerDoesNotExistException;
using mtm::NotEnoughCardsException;
using mtm::NoPlayersException;

bool blackJackExample() {
	CardDeck deck;
	BlackJack bj(deck);
	bj.addPlayer(1, BlackJack::CASINO, 100);
	bj.addPlayer(2, BlackJack::CALCULATED, 100);
	ASSERT_THROW(PlayerDoesNotExistException, bj.joinGame(3));
	bj.joinGame({ 1, 2 });
	ASSERT_THROW(NotEnoughCardsException, bj.playRound());
	bj.reloadDeck(CardDeck::getFullDeck());
	bj.playRound();
	ASSERT_EQUALS(120, bj.getBalance(2));
	ASSERT_EQUALS(2, bj.getRichest());
	bj.leaveGame({ 1, 2 });

	return true;
}
void buildDeckDealerhasBJ(CardDeck& deck) {
	deck = deck.getFullDeck();
	deck += Card(Card::Diamond, 'A') + Card(Card::Diamond, 5) + Card(Card::Heart, 8) + Card(Card::Heart, 'A');
	deck += Card(Card::Club, 'A') + Card(Card::Diamond, 'K') + Card(Card::Diamond, 2) + Card(Card::Diamond, 3)
		+ Card(Card::Club, 'J') + Card(Card::Heart, 'Q');
}
void buildDeckDealerNoBJ(CardDeck& deck) {//dealers value = 18
	deck = deck.getFullDeck();
	deck += Card(Card::Spade, 'K') + Card(Card::Spade, 4) + Card(Card::Spade, 7);
	deck += Card(Card::Diamond, 8) + Card(Card::Diamond, 5) + Card(Card::Heart, 8) + Card(Card::Heart, 'A');
	deck += Card(Card::Club, 'A') + Card(Card::Diamond, 9) + Card(Card::Diamond, 2) + Card(Card::Diamond, 3)
		+ Card(Card::Club, 'J') + Card(Card::Heart, 'Q');
	//the dealer will have 9 and 8 = 17
}
void buildDeckDealerLoses(CardDeck& deck) {//dealers value = 26
	deck = deck.getFullDeck();
	deck += Card(Card::Spade, 9) + Card(Card::Spade, 4) + Card(Card::Spade, 7);
	deck += Card(Card::Diamond, 10) + Card(Card::Diamond, 5) + Card(Card::Heart, 8) + Card(Card::Heart, 'A');
	deck += Card(Card::Club, 'A') + Card(Card::Diamond, 6) + Card(Card::Diamond, 3) + Card(Card::Diamond, 3)
		+ Card(Card::Club, 'J') + Card(Card::Heart, 'Q');
	//the dealer will have 6 10 and 9 = 25
}
bool blackJackplayRound() {
	CardDeck deck;
	BlackJack bj(deck);
	bj.addPlayer(1, BlackJack::CASINO, 100); // Q A
	bj.addPlayer(2, BlackJack::CALCULATED, 500); // J A
	bj.addPlayer(3, BlackJack::CASINO, -100); // 3 8 7
	bj.addPlayer(4, BlackJack::CALCULATED, 0); // 3 5 4 K
	ASSERT_THROW(NotEnoughCardsException, bj.playRound());
	deck = deck.getFullDeck();
	deck.draw();
	deck += Card(Card::Diamond, 5) + Card(Card::Heart, 'K');
	ASSERT_THROW(NotEnoughCardsException, bj.playRound());
	deck.clear();
	/** the dealer will have a BJ from the beginning along with player #1 and player #2**/
	buildDeckDealerhasBJ(deck);
	bj.reloadDeck(deck);
	bj.joinGame({ 1,2,3,4 });
	bj.playRound();
	ASSERT_EQUALS(bj.getBalance(1), 100);
	ASSERT_EQUALS(bj.getBalance(2), 500);
	ASSERT_EQUALS(bj.getBalance(3), -101);
	ASSERT_EQUALS(bj.getBalance(4), -20);
	int currBid1 = 2;
	int currBid2 = 19;
	int price1 = -101;
	int price2 = -20;
	for (int i = 1; i<10; i++) {
		bj.joinGame({ 1,2,3,4 });
		buildDeckDealerhasBJ(deck);
		bj.reloadDeck(deck);
		bj.playRound();
		price1 = (price1)-(currBid1);
		price2 = (price2)-(currBid2);
		ASSERT_EQUALS(bj.getBalance(1), 100);
		ASSERT_EQUALS(bj.getBalance(2), 500);
		ASSERT_EQUALS(bj.getBalance(3), price1);
		ASSERT_EQUALS(bj.getBalance(4), price2);
		currBid1 *= 2;
		currBid2--;
	}
	for (int i = 1; i<100; i++) {
		bj.leaveGame({ 1,2,3,4 });
		currBid1 = 1;
		bj.joinGame({ 1,2,3,4 });
		buildDeckDealerhasBJ(deck);
		bj.reloadDeck(deck);
		bj.playRound();
		price1 = (price1)-(currBid1);
		price2 = (price2)-(currBid2);
		ASSERT_EQUALS(bj.getBalance(1), 100);
		ASSERT_EQUALS(bj.getBalance(2), 500);
		ASSERT_EQUALS(bj.getBalance(3), price1);
		ASSERT_EQUALS(bj.getBalance(4), price2);
		if (currBid2>1) {
			currBid2--;
		}
	}
	/** the dealer will have cards with value of 18**/
	int p1Balance = 100;
	int p2Balance = 500;
	int p1CurrBid = 1;
	int p2CurrBid = 20;
	for (int i = 1; i<5; i++) {
		bj.leaveGame({ 1,2,3,4 });
		currBid1 = 1;
		bj.joinGame({ 1,2,3,4 });
		buildDeckDealerNoBJ(deck);
		bj.reloadDeck(deck);
		bj.playRound();
		p1Balance += p1CurrBid*1.5;
		p2Balance += p2CurrBid*1.5;
		p2CurrBid++;
		price1 += currBid1;
		price2 += (currBid2);
		currBid2++;
		ASSERT_EQUALS(bj.getBalance(1), p1Balance);
		ASSERT_EQUALS(bj.getBalance(2), p2Balance);
		ASSERT_EQUALS(bj.getBalance(3), price1);
		ASSERT_EQUALS(bj.getBalance(4), price2);
	}
	/**the dealer will have cards with value of 26 so he loses**/
	for (int i = 1; i<5; i++) {
		bj.leaveGame({ 1,2,3,4 });
		currBid1 = 1;
		bj.joinGame({ 1,2,3,4 });
		buildDeckDealerLoses(deck);
		bj.reloadDeck(deck);
		bj.playRound();
		p1Balance += p1CurrBid*1.5;
		p2Balance += p2CurrBid*1.5;
		p2CurrBid++;
		price1 += currBid1;
		price2 += currBid2;
		currBid2++;
		ASSERT_EQUALS(bj.getBalance(1), p1Balance);
		ASSERT_EQUALS(bj.getBalance(2), p2Balance);
		ASSERT_EQUALS(bj.getBalance(3), price1);
		ASSERT_EQUALS(bj.getBalance(4), price2);
	}
	ASSERT_EQUALS(bj.getRichest(), 2);
	return true;
}

bool blackJackShuffle() {
	CardDeck deck;
	deck += CardDeck::getFullDeck() + CardDeck::getFullDeck() +
		CardDeck::getFullDeck() + CardDeck::getFullDeck() +
		CardDeck::getFullDeck() + CardDeck::getFullDeck();
	random_shuffle(deck._Deck.begin(), deck._Deck.end());
	BlackJack bj(deck);
	ASSERT_THROW(NoPlayersException, bj.getRichest());
	bj.addPlayer(1, BlackJack::CASINO, 100);
	bj.addPlayer(2, BlackJack::CALCULATED, -100);
	try {
		bj.addPlayer(1, BlackJack::CASINO, 0);
	}
	catch (PlayerAlreadytExistException) {}
	bj.addPlayer(3, BlackJack::CALCULATED, 300);
	bj.addPlayer(4, BlackJack::CASINO, 1000);
	bj.addPlayer(5, BlackJack::CALCULATED, 50);
	bj.addPlayer(6, BlackJack::CASINO, 10000);
	bj.addPlayer(7, BlackJack::CALCULATED, 50);
	ASSERT_THROW(PlayerDoesNotExistException, bj.joinGame(8));
	try {
		bj.joinGame({ 1, 2 ,3, 4, 5, 6, 7 , 8 });
	}
	catch (PlayerDoesNotExistException) {}
	bj.joinGame({ 1, 2 ,3, 4, 5, 6, 7});
	bj.joinGame({ 1, 2 ,3, 4, 5, 6, 7 });
	for (int i = 0; i < 1000; i++) {
		try {
			bj.playRound();
		}
		catch (NotEnoughCardsException) {
			random_shuffle(deck._Deck.begin(), deck._Deck.end());
			bj.reloadDeck(deck);
		}
	}
	ASSERT_THROW(PlayerDoesNotExistException, bj.leaveGame({ 1, 2, 3, 4, 5, 6, 7, 8 }));
	bj.leaveGame({ 1, 2, 3, 4, 5, 6, 7});
	bj.getRichest();
	return true;
}

bool blackJackTest() {
	RUN_TEST(blackJackExample);
	CardDeck deck;
	CardDeck& _deck = deck;
	buildDeckDealerhasBJ(_deck);
	buildDeckDealerNoBJ(_deck);
	buildDeckDealerLoses(_deck);
	RUN_TEST(blackJackplayRound);
	RUN_TEST(blackJackShuffle);
	return true;
}
