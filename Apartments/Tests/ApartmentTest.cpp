#include <cstdlib>
#include "Apartment.h"
#include "MtmTst.h"

static void deleteSquares(Apartment::SquareType** squares, int length) {
	for (int i = 0; i < length; ++i) {
		delete[] squares[i];
	}
	delete[] squares;
}

bool apartmentTestExample() {
	const int length = 3;
	const int width = 4;
	const int price = 1;
	Apartment::SquareType** squares = new Apartment::SquareType*[length];
	for (int i = 0; i < length; ++i) {
		squares[i] = new Apartment::SquareType[width];
		for (int j = 0; j < width; ++j) {
			squares[i][j] = Apartment::EMPTY;
		}
	}
	ASSERT_NO_THROW(Apartment(squares, length, width, price));
	const Apartment apt(squares, length, width, price);
	ASSERT_EQUALS(length, apt.getLength());
	Apartment apt2(apt);
	ASSERT_NO_THROW(apt2 += apt);
	ASSERT_EQUALS(true, apt < apt2);
	deleteSquares(squares, length);
	return true;
}

bool apartmentCtorsTest() {
	const int length1 = 3;
	const int width1 = 4;
	const int price1 = 1;
	const int length2 = 2;
	const int width2 = 3;
	const int price2 = 5;
	Apartment::SquareType** squares1 = new Apartment::SquareType*[length1];
	for (int i = 0; i < length1; ++i) {
		squares1[i] = new Apartment::SquareType[width1];
		for (int j = 0; j < width1; ++j) {
			squares1[i][j] = Apartment::EMPTY;
		}
	}
	Apartment::SquareType** squares2 = new Apartment::SquareType*[length2];
	for (int i = 0; i < length2; ++i) {
		squares2[i] = new Apartment::SquareType[width2];
		for (int j = 0; j < width2; ++j) {
			squares2[i][j] = Apartment::EMPTY;
		}
	}
	ASSERT_NO_THROW(Apartment(squares1, length1, width1, price1));
	ASSERT_NO_THROW(Apartment(squares1, length1, width1, 0));
	ASSERT_NO_THROW(Apartment(squares1, 1, 1, price1));
	ASSERT_THROW(Apartment::IllegalArgException,
			Apartment(squares1, 0, width1, price1));
	ASSERT_THROW(Apartment::IllegalArgException,
			Apartment(squares1, -1, width1, price1));
	ASSERT_THROW(Apartment::IllegalArgException,
			Apartment(squares1, length1, 0, price1));
	ASSERT_THROW(Apartment::IllegalArgException,
			Apartment(squares1, length1, -1, price1));
	ASSERT_THROW(Apartment::IllegalArgException,
			Apartment(squares1, length1, width1, -1));
	ASSERT_THROW(Apartment::IllegalArgException,
			Apartment(NULL, length1, width1, price1));
	const Apartment apt1(squares1, length1, width1, price1);
	Apartment apt2(squares2, length2, width2, price2);
	{
		const Apartment tmp(squares1, length1, width1, price1);
		apt2 = tmp;
	}
	ASSERT_EQUALS(Apartment::EMPTY, apt2(length1 - 1, width1 - 1));
	ASSERT_EQUALS(length1, apt1.getLength());
	Apartment apt3(apt1);
	ASSERT_NO_THROW(apt3 += apt1);
	ASSERT_EQUALS(true, apt1 < apt3);
	deleteSquares(squares1, length1);
	deleteSquares(squares2, length2);
	return true;
}

