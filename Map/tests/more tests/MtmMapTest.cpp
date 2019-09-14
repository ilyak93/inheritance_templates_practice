#include "MtmMapTest.h"

#include "MtmTst.h"
#include "MtmMap.h"

using namespace mtm;

typedef MtmMap<int, int> IntMap;
typedef IntMap::Pair IntPair;
typedef IntMap::iterator IntMapIter;

bool mapIteratorTest() {

#ifdef MAP_ITER

	IntMap map1(-2);
	IntMap map2(-2);

	ASSERT_EQUALS(true, map1.begin() == map1.end());
	ASSERT_EQUALS(false, map1.begin() != map1.end());
	ASSERT_THROW(mtm::MapElementNotFoundException, *map1.begin());

	ASSERT_EQUALS(true, map1.begin() != map2.begin());
	ASSERT_EQUALS(true, map1.begin() != map2.end());
	ASSERT_EQUALS(true, map1.end() != map2.begin());
	ASSERT_EQUALS(true, map1.end() != map2.end());
	ASSERT_EQUALS(false, map1.begin() == map2.begin());
	ASSERT_EQUALS(false, map1.begin() == map2.end());
	ASSERT_EQUALS(false, map1.end() == map2.begin());
	ASSERT_EQUALS(false, map1.end() == map2.end());

	map1.insert(IntPair(1, 1));
	map1.insert(IntPair(2, 2));
	map1.insert(IntPair(3, 3));
	map2.insert(IntPair(3, 3));
	map2.insert(IntPair(2, 2));
	map2.insert(IntPair(1, 1));

	// check iterator of two different lists
	IntMapIter iter1 = map1.begin();
	IntMapIter iter2 = map2.begin();
	for (; iter1 != map1.end(); iter1++) {
		iter2 = map2.begin();
		for (; iter2 != map2.end(); iter2++) {
			ASSERT_EQUALS(true, iter1 != iter2);
			ASSERT_EQUALS(false, iter1 == iter2);
		}
		ASSERT_EQUALS(true, iter1 != iter2);
		ASSERT_EQUALS(false, iter1 == iter2);
	}
	ASSERT_EQUALS(true, iter1 != iter2);
	ASSERT_EQUALS(false, iter1 == iter2);

	// same test after copy constructor

	IntMap map3(-2);
	IntMap map4(map3);

	ASSERT_EQUALS(true, map3.begin() == map3.end());
	ASSERT_EQUALS(false, map3.begin() != map3.end());
	ASSERT_THROW(mtm::MapElementNotFoundException, *map3.begin());

	ASSERT_EQUALS(true, map3.begin() != map4.begin());
	ASSERT_EQUALS(true, map3.begin() != map4.end());
	ASSERT_EQUALS(true, map3.end() != map4.begin());
	ASSERT_EQUALS(true, map3.end() != map4.end());
	ASSERT_EQUALS(false, map3.begin() == map4.begin());
	ASSERT_EQUALS(false, map3.begin() == map4.end());
	ASSERT_EQUALS(false, map1.end() == map2.begin());
	ASSERT_EQUALS(false, map1.end() == map2.end());

	IntMap map5(-2);
	map5.insert(IntPair(1, 1));
	map5.insert(IntPair(2, 2));
	map5.insert(IntPair(3, 3));
	IntMap map6(map5);

	// check iterator of two different lists
	iter1 = map5.begin();
	iter2 = map6.begin();
	for (; iter1 != map5.end(); iter1++) {
		iter2 = map6.begin();
		for (; iter2 != map6.end(); iter2++) {
			ASSERT_EQUALS(true, iter1 != iter2);
			ASSERT_EQUALS(false, iter1 == iter2);
		}
		ASSERT_EQUALS(true, iter1 != iter2);
		ASSERT_EQUALS(false, iter1 == iter2);
	}
	ASSERT_EQUALS(true, iter1 != iter2);
	ASSERT_EQUALS(false, iter1 == iter2);

	map1.remove(1);
	map1.remove(2);
	map1.remove(3);
	map2.remove(1);
	map2.remove(2);
	map2.remove(3);

	map1.insert(IntPair(1, 10));
	map1.insert(IntPair(2, 20));
	map1.insert(IntPair(3, 30));
	map2.insert(IntPair(3, 13));
	map2.insert(IntPair(2, 12));
	map2.insert(IntPair(1, 11));

	ASSERT_EQUALS(true, map1.begin() == map1.begin());
	ASSERT_EQUALS(false, map2.begin() != map2.begin());
	ASSERT_EQUALS(false, map2.end() != map2.end());
	ASSERT_EQUALS(false, map1.end() != map1.end());

	iter1 = map1.begin();
	iter1++;
	++iter1;
	iter2 = map1.begin();
	ASSERT_EQUALS(false, iter1 == iter2);
	ASSERT_EQUALS(true, iter1 != iter2);
	++iter2;
	ASSERT_EQUALS(false, iter1 == iter2);
	ASSERT_EQUALS(true, iter1 != iter2);
	iter2++;
	ASSERT_EQUALS(true, iter1 == iter2);
	ASSERT_EQUALS(false, iter1 != iter2);

	// check ++ operator 1
	ASSERT_EQUALS(true, map1.begin() == map1.begin()++);
	ASSERT_EQUALS(false, map1.begin() != ((map1.begin())++));
	// check ++ operator 2
	ASSERT_EQUALS(false, map1.begin() == ++map1.begin());
	ASSERT_EQUALS(true, map1.begin() != ++map1.begin());
	// check ++ operator 3
	iter1 = ++(map1.begin()++);
	iter2 = (++map1.begin())++;
	ASSERT_EQUALS(true, iter1 == iter2);
	ASSERT_EQUALS(false, iter1 != iter2);

	// test values and dereference:
	iter1 = map1.begin();
	ASSERT_EQUALS(1, (*iter1).first);
	ASSERT_EQUALS(10, (*iter1).second);
	iter1++;
	ASSERT_EQUALS(2, (*iter1).first);
	ASSERT_EQUALS(20, (*iter1).second);
	++iter1;
	ASSERT_EQUALS(3, (*iter1).first);
	ASSERT_EQUALS(30, (*iter1).second);
	ASSERT_EQUALS(true, map1.end() == ++iter1);
	ASSERT_THROW(mtm::MapElementNotFoundException, *iter1);

	iter2 = map2.begin();
	ASSERT_EQUALS(1, (*iter2).first);
	ASSERT_EQUALS(11, (*iter2).second);
	iter2++;
	ASSERT_EQUALS(2, (*iter2).first);
	ASSERT_EQUALS(12, (*iter2).second);
	++iter2;
	ASSERT_EQUALS(3, (*iter2).first);
	ASSERT_EQUALS(13, (*iter2).second);
	ASSERT_EQUALS(true, map2.end() == ++iter2);

	iter1 = ++(++map1.begin());
	map1.insert(IntPair(5, 50));
	map1.insert(IntPair(0, 100));
	ASSERT_EQUALS(3, (*iter1).first);
	ASSERT_EQUALS(30, (*iter1).second);
	map1.remove(0);
	map1.remove(1);
	map1.remove(2);
	map1.remove(5);
	ASSERT_EQUALS(3, (*iter1).first);
	ASSERT_EQUALS(30, (*iter1).second);
	ASSERT_EQUALS(++map1.begin(), map1.end());

#endif /* MAP_ITER */

	return true;
}

