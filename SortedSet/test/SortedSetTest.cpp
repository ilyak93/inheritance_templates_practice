#include <cstdlib>
#include "SortedSet.h"
#include "MtmTst.h"
#include <iostream>

static const int numElements = 10;
static const int numElements2 = 500;

struct Int {
	int i;

	Int(int i) :
			i(i) {
	}

	operator int() const {
		return i;
	}
};

class IntCompare {
public:
	bool operator()(const Int& i1, const Int& i2) const {
		return static_cast<int>(i1) < static_cast<int>(i2);
	}
};

bool sortedSetTestExample() {
	ASSERT_NO_THROW((SortedSet<Int, IntCompare>()));
	SortedSet<Int, IntCompare> s;
	for (int i = numElements; i > 0; --i) {
		ASSERT_EQUALS(numElements - i, s.size());
		ASSERT_EQUALS(true, s.insert(i));
	}
	for (int i = 2; i <= numElements; i += 2) {
//		std::cout << "========\n";
		ASSERT_EQUALS(true, s.remove(i));
		ASSERT_EQUALS(numElements - i / 2, s.size());
	}

	int i = 1;
	for (SortedSet<Int, IntCompare>::iterator it = s.begin(); it != s.end();
			++it) {
		ASSERT_EQUALS(i, *it);
		i += 2;
	}

	return true;
}

bool sortedSetConstuctorTest() {
	ASSERT_NO_THROW((SortedSet<int, IntCompare>()));
	SortedSet<int, IntCompare> set1; // deleted after the function ends
	int arr1[] = { -6, 0, 5, 7 };
	int arr2[] = { 5, 0, 7, -6 };
	int n = 4;
	for (int i = 0; i <= n - 1; i++) {
		ASSERT_EQUALS(true, set1.insert(arr2[i]));
	}

	ASSERT_NO_THROW((SortedSet<int, IntCompare>(set1)));
	SortedSet<int, IntCompare>* set1Copy = new SortedSet<int, IntCompare>(set1);

	SortedSet<int, IntCompare>::iterator it1 = set1Copy->begin();
	for (int i = 0; i <= n - 1; i++) {
		ASSERT_EQUALS(arr1[i], *(it1++));
	}

	delete set1Copy;
	return true;
}
bool sortedSetAssignTest() {
	SortedSet<int, IntCompare> set1; // deleted after the function ends
	int arr1[] = { -6, 0, 5, 7 };
	int arr2[] = { 50, 30, 20, -10 };
	int n = 4;
	for (int i = 0; i < n; i++) {
		ASSERT_EQUALS(true, set1.insert(arr1[i]));
	}

	SortedSet<int, IntCompare> set2; // deleted after the function ends
	for (int i = 0; i < n; i++) {
		ASSERT_EQUALS(true, set2.insert(arr2[i]));
	}
	set2 = set1;

	SortedSet<int, IntCompare>::iterator it1 = set1.begin();
	SortedSet<int, IntCompare>::iterator it2 = set2.begin();
	for (int i = 0; i < n; i++) {
		ASSERT_EQUALS(*(it1++), *(it2++));
	}
	return true;
}

bool sortedSetIteratorTest() {
	SortedSet<int, IntCompare> set1; // deleted after the function ends
	SortedSet<int, IntCompare>::iterator it1 = set1.begin();

	ASSERT_EQUALS(set1.begin(), set1.end());
	ASSERT_EQUALS(true, set1.insert(60));
	it1 = set1.begin();
	ASSERT_EQUALS(60, *(it1));
	ASSERT_EQUALS(true, set1.insert(70));
	it1 = set1.begin();
	ASSERT_EQUALS(60, *(it1)); // still the begin
	it1 = set1.begin();
	ASSERT_EQUALS(true, set1.insert(50));
	it1 = set1.begin();
	ASSERT_EQUALS(50, *(it1++)); // still the begin
	ASSERT_EQUALS(60, *(it1++));
	ASSERT_EQUALS(70, *(it1));
	ASSERT_EQUALS(true, set1.insert(55));
	it1 = set1.begin();
	it1++;
	ASSERT_EQUALS(55, *(it1++));
	it1++;
	ASSERT_EQUALS(set1.end(), ++it1);
	return true;
}