bool apartmentFunctionsTest() {
	const int length1 = 3, width1 = 4, price1 = 1;
	const int length2 = 20, width2 = 15, price2 = 1000;
	Apartment::SquareType** squares1 = new Apartment::SquareType*[length1];
	for (int i = 0; i < length1; ++i) {
		squares1[i] = new Apartment::SquareType[width1];
		for (int j = 0; j < width1; ++j) {
			squares1[i][j] = Apartment::EMPTY;
		}
	}
	Apartment::SquareType** rooms4 = new Apartment::SquareType*[length2];
	for (int i = 0; i < length2; i++) {
		rooms4[i] = new Apartment::SquareType[width2];
		for (int j = 0; j < width2; j++) {
			rooms4[i][j] = Apartment::EMPTY;
		}
	}
	for (int j = 0; j < length2; j++) {
		rooms4[j][width2 / 2] = Apartment::WALL;
	}
	for (int j = 0; j < width2; j++) {
		rooms4[length2 / 2][j] = Apartment::WALL;
	}
	ASSERT_NO_THROW(Apartment(squares1, length1, width1, price1));
	const Apartment apt1(squares1, length1, width1, price1);
	const Apartment apt3(rooms4, length2, width2, price2);

	ASSERT_EQUALS(length1, apt1.getLength());
	ASSERT_EQUALS(width1, apt1.getWidth());
	ASSERT_EQUALS(price1, apt1.getPrice());
	ASSERT_EQUALS(length1 * width1, apt1.getTotalArea());

	ASSERT_EQUALS(length2, apt3.getLength());
	ASSERT_EQUALS(width2, apt3.getWidth());
	ASSERT_EQUALS(price2, apt3.getPrice());
	ASSERT_EQUALS(length2 * width2 - (width2 + length2 - 1),
			apt3.getTotalArea());

	Apartment apt4(rooms4, length2, width2, price2);
	{
		const Apartment tmp(squares1, length1, width1, price1);
		apt4 = tmp;
	}

	deleteSquares(squares1, length1);
	deleteSquares(rooms4, length2);
	return true;
}