bool mapSqaureBracketsTest() {
	IntMap map(-3);
	ASSERT_EQUALS(false, map.containsKey(-3));
	ASSERT_EQUALS(false, map.containsKey(1));
	map[1] = 7;
	ASSERT_EQUALS(true, map.containsKey(1));
	ASSERT_EQUALS(7, map[1]);
	map[2] = 5;
	ASSERT_EQUALS(5, map[2]);
	map[0] = 3;
	ASSERT_EQUALS(3, map[0]);
	IntMapIter iter = map.begin();
	ASSERT_EQUALS(0, (*iter).first);
	ASSERT_EQUALS(3, (*iter).second);
	iter++;
	ASSERT_EQUALS(1, (*iter).first);
	ASSERT_EQUALS(7, (*iter).second);
	++iter;
	ASSERT_EQUALS(2, (*iter).first);
	ASSERT_EQUALS(5, (*iter).second);
	iter++;
	ASSERT_EQUALS(map.end(), iter);
	ASSERT_EQUALS(3, map.size());

	int& tmp = map[5];
	ASSERT_EQUALS(tmp, -3);
	ASSERT_EQUALS(-3, map[5]);
	tmp = 7;
	ASSERT_EQUALS(7, map[5]);
	tmp = map[7];
	// make sure default value was not changed
	ASSERT_EQUALS(-3, map[7]);
	ASSERT_EQUALS(5, map.size());

	iter = map.begin();
	for (int i = 0; i < 4; i++) {
		iter++;
	}

	ASSERT_EQUALS(7, (*iter).first);
	ASSERT_EQUALS(-3, (*iter).second);
	map[7] = 5;
	ASSERT_EQUALS(7, (*iter).first);
	ASSERT_EQUALS(5, (*iter).second);
	ASSERT_EQUALS(5, map.size());
	map.remove(5);
	ASSERT_EQUALS(4, map.size());

	// override insert
	map.insert(IntPair(10, 11));
	map[10] = 12;
	ASSERT_EQUALS(12, map[10]);
	map.remove(10);
	map[10] = 12;
	map.insert(IntPair(10, 11));
	ASSERT_EQUALS(11, map[10]);
	// before insert

	return true;
}