bool sortedSetFindTest() {
	SortedSet<int, IntCompare> set1; // deleted after the function ends
	int arr1[] = { 8, 55, 1, 3, 2, 34, 21, 5, 13 };
	int n1 = 9;
	for (int i = 0; i < n1; i++) {
		ASSERT_EQUALS(true, set1.insert(arr1[i]));
	}
	ASSERT_EQUALS(set1.begin(), set1.find(1));
	ASSERT_EQUALS(true, set1.insert(-1));
	ASSERT_EQUALS(set1.begin(), set1.find(-1));

	int arrNotInSet[] = { 89, 11, 20, 101 };
	int n2 = 4;
	for (int i = 0; i < n2; i++) {
		ASSERT_EQUALS(set1.end(), set1.find(arrNotInSet[i]));
	}

	SortedSet<int, IntCompare>::iterator it1 = set1.find(13);
	SortedSet<int, IntCompare>::iterator currentIterator = set1.begin();
	for (int i = 0; i < 6; i++) {
		currentIterator++;
	}
	ASSERT_EQUALS(it1, currentIterator);

	return true;
}

bool sortedSetInsertRemoveTest() {
	SortedSet<int, IntCompare> set1; // deleted after the function ends
	int arr1[] = { 8, 55, 1, 3, 2, 34, 21, 5, 13 };
	int n1 = 9;
	for (int i = 0; i < n1; i++) {
		ASSERT_EQUALS(true, set1.insert(arr1[i]));
	}
	int arr2[] = { 13, 5, 21, 8, 55, 89, 1, 3, 2, 144, 34, 21, 5, 13 };
	int n2 = 14;
	for (int i = 0; i < n2; i++) {
		if (i == 5 || i == 9) {
			ASSERT_EQUALS(true, set1.insert(arr2[i]));
		}
		ASSERT_EQUALS(false, set1.insert(arr2[i]));
	}
	int arr1Sorted[] = { 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144 };
	SortedSet<int, IntCompare>::iterator it1 = set1.begin();
	for (int i = 0; i < n1 + 2; i++) {
		ASSERT_EQUALS(arr1Sorted[i], *(it1++));
	}
	ASSERT_EQUALS(set1.end(), it1);
	//remove elements not in set
	int arrNotInSet[] = { 90, 11, 20, 101 };
	int n3 = 4;
	for (int i = 0; i < n3; i++) {
		ASSERT_EQUALS(false, set1.remove(arrNotInSet[i]));
	}
	ASSERT_EQUALS(true, set1.remove(1));
	ASSERT_EQUALS(2, *(set1.begin()));

	ASSERT_EQUALS(true, set1.remove(13));
	ASSERT_EQUALS(true, set1.remove(34));
	int arr1SortedRemoved[] = { 2, 3, 5, 8, 21, 55, 89, 144 };
	it1 = set1.begin();
	for (int i = 0; i < (n1 - 1); i++) {
		ASSERT_EQUALS(arr1SortedRemoved[i], *(it1++));
	}

	return true;
}