bool apartmentOperatotsTest() {
	const int length1 = 10, width1 = 10, price1 = 700;
	Apartment::SquareType **wall_empty = new Apartment::SquareType*[length1];
	for (int i = 0; i < length1; i++) {
		wall_empty[i] = new Apartment::SquareType[width1];
		for (int j = 0; j < width1; j++) {
			if (j % 2 == 0) {
				wall_empty[i][j] = Apartment::WALL;
			} else {
				wall_empty[i][j] = Apartment::EMPTY;
			}
		}
	}

	const int length2 = 10, width2 = 10, price2 = 1000;
	Apartment::SquareType** rooms4 = new Apartment::SquareType*[length2];
	for (int i = 0; i < length2; i++) {
		rooms4[i] = new Apartment::SquareType[width2];
		for (int j = 0; j < width2; j++) {
			rooms4[i][j] = Apartment::EMPTY;
		}
	}
	for (int j = 0; j < length2; j++) {
		rooms4[j][width2 / 2] = Apartment::WALL;
	}
	for (int j = 0; j < width2; j++) {
		rooms4[length2 / 2][j] = Apartment::WALL;
	}

	const int length3 = 10, width3 = 20, price3 = 1000;
	Apartment::SquareType **chess = new Apartment::SquareType*[length3];
	for (int i = 0; i < length3; i++) {
		chess[i] = new Apartment::SquareType[width3];
		for (int j = 0; j < width3; j++) {
			if (i % 2 == j % 2) {
				chess[i][j] = Apartment::EMPTY;
			} else {
				chess[i][j] = Apartment::WALL;
			}
		}
	}

	const int length4 = 20, width4 = 10, price4 = 1000;
	Apartment::SquareType** empty = new Apartment::SquareType*[length4];
	for (int i = 0; i < length4; ++i) {
		empty[i] = new Apartment::SquareType[width1];
		for (int j = 0; j < width4; ++j) {
			empty[i][j] = Apartment::EMPTY;
		}
	}

	const int length5 = 11, width5 = 9, price5 = 1000;
	Apartment::SquareType** empty2 = new Apartment::SquareType*[length5];
	for (int i = 0; i < length5; ++i) {
		empty2[i] = new Apartment::SquareType[width5];
		for (int j = 0; j < width5; ++j) {
			empty2[i][j] = Apartment::EMPTY;
		}
	}

	Apartment we_ap(wall_empty, length1, width1, price1);
	Apartment rooms4_ap(rooms4, length2, width2, price2);
	Apartment chess_ap(chess, length3, width3, price3);
	Apartment empty1_ap(empty, length4, width4, price4);
	Apartment empty2_ap(empty2, length5, width5, price5);
	ASSERT_EQUALS(false, rooms4_ap < rooms4_ap);
	ASSERT_EQUALS(true, rooms4_ap < we_ap);
	ASSERT_EQUALS(false, we_ap < rooms4_ap);


	Apartment rooms4_ap_copy(rooms4_ap);
	ASSERT_EQUALS(81, rooms4_ap_copy.getTotalArea());
	Apartment chess_ap_copy(chess_ap);
	ASSERT_EQUALS(100, chess_ap_copy.getTotalArea());

	rooms4_ap_copy += chess_ap_copy;
	ASSERT_EQUALS(length2, rooms4_ap_copy.getLength());
	ASSERT_EQUALS(width2 + width3, rooms4_ap_copy.getWidth());
	ASSERT_EQUALS(price2 + price3, rooms4_ap_copy.getPrice());
	ASSERT_EQUALS(181, rooms4_ap_copy.getTotalArea());

	const int length6 = length2, width6 = width2 + width3;
	Apartment::SquareType** sum2and3 = new Apartment::SquareType*[length6];
	for (int i = 0; i < length6; i++) {
		sum2and3[i] = new Apartment::SquareType[width6];
		for (int j = 0; j < width6; j++) {
			sum2and3[i][j] = Apartment::WALL;
		}
	}
	for (int i = 0; i < length2; i++) {
		for (int j = 0; j < width2; j++) {
			sum2and3[i][j] = Apartment::EMPTY;
		}
	}
	for (int j = 0; j < length2; j++) {
		sum2and3[j][width2 / 2] = Apartment::WALL;
	}
	for (int j = 0; j < width2; j++) {
		sum2and3[length2 / 2][j] = Apartment::WALL;
	}
	for (int i = 0; i < length2; i++) {
		for (int j = width2; j < width2 + width3; j++) {
			if (i % 2 == j % 2) {
				sum2and3[i][j] = Apartment::EMPTY;
			} else {
				sum2and3[i][j] = Apartment::WALL;
			}
		}
	}

	for (int i = 0; i < length6; i++) {
		for (int j = 0; j < width6; j++) {
			ASSERT_EQUALS(sum2and3[i][j], rooms4_ap_copy(i,j));
		}
	}

	Apartment rooms4_ap_copy2(rooms4_ap);
	ASSERT_EQUALS(81, rooms4_ap_copy2.getTotalArea());
	Apartment empty1_copy(empty1_ap);
	ASSERT_EQUALS(200, empty1_copy.getTotalArea());

	rooms4_ap_copy2 += empty1_copy;
	ASSERT_EQUALS(length2 + length4, rooms4_ap_copy2.getLength());
	ASSERT_EQUALS(width2, rooms4_ap_copy2.getWidth());
	ASSERT_EQUALS(price2 + price3, rooms4_ap_copy2.getPrice());
	ASSERT_EQUALS(281, rooms4_ap_copy2.getTotalArea());

	const int length7 = length2 + length4, width7 = width2;
	Apartment::SquareType** sum2and4 = new Apartment::SquareType*[length7];
	for (int i = 0; i < length7; i++) {
		sum2and4[i] = new Apartment::SquareType[width7];
		for (int j = 0; j < width7; j++) {
			sum2and4[i][j] = Apartment::EMPTY;
		}
	}
	for (int j = 0; j < length2; j++) {
		sum2and4[j][width2 / 2] = Apartment::WALL;
	}
	for (int j = 0; j < width2; j++) {
		sum2and4[length2 / 2][j] = Apartment::WALL;
	}

	for (int i = 0; i < length7; i++) {
		for (int j = 0; j < width7; j++) {
			ASSERT_EQUALS(sum2and4[i][j], rooms4_ap_copy2(i, j));
		}
	}

	Apartment rooms4_ap_copy3(rooms4_ap);
	Apartment rooms4_ap_copy4(rooms4_ap);
	
	rooms4_ap_copy3 += rooms4_ap_copy4;
	ASSERT_EQUALS(false, rooms4_ap_copy3 < rooms4_ap_copy4);
	ASSERT_EQUALS(true, rooms4_ap_copy4 < rooms4_ap_copy3);

	ASSERT_EQUALS(length2 + length2, rooms4_ap_copy3.getLength());
	ASSERT_EQUALS(width2, rooms4_ap_copy3.getWidth());
	ASSERT_EQUALS(price2 + price2, rooms4_ap_copy3.getPrice());
	ASSERT_EQUALS(162, rooms4_ap_copy3.getTotalArea());

	const int length8 = length2 + length2, width8 = width2;
	Apartment::SquareType** sum2and2 = new Apartment::SquareType*[length8];
	for (int i = 0; i < length8; i++) {
		sum2and2[i] = new Apartment::SquareType[width8];
		for (int j = 0; j < width8; j++) {
			sum2and2[i][j] = Apartment::EMPTY;
		}
	}
	for (int j = 0; j < length2 + length2; j++) {
		sum2and2[j][width2 / 2] = Apartment::WALL;
	}
	for (int j = 0; j < width8; j++) {
		sum2and2[length2 / 2][j] = Apartment::WALL;
		sum2and2[length2 + length2 / 2][j] = Apartment::WALL;
	}

	for (int i = 0; i < length8; i++) {
		for (int j = 0; j < width8; j++) {
			ASSERT_EQUALS(sum2and2[i][j], rooms4_ap_copy3(i, j));
		}
	}

	rooms4_ap_copy4 += rooms4_ap_copy4 += rooms4_ap_copy4;
	ASSERT_EQUALS(4 * length2, rooms4_ap_copy4.getLength());
	ASSERT_EQUALS(width2, rooms4_ap_copy4.getWidth());
	ASSERT_EQUALS(4*price2, rooms4_ap_copy4.getPrice());
	ASSERT_EQUALS(4*81, rooms4_ap_copy4.getTotalArea());

	ASSERT_EQUALS(rooms4_ap_copy4.getLength(), (rooms4_ap + rooms4_ap + rooms4_ap + rooms4_ap).getLength());
	ASSERT_EQUALS(rooms4_ap_copy4.getWidth(), (rooms4_ap + rooms4_ap).getWidth());
	ASSERT_EQUALS(3 * price2, (rooms4_ap + rooms4_ap + rooms4_ap).getPrice());
	ASSERT_EQUALS(4 * 81, (rooms4_ap + rooms4_ap + rooms4_ap + rooms4_ap).getTotalArea());


	Apartment rooms4_ap_copy5(rooms4_ap);
	ASSERT_EQUALS(81, rooms4_ap_copy5.getTotalArea());
	Apartment empty2_copy(empty2_ap);
	ASSERT_EQUALS(99, empty2_copy.getTotalArea());

	empty2_copy += rooms4_ap_copy5;

	const int length9 = length2 + length5, width9 = width2 > width5 ? width2 : width5;
	Apartment::SquareType** sum2and5 = new Apartment::SquareType*[length9];
	for (int i = 0; i < length9; i++) {
		sum2and5[i] = new Apartment::SquareType[width9];
		for (int j = 0; j < width9; j++) {
			sum2and5[i][j] = Apartment::WALL;
		}
	}
	for (int i = 0; i < length5; i++) {
		for (int j = 0; j < width5; j++) {
			sum2and5[i][j] = Apartment::EMPTY;
		}
	}
	for (int i = length5; i < length9; i++) {
		for (int j = 0; j < width2; j++) {
			sum2and5[i][j] = Apartment::EMPTY;
		}
	}
	for (int j = length5; j < length9; j++) {
		sum2and5[j][width2 / 2] = Apartment::WALL;
	}
	for (int j = 0; j < width2; j++) {
		sum2and5[length5 + length2 / 2][j] = Apartment::WALL;
	}

	for (int i = 0; i < length9; i++) {
		for (int j = 0; j < width9; j++) {
			ASSERT_EQUALS(sum2and5[i][j], empty2_copy(i, j));
		}
	}

	deleteSquares(wall_empty, length1);
	deleteSquares(rooms4, length2);
	deleteSquares(chess, length3);
	deleteSquares(empty, length4);
	deleteSquares(empty2, length5);
	deleteSquares(sum2and3, length6);
	deleteSquares(sum2and4, length7);
	deleteSquares(sum2and2, length8);
	deleteSquares(sum2and5, length9);


	return true;
}

int main() {
	RUN_TEST(apartmentTestExample);
	RUN_TEST(apartmentCtorsTest);
	RUN_TEST(apartmentFunctionsTest);
	RUN_TEST(apartmentOperatotsTest);
	return true;
}
