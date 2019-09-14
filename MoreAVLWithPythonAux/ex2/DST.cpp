/*
 * DST.cpp

 *
 *  Created on: 4 αιεπι 2016
 *      Author: lior
 */
#include "DST.h"
#include <iostream>
using std::cout;
using std::endl;
/*
static void merge(Student** merged, Student* t1, Student* t2, int size1, int size2) {
	int itr = 0, itr1 = 0, itr2 = 0;
	StudentBySTRFunc cmp;
	if (merged == NULL) throw std::bad_alloc();
	while (itr1 < size1 && itr2 < size2) {
		if (cmp(t1[itr1], t2[itr2]) > 0) {
			(*merged)[itr++] = t2[itr2++];
		} else {
			(*merged)[itr++] = t1[itr1++];
		}
	}
	while (itr1 < size1) {
		(*merged)[itr++] = t1[itr1++];
	}
	while (itr2 < size2) {
		(*merged)[itr++] = t2[itr2++];
	}
}

static int getAmountOfStudentsToFactor(Student* Students, int teamID, int size) {
	int count = 0;
	for (int i = 0; i < size; i++) {
		count += (Students[i].getStudentTeam() == teamID);
	}
	return count;
}

static void devideInvertFactorize(Student* src, Student** to_factor, Student** not_to_factor,
		int to_factor_size, int not_to_factor_size, int teamID, int factor) {
	int itr1 = to_factor_size - 1, itr2 = not_to_factor_size - 1;
	int size = to_factor_size + not_to_factor_size;
	for (int i = 0; i < size; i++) {
		if (src[i].getStudentTeam() == teamID) {
			src[i].setStudentSTR(src[i].getStudentSTR() * factor);
			(*to_factor)[itr1--] = src[i];
		} else {
			(*not_to_factor)[itr2--] = src[i];
		}
	}
}
*/

void DST::DSTaddStudent(int id, int team, int str) {
	if (id <= 0 || team < 0 || team > this->size - 1 || str <= 0)
		throw DSTInvailedInput();
	Student tmp = Student(id, team, str);
	if (this->AVLTreeOfStudentsById.AVLTreeContain(tmp) == true)
		throw DSTFAILURE();
	this->AVLTreeOfStudentsById.insert(tmp);
	this->RankAVLTreeOfStudentsByStr.insert(tmp);
	this->HT.insert(tmp);
	int groupOwner = UF.Find(team);
	teams[groupOwner].addStudent(tmp); //ToDo: build strongest pdate func
	if (StudentByPowerFunc()(teams[groupOwner].getStrongestStudent(),tmp) < 0 ){
		teams[groupOwner].setStrongestStudent(tmp);
	}
	this->students_num++;
}

void DST::DSTremoveStudent(int id) {
	if (id <= 0) throw DSTInvailedInput();
	Student tmp(id);
	if(this->AVLTreeOfStudentsById.AVLTreeContain(tmp) == false)
		throw DSTFAILURE();
	tmp = AVLTreeOfStudentsById.findElement(tmp);
	this->AVLTreeOfStudentsById.deleteByInfo(tmp);
	this->RankAVLTreeOfStudentsByStr.deleteByInfo(tmp);
	int groupOwner = UF.Find(tmp.getStudentTeam());
	teams[groupOwner].removeStudent(tmp); //ToDo: build strongest pdate func
	this->HT.remove(id);
	this->students_num--;
}

void DST::DSTjoinTeams(int t1, int t2) {
	if (t1 < 0 || t1 > size - 1 || t2 < 0 || t2 > size - 1)
		throw DSTInvailedInput();

	int t1group = UF.Find(t1);
	int t2group = UF.Find(t2);
	if(t1group==t2group) return;
	groupNameToOwner[UF.findGroupName(t2)]=-1;
	groupNameToOwner[t2] = -1;
	int combinedGroup = UF.Union(t1, t2);
	
	if (combinedGroup != t1group) {
		groupNameToOwner[UF.findGroupName(t2)] = combinedGroup;
		groupNameToOwner[t2group] = -1;
		groupNameToOwner[t2] = -1;
		teams[combinedGroup].setGroupName(teams[t1group].getGroupName());

		if (StudentByPowerFunc()(teams[t1group].getStrongestStudent(),teams[combinedGroup].getStrongestStudent()) > 0 ){
			teams[combinedGroup].setStrongestStudent(teams[t1group].getStrongestStudent());
		}
		Student tmp(-1);
		teams[t1group].setStrongestStudent(tmp);
	} else {
		groupNameToOwner[t2group] = -1;
		groupNameToOwner[t2] = -1;
		if (StudentByPowerFunc()(teams[t1group].getStrongestStudent(),teams[t2group].getStrongestStudent()) < 0) {
			teams[combinedGroup].setStrongestStudent(
					teams[t2group].getStrongestStudent());
		} else {
			teams[combinedGroup].setStrongestStudent(
								teams[t1group].getStrongestStudent());
		}
		Student tmp(-1);
		//teams[t1group].setStrongestStudent(tmp);
	}
	teams[combinedGroup].joinWith(teams[t1group + t2group - combinedGroup]);
}

void DST::DSTteamFight(int t1, int t2, int num_of_fighters){
	if (t1 < 0 || t1 > size - 1 || t2 < 0 || t2 > size - 1)
		throw DSTInvailedInput();
	int t1group = UF.Find(t1);
	int t2group = UF.Find(t2);
	if(t1group==t2group) return; //ToDo:: what if same group or t1 == t2
	teams[t1group].fightWith(teams[t2group], num_of_fighters);
}