bool sortedSetSizeTest() {
	SortedSet<int, IntCompare> set1; // deleted after the function ends
	int arr1[] = { 8, 55, 89, 1, 3, 2, 144, 34, 21, 5, 13 };
	int n1 = 11;
	for (int i = 0; i < n1; i++) {
		ASSERT_EQUALS(true, set1.insert(arr1[i]));
	}
	ASSERT_EQUALS(n1, set1.size());
	ASSERT_EQUALS(false, set1.remove(111));
	ASSERT_EQUALS(n1, set1.size());

	for (int i = 0; i < n1; i++) {
		ASSERT_EQUALS(true, set1.remove(arr1[i]));
		ASSERT_EQUALS(n1 - (i + 1), set1.size());
	}
	for (int i = n1 - 1; i >= 0; i--) {
		ASSERT_EQUALS(true, set1.insert(arr1[i]));
		ASSERT_EQUALS(n1 - i, set1.size());
	}
	return true;
}
bool sortedSetMathOperatorsTest() {
	SortedSet<int, IntCompare> set; // deleted after the function ends
	int arr[] = { 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144 };
	int n = 11;
	for (int i = 0; i < n; i++) {
		ASSERT_EQUALS(true, set.insert(arr[i]));
	}
	SortedSet<int, IntCompare> set1; // deleted after the function ends
	int arr1[] = { 1, 3, 5, 13, 21, 55, 89 };
	int n1 = 7;
	for (int i = 0; i < n1; i++) {
		ASSERT_EQUALS(true, set1.insert(arr1[i]));
	}
	SortedSet<int, IntCompare> set2; // deleted after the function ends
	int n2 = 4;
	int arr2[] = { 2, 8, 34, 144 };
	for (int i = 0; i < n2; i++) {
		ASSERT_EQUALS(true, set2.insert(arr2[i]));
	}
	SortedSet<int, IntCompare> intersectionSet = set & set1; //intersectionSet=set1
	SortedSet<int, IntCompare>::iterator it1 = intersectionSet.begin();
	for (int i = 0; i < n1; i++) {
		ASSERT_EQUALS(arr1[i], *(it1++)); //checking that intersectionSet==set1
	}
	intersectionSet = set2 & set2; //intersectionSet=set2
	it1 = intersectionSet.begin();
	for (int i = 0; i < n2; i++) {
		ASSERT_EQUALS(arr2[i], *(it1++)); //checking that intersectionSet=set2
	}
	intersectionSet = set2 & set; //intersectionSet=set2
	it1 = intersectionSet.begin();
	for (int i = 0; i < n2; i++) {
		ASSERT_EQUALS(arr2[i], *(it1++)); //checking that intersectionSet=set2
	}

	SortedSet<int, IntCompare> unrelevantSet; // deleted after the function ends
	int arrOut[] = { 111, 555, 888 };
	int nOut = 3;
	for (int i = 0; i < nOut; i++) {
		ASSERT_EQUALS(true, unrelevantSet.insert(arrOut[i]));
	}
	unrelevantSet = unrelevantSet & set2; //unrelevantSet={}
	ASSERT_EQUALS(unrelevantSet.begin(), unrelevantSet.end()); // checking that unrelevantSet={}

	intersectionSet = set2 & unrelevantSet; //intersectionSet={}
	ASSERT_EQUALS(intersectionSet.begin(), intersectionSet.end()); // checking that intersectionSet={}

	SortedSet<int, IntCompare> unionSet = intersectionSet | set1; //unionSet={}|set1=set1
	set1 = set1 | intersectionSet; //set1=set1|{}=set1
	it1 = set1.begin();
	for (int i = 0; i < n1; i++) {
		ASSERT_EQUALS(arr1[i], *(it1++)); //checking that set is unchanged
	}
	
	unionSet = (set | set1) | set2; //unionSet=set
	it1 = set.begin();
	for (int i = 0; i < n; i++) {
		ASSERT_EQUALS(arr[i], *(it1++)); //checking that set is unchanged
	}
	unionSet = (set & set1) | (set & set2); //unionSet=set
	it1 = set.begin();
	for (int i = 0; i < n; i++) {
		ASSERT_EQUALS(arr[i], *(it1++)); //checking that set is unchanged
	}
	
	
	SortedSet<int, IntCompare> complementSet = set1 - set1; //complementSet={}
	ASSERT_EQUALS(complementSet.begin(), complementSet.end()); // checking that complementSet={}
	complementSet = set - set1; //complementSet=set2

	it1 = complementSet.begin();
	SortedSet<int, IntCompare>::iterator it2 = set2.begin();
	for (int i = 0; i < n2; i++) {
		ASSERT_EQUALS(*(it1++), *(it2++)); //checking that set2==complementSet
	}

	SortedSet<int, IntCompare> symmetricSet = set ^ set; //set={}
	ASSERT_EQUALS(symmetricSet.begin(), symmetricSet.end());

	symmetricSet = set ^ set1; //symmetricSet=set2
	it1 = set2.begin();
	for (int i = 0; i < n2; i++) {
		ASSERT_EQUALS(arr2[i], *(it1++)); //checking that symmetricSet=set2
	}

	symmetricSet = set1 ^ set2; //symmetricSet=set
	it1 = set.begin();
	for (int i = 0; i < n; i++) {
		ASSERT_EQUALS(arr[i], *(it1++)); //checking that symmetricSet=set
	}

	SortedSet<int, IntCompare> crazySet = (((((((unrelevantSet ^ set) - set1)
			^ set2) - unrelevantSet) & set) | set2) - set1) | set1; //crazySet=set, holy cow
	it1 = crazySet.begin();
	for (int i = 0; i < n; i++) {
		ASSERT_EQUALS(arr[i], *(it1++)); //checking that crazySet=set
	}

	crazySet = (crazySet & unrelevantSet) | ((set1 ^ set2) & (set | set));
	
	return true;
}

