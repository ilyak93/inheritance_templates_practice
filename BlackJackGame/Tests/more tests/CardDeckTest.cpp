#include "CardDeck.h"
#include "CardDeckInputTest.h"
#include "Exceptions.h"
#include "MtmTst.h"

#include <vector>

using mtm::CardWrongArgsException;
using mtm::CardDeckIsEmptyException;
using std::endl;
using std::vector;

static bool checkAllComparisons(CardDeck first, CardDeck second, bool hasLessCards, bool hasSameCards) {
	if (hasLessCards) {
		if (!(first < second)) return false;
		if ((second < first)) return false;

		if (!(first <= second)) return false;
		if ((second <= first)) return false;

		if ((first > second)) return false;
		if (!(second > first)) return false;

		if ((first >= second)) return false;
		if (!(second >= first)) return false;

		if (!(first != second)) return false;
		if (!(second != first)) return false;

		if ((first == second)) return false;
		if ((second == first)) return false;
	}
	if (hasSameCards) {
		if ((first < second)) return false;
		if ((second < first)) return false;

		if (!(first <= second)) return false;
		if (!(second <= first)) return false;

		if ((first > second)) return false;
		if ((second > first)) return false;

		if (!(first >= second)) return false;
		if (!(second >= first)) return false;

		if (compareDecks(first, second)) {
			if ((first != second)) return false;
			if ((second != first)) return false;

			if (!(first == second)) return false;
			if (!(second == first)) return false;
		} else {
			if (!(first != second)) return false;
			if (!(second != first)) return false;

			if ((first == second)) return false;
			if ((second == first)) return false;
		}
	}

	return true;
}

bool cardDeckFullTest() {
	CardDeck deck;
	for (Card::Suit suit : {Card::Heart, Card::Diamond, Card::Club, Card::Spade}) {
		for (int i = 1; i <= 10; ++i) {
			deck += Card(suit, i);
		}
		for (char c : {'j','q','k'}) {
			deck += Card(suit, c);
		}
	}

	compareDecks(deck, CardDeck::getFullDeck());

	CardDeck::getFullDeck().draw();
	ASSERT_EQUALS(Card(Card::Spade, 'K'), CardDeck::getFullDeck().top());
	
	return true;
}

DEFINE_INPUT_TEST(cardDeckInput)

