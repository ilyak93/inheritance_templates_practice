#include "CardDeck.h"
#include "Exceptions.h"
#include "MtmTst.h"

using mtm::CardDeckIsEmptyException;
using std::stringstream;


DEFINE_INPUT_TEST(cardDeckExample)
CardDeck emptyDeck;
CardDeck fullDeck = CardDeck::getFullDeck();
Card kingSpade = fullDeck.draw();
ASSERT_EQUALS(kingSpade, Card(Card::Spade, 'K'));
ASSERT_EQUALS(Card(Card::Spade, 'Q'), fullDeck.top());
ASSERT_THROW(CardDeckIsEmptyException, emptyDeck.top());
unsigned expecetdSize = 51;
ASSERT_EQUALS(expecetdSize, fullDeck.size());
ASSERT_EQUALS(true, emptyDeck.isEmpty());
CardDeck singleCardDeck = kingSpade;
singleCardDeck.clear();
Card twoDiamond(Card::Diamond, 2);
singleCardDeck = twoDiamond;
unsigned expectedValue = 2;
ASSERT_EQUALS(expectedValue, singleCardDeck.value());
singleCardDeck += kingSpade;
ASSERT_EQUALS(kingSpade, singleCardDeck.top());
CardDeck newDeck;
input >> newDeck;
ASSERT_EQUALS(Card(Card::Club, 4), newDeck.top());
std::cout << newDeck * 2 << std::endl;
CardDeck first;
CardDeck second;
input >> first;
input >> second;
std::cout << first + second << std::endl;

CardDeck smallDeck = Card(Card::Diamond, 7) + Card(Card::Diamond, 10);
ASSERT_EQUALS(true, smallDeck < fullDeck);
ASSERT_EQUALS(true, smallDeck <= fullDeck);
ASSERT_EQUALS(true, fullDeck > smallDeck);
ASSERT_EQUALS(true, fullDeck >= smallDeck);
ASSERT_EQUALS(true, fullDeck != smallDeck);
ASSERT_EQUALS(false, fullDeck == smallDeck);

return true;
}

DEFINE_INPUT_TEST(cardDeckCtorTest)
CardDeck empty_deck;
ASSERT_EQUALS(true, empty_deck.isEmpty());
ASSERT_EQUALS(0, empty_deck.value());
ASSERT_EQUALS(0, empty_deck.size());
Card king_heart(Card::Heart, 'K');
CardDeck single_card_deck = king_heart;
ASSERT_EQUALS(false, single_card_deck.isEmpty());
ASSERT_EQUALS(10, single_card_deck.value());
ASSERT_EQUALS(1, single_card_deck.size());
CardDeck single_card_deck2(Card(Card::Spade, 5));
ASSERT_EQUALS(false, single_card_deck2.isEmpty());
ASSERT_EQUALS(5, single_card_deck2.value());

return true;
}

DEFINE_INPUT_TEST(cardDeckDrawAndTopTest)
CardDeck deck = Card(Card::Heart, 'K') + Card(Card::Spade, 'A');
ASSERT_EQUALS(11, deck.value());
ASSERT_EQUALS(false, deck.isEmpty());
ASSERT_EQUALS(2, deck.size());
CardDeck empty_deck;
Card king_heart(Card::Heart, 'K');
Card ace_spade(Card::Spade, 'A');
ASSERT_NO_THROW(deck.top());
ASSERT_EQUALS(true, deck.top() == ace_spade);
ASSERT_THROW(CardDeckIsEmptyException, empty_deck.top());
Card drawn;
ASSERT_NO_THROW(drawn = deck.draw());
ASSERT_EQUALS(true, drawn == ace_spade);
ASSERT_EQUALS(false, deck.top() == ace_spade);
ASSERT_NO_THROW(drawn = deck.draw());
ASSERT_EQUALS(true, drawn == king_heart);
ASSERT_THROW(CardDeckIsEmptyException, deck.top());
ASSERT_THROW(CardDeckIsEmptyException, deck.draw());