bool sortedSetConstructorDeconstructorTest(){
	ASSERT_NO_THROW((SortedSet<Int , IntCompare>()));
	SortedSet<Int , IntCompare> set;
	ASSERT_EQUALS(true , set.insert(1));
	ASSERT_EQUALS(true , set.insert(-2));
	ASSERT_EQUALS(true , set.insert(3));

	ASSERT_NO_THROW((SortedSet<Int , IntCompare>(set)));

	SortedSet<Int , IntCompare>* setCopy = new SortedSet<Int , IntCompare>(set);

	SortedSet<Int , IntCompare>::iterator iter = setCopy->begin();

	ASSERT_EQUALS(-2 , *(iter++));
	ASSERT_EQUALS(1 , *(iter++));
	ASSERT_EQUALS(3 , *(iter));

	delete setCopy;
	return true;
}

bool sortedSetAssignmentTest(){
	SortedSet<Int , IntCompare> set;
	ASSERT_EQUALS(true , set.insert(1));
	ASSERT_EQUALS(true , set.insert(-2));
	ASSERT_EQUALS(true , set.insert(3));

	SortedSet<Int , IntCompare> set2;
	ASSERT_EQUALS(true , set2.insert(3));
	ASSERT_EQUALS(true , set2.insert(66));
	ASSERT_EQUALS(true , set2.insert(88));

	set2 = set;

	ASSERT_EQUALS(true , set.remove(-2));
	ASSERT_EQUALS(-2 , *(set2.begin()));

	return true;
}

bool sortedSetIteratorFunctionsTest(){
	SortedSet<Int , IntCompare> set;
	ASSERT_EQUALS(set.end() , set.begin());
	ASSERT_EQUALS(true , set.insert(452));
	SortedSet<Int , IntCompare>::iterator it = set.begin();
	ASSERT_EQUALS(452 , *it);
	ASSERT_EQUALS(true , set.insert(3));
	ASSERT_EQUALS(true , set.insert(532));
	it = set.begin();
	ASSERT_EQUALS(3 , *(it++));
	ASSERT_EQUALS(452 , *(it++));
	ASSERT_EQUALS(532 , *(it++));
	ASSERT_EQUALS(set.end() , it);
	return true;
}

