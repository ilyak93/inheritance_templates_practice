/*
 * library2.cpp
 *
 *  Created on: 7 αιεπι 2016
 *      Author: lior
 */

#include "library2.h"
#include <stdlib.h>
#include "DST.h"
using std::bad_alloc;
void* Init(int n) {
	try {
		if (n < 2)
			return NULL;
		DST* tmp = new DST(n);
		return tmp;
	} catch (const bad_alloc& bad_alloc) {
		return NULL;
	}
}
StatusType AddTroll(void* DS, int trollID, int strength) {
	try {
		if (DS == NULL || trollID < 0 || strength < 0)
			return INVALID_INPUT;
		DST* ds1 = static_cast<DST*>(DS);
		if ((*ds1).isTrollExist(trollID) == true)
			return FAILURE;
		(*ds1).DSTaddTroll(trollID, strength);
	} catch (const bad_alloc& bad_alloc) {
		return ALLOCATION_ERROR;
	}
}
//StatusType   AssignTroll(void* DS, int trollID, int team);
//StatusType   JoinGroups(void* DS, int team1, int team2);
//StatusType   GetGroup(void* DS, int trollID, int* group);
//StatusType   TeamUpgrade(void* DS, int teamID, int factor);
//StatusType   GetStrongestTroll(void* DS, int groupID, int* troll);
//StatusType   GetNumOfTrollsInRange(void* DS, int min, int max, int* num);
//void        Quit(void** DS);