return true;
}

DEFINE_INPUT_TEST(cardDeckGetFullDeckTest)
CardDeck deck = CardDeck::getFullDeck();
ASSERT_EQUALS(52, deck.size());
ASSERT_EQUALS(350, deck.value());
for (int suit = 3; suit >= 0; suit--) {
	Card::Suit cur_suit = (Card::Suit)suit;
	Card cur_card(cur_suit, 'K');
	ASSERT_EQUALS(true, deck.top() == cur_card);
	Card drawn;
	ASSERT_NO_THROW(drawn = deck.draw());
	cur_card = Card(cur_suit, 'Q');
	ASSERT_EQUALS(true, deck.top() == cur_card);
	ASSERT_NO_THROW(drawn = deck.draw());
	cur_card = Card(cur_suit, 'J');
	ASSERT_EQUALS(true, deck.top() == cur_card);
	ASSERT_NO_THROW(drawn = deck.draw());
	ASSERT_EQUALS(unsigned(350 - 55 * (3 - suit) - (4 - suit) * 3 * 10), deck.value());
	for (int i = 10; i >= 2; i--) {
		cur_card = Card(cur_suit, i);
		ASSERT_EQUALS(true, deck.top() == cur_card);
		ASSERT_NO_THROW(drawn = deck.draw());
	}
	cur_card = Card(cur_suit, 'A');
	ASSERT_EQUALS(true, deck.top() == cur_card);
	ASSERT_NO_THROW(drawn = deck.draw());
}
ASSERT_EQUALS(0, deck.value());
ASSERT_THROW(CardDeckIsEmptyException, deck.top());
ASSERT_THROW(CardDeckIsEmptyException, deck.draw());

return true;
}

DEFINE_INPUT_TEST(cardDeckClearTest)
CardDeck deck = CardDeck::getFullDeck();
CardDeck empty;
ASSERT_EQUALS(52, deck.size());
ASSERT_EQUALS(350, deck.value());
deck.clear();
ASSERT_EQUALS(0, deck.value());
ASSERT_EQUALS(0, deck.size());
ASSERT_EQUALS(true, deck.isEmpty());
empty.clear();

return true;
}

DEFINE_INPUT_TEST(cardDeckArithmBaseTest)
CardDeck empty;
CardDeck empty1;
CardDeck empty2;
CardDeck empty3;
Card ten_spade(Card::Spade, 10);
Card queen_heart(Card::Heart, 'Q');
Card five_club(Card::Club, 5);
CardDeck full1 = CardDeck::getFullDeck();
CardDeck full2 = CardDeck::getFullDeck();
CardDeck full3 = CardDeck::getFullDeck();

empty1 += (empty + full1);
ASSERT_EQUALS(52, empty1.size());
ASSERT_EQUALS(350, empty1.value());
ASSERT_EQUALS(true, empty1.top() == Card(Card::Spade, 'K'));

