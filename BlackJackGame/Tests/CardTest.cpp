
#include "Card.h"
#include "Exceptions.h"
#include "MtmTst.h"

using mtm::CardWrongArgsException;
using std::stringstream;

DEFINE_INPUT_TEST(cardExample)
	ASSERT_THROW(CardWrongArgsException, Card(Card::Spade, -1));
	Card card1(Card::Club, 2); \
	Card card2(Card::Diamond, 'K'); \
	input >> card2;
	ASSERT_EQUALS(true, card1 == card2);
	ASSERT_EQUALS(false, card1 != card2);

	return true;
}

DEFINE_INPUT_TEST(ctorTest);
	ASSERT_NO_THROW(Card());
	ASSERT_NO_THROW(Card(Card::Club, 2));
	Card card1(Card::Club, 2); \
	ASSERT_NO_THROW(Card(Card::Diamond, 'K'));
	Card card2(Card::Diamond, 'K'); \
	ASSERT_NO_THROW(Card(Card::Heart, 10));
	Card card3(Card::Heart, 10); \
	ASSERT_NO_THROW(Card(Card::Diamond, 1));
	Card card4(Card::Diamond, 1); \
	ASSERT_NO_THROW(Card(Card::Club, 'J'));
	Card card5(Card::Club, 'J'); \
	ASSERT_NO_THROW(Card(Card::Spade, 'Q'));
	Card card6(Card::Spade, 'Q'); \
	ASSERT_NO_THROW(Card(Card::Diamond, 'A'));
	Card card7(Card::Diamond, 'A'); \
	ASSERT_NO_THROW(Card(Card::Spade, 'q'));
	Card card8(Card::Spade, 'q'); \

	return true;
}

DEFINE_INPUT_TEST(inputTest);
	Card card[17];
	for (int i = 0; i < 9; i++) {
		ASSERT_NO_THROW(input >> card[i]);
	}
	for (int i = 8; i < 16; i++) {
		ASSERT_THROW(CardWrongArgsException, input >> card[i]);
	}

	return true;
}

DEFINE_INPUT_TEST(EquationTest);
	Card card[22];
	for (int i = 0; i < 22; i++) {
		ASSERT_NO_THROW(input >> card[i]);
	}
	for (int i = 0; i < 5; i++) {
		ASSERT_EQUALS(true, card[i] == card[i+11]);
		ASSERT_EQUALS(false, card[i] != card[i + 11]);
	}
	for (int i = 5; i <11; i++) {
		ASSERT_EQUALS(false, card[i] == card[i + 11]);
		ASSERT_EQUALS(true, card[i] != card[i + 11]);
	}

	return true;
}

DEFINE_INPUT_TEST(ctorVsInputTest);
	Card card[16];
	for (int i = 0; i < 8; i++) {
		ASSERT_NO_THROW(input >> card[i]);
	}
	card[8] = Card(Card::Club, 2);
	card[9] = Card(Card::Diamond, 'K');
	card[10] = Card(Card::Heart, 10);
	card[11] = Card(Card::Diamond, 1);
	card[12] = Card(Card::Club, 'J');
	card[13] = Card(Card::Spade, 'Q');
	card[14] = Card(Card::Diamond, 'A');
	card[15] = Card(Card::Spade, 'q');
	int i = 0;
	while(i < 8) {
		ASSERT_EQUALS(true, card[i] == card[i + 8]);
		i++;
	}

	return true;
}

DEFINE_INPUT_TEST(AsiggmentTest);
	Card empty_card;
	Card assigm_card;
	input >> assigm_card;
	empty_card = assigm_card;
	Card same_as_assigm_card;
	input >> same_as_assigm_card;
	ASSERT_EQUALS(true, empty_card == same_as_assigm_card);

	Card diff_card;
	input >> diff_card;
	Card new_card;
	input >> new_card;
	diff_card = new_card;
	Card same_as_new;
	input >> same_as_new;
	ASSERT_EQUALS(true, diff_card == same_as_new);

	Card first;
	input >> first;
	input >> diff_card;
	first = diff_card;
	Card same_as_first;
	input >> same_as_first;
	ASSERT_EQUALS(true, first != same_as_first);

	return true;
}

DEFINE_INPUT_TEST(IOTest)
	Card icard;
	input >> icard;
	Card king_heart(Card::Heart, 'K');
	stringstream buffer;
	buffer << icard;
	string str_icard = buffer.str();
	buffer.str(string());
	buffer << king_heart;
	string str_ocard = buffer.str();
	ASSERT_EQUALS(true, str_icard == str_ocard);

return true;
}

bool cardTest() {
	RUN_TEST(cardExample);
	RUN_TEST(ctorTest);
	RUN_TEST(inputTest);
	RUN_TEST(EquationTest);
	RUN_TEST(ctorVsInputTest);
	RUN_TEST(AsiggmentTest);
	RUN_TEST(IOTest);
	return true;
}
