
#include <algorithm>
#include <fstream>
#include <vector>

#include "Card.h"
#include "Exceptions.h"
#include "MtmTst.h"

using mtm::CardWrongArgsException;
using std::cout;
using std::endl;
using std::ifstream;
using std::vector;

bool cardIllegalCtor() {
	for (int i = 0; i >= -100; --i) {
		for (Card::Suit suit : {Card::Heart, Card::Diamond, Card::Club, Card::Spade}) {
			ASSERT_THROW(CardWrongArgsException, Card(suit, i));
		}
	}
		
	for (int i = 11; i < 100; ++i) {
		for (Card::Suit suit : {Card::Heart, Card::Diamond, Card::Club, Card::Spade}) {
			ASSERT_THROW(CardWrongArgsException, Card(suit, i));
		}
	}

	vector<char> legalVals = { 'A', 'J', 'Q', 'K','a','j','q','k'};
	for (char c = 'A'; c <= 'z'; ++c) {
		if (find(legalVals.begin(), legalVals.end(), c) == legalVals.end()) {
			for (Card::Suit suit : {Card::Heart, Card::Diamond, Card::Club, Card::Spade}) {
				ASSERT_THROW(CardWrongArgsException, Card(suit, c));
			}
		}
	}

	return true;
}

DEFINE_INPUT_TEST(cardIllegalInput)
	
	Card c(Card::Heart, 'A');
	while (!input.eof()) {
	ASSERT_THROW(CardWrongArgsException, input >> c);
	}
	return true;
}

DEFINE_INPUT_TEST(cardCompareInputAndCtor)
	Card card(Card::Heart, 2);
	const Card numberCard(Card::Diamond, 7);
	const Card faceCard(Card::Club, 'Q');
	for (Card::Suit suit : {Card::Heart, Card::Diamond, Card::Club, Card::Spade}) {
		// compare twice for each suit:
		for (int j1 = 0; j1 < 2; j1++) {
			for (int i1 = 1; i1 <= 10; ++i1) {
				input >> card;
				Card tempCard(suit, i1);
				ASSERT_EQUALS(tempCard, card);
				ASSERT_EQUALS(false,tempCard != card);
				ASSERT_EQUALS(false, card == faceCard);
				ASSERT_EQUALS(true, card != faceCard);
			}
			for (char c : {'J', 'Q', 'K', 'A', 'j', 'q', 'k', 'a'}) {
				input >> card;
				Card tempCard(suit, c);
				ASSERT_EQUALS(tempCard, card);
				ASSERT_EQUALS(false, tempCard != card);
				ASSERT_EQUALS(false, card == numberCard);
				ASSERT_EQUALS(true, card != numberCard);
			}
		}
	}

	// compare diefferent representation
	Card card1(Card::Diamond, 2);
	Card card2(Card::Club, 3);
	input >> card1 >> card2;
	ASSERT_EQUALS(card1, card2);
	ASSERT_EQUALS(false, card1 != card2);
	return true;
}

static bool sameLetter(char c1, char c2) {
	if (c1 >= 'A' && c1 <= 'Z') {
		c1 += ('a' - 'A');
	}
	if (c2 >= 'A' && c2 <= 'Z') {
		c2 += ('a' - 'A');
	}
	return (c1 == c2);
}

bool cardCompareAll() {
	for (Card::Suit suit1 : {Card::Heart, Card::Diamond, Card::Club, Card::Spade}) {
		for (int i1 = 1; i1 <= 10; ++i1) {	
			Card firstCard(suit1, i1);
			for (Card::Suit suit2 : {Card::Heart, Card::Diamond, Card::Club, Card::Spade}) {
				for (int i2 = 1; i2 <= 10; ++i2) {
					Card secondCard(suit2, i2);
					if (i1 == i2 && suit1 == suit2) {
						ASSERT_EQUALS(firstCard, secondCard);
						ASSERT_EQUALS(false, firstCard !=secondCard);
					} else {
						ASSERT_EQUALS(false, firstCard == secondCard);
						ASSERT_EQUALS(true, firstCard != secondCard);
					}
				}
				for (char c : {'J', 'Q', 'K', 'A', 'j', 'q', 'k', 'a'}) {
					Card secondCard(suit2, c);
					if (i1 == 1 && (c == 'A' || c == 'a') && suit1 == suit2) {
						ASSERT_EQUALS(firstCard, secondCard);
						ASSERT_EQUALS(false, firstCard != secondCard);
					}
					else {
						ASSERT_EQUALS(false, firstCard == secondCard);
						ASSERT_EQUALS(true, firstCard != secondCard);
					}
				}
			}
		}
		for (char c1 : {'J', 'Q', 'K', 'A', 'j', 'q', 'k', 'a'}) {
			Card firstCard(suit1, c1);
			for (Card::Suit suit2 : {Card::Heart, Card::Diamond, Card::Club, Card::Spade}) {
				for (int i2 = 1; i2 <= 10; ++i2) {
					Card secondCard(suit2, i2);
					if ((c1 == 'A' || c1 == 'a') && i2 == 1 && suit1 == suit2) {
						ASSERT_EQUALS(firstCard, secondCard);
						ASSERT_EQUALS(false, firstCard != secondCard);
					}
					else {
						ASSERT_EQUALS(false, firstCard == secondCard);
						ASSERT_EQUALS(true, firstCard != secondCard);
					}
				}
				for (char c2 : {'J', 'Q', 'K', 'A', 'j', 'q', 'k', 'a'}) {
					Card secondCard(suit2, c2);
					if (sameLetter(c1, c2) && suit1 == suit2) {
						ASSERT_EQUALS(firstCard, secondCard);
						ASSERT_EQUALS(false, firstCard != secondCard);
					} else {
						ASSERT_EQUALS(false, firstCard == secondCard);
						ASSERT_EQUALS(true, firstCard != secondCard);
					}
				}
			}
		}
	}
	return true;
}

DEFINE_INPUT_TEST(cardExample)
	ASSERT_THROW(CardWrongArgsException, Card(Card::Spade, -1));
	Card card1(Card::Club, 2); \
	Card card2(Card::Diamond, 'K'); \
	input >> card2;
	ASSERT_EQUALS(true, card1 == card2);
	ASSERT_EQUALS(false, card1 != card2);
	return true;
}

bool cardTest(int testNum) {
	if (testNum == 0) {
		RUN_TEST(cardExample);
		RUN_TEST(cardIllegalCtor);
		RUN_TEST(cardIllegalInput);
		RUN_TEST(cardCompareInputAndCtor);
		RUN_TEST(cardCompareAll);
	} else {
		switch (testNum) {
		case 1:
			RUN_TEST(cardExample);
			break;
		case 2:
			RUN_TEST(cardIllegalCtor);
			break;
		case 3:
			RUN_TEST(cardIllegalInput);
			break;
		case 4:
			RUN_TEST(cardCompareInputAndCtor);
			break;
		case 5:
			RUN_TEST(cardCompareAll);
			break;
		}
	}

	return true;
}