#ifdef DECK_INPUT

	CardDeck deck;
	CardDeck temp;
	// Test 1
	input >> deck;
	temp.clear();
	ASSERT_EQUALS(true, compareDecks(deck, temp));
	// Test 2
	ASSERT_THROW(CardWrongArgsException, input >> deck);
	temp.clear();
	ASSERT_EQUALS(true, compareDecks(deck, temp));
	// Test 3
	input >> deck;
	temp.clear();
	temp += Card(Card::Heart, 'J');
	ASSERT_EQUALS(true, compareDecks(deck, temp));
	// Test 4
	ASSERT_THROW(CardWrongArgsException, input >> deck);
	temp.clear();
	ASSERT_EQUALS(true, compareDecks(deck, temp));
	// Test 5
	ASSERT_THROW(CardWrongArgsException, input >> deck);
	temp.clear();
	temp += Card(Card::Diamond, 'k');
	ASSERT_EQUALS(true, compareDecks(deck, temp));

	ASSERT_EQUALS(true, inputTest6(input, deck, temp));
	ASSERT_EQUALS(true, inputTest7(input, deck, temp));
	ASSERT_EQUALS(true, inputTest8(input, deck, temp));
	ASSERT_EQUALS(true, inputTest9(input, deck, temp));
	ASSERT_EQUALS(true, inputTest10(input, deck, temp));
	ASSERT_EQUALS(true, inputTest11(input, deck, temp));
	ASSERT_EQUALS(true, inputTest12(input, deck, temp));
	ASSERT_EQUALS(true, inputTest13(input, deck, temp));
	ASSERT_EQUALS(true, inputTest14(input, deck, temp));
	ASSERT_EQUALS(true, inputTest15(input, deck, temp));
	ASSERT_EQUALS(true, inputTest16(input, deck, temp));
	ASSERT_EQUALS(true, inputTest17(input, deck, temp));
	ASSERT_EQUALS(true, inputTest18(input, deck, temp));
	ASSERT_EQUALS(true, inputTest19(input, deck, temp));
	ASSERT_EQUALS(true, inputTest20(input, deck, temp));
	ASSERT_EQUALS(true, inputTest21(input, deck, temp));
	ASSERT_EQUALS(true, inputTest22(input, deck, temp));
	ASSERT_EQUALS(true, inputTest23(input, deck, temp));
	ASSERT_EQUALS(true, inputTest24(input, deck, temp));
	ASSERT_EQUALS(true, inputTest25(input, deck, temp));
	ASSERT_EQUALS(true, inputTest26(input, deck, temp));
	ASSERT_EQUALS(true, inputTest27(input, deck, temp));
	ASSERT_EQUALS(true, inputTest28(input, deck, temp));
	ASSERT_EQUALS(true, inputTest29(input, deck, temp));
	ASSERT_EQUALS(true, inputTest30(input, deck, temp));
	ASSERT_EQUALS(true, inputTest31(input, deck, temp));
	ASSERT_EQUALS(true, inputTest32(input, deck, temp));
	ASSERT_EQUALS(true, inputTest33(input, deck, temp));
	ASSERT_EQUALS(true, inputTest34(input, deck, temp));
	ASSERT_EQUALS(true, inputTest35(input, deck, temp));
	ASSERT_EQUALS(true, inputTest36(input, deck, temp));
	ASSERT_EQUALS(true, inputTest37(input, deck, temp));
	ASSERT_EQUALS(true, inputTest38(input, deck, temp));
	ASSERT_EQUALS(true, inputTest39(input, deck, temp));
	ASSERT_EQUALS(true, inputTest40(input, deck, temp));
	ASSERT_EQUALS(true, inputTest41(input, deck, temp));
	ASSERT_EQUALS(true, inputTest42(input, deck, temp));
	ASSERT_EQUALS(true, inputTest43(input, deck, temp));
	ASSERT_EQUALS(true, inputTest44(input, deck, temp));
	ASSERT_EQUALS(true, inputTest45(input, deck, temp));
	ASSERT_EQUALS(true, inputTest46(input, deck, temp));
	ASSERT_EQUALS(true, inputTest47(input, deck, temp));
	ASSERT_EQUALS(true, inputTest48(input, deck, temp));
	ASSERT_EQUALS(true, inputTest49(input, deck, temp));
	ASSERT_EQUALS(true, inputTest50(input, deck, temp));
	ASSERT_EQUALS(true, inputTest51(input, deck, temp));
	ASSERT_EQUALS(true, inputTest52(input, deck, temp));
	ASSERT_EQUALS(true, inputTest53(input, deck, temp));
	ASSERT_EQUALS(true, inputTest54(input, deck, temp));
	ASSERT_EQUALS(true, inputTest55(input, deck, temp));
	ASSERT_EQUALS(true, inputTest56(input, deck, temp));
	ASSERT_EQUALS(true, inputTest57(input, deck, temp));
	ASSERT_EQUALS(true, inputTest58(input, deck, temp));
	ASSERT_EQUALS(true, inputTest59(input, deck, temp));
	ASSERT_EQUALS(true, inputTest60(input, deck, temp));
	ASSERT_EQUALS(true, inputTest61(input, deck, temp));
	ASSERT_EQUALS(true, inputTest62(input, deck, temp));
	ASSERT_EQUALS(true, inputTest63(input, deck, temp));
	ASSERT_EQUALS(true, inputTest64(input, deck, temp));
	ASSERT_EQUALS(true, inputTest65(input, deck, temp));
	ASSERT_EQUALS(true, inputTest66(input, deck, temp));
	ASSERT_EQUALS(true, inputTest67(input, deck, temp));
	ASSERT_EQUALS(true, inputTest68(input, deck, temp));
	ASSERT_EQUALS(true, inputTest69(input, deck, temp));
	ASSERT_EQUALS(true, inputTest70(input, deck, temp));
	ASSERT_EQUALS(true, inputTest71(input, deck, temp));
	ASSERT_EQUALS(true, inputTest72(input, deck, temp));
	ASSERT_EQUALS(true, inputTest73(input, deck, temp));
	ASSERT_EQUALS(true, inputTest74(input, deck, temp));
	ASSERT_EQUALS(true, inputTest75(input, deck, temp));
	ASSERT_EQUALS(true, inputTest76(input, deck, temp));
	ASSERT_EQUALS(true, inputTest77(input, deck, temp));
	ASSERT_EQUALS(true, inputTest78(input, deck, temp));
	ASSERT_EQUALS(true, inputTest79(input, deck, temp));
	ASSERT_EQUALS(true, inputTest80(input, deck, temp));
	ASSERT_EQUALS(true, inputTest81(input, deck, temp));
	ASSERT_EQUALS(true, inputTest82(input, deck, temp));
	ASSERT_EQUALS(true, inputTest83(input, deck, temp));
	ASSERT_EQUALS(true, inputTest84(input, deck, temp));
	ASSERT_EQUALS(true, inputTest85(input, deck, temp));
	ASSERT_EQUALS(true, inputTest86(input, deck, temp));
	ASSERT_EQUALS(true, inputTest87(input, deck, temp));
	ASSERT_EQUALS(true, inputTest88(input, deck, temp));
	ASSERT_EQUALS(true, inputTest89(input, deck, temp));
	ASSERT_EQUALS(true, inputTest90(input, deck, temp));
	ASSERT_EQUALS(true, inputTest91(input, deck, temp));
	ASSERT_EQUALS(true, inputTest92(input, deck, temp));
	ASSERT_EQUALS(true, inputTest93(input, deck, temp));
	ASSERT_EQUALS(true, inputTest94(input, deck, temp));
	ASSERT_EQUALS(true, inputTest95(input, deck, temp));
	ASSERT_EQUALS(true, inputTest96(input, deck, temp));
	ASSERT_EQUALS(true, inputTest97(input, deck, temp));
	ASSERT_EQUALS(true, inputTest98(input, deck, temp));
	ASSERT_EQUALS(true, inputTest99(input, deck, temp));
	ASSERT_EQUALS(true, inputTest100(input, deck, temp));
	ASSERT_EQUALS(true, inputTest101(input, deck, temp));
	ASSERT_EQUALS(true, inputTest102(input, deck, temp));
	ASSERT_EQUALS(true, inputTest103(input, deck, temp));
	ASSERT_EQUALS(true, inputTest104(input, deck, temp));
	ASSERT_EQUALS(true, inputTest105(input, deck, temp));
	ASSERT_EQUALS(true, inputTest106(input, deck, temp));
	ASSERT_EQUALS(true, inputTest107(input, deck, temp));
	ASSERT_EQUALS(true, inputTest108(input, deck, temp));
	ASSERT_EQUALS(true, inputTest109(input, deck, temp));
	ASSERT_EQUALS(true, inputTest110(input, deck, temp));
	ASSERT_EQUALS(true, inputTest111(input, deck, temp));
	ASSERT_EQUALS(true, inputTest112(input, deck, temp));
	ASSERT_EQUALS(true, inputTest113(input, deck, temp));
	ASSERT_EQUALS(true, inputTest114(input, deck, temp));
	ASSERT_EQUALS(true, inputTest115(input, deck, temp));
	ASSERT_EQUALS(true, inputTest116(input, deck, temp));
	ASSERT_EQUALS(true, inputTest117(input, deck, temp));
	ASSERT_EQUALS(true, inputTest118(input, deck, temp));
	ASSERT_EQUALS(true, inputTest119(input, deck, temp));
	ASSERT_EQUALS(true, inputTest120(input, deck, temp));
	ASSERT_EQUALS(true, inputTest121(input, deck, temp));
	ASSERT_EQUALS(true, inputTest122(input, deck, temp));
	ASSERT_EQUALS(true, inputTest123(input, deck, temp));
	ASSERT_EQUALS(true, inputTest124(input, deck, temp));
	ASSERT_EQUALS(true, inputTest125(input, deck, temp));
	ASSERT_EQUALS(true, inputTest126(input, deck, temp));
	ASSERT_EQUALS(true, inputTest127(input, deck, temp));
	ASSERT_EQUALS(true, inputTest128(input, deck, temp));
	ASSERT_EQUALS(true, inputTest129(input, deck, temp));
	ASSERT_EQUALS(true, inputTest130(input, deck, temp));
	ASSERT_EQUALS(true, inputTest131(input, deck, temp));
	ASSERT_EQUALS(true, inputTest132(input, deck, temp));
	ASSERT_EQUALS(true, inputTest133(input, deck, temp));
	ASSERT_EQUALS(true, inputTest134(input, deck, temp));
	ASSERT_EQUALS(true, inputTest135(input, deck, temp));
	ASSERT_EQUALS(true, inputTest136(input, deck, temp));
	ASSERT_EQUALS(true, inputTest137(input, deck, temp));
	ASSERT_EQUALS(true, inputTest138(input, deck, temp));
	ASSERT_EQUALS(true, inputTest139(input, deck, temp));
	ASSERT_EQUALS(true, inputTest140(input, deck, temp));
	ASSERT_EQUALS(true, inputTest141(input, deck, temp));
	ASSERT_EQUALS(true, inputTest142(input, deck, temp));
	ASSERT_EQUALS(true, inputTest143(input, deck, temp));
	ASSERT_EQUALS(true, inputTest144(input, deck, temp));
	ASSERT_EQUALS(true, inputTest145(input, deck, temp));
	ASSERT_EQUALS(true, inputTest146(input, deck, temp));
	ASSERT_EQUALS(true, inputTest147(input, deck, temp));
	ASSERT_EQUALS(true, inputTest148(input, deck, temp));
	ASSERT_EQUALS(true, inputTest149(input, deck, temp));
	ASSERT_EQUALS(true, inputTest150(input, deck, temp));
	ASSERT_EQUALS(true, inputTest151(input, deck, temp));
	ASSERT_EQUALS(true, inputTest152(input, deck, temp));
	ASSERT_EQUALS(true, inputTest153(input, deck, temp));
	ASSERT_EQUALS(true, inputTest154(input, deck, temp));
	ASSERT_EQUALS(true, inputTest155(input, deck, temp));
	ASSERT_EQUALS(true, inputTest156(input, deck, temp));
	ASSERT_EQUALS(true, inputTest157(input, deck, temp));
	ASSERT_EQUALS(true, inputTest158(input, deck, temp));
	ASSERT_EQUALS(true, inputTest159(input, deck, temp));
	ASSERT_EQUALS(true, inputTest160(input, deck, temp));
	ASSERT_EQUALS(true, inputTest161(input, deck, temp));
	ASSERT_EQUALS(true, inputTest162(input, deck, temp));
	ASSERT_EQUALS(true, inputTest163(input, deck, temp));
	ASSERT_EQUALS(true, inputTest164(input, deck, temp));
	ASSERT_EQUALS(true, inputTest165(input, deck, temp));
	ASSERT_EQUALS(true, inputTest166(input, deck, temp));
	ASSERT_EQUALS(true, inputTest167(input, deck, temp));
	ASSERT_EQUALS(true, inputTest168(input, deck, temp));
	ASSERT_EQUALS(true, inputTest169(input, deck, temp));
	ASSERT_EQUALS(true, inputTest170(input, deck, temp));
	ASSERT_EQUALS(true, inputTest171(input, deck, temp));
	ASSERT_EQUALS(true, inputTest172(input, deck, temp));
	ASSERT_EQUALS(true, inputTest173(input, deck, temp));
	ASSERT_EQUALS(true, inputTest174(input, deck, temp));
	ASSERT_EQUALS(true, inputTest175(input, deck, temp));
	ASSERT_EQUALS(true, inputTest176(input, deck, temp));
	ASSERT_EQUALS(true, inputTest177(input, deck, temp));
	ASSERT_EQUALS(true, inputTest178(input, deck, temp));
	ASSERT_EQUALS(true, inputTest179(input, deck, temp));
	ASSERT_EQUALS(true, inputTest180(input, deck, temp));
	ASSERT_EQUALS(true, inputTest181(input, deck, temp));
	ASSERT_EQUALS(true, inputTest182(input, deck, temp));
	ASSERT_EQUALS(true, inputTest183(input, deck, temp));
	ASSERT_EQUALS(true, inputTest184(input, deck, temp));
	ASSERT_EQUALS(true, inputTest185(input, deck, temp));
	ASSERT_EQUALS(true, inputTest186(input, deck, temp));
	ASSERT_EQUALS(true, inputTest187(input, deck, temp));
	ASSERT_EQUALS(true, inputTest188(input, deck, temp));
	ASSERT_EQUALS(true, inputTest189(input, deck, temp));
	ASSERT_EQUALS(true, inputTest190(input, deck, temp));
	ASSERT_EQUALS(true, inputTest191(input, deck, temp));
	ASSERT_EQUALS(true, inputTest192(input, deck, temp));
	ASSERT_EQUALS(true, inputTest193(input, deck, temp));
	ASSERT_EQUALS(true, inputTest194(input, deck, temp));
	ASSERT_EQUALS(true, inputTest195(input, deck, temp));
	ASSERT_EQUALS(true, inputTest196(input, deck, temp));
	ASSERT_EQUALS(true, inputTest197(input, deck, temp));
	ASSERT_EQUALS(true, inputTest198(input, deck, temp));
	ASSERT_EQUALS(true, inputTest199(input, deck, temp));
	ASSERT_EQUALS(true, inputTest200(input, deck, temp));
	ASSERT_EQUALS(true, inputTest201(input, deck, temp));
	ASSERT_EQUALS(true, inputTest202(input, deck, temp));
	ASSERT_EQUALS(true, inputTest203(input, deck, temp));
	ASSERT_EQUALS(true, inputTest204(input, deck, temp));
	ASSERT_EQUALS(true, inputTest205(input, deck, temp));
	ASSERT_EQUALS(true, inputTest206(input, deck, temp));
	ASSERT_EQUALS(true, inputTest207(input, deck, temp));
	ASSERT_EQUALS(true, inputTest208(input, deck, temp));
	ASSERT_EQUALS(true, inputTest209(input, deck, temp));
	ASSERT_EQUALS(true, inputTest210(input, deck, temp));
	ASSERT_EQUALS(true, inputTest211(input, deck, temp));
	ASSERT_EQUALS(true, inputTest212(input, deck, temp));
	ASSERT_EQUALS(true, inputTest213(input, deck, temp));
	ASSERT_EQUALS(true, inputTest214(input, deck, temp));
	ASSERT_EQUALS(true, inputTest215(input, deck, temp));
	ASSERT_EQUALS(true, inputTest216(input, deck, temp));
	ASSERT_EQUALS(true, inputTest217(input, deck, temp));
	ASSERT_EQUALS(true, inputTest218(input, deck, temp));
	ASSERT_EQUALS(true, inputTest219(input, deck, temp));
	ASSERT_EQUALS(true, inputTest220(input, deck, temp));
	ASSERT_EQUALS(true, inputTest221(input, deck, temp));
	ASSERT_EQUALS(true, inputTest222(input, deck, temp));
	ASSERT_EQUALS(true, inputTest223(input, deck, temp));
	ASSERT_EQUALS(true, inputTest224(input, deck, temp));
	ASSERT_EQUALS(true, inputTest225(input, deck, temp));
	ASSERT_EQUALS(true, inputTest226(input, deck, temp));
	ASSERT_EQUALS(true, inputTest227(input, deck, temp));
	ASSERT_EQUALS(true, inputTest228(input, deck, temp));
	ASSERT_EQUALS(true, inputTest229(input, deck, temp));
	ASSERT_EQUALS(true, inputTest230(input, deck, temp));
	ASSERT_EQUALS(true, inputTest231(input, deck, temp));
	ASSERT_EQUALS(true, inputTest232(input, deck, temp));
	ASSERT_EQUALS(true, inputTest233(input, deck, temp));
	ASSERT_EQUALS(true, inputTest234(input, deck, temp));
	ASSERT_EQUALS(true, inputTest235(input, deck, temp));
	ASSERT_EQUALS(true, inputTest236(input, deck, temp));
	ASSERT_EQUALS(true, inputTest237(input, deck, temp));
	ASSERT_EQUALS(true, inputTest238(input, deck, temp));
	ASSERT_EQUALS(true, inputTest239(input, deck, temp));
	ASSERT_EQUALS(true, inputTest240(input, deck, temp));
	ASSERT_EQUALS(true, inputTest241(input, deck, temp));
	ASSERT_EQUALS(true, inputTest242(input, deck, temp));
	ASSERT_EQUALS(true, inputTest243(input, deck, temp));
	ASSERT_EQUALS(true, inputTest244(input, deck, temp));
	ASSERT_EQUALS(true, inputTest245(input, deck, temp));
	ASSERT_EQUALS(true, inputTest246(input, deck, temp));
	ASSERT_EQUALS(true, inputTest247(input, deck, temp));
	ASSERT_EQUALS(true, inputTest248(input, deck, temp));
	ASSERT_EQUALS(true, inputTest249(input, deck, temp));
	ASSERT_EQUALS(true, inputTest250(input, deck, temp));
	ASSERT_EQUALS(true, inputTest251(input, deck, temp));
	ASSERT_EQUALS(true, inputTest252(input, deck, temp));
	ASSERT_EQUALS(true, inputTest253(input, deck, temp));
	ASSERT_EQUALS(true, inputTest254(input, deck, temp));
	ASSERT_EQUALS(true, inputTest255(input, deck, temp));
	ASSERT_EQUALS(true, inputTest256(input, deck, temp));
	ASSERT_EQUALS(true, inputTest257(input, deck, temp));
	ASSERT_EQUALS(true, inputTest258(input, deck, temp));
	ASSERT_EQUALS(true, inputTest259(input, deck, temp));
	ASSERT_EQUALS(true, inputTest260(input, deck, temp));
	ASSERT_EQUALS(true, inputTest261(input, deck, temp));
	ASSERT_EQUALS(true, inputTest262(input, deck, temp));
	ASSERT_EQUALS(true, inputTest263(input, deck, temp));
	ASSERT_EQUALS(true, inputTest264(input, deck, temp));
	ASSERT_EQUALS(true, inputTest265(input, deck, temp));
	ASSERT_EQUALS(true, inputTest266(input, deck, temp));
	ASSERT_EQUALS(true, inputTest267(input, deck, temp));
	ASSERT_EQUALS(true, inputTest268(input, deck, temp));
	ASSERT_EQUALS(true, inputTest269(input, deck, temp));
	ASSERT_EQUALS(true, inputTest270(input, deck, temp));
	ASSERT_EQUALS(true, inputTest271(input, deck, temp));
	ASSERT_EQUALS(true, inputTest272(input, deck, temp));
	ASSERT_EQUALS(true, inputTest273(input, deck, temp));
	ASSERT_EQUALS(true, inputTest274(input, deck, temp));
	ASSERT_EQUALS(true, inputTest275(input, deck, temp));
	ASSERT_EQUALS(true, inputTest276(input, deck, temp));
	ASSERT_EQUALS(true, inputTest277(input, deck, temp));
	ASSERT_EQUALS(true, inputTest278(input, deck, temp));
	ASSERT_EQUALS(true, inputTest279(input, deck, temp));
	ASSERT_EQUALS(true, inputTest280(input, deck, temp));
	ASSERT_EQUALS(true, inputTest281(input, deck, temp));
	ASSERT_EQUALS(true, inputTest282(input, deck, temp));
	ASSERT_EQUALS(true, inputTest283(input, deck, temp));
	ASSERT_EQUALS(true, inputTest284(input, deck, temp));
	ASSERT_EQUALS(true, inputTest285(input, deck, temp));
	ASSERT_EQUALS(true, inputTest286(input, deck, temp));
	ASSERT_EQUALS(true, inputTest287(input, deck, temp));
	ASSERT_EQUALS(true, inputTest288(input, deck, temp));
	ASSERT_EQUALS(true, inputTest289(input, deck, temp));
	ASSERT_EQUALS(true, inputTest290(input, deck, temp));
	ASSERT_EQUALS(true, inputTest291(input, deck, temp));
	ASSERT_EQUALS(true, inputTest292(input, deck, temp));
	ASSERT_EQUALS(true, inputTest293(input, deck, temp));
	ASSERT_EQUALS(true, inputTest294(input, deck, temp));
	ASSERT_EQUALS(true, inputTest295(input, deck, temp));
	ASSERT_EQUALS(true, inputTest296(input, deck, temp));
	ASSERT_EQUALS(true, inputTest297(input, deck, temp));
	ASSERT_EQUALS(true, inputTest298(input, deck, temp));
	ASSERT_EQUALS(true, inputTest299(input, deck, temp));
	ASSERT_EQUALS(true, inputTest300(input, deck, temp));
	ASSERT_EQUALS(true, inputTest301(input, deck, temp));
	ASSERT_EQUALS(true, inputTest302(input, deck, temp));
	ASSERT_EQUALS(true, inputTest303(input, deck, temp));
	ASSERT_EQUALS(true, inputTest304(input, deck, temp));
	ASSERT_EQUALS(true, inputTest305(input, deck, temp));
	ASSERT_EQUALS(true, inputTest306(input, deck, temp));
	ASSERT_EQUALS(true, inputTest307(input, deck, temp));
	ASSERT_EQUALS(true, inputTest308(input, deck, temp));
	ASSERT_EQUALS(true, inputTest309(input, deck, temp));
	ASSERT_EQUALS(true, inputTest310(input, deck, temp));
	ASSERT_EQUALS(true, inputTest311(input, deck, temp));
	ASSERT_EQUALS(true, inputTest312(input, deck, temp));
	ASSERT_EQUALS(true, inputTest313(input, deck, temp));
	ASSERT_EQUALS(true, inputTest314(input, deck, temp));
	ASSERT_EQUALS(true, inputTest315(input, deck, temp));
	ASSERT_EQUALS(true, inputTest316(input, deck, temp));
	ASSERT_EQUALS(true, inputTest317(input, deck, temp));
	ASSERT_EQUALS(true, inputTest318(input, deck, temp));
	ASSERT_EQUALS(true, inputTest319(input, deck, temp));
	ASSERT_EQUALS(true, inputTest320(input, deck, temp));
	ASSERT_EQUALS(true, inputTest321(input, deck, temp));
	ASSERT_EQUALS(true, inputTest322(input, deck, temp));
	ASSERT_EQUALS(true, inputTest323(input, deck, temp));
	ASSERT_EQUALS(true, inputTest324(input, deck, temp));
	ASSERT_EQUALS(true, inputTest325(input, deck, temp));
	ASSERT_EQUALS(true, inputTest326(input, deck, temp));
	ASSERT_EQUALS(true, inputTest327(input, deck, temp));
	ASSERT_EQUALS(true, inputTest328(input, deck, temp));
	ASSERT_EQUALS(true, inputTest329(input, deck, temp));
	ASSERT_EQUALS(true, inputTest330(input, deck, temp));
	ASSERT_EQUALS(true, inputTest331(input, deck, temp));
	ASSERT_EQUALS(true, inputTest332(input, deck, temp));
	ASSERT_EQUALS(true, inputTest333(input, deck, temp));
	ASSERT_EQUALS(true, inputTest334(input, deck, temp));
	ASSERT_EQUALS(true, inputTest335(input, deck, temp));
	ASSERT_EQUALS(true, inputTest336(input, deck, temp));
	ASSERT_EQUALS(true, inputTest337(input, deck, temp));
	ASSERT_EQUALS(true, inputTest338(input, deck, temp));
	ASSERT_EQUALS(true, inputTest339(input, deck, temp));
	ASSERT_EQUALS(true, inputTest340(input, deck, temp));
	ASSERT_EQUALS(true, inputTest341(input, deck, temp));
	ASSERT_EQUALS(true, inputTest342(input, deck, temp));
	ASSERT_EQUALS(true, inputTest343(input, deck, temp));
	ASSERT_EQUALS(true, inputTest344(input, deck, temp));
	ASSERT_EQUALS(true, inputTest345(input, deck, temp));
	ASSERT_EQUALS(true, inputTest346(input, deck, temp));
	ASSERT_EQUALS(true, inputTest347(input, deck, temp));
	ASSERT_EQUALS(true, inputTest348(input, deck, temp));
	ASSERT_EQUALS(true, inputTest349(input, deck, temp));
	ASSERT_EQUALS(true, inputTest350(input, deck, temp));
	ASSERT_EQUALS(true, inputTest351(input, deck, temp));
	ASSERT_EQUALS(true, inputTest352(input, deck, temp));
	ASSERT_EQUALS(true, inputTest353(input, deck, temp));
	ASSERT_EQUALS(true, inputTest354(input, deck, temp));
	ASSERT_EQUALS(true, inputTest355(input, deck, temp));
	ASSERT_EQUALS(true, inputTest356(input, deck, temp));
	ASSERT_EQUALS(true, inputTest357(input, deck, temp));
	ASSERT_EQUALS(true, inputTest358(input, deck, temp));
	ASSERT_EQUALS(true, inputTest359(input, deck, temp));
	ASSERT_EQUALS(true, inputTest360(input, deck, temp));
	ASSERT_EQUALS(true, inputTest361(input, deck, temp));
	ASSERT_EQUALS(true, inputTest362(input, deck, temp));
	ASSERT_EQUALS(true, inputTest363(input, deck, temp));
	ASSERT_EQUALS(true, inputTest364(input, deck, temp));
	ASSERT_EQUALS(true, inputTest365(input, deck, temp));
	ASSERT_EQUALS(true, inputTest366(input, deck, temp));
	ASSERT_EQUALS(true, inputTest367(input, deck, temp));
	ASSERT_EQUALS(true, inputTest368(input, deck, temp));
	ASSERT_EQUALS(true, inputTest369(input, deck, temp));
	ASSERT_EQUALS(true, inputTest370(input, deck, temp));
	ASSERT_EQUALS(true, inputTest371(input, deck, temp));
	ASSERT_EQUALS(true, inputTest372(input, deck, temp));
	ASSERT_EQUALS(true, inputTest373(input, deck, temp));
	ASSERT_EQUALS(true, inputTest374(input, deck, temp));
	ASSERT_EQUALS(true, inputTest375(input, deck, temp));
	ASSERT_EQUALS(true, inputTest376(input, deck, temp));
	ASSERT_EQUALS(true, inputTest377(input, deck, temp));
	ASSERT_EQUALS(true, inputTest378(input, deck, temp));
	ASSERT_EQUALS(true, inputTest379(input, deck, temp));
	ASSERT_EQUALS(true, inputTest380(input, deck, temp));
	ASSERT_EQUALS(true, inputTest381(input, deck, temp));
	ASSERT_EQUALS(true, inputTest382(input, deck, temp));
	ASSERT_EQUALS(true, inputTest383(input, deck, temp));
	ASSERT_EQUALS(true, inputTest384(input, deck, temp));
	ASSERT_EQUALS(true, inputTest385(input, deck, temp));
	ASSERT_EQUALS(true, inputTest386(input, deck, temp));
	ASSERT_EQUALS(true, inputTest387(input, deck, temp));
	ASSERT_EQUALS(true, inputTest388(input, deck, temp));
	ASSERT_EQUALS(true, inputTest389(input, deck, temp));
	ASSERT_EQUALS(true, inputTest390(input, deck, temp));
	ASSERT_EQUALS(true, inputTest391(input, deck, temp));
	ASSERT_EQUALS(true, inputTest392(input, deck, temp));
	ASSERT_EQUALS(true, inputTest393(input, deck, temp));
	ASSERT_EQUALS(true, inputTest394(input, deck, temp));
	ASSERT_EQUALS(true, inputTest395(input, deck, temp));
	ASSERT_EQUALS(true, inputTest396(input, deck, temp));
	ASSERT_EQUALS(true, inputTest397(input, deck, temp));
	ASSERT_EQUALS(true, inputTest398(input, deck, temp));
	ASSERT_EQUALS(true, inputTest399(input, deck, temp));
	ASSERT_EQUALS(true, inputTest400(input, deck, temp));
	ASSERT_EQUALS(true, inputTest401(input, deck, temp));
	ASSERT_EQUALS(true, inputTest402(input, deck, temp));
	ASSERT_EQUALS(true, inputTest403(input, deck, temp));
	ASSERT_EQUALS(true, inputTest404(input, deck, temp));
	ASSERT_EQUALS(true, inputTest405(input, deck, temp));
	ASSERT_EQUALS(true, inputTest406(input, deck, temp));
	ASSERT_EQUALS(true, inputTest407(input, deck, temp));
	ASSERT_EQUALS(true, inputTest408(input, deck, temp));
	ASSERT_EQUALS(true, inputTest409(input, deck, temp));
	ASSERT_EQUALS(true, inputTest410(input, deck, temp));
	ASSERT_EQUALS(true, inputTest411(input, deck, temp));
	ASSERT_EQUALS(true, inputTest412(input, deck, temp));
	ASSERT_EQUALS(true, inputTest413(input, deck, temp));
	ASSERT_EQUALS(true, inputTest414(input, deck, temp));
	ASSERT_EQUALS(true, inputTest415(input, deck, temp));
	ASSERT_EQUALS(true, inputTest416(input, deck, temp));
	ASSERT_EQUALS(true, inputTest417(input, deck, temp));
	ASSERT_EQUALS(true, inputTest418(input, deck, temp));
	ASSERT_EQUALS(true, inputTest419(input, deck, temp));
	ASSERT_EQUALS(true, inputTest420(input, deck, temp));
	ASSERT_EQUALS(true, inputTest421(input, deck, temp));
	ASSERT_EQUALS(true, inputTest422(input, deck, temp));
	ASSERT_EQUALS(true, inputTest423(input, deck, temp));
	ASSERT_EQUALS(true, inputTest424(input, deck, temp));
	ASSERT_EQUALS(true, inputTest425(input, deck, temp));
	ASSERT_EQUALS(true, inputTest426(input, deck, temp));
	ASSERT_EQUALS(true, inputTest427(input, deck, temp));
	ASSERT_EQUALS(true, inputTest428(input, deck, temp));
	ASSERT_EQUALS(true, inputTest429(input, deck, temp));
	ASSERT_EQUALS(true, inputTest430(input, deck, temp));
	ASSERT_EQUALS(true, inputTest431(input, deck, temp));
	ASSERT_EQUALS(true, inputTest432(input, deck, temp));
	ASSERT_EQUALS(true, inputTest433(input, deck, temp));
	ASSERT_EQUALS(true, inputTest434(input, deck, temp));
	ASSERT_EQUALS(true, inputTest435(input, deck, temp));
	ASSERT_EQUALS(true, inputTest436(input, deck, temp));
	ASSERT_EQUALS(true, inputTest437(input, deck, temp));
	ASSERT_EQUALS(true, inputTest438(input, deck, temp));
	ASSERT_EQUALS(true, inputTest439(input, deck, temp));
	ASSERT_EQUALS(true, inputTest440(input, deck, temp));
	ASSERT_EQUALS(true, inputTest441(input, deck, temp));
	ASSERT_EQUALS(true, inputTest442(input, deck, temp));
	ASSERT_EQUALS(true, inputTest443(input, deck, temp));
	ASSERT_EQUALS(true, inputTest444(input, deck, temp));
	ASSERT_EQUALS(true, inputTest445(input, deck, temp));
	ASSERT_EQUALS(true, inputTest446(input, deck, temp));
	ASSERT_EQUALS(true, inputTest447(input, deck, temp));
	ASSERT_EQUALS(true, inputTest448(input, deck, temp));
	ASSERT_EQUALS(true, inputTest449(input, deck, temp));
	ASSERT_EQUALS(true, inputTest450(input, deck, temp));
	ASSERT_EQUALS(true, inputTest451(input, deck, temp));
	ASSERT_EQUALS(true, inputTest452(input, deck, temp));
	ASSERT_EQUALS(true, inputTest453(input, deck, temp));
	ASSERT_EQUALS(true, inputTest454(input, deck, temp));
	ASSERT_EQUALS(true, inputTest455(input, deck, temp));
	ASSERT_EQUALS(true, inputTest456(input, deck, temp));
	ASSERT_EQUALS(true, inputTest457(input, deck, temp));
	ASSERT_EQUALS(true, inputTest458(input, deck, temp));
	ASSERT_EQUALS(true, inputTest459(input, deck, temp));
	ASSERT_EQUALS(true, inputTest460(input, deck, temp));
	ASSERT_EQUALS(true, inputTest461(input, deck, temp));
	ASSERT_EQUALS(true, inputTest462(input, deck, temp));
	ASSERT_EQUALS(true, inputTest463(input, deck, temp));
	ASSERT_EQUALS(true, inputTest464(input, deck, temp));
	ASSERT_EQUALS(true, inputTest465(input, deck, temp));
	ASSERT_EQUALS(true, inputTest466(input, deck, temp));
	ASSERT_EQUALS(true, inputTest467(input, deck, temp));
	ASSERT_EQUALS(true, inputTest468(input, deck, temp));
	ASSERT_EQUALS(true, inputTest469(input, deck, temp));
	ASSERT_EQUALS(true, inputTest470(input, deck, temp));
	ASSERT_EQUALS(true, inputTest471(input, deck, temp));
	ASSERT_EQUALS(true, inputTest472(input, deck, temp));
	ASSERT_EQUALS(true, inputTest473(input, deck, temp));
	ASSERT_EQUALS(true, inputTest474(input, deck, temp));
	ASSERT_EQUALS(true, inputTest475(input, deck, temp));
	ASSERT_EQUALS(true, inputTest476(input, deck, temp));
	ASSERT_EQUALS(true, inputTest477(input, deck, temp));
	ASSERT_EQUALS(true, inputTest478(input, deck, temp));
	ASSERT_EQUALS(true, inputTest479(input, deck, temp));
	ASSERT_EQUALS(true, inputTest480(input, deck, temp));
	ASSERT_EQUALS(true, inputTest481(input, deck, temp));
	ASSERT_EQUALS(true, inputTest482(input, deck, temp));
	ASSERT_EQUALS(true, inputTest483(input, deck, temp));
	ASSERT_EQUALS(true, inputTest484(input, deck, temp));
	ASSERT_EQUALS(true, inputTest485(input, deck, temp));
	ASSERT_EQUALS(true, inputTest486(input, deck, temp));
	ASSERT_EQUALS(true, inputTest487(input, deck, temp));
	ASSERT_EQUALS(true, inputTest488(input, deck, temp));
	ASSERT_EQUALS(true, inputTest489(input, deck, temp));
	ASSERT_EQUALS(true, inputTest490(input, deck, temp));
	ASSERT_EQUALS(true, inputTest491(input, deck, temp));
	ASSERT_EQUALS(true, inputTest492(input, deck, temp));
	ASSERT_EQUALS(true, inputTest493(input, deck, temp));
	ASSERT_EQUALS(true, inputTest494(input, deck, temp));
	ASSERT_EQUALS(true, inputTest495(input, deck, temp));
	ASSERT_EQUALS(true, inputTest496(input, deck, temp));
	ASSERT_EQUALS(true, inputTest497(input, deck, temp));
	ASSERT_EQUALS(true, inputTest498(input, deck, temp));
	ASSERT_EQUALS(true, inputTest499(input, deck, temp));
	ASSERT_EQUALS(true, inputTest500(input, deck, temp));
	ASSERT_EQUALS(true, inputTest501(input, deck, temp));
	ASSERT_EQUALS(true, inputTest502(input, deck, temp));
	ASSERT_EQUALS(true, inputTest503(input, deck, temp));
	ASSERT_EQUALS(true, inputTest504(input, deck, temp));
	ASSERT_EQUALS(true, inputTest505(input, deck, temp));
	ASSERT_EQUALS(true, inputTest506(input, deck, temp));
	ASSERT_EQUALS(true, inputTest507(input, deck, temp));
	ASSERT_EQUALS(true, inputTest508(input, deck, temp));
	ASSERT_EQUALS(true, inputTest509(input, deck, temp));
	ASSERT_EQUALS(true, inputTest510(input, deck, temp));
	ASSERT_EQUALS(true, inputTest511(input, deck, temp));
	ASSERT_EQUALS(true, inputTest512(input, deck, temp));
	ASSERT_EQUALS(true, inputTest513(input, deck, temp));
	ASSERT_EQUALS(true, inputTest514(input, deck, temp));
	ASSERT_EQUALS(true, inputTest515(input, deck, temp));
	ASSERT_EQUALS(true, inputTest516(input, deck, temp));
	ASSERT_EQUALS(true, inputTest517(input, deck, temp));
	ASSERT_EQUALS(true, inputTest518(input, deck, temp));
	ASSERT_EQUALS(true, inputTest519(input, deck, temp));
	ASSERT_EQUALS(true, inputTest520(input, deck, temp));
	ASSERT_EQUALS(true, inputTest521(input, deck, temp));
	ASSERT_EQUALS(true, inputTest522(input, deck, temp));