bool sortedSetFindTest2(){
	SortedSet<Int , IntCompare> set;

	ASSERT_EQUALS(true , set.insert(412));
	ASSERT_EQUALS(true , set.insert(2));
	ASSERT_EQUALS(true , set.insert(654));
	ASSERT_EQUALS(true , set.insert(-4234));
	ASSERT_EQUALS(true , set.insert(32));
	ASSERT_EQUALS(true , set.insert(31415));

	ASSERT_EQUALS(set.end() , set.find(1));
	ASSERT_EQUALS(set.begin() , set.find(-4234));

	SortedSet<Int , IntCompare>::iterator begin = set.begin();
	for(int i = 0 ; i < 4; i++ , begin++);
	ASSERT_EQUALS(set.find(654) , begin);

	ASSERT_EQUALS(true , set.insert(-99999));
	ASSERT_EQUALS(set.begin() , set.find(-99999));

	return true;
}

bool sortedSetInsertRemoveTest2(){
	SortedSet<Int , IntCompare> set;
	Int array[] = { 412 , 2 , 654 , -4234 , 32 , 31415 };
	for(int i = 0 ; i < 6 ; i++){
		ASSERT_EQUALS(true , set.insert(array[i]));
	}
	ASSERT_EQUALS(false , set.insert(31415));
	ASSERT_EQUALS(false , set.insert(654));
	SortedSet<Int , IntCompare>::iterator begin = set.begin();
	ASSERT_EQUALS(-4234 , *(begin++));
	ASSERT_EQUALS(2 , *(begin++));
	ASSERT_EQUALS(32 , *(begin++));
	ASSERT_EQUALS(412 , *(begin++));
	ASSERT_EQUALS(654 , *(begin++));
	ASSERT_EQUALS(31415 , *(begin++));

	ASSERT_EQUALS(false , set.remove(271818));
	ASSERT_EQUALS(true , set.remove(-4234));
	ASSERT_EQUALS(2 , *(set.begin()));

	ASSERT_EQUALS(true , set.remove(412));
	begin = set.begin();
	for(int i = 0 ; i < 2; i++ , begin++);
	ASSERT_EQUALS(654 , *begin);
	ASSERT_EQUALS(true , set.remove(31415)); //Check if removing the last element leads to a crash....
	return true;
}

bool sortedSetGetSizeTest(){
	SortedSet<Int , IntCompare> set;
	Int array[] = { 412 , 2 , 654 , -4234 , 32 , 31415 };
	for(int i = 0 ; i < 6 ; i++){
		ASSERT_EQUALS(true , set.insert(array[i]));
	}

	ASSERT_EQUALS(6 , set.size());
	ASSERT_EQUALS(false , set.remove(31));
	ASSERT_EQUALS(6 , set.size());
	set.remove(412);
	set.remove(2);
	set.remove(654);
	set.remove(-4234);
	set.remove(32);
	ASSERT_EQUALS(1 , set.size());
	set.remove(31415);
	ASSERT_EQUALS(0 , set.size());
	set.insert(4312);
	ASSERT_EQUALS(1 , set.size());
	return true;
}