empty2 += (ten_spade + queen_heart);
ASSERT_EQUALS(2, empty2.size());
ASSERT_EQUALS(20, empty2.value());
ASSERT_EQUALS(true, empty2.top() == Card(Card::Heart, 'q'));
Card drawn;
ASSERT_NO_THROW(drawn = empty2.draw());
ASSERT_EQUALS(true, drawn == Card(Card::Heart, 'q'));
ASSERT_EQUALS(true, empty2.top() == Card(Card::Spade, 10));
ASSERT_NO_THROW(drawn = empty2.draw());
ASSERT_EQUALS(true, drawn == Card(Card::Spade, 10));
ASSERT_EQUALS(true, empty2.isEmpty());
empty3 += (full1 + five_club);
ASSERT_EQUALS(53, empty3.size());
ASSERT_EQUALS(355, empty3.value());
ASSERT_EQUALS(true, empty3.top() == Card(Card::Club, 5));
empty3.draw();
ASSERT_EQUALS(true, empty3.top() == Card(Card::Spade, 'K'));
ASSERT_EQUALS(52, empty3.size());
ASSERT_EQUALS(350, empty3.value());
full1 += (empty + five_club);
ASSERT_EQUALS(53, full1.size());
ASSERT_EQUALS(355, full1.value());
ASSERT_EQUALS(true, full1.top() == Card(Card::Club, 5));
full1.draw();
ASSERT_EQUALS(true, full1.top() == Card(Card::Spade, 'K'));
ASSERT_EQUALS(52, full1.size());
ASSERT_EQUALS(350, full1.value());
full2 += (queen_heart + empty);
ASSERT_EQUALS(53, full2.size());
ASSERT_EQUALS(360, full2.value());
ASSERT_EQUALS(true, full2.top() == Card(Card::Heart, 'q'));
full2.draw();
ASSERT_EQUALS(true, full2.top() == Card(Card::Spade, 'K'));
ASSERT_EQUALS(52, full2.size());
ASSERT_EQUALS(350, full2.value());
full3 += (full1 + empty);
ASSERT_EQUALS(104, full3.size());
ASSERT_EQUALS(690, full3.value());
ASSERT_EQUALS(true, full3.top() == Card(Card::Spade, 'k'));
full3.draw();
ASSERT_EQUALS(true, full3.top() == Card(Card::Spade, 'q'));
ASSERT_EQUALS(103, full3.size());
ASSERT_EQUALS(680, full3.value());

return true;
}


DEFINE_INPUT_TEST(cardDeckArithmAdvanceTest)
	Card nine_diam(Card::Diamond, 9);
	Card ace_heart(Card::Heart, 1);
	Card two_spade(Card::Spade, 2);
	CardDeck empty1, empty2;
	CardDeck full = CardDeck::getFullDeck();
	CardDeck full1 = CardDeck::getFullDeck();
	CardDeck full4 = CardDeck::getFullDeck();
	full4 += full1 + nine_diam;
	ASSERT_EQUALS(105, full4.size());
	ASSERT_EQUALS(699, full4.value());
	ASSERT_EQUALS(true, full4.top() == Card(Card::Diamond, 9));
	full4.draw();
	ASSERT_EQUALS(true, full4.top() == Card(Card::Spade, 'K'));
	ASSERT_EQUALS(104, full4.size());
	ASSERT_EQUALS(690, full4.value());
	CardDeck full5 = CardDeck::getFullDeck();
	full5 += empty1 + empty2;
	ASSERT_EQUALS(true, full5 == full1);
	full4 = full5 + full1;
	ASSERT_EQUALS(true, full4.top() == Card(Card::Spade, 'K'));
	ASSERT_EQUALS(104, full4.size());
	ASSERT_EQUALS(690, full4.value());
	full += full;
	ASSERT_EQUALS(104, full.size());
	ASSERT_EQUALS(690, full.value());
	ASSERT_EQUALS(true, full.top() == Card(Card::Spade, 'k'));
	(full += ace_heart) += full1;
	ASSERT_EQUALS(157, full.size());
	ASSERT_EQUALS(1041, full.value());
	ASSERT_EQUALS(true, full.top() == Card(Card::Spade, 'k'));
	full += full += full;
	ASSERT_EQUALS(4*157, full.size());
	ASSERT_EQUALS(4 * 1041 - 30, full.value()); ///30 = 3*11(high ace value) - 3*1(low ace value)
	ASSERT_EQUALS(true, full.top() == Card(Card::Spade, 'k'));
	CardDeck full2 = CardDeck::getFullDeck();
	CardDeck full3 = CardDeck::getFullDeck();
	full4 = CardDeck::getFullDeck();
	ASSERT_EQUALS(true, (full2+=full2+=full2+=full2) == 8*full3);
	ASSERT_EQUALS(true, (full3 + full3 + full3 + full3) == full3 * 4);

	ASSERT_EQUALS(true, (full3 * 4 == 4 * full3));
	ASSERT_EQUALS(true, (full3 * 5 + 2 * full3) == full3 * 7);
	ASSERT_EQUALS(true, (full3 + 2 * full4) == full3 * 3);
	ASSERT_EQUALS(true, (full3 + 2 * full4) == (2 * full4 + full3 ));
	ASSERT_EQUALS(true, (1*full3) == full3);
	CardDeck empty;
	ASSERT_EQUALS(true, (0 * full3) == empty);

	return true;
}