class AbsIntWrapper {
public:
	// add default constructor to allow initializing comparer
	AbsIntWrapper() {
	}
	AbsIntWrapper(int val)
		: m_val(val) {
	}
	int m_val;

	// compare self
	bool operator()(AbsIntWrapper a, AbsIntWrapper b) const {
		int aAbs = (a.m_val >= 0 ? a.m_val : -a.m_val);
		int bAbs = (b.m_val >= 0 ? b.m_val : -b.m_val);
		return aAbs < bAbs;
	}
	// compare self
	bool operator<(AbsIntWrapper a) const {
		throw - 1;
	}
	bool operator>(AbsIntWrapper a) const {
		throw - 1;
	}
	bool operator>=(AbsIntWrapper a) const {
		throw - 1;
	}
	bool operator<=(AbsIntWrapper a) const {
		throw - 1;
	}
	bool operator==(AbsIntWrapper a) const {
		throw - 1;
	}
	bool operator!=(AbsIntWrapper a) const {
		throw - 1;
	}
};

typedef MtmMap<AbsIntWrapper, AbsIntWrapper, AbsIntWrapper> WrapperMap;
typedef WrapperMap::Pair WrapperPair;
typedef WrapperMap::iterator WrapperIterator;

bool mapComplicatedCompareTest() {
	WrapperMap map(AbsIntWrapper(1000));
	AbsIntWrapper obj(2);
	ASSERT_NO_THROW(map.insert(WrapperPair(obj, AbsIntWrapper(4)))); // [2, 4]
	ASSERT_NO_THROW(map[AbsIntWrapper(4)] = obj); // [2, 4] , [4, 2]
	ASSERT_EQUALS(2, map.size());
	ASSERT_NO_THROW(map.insert(WrapperPair(AbsIntWrapper(-2), AbsIntWrapper(8)))); // [2, 8] , [4, 2]
	ASSERT_NO_THROW(map.remove(AbsIntWrapper(-4))); // [2, 8]
	ASSERT_EQUALS(1, map.size());
	AbsIntWrapper res = map[AbsIntWrapper(10)]; // [2, 8] , [10, 1000]
	ASSERT_NO_THROW(map[AbsIntWrapper(-5)] = AbsIntWrapper(13)); // [2, 8] , [-5, 13], [10, 1000]
	ASSERT_EQUALS(1000, res.m_val);
	ASSERT_EQUALS(true, map.containsKey(AbsIntWrapper(5)));
	WrapperIterator iter = map.begin();
	ASSERT_EQUALS(8, (*iter).second.m_val);
	iter++;
	ASSERT_EQUALS(13, (*iter).second.m_val);
	iter++;
	ASSERT_EQUALS(1000, (*iter).second.m_val);
	iter++;
	ASSERT_EQUALS(map.end(), iter);

	return true;
}