#endif /* DECK_INPUT */

	return true;
}

DEFINE_INPUT_TEST(cardDeckOutput)

#ifdef DECK_OUTPUT
	CardDeck deck;

	//std::stringstream sstrm;
	//ostream& os = sstrm;
	ostream& os = std::cout;

	input >> deck;
	os << deck << endl;
	
	ASSERT_THROW(CardWrongArgsException, input >> deck);
	os << deck << endl;

	input >> deck;
	os << deck << endl;

	ASSERT_THROW(CardWrongArgsException, input >> deck);
	os << deck << endl;

	ASSERT_THROW(CardWrongArgsException, input >> deck);
	os << deck << endl;
	
	while (!input.eof()) {
		input >> deck;
		os << deck << endl;
	}

	os << deck << endl;

#endif /* DECK_OUTPUT */

	return true;
}

// one test for draw, top, size, isEmpty, clear
bool cardDeckBasicActions() {
	CardDeck deck;
	ASSERT_EQUALS(true, deck.isEmpty());
	ASSERT_EQUALS(0, deck.size());
	ASSERT_THROW(CardDeckIsEmptyException, deck.top());
	ASSERT_THROW(CardDeckIsEmptyException, deck.draw());
	Card  top = CardDeck::getFullDeck().top();
	ASSERT_EQUALS(Card(Card::Spade,'K'), top);
	
	deck += (Card(Card::Diamond, 'Q') + top + top + Card(Card::Club, 7));
	ASSERT_EQUALS(Card(Card::Club, 7), deck.top());
	deck.draw();
	Card card = deck.draw();
	ASSERT_EQUALS(2, deck.size());
	ASSERT_EQUALS(deck.top(), card);
	ASSERT_EQUALS(false, deck.isEmpty());
	ASSERT_EQUALS(false, CardDeck::getFullDeck().isEmpty());
	CardDeck::getFullDeck().clear();
	ASSERT_EQUALS(false, CardDeck::getFullDeck().isEmpty());
	deck.clear();
	ASSERT_EQUALS(0, deck.size());
	ASSERT_EQUALS(true, deck.isEmpty());
	deck += Card(Card::Diamond, 10);
	ASSERT_EQUALS(1, deck.size());
	ASSERT_EQUALS(false, deck.isEmpty());
	ASSERT_EQUALS(Card(Card::Diamond, 10), deck.top());
	deck += Card(Card::Diamond, 9);
	ASSERT_EQUALS(2, deck.size());
	ASSERT_EQUALS(false, deck.isEmpty());
	ASSERT_EQUALS(Card(Card::Diamond, 9), deck.top());

	return true;
}

