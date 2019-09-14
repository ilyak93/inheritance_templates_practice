/*
 * library2.cpp
 *
 *  Created on: 7 αιεπι 2016
 *      Author: lior
 */

#include "library2.h"
#include <stdlib.h>
#include "DST.h"
#include <iostream>
using std::cout;
using std::endl;
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

StatusType AddStudent(void* DS, int trollID, int team, int strength) {
	try {
		if (DS == NULL || trollID <= 0 || team <= 0 || strength <= 0)
			return INVALID_INPUT;
		DST* ds1 = static_cast<DST*>(DS);
		if((*ds1).DSTGetSize() < team  ) return INVALID_INPUT;
		if ((*ds1).isStudentExist(trollID) == true)
			return FAILURE;
		(*ds1).DSTaddStudent(trollID, team-1, strength);
		return SUCCESS;
	} catch (const bad_alloc& bad_alloc) {
		return ALLOCATION_ERROR;
	}
}

StatusType RemoveStudent(void* DS, int trollID) {
	try {
		if (DS == NULL || trollID <= 0)
			return INVALID_INPUT;
		DST* ds1 = static_cast<DST*>(DS);
		if ((*ds1).isStudentExist(trollID) == false)
			return FAILURE;
		(*ds1).DSTremoveStudent(trollID);
		return SUCCESS;
	} catch (const bad_alloc& bad_alloc) {
		return ALLOCATION_ERROR;
	}
}
/*
StatusType   AssignTroll(void* DS, int trollID, int team){
	if(DS==NULL || trollID < 0 || team < 0 ) return INVALID_INPUT;
	DST* ds1 = static_cast<DST*>(DS);
	if((*ds1).DSTGetSize()-1 < team  ) return INVALID_INPUT;
	if((*ds1).isStudentExist(trollID)==false) return FAILURE;
	int teamOfTroll=(*ds1).getStudentTeam(trollID);
	if(teamOfTroll!=-1 && team != teamOfTroll) return FAILURE;
	if(team == teamOfTroll) return SUCCESS;
	//(*ds1).DSTassignStudent(trollID,team);
	return SUCCESS;
}
*/

StatusType JoinTeams(void* DS, int team1, int team2){
	if(DS == NULL || team1 <= 0 || team2 <= 0)  return INVALID_INPUT;
	DST* ds1 = static_cast<DST*>(DS);
	if((*ds1).DSTGetSize() < team1 || (*ds1).DSTGetSize() < team2  ){
		return INVALID_INPUT;
	}
	//if((*ds1).isOnSameGroup(team1,team2)==true) return FAILURE;
	(*ds1).DSTjoinTeams(team1-1,team2-1);
	return SUCCESS;
}

StatusType TeamFight(void *DS, int Team1, int Team2, int NumOfFighters){
	if(DS == NULL || Team1 <= 0 || Team2 <= 0 || NumOfFighters <= 0)
		return INVALID_INPUT;
	DST* ds1 = static_cast<DST*>(DS);
	if((*ds1).DSTGetSize() < Team1 || (*ds1).DSTGetSize() < Team2  ){
		return INVALID_INPUT;
	}
	ds1->DSTteamFight(Team1-1,Team2-1, NumOfFighters);
	return SUCCESS;
}

StatusType GetNumOfWins(void *DS, int Team, int* Wins){
	if(DS == NULL || Team <= 0 || Wins == NULL)
			return INVALID_INPUT;
	DST* ds1 = static_cast<DST*>(DS);
	if((*ds1).DSTGetSize() < Team) return INVALID_INPUT;
	*Wins = ds1->DSTgetNumOfWins(Team-1);
	return SUCCESS;
}

/*
StatusType   GetGroup(void* DS, int trollID, int* group){
	if(DS==NULL || group==NULL || trollID < 0) return INVALID_INPUT;
	DST* ds1 = static_cast<DST*>(DS);
	int groupName=(*ds1).DSTgetGroup(trollID);
	if(groupName==-1) return FAILURE;
	*group=groupName;
	return SUCCESS;
}
*/
/*
StatusType   TeamUpgrade(void* DS, int teamID, int factor){
	if(DS==NULL || teamID < 0 || factor < 1) return INVALID_INPUT;
	DST* ds1 = static_cast<DST*>(DS);
		if((*ds1).DSTGetSize()-1 < teamID) return INVALID_INPUT;
	(*ds1).DSTteamUpgrade(teamID,factor);
	return SUCCESS;
}
*/
StatusType   GetStudentTeamLeader(void* DS, int StudentID, int* troll){
	if(DS==NULL || StudentID <= 0 || troll==NULL) return INVALID_INPUT;
	DST* ds1 = static_cast<DST*>(DS);
	int strongest=(*ds1).DSTgetStudentTeamLeader(StudentID);
	if(strongest==-1) return FAILURE;
	*troll=strongest;
	return SUCCESS;
}
/*
StatusType GetNumOfTrollsInRange(void* DS, int min, int max, int* num){
	if (min < 0 || min >= max) return INVALID_INPUT;
	if (DS == NULL || num == NULL) return FAILURE;
	DST* ds = static_cast<DST*>(DS);
	*num = ds->DSTgetNumberOfStudentsInRange(min, max);
	return SUCCESS;
}
*/

void        Quit(void** DS){
	if(DS==NULL) return;
	if (DS != NULL || *DS != NULL) {
			void* ds = *DS;
			DST* ds1 = static_cast<DST*>(ds);
			delete (ds1);
			*DS = NULL;
		}
	//ToDo: build the function
}
