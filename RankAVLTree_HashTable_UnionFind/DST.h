/*
 * DS.h
 *
 *  Created on: 4 αιεπι 2016
 *      Author: lior
 */
#include "Troll.h"
#include "AVLTree.h"
#include "HashTable.h"
#include "Team.h"
#include "UnionFind.h";
#include "RankAVLTree.h"
class DST{
private:
	RankAVLTree<Troll,trollByIDfunc,trollBySTRFunc> RankAVLTreeOfTrollsByStr;
	AVLTree<Troll,trollByIDfunc,trollByIDfunc> AVLTreeOfTrollsById;
	HashTable<Troll,getIdForHash,cmpTroll,trollByIDfunc> HT;
	Team *teams;
	int size;
	int trolls_num; //Todo: update everywhere trolls_num
	UnionFind UF;
	int *groupNameToOwner;
	void updateTreeById(int S, int factor);
	Troll updateRankTreeByStr(int S, int factor);
	void updateTreeByID(int S, int factor);
public:
	/*
	 * c'tor for creating a new data structure with amounts of team n
	 * in case of n under 2 it will throw DSTInvalidInput
	 */
	DST(int n){
		if(n<2) throw DSTInvailedInput();
		teams=new Team[n];
		groupNameToOwner=new int[n];
		for(int i=0;i<n;i++){
			teams[i].setTeam(i);
			groupNameToOwner[i]=i;
		}
		size=n;
		UnionFind temp1(n);
		UF=temp1;
		this->trolls_num = 0;
	}
	~DST(){};
	/*
	 * Adds a new troll to the DS, if id or str are under 0 it will throw
	 * DSTInavalidInput. if there is already a troll with that name it will
	 * throw DSTFAILURE
	 */
	void DSTaddTroll(int id, int str);
	/*
	 * Assign a troll to a group if id or str are under 0 it will throw
	 * DSTInvaliedInput.if there is no troll with id or it already has different
	 * it will throw DSTFAILURE
	 */
	void DSTassignTroll(int id, int team);
	/*
	 * merge the teams of the group of t2 into the group of t1
	 * if t1 or t2 are under 0 or the t are over n it will throw DSTInvalidInput
	 * if teams are at the same group it will throw DSTFAILURE
	 */
	void DSTjoinGroups(int t1, int t2);
	/*
	 * return the name of the group which the trool with id is belongs to.
	 * if id is under 0 it will throw DSTInvalidInput
	 * if the troll has no group or not in the DS it throw DSTFAILURE
	 */
	int DSTgetGroup(int id);
	/*
	 * multiply all the trolls strength with factor
	 * if teamId is under 0, or factor under 1 or teamId is over n-1
	 * it will throw DSTInvalidInput
	 */
	int DSTteamUpgrade(int teamID, int factor);
	/*
	 * return the strongest troll of a group with id;
	 * if id  is under 0 or over n-1 it will throw DSTInvailedInput
	 */
	int DSTgetStrongestTroll(int id);
	/*
	 * return the number of trolls at DS which there strength is over min and
	 * under max+1;
	 */
	int DSTgetNumberOfTrollsInRange(int min, int max);
	bool isTrollExist(int id);
};