DEFINE_INPUT_TEST(cardDeckEquationsTest)
	CardDeck full = CardDeck::getFullDeck();
	CardDeck full1 = CardDeck::getFullDeck();
	CardDeck full2 = CardDeck::getFullDeck();
	ASSERT_EQUALS(true, full1 == full2);
	ASSERT_EQUALS(false, full1 != full2);
	ASSERT_EQUALS(true, full1 <= full2);
	ASSERT_EQUALS(true, full1 >= full2);
	full2.draw();
	ASSERT_EQUALS(true, full1 != full2);
	ASSERT_EQUALS(false, full1 == full2);
	ASSERT_EQUALS(true, full1 >= full2);
	ASSERT_EQUALS(false, full1 <= full2);
	ASSERT_EQUALS(true, full1 > full2);
	ASSERT_EQUALS(false, full1 < full2);
	full1.draw();
	Card nine_diam(Card::Diamond, 9);
	Card ace_heart(Card::Heart, 1);
	CardDeck empty1, empty2;
	ASSERT_EQUALS(false, full1 + nine_diam < full2 + ace_heart);
	ASSERT_EQUALS(false, full1 + nine_diam <= full2 + ace_heart);
	ASSERT_EQUALS(false, full1 + nine_diam > full2 + ace_heart);
	ASSERT_EQUALS(false, full1 + nine_diam >= full2 + ace_heart);
	ASSERT_EQUALS(false, full1 + nine_diam == full2 + ace_heart);
	ASSERT_EQUALS(true, full1 + nine_diam != full2 + ace_heart);

	ASSERT_EQUALS(true, empty1 < ace_heart);
	ASSERT_EQUALS(true, empty1 <= ace_heart);
	ASSERT_EQUALS(true, empty1 == empty2);
	ASSERT_EQUALS(true, empty1 <= empty2);
	ASSERT_EQUALS(true, empty1 >= empty2);

	ASSERT_EQUALS(false, nine_diam < ace_heart);
	ASSERT_EQUALS(true, Card(Card::Heart, 1) <= Card(Card::Heart, 1));
	ASSERT_EQUALS(true, nine_diam <= nine_diam);
	ASSERT_EQUALS(false, nine_diam <= ace_heart);
	ASSERT_EQUALS(false, nine_diam > ace_heart);
	ASSERT_EQUALS(false, nine_diam >= ace_heart);
	ASSERT_EQUALS(false, nine_diam == ace_heart);
	ASSERT_EQUALS(true, nine_diam != ace_heart);
	ASSERT_EQUALS(true, (nine_diam + ace_heart).top() == Card(Card::Heart, 1));

	return true;
}

DEFINE_INPUT_TEST(cardDeckIOTest)
	CardDeck ideck;
	input >> ideck;
	CardDeck full = CardDeck::getFullDeck();
	stringstream buffer;
	buffer << ideck;
	string str_ideck = buffer.str();
	buffer.str(string());
	buffer << full;
	string str_odeck = buffer.str();
	ASSERT_EQUALS(true, str_ideck == str_odeck);

	return true;
}

bool cardDeckTest() {
	RUN_TEST(cardDeckExample);
	RUN_TEST(cardDeckCtorTest);
	RUN_TEST(cardDeckDrawAndTopTest);
	RUN_TEST(cardDeckGetFullDeckTest);
	RUN_TEST(cardDeckClearTest);
	RUN_TEST(cardDeckArithmBaseTest);
	RUN_TEST(cardDeckArithmAdvanceTest);
	RUN_TEST(cardDeckEquationsTest);
	RUN_TEST(cardDeckIOTest);


	return true;
}
