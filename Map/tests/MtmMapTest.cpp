#include "MtmTst.h"
#include "MtmMap.h"

using namespace mtm;

typedef MtmMap<int, int> IntMap;
typedef IntMap::Pair IntPair;
typedef IntMap::iterator IntMapIter;

class AbsCompare {
public:
	bool operator()(int a, int b) const {
		int absA = ( a >=0 ? a : -a);
		int absB = ( b >=0 ? b : -b);
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

bool MtmMapTest() {
	RUN_TEST(basicMapExample);

	return true;
}