bool sortedSetSetOperatorsTest(){
	SortedSet<Int , IntCompare> setEven;
	SortedSet<Int , IntCompare> setOdd;
	SortedSet<Int , IntCompare> setOneToTen;

	for(int i = 0 ; i < 10 ; i++){
		if(i % 2 == 0){
			setEven.insert(i);
		}
		else{
			setOdd.insert(i);
		}
		setOneToTen.insert(i);
	}

	SortedSet<Int , IntCompare> intersectionSet = (setEven & setOdd); //Should be the same as setOdd & setEven
	ASSERT_EQUALS(intersectionSet.end() , intersectionSet.begin());
	intersectionSet = (setOdd & setEven); //Should be the same as setOdd & setEven
	ASSERT_EQUALS(intersectionSet.end() , intersectionSet.begin());

	intersectionSet = setEven & setEven; //Intersection of the same set = the same set.
	SortedSet<Int , IntCompare>::iterator it = intersectionSet.begin();
	for(int i = 0; i < 10 ; i+=2){ ASSERT_EQUALS(i , *(it++)); }

	SortedSet<Int , IntCompare> unionSet = (setEven | setOdd);
	it = unionSet.begin();
	for(int i = 0; i < 10 ; i++){ ASSERT_EQUALS(i , *(it++)); }

	unionSet = (setOdd | setEven);
	it = unionSet.begin();
	for(int i = 0; i < 10 ; i++){ ASSERT_EQUALS(i , *(it++)); }

	unionSet = (setEven | setEven);
	it = unionSet.begin();
	for(int i = 0 ; i < 10 ; i+=2){ ASSERT_EQUALS(i , *(it++)); }

	SortedSet<Int , IntCompare> complementSet = setEven - setOdd; //Should still be setEven
	it = complementSet.begin();
	for(int i = 0; i < 10 ; i+=2){ ASSERT_EQUALS(i , *(it++)); }

	complementSet = setOneToTen - setEven; //Should be the same as setOdd
	it = complementSet.begin();
	for(int i = 1; i < 10 ; i+=2){ ASSERT_EQUALS(i , *(it++)); }

	complementSet = setOneToTen - setOneToTen;
	ASSERT_EQUALS(complementSet.end() , complementSet.begin()); //Empty set

	SortedSet<Int , IntCompare> symComplementSet = setEven ^ setOdd; //Should be like setOneToTen
	it = symComplementSet.begin();
	for(int i = 0; i < 10 ; i++){ ASSERT_EQUALS(i , *(it++)); }

	//These are all odd numbers, so the symmetrical set of even and odd should not include those.
	setEven.insert(5); //Let's mess with the eveness...
	setEven.insert(1); //Let's mess with the eveness...
	setEven.insert(7); //Let's mess with the eveness...

	symComplementSet = setEven ^ setOdd;
	it = symComplementSet.begin();
	for(int i = 0 ; i < 10 ; i++){
		if(i == 1 || i == 5 || i == 7){
			i++;
		}
		ASSERT_EQUALS(i , *(it++));
	}

	symComplementSet = setEven ^ setEven;
	ASSERT_EQUALS(symComplementSet.end() , symComplementSet.begin());

	SortedSet<Int , IntCompare> emptySet;
	intersectionSet = setOneToTen & emptySet; // Should be empty
	unionSet = setOneToTen | emptySet; // Should be OneToTen
	complementSet = setOneToTen - emptySet; // Should be OneToTen
	symComplementSet = setOneToTen ^ emptySet; // Should be OneToTen

	ASSERT_EQUALS(intersectionSet.begin() , intersectionSet.end());
	it = unionSet.begin();
	SortedSet<Int , IntCompare>::iterator it1 = complementSet.begin();
	SortedSet<Int , IntCompare>::iterator it2 = symComplementSet.begin();
	for(int i = 0 ; i < 10 ; i++){
		ASSERT_EQUALS(i , *(it++));
		ASSERT_EQUALS(i , *(it1++));
		ASSERT_EQUALS(i , *(it2++));
	}

	return true;
}

bool sortedSetTest() {
	RUN_TEST(sortedSetTestExample);
	RUN_TEST(sortedSetConstuctorTest);
	RUN_TEST(sortedSetAssignTest);
	RUN_TEST(sortedSetIteratorTest);
	RUN_TEST(sortedSetFindTest);
	RUN_TEST(sortedSetInsertRemoveTest);
	RUN_TEST(sortedSetSizeTest);
	RUN_TEST(sortedSetMathOperatorsTest);
	RUN_TEST(sortedSetConstructorDeconstructorTest);
	RUN_TEST(sortedSetAssignmentTest);
	RUN_TEST(sortedSetIteratorFunctionsTest);
	RUN_TEST(sortedSetFindTest2);
	RUN_TEST(sortedSetInsertRemoveTest2);
	RUN_TEST(sortedSetGetSizeTest);
	RUN_TEST(sortedSetSetOperatorsTest);
	return true;
}

int main() {
	setvbuf(stdout, NULL, _IONBF, 0);
	sortedSetTest();
	return 0;
}
