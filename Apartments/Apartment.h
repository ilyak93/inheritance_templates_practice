#ifndef MTM4_APARTMENT_H
#define MTM4_APARTMENT_H

#include <exception>

class Apartment {

public:
    class ApartmentException : public std::exception {};
    class IllegalArgException : public ApartmentException {};
    class OutOfApartmentBoundsException : public ApartmentException {};

    enum SquareType {EMPTY, WALL, NUM_SQUARE_TYPES};

    Apartment(int length, int width, int price);
    Apartment(SquareType **squares, int length, int width, int price);
	Apartment(const Apartment& apartment);
    ~Apartment();
    Apartment& operator=(const Apartment& apartment);
    Apartment& operator+=(const Apartment& apartment);
    SquareType& operator()(const int i, const int j);
	SquareType operator()(const int i, const int j) const;

    int getTotalArea() const;
    int getPrice() const;
    int getLength() const;
    int getWidth() const;

    private:
    	SquareType **squares;
		int length;
    	int width;
		int price;
};

/*****************************
 * External operator function
 ****************************/

Apartment operator+(const Apartment& apartment1, const Apartment& apartment2);
bool operator<(const Apartment& apartment1, const Apartment& apartment2);

#endif //MTM4_APARTMENT_H
