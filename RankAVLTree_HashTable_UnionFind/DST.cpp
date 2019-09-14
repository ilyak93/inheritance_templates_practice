/*
 * DST.cpp

 *
 *  Created on: 4 αιεπι 2016
 *      Author: lior
 */
#include "DST.h"
static Troll* mergeAndInvert(Troll* t1, Troll* t2, int size1, int size2) {
	int itr = 0, itr1 = size1-1, itr2 = size2-1;
	trollBySTRFunc cmp;
	Troll* merged = new Troll[size1 + size2]; // Todo:: check valgrind leak
	while (itr1 >= 0 && itr2 >= 0) {
		if (cmp(t1[itr1], t2[itr2]) > 0) {
			merged[itr++] = t1[itr1--];
		}
		else {
			merged[itr++] = t2[itr2--];
		}
	}
	while (itr1 >= 0) {
		merged[itr++] = t1[itr1--];
	}
	while (itr2 >= 0) {
		merged[itr++] = t2[itr2--];
	}
	return merged;
}

static int getAmountOfTrollsToFactor(Troll* trolls, int teamID, int size) {
	int count = 0;
	for (int i = 0; i < size; i++) {
		count += (trolls[i].getTrollTeam() == teamID);
	}
	return count;
}

static void devideByFactor(Troll* src, Troll** to_factor, Troll** not_to_factor,
	int to_factor_size, int not_to_factor_size,
	int teamID, int factor) {
	int itr1 = 0, itr2 = 0;
	int size = to_factor_size + not_to_factor_size;
	for (int i = 0; i < size; i++) {
		if (src[i].getTrollTeam() == teamID) {
			src[i].setTrollSTR(src[i].getTrollSTR() * factor);
			(*to_factor)[itr1++] = src[i];
		}
		else {
			(*not_to_factor)[itr2++] = src[i];
		}
	}
}

void DST::DSTaddTroll(int id, int str) {
	if (id < 0 || str < 0)
		throw DSTInvailedInput();
	Troll tmp = Troll(id, str);
	if (this->AVLTreeOfTrollsById.AVLTreeContain(tmp) == true)
		throw DSTFAILURE();
	this->AVLTreeOfTrollsById.insert(tmp);
	this->RankAVLTreeOfTrollsByStr.insert(tmp);
	this->trolls_num++;
}
void DST::DSTassignTroll(int id, int team) {
	if (id < 0 || team < 0 || team >= size)
		throw DSTInvailedInput();
	Troll tmp(id, 0);
	if (this->AVLTreeOfTrollsById.AVLTreeContain(tmp) == false)
		throw DSTFAILURE();
	Troll target = this->AVLTreeOfTrollsById.findElement(tmp);
	if (target.getTrollTeam() == -1) {
		target.setTrollTeam(team);
		AVLTreeOfTrollsById.find(target)->setData(target);
		RankAVLTreeOfTrollsByStr.find(target)->setData(target);
		this->HT.insert(target);
	}
	target=HT.find(15);
	int groupOwner=UF.Find(team);
	if((teams[groupOwner].getStrongestTroll().getTrollSTR()< target.getTrollSTR())
			||(teams[groupOwner].getStrongestTroll().getTrollSTR()==target.getTrollSTR() && teams[groupOwner].getStrongestTroll().getTrollID()>target.getTrollID())){
		teams[groupOwner].setStrongestTroll(target);
	}

}
;
void DST::DSTjoinGroups(int t1, int t2) {
	if (t1 < 0 || t1 > size - 1 || t2 < 0 || t2 > size - 1)
		throw DSTInvailedInput();
	int t1group = UF.Find(t1);
	int t2group = UF.Find(t2);
	int combinedGroup = UF.Union(t1, t2);
	if (combinedGroup != t1group) {
		groupNameToOwner[t1group]=combinedGroup;
		teams[combinedGroup].setGroupName(teams[t1group].getGroupName());

		if (teams[t1group].getStrongestTroll().getTrollSTR()
				> teams[t2group].getStrongestTroll().getTrollSTR()) {
			teams[combinedGroup].setStrongestTroll(
					teams[t1group].getStrongestTroll().getTrollSTR());
		} else if(teams[t1group].getStrongestTroll().getTrollSTR() == teams[t2group].getStrongestTroll().getTrollSTR()){
			if(teams[t1group].getStrongestTroll().getTrollID() < teams[t2group].getStrongestTroll().getTrollID()){
				teams[combinedGroup].setStrongestTroll(teams[t1group].getStrongestTroll());
			}
		}
		Troll tmp(-1);
		teams[t1group].setStrongestTroll(tmp);
	}else{
		if (teams[t1group].getStrongestTroll().getTrollSTR() < teams[t2group].getStrongestTroll().getTrollSTR()) {
					teams[combinedGroup].setStrongestTroll(teams[t2group].getStrongestTroll().getTrollSTR());
				} else if(teams[t1group].getStrongestTroll().getTrollSTR() == teams[t2group].getStrongestTroll().getTrollSTR()){
					if(teams[t2group].getStrongestTroll().getTrollID() < teams[t1group].getStrongestTroll().getTrollID()){
						teams[combinedGroup].setStrongestTroll(teams[t2group].getStrongestTroll());
					}
				}

		Troll tmp(-1);
		teams[t2group].setStrongestTroll(tmp);
	}
}
int DST::DSTgetGroup(int id){
	if(id < 0) throw DSTInvailedInput();
	Troll target=this->HT.find(id);
	if(target.getTrollID()==-1 || target.getTrollTeam()==-1) return -1;
	int place=UF.Find(target.getTrollTeam());
	return teams[place].getGroupName();
}
//int DST::DSTteamUpgrade(int teamID, int factor);
int DST::DSTgetStrongestTroll(int groupID){
	if(groupID < 0 || groupID > size-1) throw DSTInvailedInput();
	int place=groupNameToOwner[groupID];
	cout<<place<<endl;
	if(teams[place].getStrongestTroll().getTrollID()==-1){
	 return -1;
	}
	return teams[place].getStrongestTroll().getTrollID();

}
//int DST::DSTgetNumberOfTrollsInRange(int min, int max);
bool DST::isTrollExist(int id){
	if(id<0) return false;
	Troll tmp(id,0);
	return this->AVLTreeOfTrollsById.AVLTreeContain(tmp);
}

