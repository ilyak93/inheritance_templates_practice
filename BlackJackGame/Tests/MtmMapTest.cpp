#include "MtmTst.h"
#include "MtmMap.h"

using namespace mtm;

typedef MtmMap<int, int> IntMap;
typedef IntMap::Pair IntPair;
typedef IntMap::iterator IntMapIter;

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
	ASSERT_THROW(MapElementNotFoundException, (*iter4));

	const IntMap map5(17);
	ASSERT_EQUALS(17, map5[8]);

	return true;
}

bool mapTest() {
	IntMap map6(10);
	ASSERT_EQUALS(false, map6.containsKey(10));
	int count6 = 0;
	for (IntMapIter iter = map6.begin(); iter != map6.end(); iter++) {
		count6++;
	}
	ASSERT_EQUALS(0, count6);
	IntMap map7(0);
	map6 = map7;
	ASSERT_EQUALS(0, map6[8]);
	IntMap map8(map6);
	ASSERT_EQUALS(0, map8[8]);


	IntMap map9(67);
	map9.insert(IntPair(1, 2));
	map9.insert(IntPair(3, 4));
	map9.insert(IntPair(5, 1));
	map9.insert(IntPair(-3, 6));
	map9.insert(IntPair(5, 7));
	map9.insert(IntPair(-2, 1));

	ASSERT_THROW(MapElementNotFoundException, map9.remove(6));
	map9.remove(1);
	map9.remove(-2);

	ASSERT_EQUALS(false, map9.containsKey(67));
	ASSERT_EQUALS(true, map9.containsKey(3));
	ASSERT_EQUALS(true, map9.containsKey(5));
	ASSERT_EQUALS(true, map9.containsKey(-3));
	ASSERT_EQUALS(false, map9.containsKey(1));
	ASSERT_EQUALS(false, map9.containsKey(-2));

	ASSERT_EQUALS(true, 4 == map9[3]);
	ASSERT_EQUALS(false, 1 == map9[5]);
	ASSERT_EQUALS(true, 7 == map9[5]);
	ASSERT_EQUALS(false, map9.containsKey(6));
	ASSERT_EQUALS(true, 67 == map9[6]);
	ASSERT_EQUALS(true, map9.containsKey(6));
	ASSERT_EQUALS(true, 67 == map9[6]);

	int count9 = 0;
	for (IntMapIter iter = map9.begin(); iter != map9.end(); iter++) {
		count9++;
	}
	ASSERT_EQUALS(4, count9);

	count9 = 0;
	IntMapIter iter11 = map9.begin();
	for (IntMapIter iter10 = map9.begin(); iter10 != map9.end(); ++iter10) {
		ASSERT_EQUALS(iter10, iter11);
		count9++;
		++iter11;
	}
	ASSERT_EQUALS(4, count9);

	count9 = 0;
	IntMapIter iter13 = map9.begin();
	IntMapIter iter12 = map9.begin();
	ASSERT_EQUALS(true, iter12++ != ++iter13);
	ASSERT_EQUALS(true, map9.end() == map9.end());
	ASSERT_EQUALS(false, map9.end() == map7.end());
	count9 = 0;
	for (IntMapIter iter = map9.begin(); iter != map9.end(); iter++) {
		for (IntMapIter iter2 = map9.begin(); iter2 != map9.end(); iter2++) {
			IntMapIter iter3 = map9.begin();
			iter3++;
			count9++;
		}
	}
	ASSERT_EQUALS(16, count9);

	IntMapIter iter14 = map9.begin();
	IntMapIter iter15 = map7.end();
	iter15 = iter14;
	ASSERT_EQUALS(iter15, map9.begin());
	ASSERT_EQUALS(false, iter15 == map7.end());
	ASSERT_EQUALS(false, iter15 == map7.begin());
	ASSERT_EQUALS(true, iter15 != map7.end());
	ASSERT_EQUALS(true, iter15 != map7.begin());

	IntMapIter iter16 = map9.end();
	IntMapIter iter17 = map7.end();
	iter16 = iter17;
	ASSERT_EQUALS(iter16, map7.end());
	ASSERT_EQUALS(false, iter16 == map9.end());
	ASSERT_EQUALS(true, iter16 != map9.end());

	return true;
}

bool MtmMapTest() {
	RUN_TEST(basicMapExample);
	RUN_TEST(mapTest);
	return true;
}

