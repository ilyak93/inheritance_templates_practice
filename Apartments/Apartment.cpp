#include <iostream>
#include <cstdlib>
#include "Apartment.h"

bool isSquaresValid(Apartment::SquareType** squares, int length, int width) {
	if (squares == NULL || length < 1 || width < 1)
		return false;
	for (int l = 0; l < length; l++) {
		for (int w = 0; w < width; w++) {
			if (squares[l][w] < Apartment::EMPTY
					|| squares[l][w] > Apartment::WALL) {
				return false;
			}
		}
	}
	return true;
}

Apartment::Apartment(int length, int width, int price) :
		squares(NULL), length(length), width(width), price(price) {
	if (length < 1 || width < 1 || price < 0)
		throw Apartment::IllegalArgException();
	squares = new SquareType*[length];
	for (int l = 0; l < length; l++) {
		squares[l] = new SquareType[width];
		for (int w = 0; w < width; w++) {
			this->squares[l][w] = WALL;
		}
	}
}

Apartment::Apartment(SquareType **squares, int length, int width, int price) :
		squares(NULL), length(length), width(width), price(price) {
	if (isSquaresValid(squares, length, width) == false || price < 0)
		throw Apartment::IllegalArgException();
	this->squares = new SquareType*[length];
	for (int l = 0; l < length; l++) {
		this->squares[l] = new SquareType[width];
		for (int w = 0; w < width; w++) {
			this->squares[l][w] = squares[l][w];
		}
	}
}

Apartment::Apartment(const Apartment& apartment) {
	this->squares = NULL;
	*this = Apartment(apartment.squares, apartment.length, apartment.width,
			apartment.price);
}

Apartment::~Apartment() {
	if (this->squares != NULL) {
		for (int l = 0; l < length; l++) {
			delete[] squares[l];
		}
		delete[] squares;
	}
}
Apartment& Apartment::operator=(const Apartment& apartment) {
	SquareType** squares_copy = new SquareType*[apartment.length];
	for (int l = 0; l < apartment.length; l++) {
		squares_copy[l] = new SquareType[apartment.width];
		for (int w = 0; w < apartment.width; w++) {
			squares_copy[l][w] = apartment.squares[l][w];
		}
	}
	this->~Apartment();
	this->squares = squares_copy;
	this->price = apartment.price;
	this->length = apartment.length;
	this->width = apartment.width;
	return *this;
}

Apartment& Apartment::operator+=(const Apartment& apartment) {
	if (this->width == apartment.width || length != apartment.length) {
		int max_width = width > apartment.width ? width : apartment.width;
		//int min_width = length == max_width ? apartment.width : width;
		Apartment united(length+apartment.length,max_width,price+apartment.price);
		for (int l = 0; l < length; l++) {
			for (int w = 0; w < width; w++) {
				united.squares[l][w] = squares[l][w];
			}
		}
		for (int l = length; l < united.length; l++) {
			for (int w = 0; w < apartment.width; w++) {
				united.squares[l][w] = apartment.squares[l - length][w];
			}
		}
		*this = united;
	} else {
		Apartment united(length,width+apartment.width,price+apartment.price);
		for (int l = 0; l < united.length; l++) {
			for (int w = 0; w < width; w++) {
				united.squares[l][w] = squares[l][w];
			}
			for (int w = width; w < united.width; w++) {
				united.squares[l][w] = apartment.squares[l][w - width];
			}
		}
		*this = united;
	}
	return *this;
}

/*Apartment& Apartment::operator+=(const Apartment& apartment) {
	if (this->width == apartment.width || length != apartment.length) {
		int max_length = length > apartment.length ? length : apartment.length;
		int min_length = length == max_length ? apartment.length : length;
		Apartment united(max_length, width + apartment.width,
				price + apartment.price);
		for (int l = 0; l < min_length; l++) {
			for (int w = 0; w < apartment.width; w++) {
				united.squares[l][w] = apartment.squares[l][w];
			}
			for (int w = apartment.width; w < apartment.width + width; w++) {
				united.squares[l][w] = squares[l][w - apartment.width];
			}
		}
		*this = united;
	} else {
		Apartment united(length + apartment.length, width,
				price + apartment.price);
		for (int l = 0; l < length; l++) {
			for (int w = 0; w < width; w++) {
				united.squares[l][w] = squares[l][w];
			}
		}
		for (int l = length; l < length + apartment.length; l++) {
			for (int w = 0; w < width; w++) {
				united.squares[l][w] = apartment.squares[l - length][w];
			}
		}
		*this = united;
	}
	return *this;
}*/

Apartment::SquareType& Apartment::operator()(const int i, const int j) {
	if (i < 0 || i >= length || j < 0 || j >= width)
		throw Apartment::OutOfApartmentBoundsException();
	return squares[i][j];
}

Apartment::SquareType Apartment::operator()(const int i, const int j) const {
	if (i >= length || j >= width)
		throw Apartment::OutOfApartmentBoundsException();
	return squares[i][j];
}

int Apartment::getTotalArea() const {
	int area = 0;
	for (int l = 0; l < length; l++) {
		for (int w = 0; w < width; w++) {
			if (squares[l][w] == EMPTY) {
				area++;
			}
		}
	}
	return area;
}
int Apartment::getPrice() const {
	return price;
}
int Apartment::getLength() const {
	return length;
}
int Apartment::getWidth() const {
	return width;
}

Apartment operator+(const Apartment& apartment1, const Apartment& apartment2) {
	Apartment sum(apartment1);
	return (sum += apartment2);
}
bool operator<(const Apartment& apartment1, const Apartment& apartment2) {
	int price1 = apartment1.getPrice(), price2 = apartment2.getPrice(), area1 =
			apartment1.getTotalArea(), area2 = apartment2.getTotalArea();
	return (price1 * area2 == price2 * area1) ? price1 < price2 : price1 * area2
		< price2 * area1;
}