// test insert remove, contains, size, copy, =
bool mapBasicTest() {
	IntMap map(-2);
	map.insert(IntPair(88, 0));
	map.insert(IntPair(90, 1));
	map.insert(IntPair(89, 2));
	IntMapIter iter = map.begin();
	ASSERT_EQUALS(88, (*iter).first);
	ASSERT_EQUALS(0, (*iter).second);
	iter++;
	ASSERT_EQUALS(89, (*iter).first);
	ASSERT_EQUALS(2, (*iter).second);
	iter++;
	ASSERT_EQUALS(90, (*iter).first);
	ASSERT_EQUALS(1, (*iter).second);
	iter++;
	ASSERT_EQUALS(map.end(), iter);
	map.insert(IntPair(70, 3));
	map.insert(IntPair(88, 4));
	map.insert(IntPair(100, 5));
	map.remove(89);
	ASSERT_EQUALS(false, map.containsKey(89));
	ASSERT_EQUALS(true, map.containsKey(88));
	ASSERT_EQUALS(4, map.size());
	map = map;
	ASSERT_EQUALS(4, map.size());

	iter = map.begin();
	ASSERT_EQUALS(70, (*iter).first);
	ASSERT_EQUALS(3, (*iter).second);
	iter++;
	ASSERT_EQUALS(88, (*iter).first);
	ASSERT_EQUALS(4, (*iter).second);
	++iter;
	ASSERT_EQUALS(90, (*iter).first);
	ASSERT_EQUALS(1, (*iter).second);
	iter++;
	ASSERT_EQUALS(100, (*iter).first);
	ASSERT_EQUALS(5, (*iter).second);
	++iter;
	ASSERT_EQUALS(map.end(), iter);
	ASSERT_EQUALS(3, map[70]);
	ASSERT_EQUALS(5, map[100]);
	ASSERT_EQUALS(-2, map[101]);
	ASSERT_EQUALS(5, map.size());
	ASSERT_EQUALS(true, map.containsKey(101));
	ASSERT_EQUALS(false, map.containsKey(-2));

	IntMap map2(map);
	ASSERT_EQUALS(-2, map2[102]);
	ASSERT_EQUALS(6, map2.size());
	ASSERT_EQUALS(5, map.size());
	ASSERT_EQUALS(5, map2[100]);
	map2.remove(70);
	map2[102] = -1;
	map2.remove(88);
	map = map2;
	ASSERT_EQUALS(4, map2.size());
	ASSERT_EQUALS(false, map.containsKey(88));
	ASSERT_EQUALS(true, map.containsKey(100));
	ASSERT_EQUALS(-1, map[102]);
	ASSERT_EQUALS(-2, map[103]);
	ASSERT_EQUALS(4, map2.size());
	ASSERT_EQUALS(5, map.size());

	map[85] = 6;
	map.insert(IntPair(85, 5));
	map.remove(85);
	ASSERT_THROW(MapElementNotFoundException, map.remove(85));

	return true;
}

class AbsCompare {
public:
	bool operator()(int a, int b) const {
		int absA = (a >= 0 ? a : -a);
		int absB = (b >= 0 ? b : -b);
		return absA < absB;
	}
};

bool basicMapExample() {
	IntMap map1(10);
	map1.insert(IntPair(1, 2));
	map1.insert(IntPair(3, 4));
	map1.remove(1);

	IntMap map2(map1);
	int count = 0;
	for (IntMapIter iter = map2.begin(); iter != map2.end(); iter++) {
		count++;
	}
	ASSERT_EQUALS(1, count);
	IntMap map3(0);
	map3 = map1;
	ASSERT_EQUALS(3, (*map3.begin()).first);
	ASSERT_EQUALS(4, (*map3.begin()).second);
	ASSERT_EQUALS(true, ++map3.begin() == map3.end());

	int n = map1[8];
	ASSERT_EQUALS(10, n);
	map1[5] = 12;
	ASSERT_EQUALS(true, map1.containsKey(5));
	ASSERT_EQUALS(3, map1.size());

	MtmMap<int, int, AbsCompare> map4(0);
	map4.insert(MtmMap<int, int, AbsCompare>::Pair(1, 1));
	map4.insert(MtmMap<int, int, AbsCompare>::Pair(-5, 2));
	map4.insert(MtmMap<int, int, AbsCompare>::Pair(-4, 3));
	map4.insert(MtmMap<int, int, AbsCompare>::Pair(3, 4));
	map4.insert(MtmMap<int, int, AbsCompare>::Pair(10, 5));

	MtmMap<int, int, AbsCompare>::iterator iter4 = map4.begin();
	ASSERT_EQUALS(1, (*iter4++).second);
	ASSERT_EQUALS(4, (*iter4++).second);
	ASSERT_EQUALS(3, (*iter4++).second);
	ASSERT_EQUALS(2, (*iter4++).second);
	ASSERT_EQUALS(5, (*iter4++).second);

	const IntMap map5(17);
	ASSERT_EQUALS(17, map5[8]);

	return true;
}

bool MtmMapTest(int testNum) {
	if (testNum == 0 || testNum == 1)
		RUN_TEST(basicMapExample);
	if (testNum == 0 || testNum == 2)
		RUN_TEST(mapBasicTest);
	if (testNum == 0 || testNum == 3)
		RUN_TEST(mapIteratorTest);
	if (testNum == 0 || testNum == 4)
		RUN_TEST(mapSqaureBracketsTest);
	if (testNum == 0 || testNum == 5)
		RUN_TEST(mapComplicatedCompareTest);

	return true;
}