int DST::DSTgetGroup(int id) {
	if (id < 0)
		throw DSTInvailedInput();
	Student* target = this->HT.find(id);
	if (target->getStudentID() == -1 || target->getStudentTeam() == -1)
		return -1;
	int place = UF.Find(target->getStudentTeam());
	return teams[place].getGroupName();
}

int DST::DSTgetStudentTeamLeader(int StudentID) {
	if (StudentID < 0)
		throw DSTInvailedInput();
	Student* target = this->HT.find(StudentID);
	if (target == NULL) return -1;
	if (target->getStudentID() == -1/* || target->getStudentTeam() == -1*/)
		return -1;
	int place = UF.Find(target->getStudentTeam());
	return teams[place].getStrongestStudent().getStudentID();
}

//int DST::DSTteamUpgrade(int teamID, int factor);
/*
int DST::DSTgetStudentTeamLeader(int groupID) {
	if (groupID < 0 || groupID > size - 1)
		throw DSTInvailedInput();
	int place = groupNameToOwner[groupID];
	if(place==-1) {
		return -1;
	}
	if (teams[place].getStrongestStudent().getStudentID() == -1) {
		return -1;
	}
	return teams[place].getStrongestStudent().getStudentID();
}*/

/*
int DST::DSTgetNumberOfStudentsInRange(int min_str, int max_str) {
	if (min_str < 0 || min_str >= max_str) return -1;
	return this->RankAVLTreeOfStudentsByStr.getRange(Student(0, min_str), Student(0, max_str));
}
*/
bool DST::isStudentExist(int id) {
	if (id <= 0)
		return false;
	Student tmp(id,1, 1);
	return this->AVLTreeOfStudentsById.AVLTreeContain(tmp);
}
int DST::DSTGetSize(){
	return size;
}
int DST::getStudentTeam(int id){
	Student tmp(id,1,1);
	return this->AVLTreeOfStudentsById.findElement(tmp).getStudentTeam();
}
bool DST::isOnSameGroup(int t1, int t2){
	if(t1 < 0|| t2 < 0 || t1>size-1 || t2>size-1){
		return false;
	}
	if(UF.Find(t1)==UF.Find(t2)) return true;
	return false;
}

int DST::DSTgetNumOfWins(int team){
	if (team < 0 || team > size - 1)
		throw DSTInvailedInput();
	return teams[this->UF.Find(team)].getNumberOfWins();
}

/*
int DST::DSTteamUpgrade(int teamID, int factor) {
	int size_Students_by_str = this->RankAVLTreeOfStudentsByStr.getSize();
	if (size_Students_by_str == 0)
		return -1; // return -1 if no Students
	this->updateTreeById(teamID, factor); // updated by private func updateTreeById
	Student strongest = this->updateRankTreeByStr(teamID, factor); // strongest_Student returned by aux private func updateRankTreeByStr
	if(strongest.getStudentID()==-1){
		return 1;
	}
	int teamGroup = this->UF.Find(teamID);
	if(this->teams[teamGroup].getStrongestStudent().getStudentID()==-1){
		return 1;
	}
	if (this->teams[teamGroup].getStrongestStudent().getStudentSTR()
			< strongest.getStudentSTR()
			|| (this->teams[teamGroup].getStrongestStudent().getStudentSTR()
					== strongest.getStudentSTR()
					&& this->teams[teamGroup].getStrongestStudent().getStudentID()
							> strongest.getStudentID())) {
		this->teams[teamGroup].setStrongestStudent(strongest);
	}
	return 1;
}

void DST::updateTreeById(int teamID, int factor) {
	Student* Students = this->AVLTreeOfStudentsById.returnSortedTreeElementsInOrder();
	for (int i = 0; i < this->students_num; i++) {
		if (i < students_num / 2) {
			Student tmp = Students[i];
			Students[i] = Students[students_num - i - 1];
			Students[students_num - i - 1] = tmp;
		}
		if (Students[i].getStudentTeam() == teamID) {
			Students[i].setStudentSTR(Students[i].getStudentSTR() * factor);
		}
	}
	this->AVLTreeOfStudentsById.fillInAVLTree(Students);
	free(Students);
}

Student DST::updateRankTreeByStr(int teamID, int factor) { //Todo: free if allocation failed
	Student* Students_by_str =
			this->RankAVLTreeOfStudentsByStr.returnSortedTreeElementsInOrder();
	if (Students_by_str == NULL) throw std::bad_alloc();
	int to_factor_size = getAmountOfStudentsToFactor(Students_by_str, teamID, students_num);
	int not_to_factor_size = students_num - to_factor_size;
	Student* to_factor = new Student[to_factor_size];
	if (to_factor == NULL) throw std::bad_alloc();
	Student* not_to_factor = new Student[not_to_factor_size];
	if (not_to_factor == NULL) throw std::bad_alloc();
	devideInvertFactorize(Students_by_str, &to_factor, &not_to_factor, to_factor_size,
			not_to_factor_size, teamID, factor);
	Student* merged = new Student[students_num]; // Todo:: check valgrind leak
	merge(&merged, to_factor, not_to_factor, to_factor_size,
			not_to_factor_size);
	Student strongest;
	if(to_factor_size==0){
		Student strongest1(5);
		strongest=strongest1;
	}else{
		Student strongest1 = to_factor[0];
		strongest=strongest1;
	}

	this->RankAVLTreeOfStudentsByStr.fillInRankAVLTree(merged);
	delete []merged;
	delete []to_factor;
	delete[]not_to_factor;
	free(Students_by_str);
	return strongest;
}

*/