int DST::DSTteamUpgrade(int teamID, int factor) {
	int size_trolls_by_str = this->RankAVLTreeOfTrollsByStr.getSize();
	if (size_trolls_by_str == 0) return -1; // return -1 if no trolls
	this->updateTreeById(teamID, factor); // updated by private func updateTreeById
	Troll strongest = this->updateRankTreeByStr(teamID, factor); // strongest_troll returned by aux private func updateRankTreeByStr
	//Todo: update strongest troll
}

void DST::updateTreeById(int teamID, int factor) {
	Troll* trolls = this->AVLTreeOfTrollsById.returnSortedTreeElementsInOrder();
	for (int i = 0; i<this->trolls_num; i++) {
		if (trolls[i].getTrollTeam() == teamID) {
			trolls[i].setTrollSTR(trolls[i].getTrollSTR() * factor);
		}
	}
	this->AVLTreeOfTrollsById.fillInAVLTree(trolls);
	free(trolls);
}

Troll DST::updateRankTreeByStr(int teamID, int factor) {
	Troll* trolls_by_str = this->RankAVLTreeOfTrollsByStr.returnSortedTreeElementsInOrder();
	int to_factor_size = getAmountOfTrollsToFactor(trolls_by_str, teamID, size);
	int not_to_factor_size = size - to_factor_size;
	Troll* to_factor = new Troll[to_factor_size];
	Troll* not_to_factor = new Troll[not_to_factor_size];
	devideByFactor(trolls_by_str, &to_factor, &not_to_factor, to_factor_size,
		not_to_factor_size, teamID, factor);
	Troll* new_trolls = mergeAndInvert(to_factor, not_to_factor, to_factor_size, not_to_factor_size);
	Troll strongest = new_trolls[0];
	this->RankAVLTreeOfTrollsByStr.fillInRankAVLTree(new_trolls);
	free(trolls_by_str);
	return strongest;
}