DEFINE_INPUT_TEST(cardDeckValueTest)
	CardDeck deck;
	ASSERT_EQUALS(0, deck.value());
	Card ace = Card(Card::Heart, 1);
	ASSERT_EQUALS(0, deck.value());
	for (int i = 2; i <= 10; ++i) {
		Card card = Card(Card::Diamond, i);
		ASSERT_EQUALS((unsigned)i, (deck + card).value());
	}
	for (char c : {'K','Q','J'}) {
		Card card = Card(Card::Diamond, c);
		ASSERT_EQUALS(10, (deck + card).value());
	}
	for (int i = 11; i <= 21; i++) {
		deck += ace;
		ASSERT_EQUALS((unsigned)i, deck.value());
	}
	for (int i = 12; i <= 21; ++i) {
		deck += ace;
		ASSERT_EQUALS((unsigned)i, deck.value());
	}
	deck += ace;
	ASSERT_EQUALS(42, deck.value());
	deck += ace;
	ASSERT_EQUALS(33, deck.value());

	deck.clear();
	deck += ace;
	deck += Card(Card::Club, 'K');
	deck += Card(Card::Club, 'Q');
	deck += Card(Card::Club, 'J');
	deck += Card(Card::Club, 5);
	deck += Card(Card::Club, 6);
	
	ASSERT_EQUALS(42, deck.value());
	
	deck.draw();
	deck += Card(Card::Club, 7);
	ASSERT_EQUALS(53, deck.value());
	
	deck.draw();
	deck += Card(Card::Club, 6);
	deck += ace;
	ASSERT_EQUALS(63, deck.value());

	deck += ace;
	ASSERT_EQUALS(54, deck.value());

	input >> deck;
	ASSERT_EQUALS(17, deck.value());
	input >> deck;
	ASSERT_EQUALS(17, deck.value());
	input >> deck;
	ASSERT_EQUALS(13, deck.value());
	input >> deck;
	ASSERT_EQUALS(11, deck.value());
	input >> deck;
	ASSERT_EQUALS(18, deck.value());
	input >> deck;
	ASSERT_EQUALS(42, deck.value());
	input >> deck;
	ASSERT_EQUALS(11, deck.value());
	input >> deck;
	ASSERT_EQUALS(18, deck.value());
	input >> deck;
	ASSERT_EQUALS(14, deck.value());
	input >> deck;
	ASSERT_EQUALS(13, deck.value());
	input >> deck;
	ASSERT_EQUALS(19, deck.value());
	input >> deck;
	ASSERT_EQUALS(12, deck.value());
	input >> deck;
	ASSERT_EQUALS(15, deck.value());
	input >> deck;
	ASSERT_EQUALS(14, deck.value());
	input >> deck;
	ASSERT_EQUALS(12, deck.value());
	input >> deck;
	ASSERT_EQUALS(12, deck.value());
	input >> deck;
	ASSERT_EQUALS(13, deck.value());
	input >> deck;
	ASSERT_EQUALS(13, deck.value());
	input >> deck;
	ASSERT_EQUALS(11, deck.value());
	input >> deck;
	ASSERT_EQUALS(15, deck.value());
	input >> deck;
	ASSERT_EQUALS(12, deck.value());
	input >> deck;
	ASSERT_EQUALS(15, deck.value());
	input >> deck;
	ASSERT_EQUALS(15, deck.value());
	input >> deck;
	ASSERT_EQUALS(11, deck.value());
	input >> deck;
	ASSERT_EQUALS(11, deck.value());
	input >> deck;
	ASSERT_EQUALS(18, deck.value());
	input >> deck;
	ASSERT_EQUALS(14, deck.value());
	input >> deck;
	ASSERT_EQUALS(12, deck.value());
	input >> deck;
	ASSERT_EQUALS(11, deck.value());
	input >> deck;
	ASSERT_EQUALS(11, deck.value());
	input >> deck;
	ASSERT_EQUALS(21, deck.value());
	input >> deck;
	ASSERT_EQUALS(10, deck.value());
	input >> deck;
	ASSERT_EQUALS(18, deck.value());
	input >> deck;
	ASSERT_EQUALS(17, deck.value());
	input >> deck;
	ASSERT_EQUALS(12, deck.value());
	input >> deck;
	ASSERT_EQUALS(16, deck.value());
	input >> deck;
	ASSERT_EQUALS(12, deck.value());
	input >> deck;
	ASSERT_EQUALS(12, deck.value());
	input >> deck;
	ASSERT_EQUALS(13, deck.value());
	input >> deck;
	ASSERT_EQUALS(12, deck.value());
	input >> deck;
	ASSERT_EQUALS(18, deck.value());
	input >> deck;
	ASSERT_EQUALS(13, deck.value());
	input >> deck;
	ASSERT_EQUALS(21, deck.value());
	input >> deck;
	ASSERT_EQUALS(12, deck.value());
	input >> deck;
	ASSERT_EQUALS(21, deck.value());
	input >> deck;
	ASSERT_EQUALS(12, deck.value());
	input >> deck;
	ASSERT_EQUALS(2, deck.value());
	input >> deck;
	ASSERT_EQUALS(13, deck.value());
	input >> deck;
	ASSERT_EQUALS(12, deck.value());
	input >> deck;
	ASSERT_EQUALS(3, deck.value());
	input >> deck;
	ASSERT_EQUALS(12, deck.value());
	input >> deck;
	ASSERT_EQUALS(13, deck.value());
	input >> deck;
	ASSERT_EQUALS(19, deck.value());
	input >> deck;
	ASSERT_EQUALS(17, deck.value());
	input >> deck;
	ASSERT_EQUALS(9, deck.value());
	input >> deck;
	ASSERT_EQUALS(19, deck.value());
	input >> deck;
	ASSERT_EQUALS(16, deck.value());
	input >> deck;
	ASSERT_EQUALS(19, deck.value());
	input >> deck;
	ASSERT_EQUALS(21, deck.value());
	input >> deck;
	ASSERT_EQUALS(19, deck.value());
	input >> deck;
	ASSERT_EQUALS(14, deck.value());
	input >> deck;
	ASSERT_EQUALS(11, deck.value());
	input >> deck;
	ASSERT_EQUALS(21, deck.value());
	input >> deck;
	ASSERT_EQUALS(15, deck.value());
	input >> deck;
	ASSERT_EQUALS(15, deck.value());
	input >> deck;
	ASSERT_EQUALS(20, deck.value());
	input >> deck;
	ASSERT_EQUALS(12, deck.value());
	input >> deck;
	ASSERT_EQUALS(18, deck.value());
	input >> deck;
	ASSERT_EQUALS(3, deck.value());
	input >> deck;
	ASSERT_EQUALS(21, deck.value());
	input >> deck;
	ASSERT_EQUALS(19, deck.value());
	input >> deck;
	ASSERT_EQUALS(18, deck.value());
	input >> deck;
	ASSERT_EQUALS(15, deck.value());
	input >> deck;
	ASSERT_EQUALS(21, deck.value());
	input >> deck;
	ASSERT_EQUALS(21, deck.value());
	input >> deck;
	ASSERT_EQUALS(19, deck.value());
	input >> deck;
	ASSERT_EQUALS(40, deck.value());
	input >> deck;
	ASSERT_EQUALS(12, deck.value());
	input >> deck;
	ASSERT_EQUALS(21, deck.value());
	input >> deck;
	ASSERT_EQUALS(18, deck.value());
	input >> deck;
	ASSERT_EQUALS(11, deck.value());
	input >> deck;
	ASSERT_EQUALS(16, deck.value());
	input >> deck;
	ASSERT_EQUALS(20, deck.value());
	input >> deck;
	ASSERT_EQUALS(21, deck.value());
	input >> deck;
	ASSERT_EQUALS(11, deck.value());
	input >> deck;
	ASSERT_EQUALS(9, deck.value());
	input >> deck;
	ASSERT_EQUALS(11, deck.value());
	input >> deck;
	ASSERT_EQUALS(12, deck.value());
	input >> deck;
	ASSERT_EQUALS(15, deck.value());
	input >> deck;
	ASSERT_EQUALS(11, deck.value());
	input >> deck;
	ASSERT_EQUALS(15, deck.value());
	input >> deck;
	ASSERT_EQUALS(10, deck.value());
	input >> deck;
	ASSERT_EQUALS(15, deck.value());
	input >> deck;
	ASSERT_EQUALS(38, deck.value());
	input >> deck;
	ASSERT_EQUALS(13, deck.value());
	input >> deck;
	ASSERT_EQUALS(20, deck.value());
	input >> deck;
	ASSERT_EQUALS(14, deck.value());
	input >> deck;
	ASSERT_EQUALS(12, deck.value());
	input >> deck;
	ASSERT_EQUALS(20, deck.value());
	input >> deck;
	ASSERT_EQUALS(42, deck.value());
	input >> deck;
	ASSERT_EQUALS(34, deck.value());
	input >> deck;
	ASSERT_EQUALS(10, deck.value());
	input >> deck;
	ASSERT_EQUALS(16, deck.value());
	input >> deck;
	ASSERT_EQUALS(4, deck.value());
	input >> deck;
	ASSERT_EQUALS(39, deck.value());
	input >> deck;
	ASSERT_EQUALS(11, deck.value());
	input >> deck;
	ASSERT_EQUALS(15, deck.value());
	input >> deck;
	ASSERT_EQUALS(41, deck.value());
	input >> deck;
	ASSERT_EQUALS(16, deck.value());
	input >> deck;
	ASSERT_EQUALS(31, deck.value());
	input >> deck;
	ASSERT_EQUALS(14, deck.value());
	input >> deck;
	ASSERT_EQUALS(26, deck.value());
	input >> deck;
	ASSERT_EQUALS(14, deck.value());
	input >> deck;
	ASSERT_EQUALS(76, deck.value());
	input >> deck;
	ASSERT_EQUALS(16, deck.value());
	input >> deck;
	ASSERT_EQUALS(15, deck.value());
	input >> deck;
	ASSERT_EQUALS(17, deck.value());
	input >> deck;
	ASSERT_EQUALS(11, deck.value());
	input >> deck;
	ASSERT_EQUALS(17, deck.value());
	input >> deck;
	ASSERT_EQUALS(19, deck.value());
	input >> deck;
	ASSERT_EQUALS(16, deck.value());
	input >> deck;
	ASSERT_EQUALS(19, deck.value());
	input >> deck;
	ASSERT_EQUALS(17, deck.value());
	input >> deck;
	ASSERT_EQUALS(16, deck.value());
	input >> deck;
	ASSERT_EQUALS(21, deck.value());
	input >> deck;
	ASSERT_EQUALS(15, deck.value());
	input >> deck;
	ASSERT_EQUALS(20, deck.value());
	input >> deck;
	ASSERT_EQUALS(78, deck.value());
	input >> deck;
	ASSERT_EQUALS(18, deck.value());
	input >> deck;
	ASSERT_EQUALS(40, deck.value());
	input >> deck;
	ASSERT_EQUALS(15, deck.value());
	input >> deck;
	ASSERT_EQUALS(5, deck.value());
	input >> deck;
	ASSERT_EQUALS(15, deck.value());
	input >> deck;
	ASSERT_EQUALS(54, deck.value());
	input >> deck;
	ASSERT_EQUALS(58, deck.value());
	input >> deck;
	ASSERT_EQUALS(41, deck.value());
	input >> deck;
	ASSERT_EQUALS(17, deck.value());
	input >> deck;
	ASSERT_EQUALS(181, deck.value());
	input >> deck;
	ASSERT_EQUALS(63, deck.value());
	input >> deck;
	ASSERT_EQUALS(83, deck.value());
	input >> deck;
	ASSERT_EQUALS(105, deck.value());
	input >> deck;
	ASSERT_EQUALS(208, deck.value());
	input >> deck;
	ASSERT_EQUALS(103, deck.value());
	input >> deck;
	ASSERT_EQUALS(124, deck.value());

	return true;
}

DEFINE_INPUT_TEST(cardDeckComparisonTest)
	ASSERT_EQUALS(true, checkAllComparisons(CardDeck(), CardDeck(), false, true));
	CardDeck singleCardDeck = Card(Card::Spade, 7);
	CardDeck doubleCardDeck = (singleCardDeck + singleCardDeck);
	
	ASSERT_EQUALS(true, checkAllComparisons(singleCardDeck, singleCardDeck, false, false));
	ASSERT_EQUALS(true, checkAllComparisons(CardDeck(), doubleCardDeck, true, false));
	ASSERT_EQUALS(true, checkAllComparisons(singleCardDeck, doubleCardDeck, true, false));
	ASSERT_EQUALS(true, checkAllComparisons(doubleCardDeck, doubleCardDeck, false, true));

	CardDeck first;
	CardDeck second;
	
	while (!input.eof()) {
		std::string inputStr;
		input >> inputStr;
		if (inputStr == "<=:") {
			input >> inputStr;
			// assert(inputStr == "STRICT:");
			bool strict;
			input >> strict;
			for (int i = 0; i < 2; ++i) {
				input >> first;
				input >> second;
				ASSERT_EQUALS(true, checkAllComparisons(first, second, strict, !strict));
			}
		} else {
			// assert(inputStr == "!=:");
			input >> first;
			input >> second;
			ASSERT_EQUALS(true, checkAllComparisons(first, second, false, false));
		}
	}

	return true;
}

DEFINE_INPUT_TEST(cardDeckArithmeticOperatorsTest)

#ifdef DECK_ARITH

	ostream& os = std::cout;
	while (!input.eof()) {
		std::string op;
		input >> op;
		CardDeck first;
		CardDeck second;
		CardDeck third;
		if (op == "+") {
			input >> first;
			input >> second;
			os << (first + second) << endl;
		}
		else if (op == "+3") {
			input >> first;
			input >> second;
			input >> third;
			os << (first + second + third) << endl;
		}
		else if (op == "+=3") {
			input >> first;
			input >> second;
			input >> third;
			CardDeck firstCopy = first;
			first += second;
			first += third;
			os << (first) << endl;
			os << (second) << endl;
			os << (third) << endl;
			first = firstCopy;
			second += third;
			third += first;
			os << (first) << endl;
			os << (second) << endl;
			os << (third) << endl;

			first += (second += third);
			os << (first) << endl;
			os << (second) << endl;
			os << (third) << endl;
		} else if (op == "*") {
			input >> first;
			os << 0 * first << endl << first * 0 << endl;
			os << 1 * first << endl << first * 1 << endl;
			os << 2 * first << endl << first * 2 << endl;
			os << 3 * first << endl << first * 3 << endl;
		} else {
			os << "unexpected op: " << op << endl;
		}
	}
#endif /* DECK_ARITH */

	return true;
}

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
	ASSERT_EQUALS(Card(Card::Club,4), newDeck.top());
	std::cout << newDeck * 2 << endl;
	CardDeck first;
	CardDeck second;
	input >> first;
	input >> second;
	std::cout << first + second << endl;

	CardDeck smallDeck = Card(Card::Diamond, 7) + Card(Card::Diamond, 10);
	ASSERT_EQUALS(true, smallDeck < fullDeck);
	ASSERT_EQUALS(true, smallDeck <= fullDeck);
	ASSERT_EQUALS(true, fullDeck > smallDeck);
	ASSERT_EQUALS(true, fullDeck >= smallDeck);
	ASSERT_EQUALS(true, fullDeck != smallDeck);
	ASSERT_EQUALS(false, fullDeck == smallDeck);

	return true;
}

bool cardDeckTest(int testNum) {
	if (testNum == 0) {
		RUN_TEST(cardDeckExample);
		RUN_TEST(cardDeckFullTest);
		RUN_TEST(cardDeckInput);
		RUN_TEST(cardDeckOutput);
		RUN_TEST(cardDeckBasicActions);
		RUN_TEST(cardDeckValueTest);
		RUN_TEST(cardDeckComparisonTest);
		RUN_TEST(cardDeckArithmeticOperatorsTest);
	}
	else {
		switch (testNum) {
		case 1:
			RUN_TEST(cardDeckExample);
			break;
		case 2:
			RUN_TEST(cardDeckFullTest);
			break;
		case 3:
			RUN_TEST(cardDeckInput);
			break;
		case 4:
			RUN_TEST(cardDeckOutput);
			break;
		case 5:
			RUN_TEST(cardDeckBasicActions);
			break;
		case 6:
			RUN_TEST(cardDeckValueTest);
			break;
		case 7:
			RUN_TEST(cardDeckComparisonTest);
			break;
		case 8:
			RUN_TEST(cardDeckArithmeticOperatorsTest);
			break;
		}
	}

	return true;
}
