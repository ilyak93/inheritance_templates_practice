/*
 * Team.cpp
 *
 *  Created on: 4 αιεπι 2016
 *      Author: lior
 */
#include "Team.h"
int Team::getGroupName(){
	return this->groupName;
}
int Team::getTeamNum(){
	return this->teamNum;
}
Student Team::getStrongestStudent(){
	return this->strongestStudent;
}
bool Team::isOnAGroup(){
	return this->onAGroup;
}
void Team::setStrongestStudent(Student t){
	this->strongestStudent=t;
}

/*void Team::updateStrongestStudent(){
	RankAVLTreeNode<Student, StudentByPowerFunc, studentGetSTR>* max =
			RankAVLTreeOfStudentsByStr.minPointerInRankAVLTree(
							RankAVLTreeOfStudentsByStr.getRoot());
	this->strongestStudent = max == NULL ? Student(-1) : max->getInfo();
}*/

void Team::setGroupName(int i){
	groupName=i;
	onAGroup=true;
}

void Team::setTeam(int i){
	if(i<0) throw TeamInvailedInput();
	teamNum=i;
	groupName=i;
}

void Team::addStudent(Student& s) {
	if (s.getStudentID() < 0 || s.getStudentTeam() < 0 || s.getStudentSTR() < 0)
		throw DSTInvailedInput();
	if (this->AVLTreeOfStudentsById.AVLTreeContain(s) == true)
		throw DSTFAILURE();
	this->AVLTreeOfStudentsById.insert(s);
	this->RankAVLTreeOfStudentsByStr.insert(s);
	if (StudentByPowerFunc()(this->strongestStudent , s) < 0 ){
		this->strongestStudent = s;
	}
	this->students_num++;
}

void Team::removeStudent(Student& s) {
	if (s.getStudentID() < 0) throw DSTInvailedInput();
	if(this->AVLTreeOfStudentsById.AVLTreeContain(s) == false) throw DSTFAILURE();
	this->AVLTreeOfStudentsById.deleteByInfo(s);
	this->RankAVLTreeOfStudentsByStr.deleteByInfo(s);
	RankAVLTreeNode<Student, StudentByPowerFunc, studentGetSTR>* max =
				RankAVLTreeOfStudentsByStr.minPointerInRankAVLTree(
								RankAVLTreeOfStudentsByStr.getRoot());
	this->strongestStudent = max == NULL ? Student(-1) : max->getInfo();
	this->students_num--;
}



static Student* mergeById(Student* p1, Student* p2, int size1, int size2) {
	//assert(p1 && p2);
	int itr = 0, itr1 = 0, itr2 = 0;
	StudentByStudentIdFunc cmp;
	Student* merged = new Student[size1 + size2];
	while (itr1 < size1 && itr2 < size2) {
		if(cmp(p1[itr1], p2[itr2]) > 0){
			merged[itr++] = p1[itr1++];
		} else {
			merged[itr++] = p2[itr2++];
		}
	}
	while (itr1 < size1) {
		merged[itr++] = p1[itr1++];
	}
	while (itr2 < size2) {
		merged[itr++] = p2[itr2++];
	}

	return merged;
}

static int nearest2Pow(int x) {
	int power = 1;
	while (power <= x) {
		power *= 2;
	}
	return power;
}



static Student* mergeByLvl(Student* p1, Student* p2, int size1, int size2) {
	//assert(p1 && p2);
	int itr = 0, itr1 = 0, itr2 = 0;
	StudentByPowerFunc cmp;
	Student* merged = new Student[size1 + size2];
	while (itr1 < size1 && itr2 < size2) {
		if (cmp(p1[itr1], p2[itr2]) > 0) {
			merged[itr++] = p1[itr1++];
		}
		else {
			merged[itr++] = p2[itr2++];
		}
	}
	while (itr1 < size1) {
		merged[itr++] = p1[itr1++];
	}
	while (itr2 < size2) {
		merged[itr++] = p2[itr2++];
	}
	return merged;
}

void Team::joinById(Team& to_join) {
	Student* c1 = this->AVLTreeOfStudentsById.returnSortedTreeElementsInOrder();
	Student* c2 = to_join.AVLTreeOfStudentsById.returnSortedTreeElementsInOrder();
	/*for(int i = 0; i < to_join.students_num(); ++i) {
		c2[i]->setTeam(this);
	}*/
	Student* c3 = mergeById(c1, c2, students_num, to_join.students_num);
	int new_size = students_num + to_join.students_num;
	this->AVLTreeOfStudentsById.~AVLTree();
	int nearest2pow = nearest2Pow(new_size) - 1;
	int dif = nearest2pow - new_size;
	AVLTreeOfStudentsById.createEmptyWholeAVLTree(nearest2pow);
	AVLTreeOfStudentsById.removeInorderRightLeft(dif);
	AVLTreeOfStudentsById.fillInAVLTree(c3); //ToDo : check why pointer
	free(c1);
	free(c2);
	delete[] c3;
}

void Team::joinByLvl(Team& to_join) {
	Student* c1 = this->RankAVLTreeOfStudentsByStr.returnSortedTreeElementsInOrder();
	Student* c2 = to_join.RankAVLTreeOfStudentsByStr.returnSortedTreeElementsInOrder();
	/*for (int i = 0; i < to_join.students_num; ++i) {
		c2[i]->setTeam(this);
	}*/
	Student* c3 = mergeByLvl(c1, c2, students_num,to_join.students_num);
	this->RankAVLTreeOfStudentsByStr.~RankAVLTree();
	int new_size = students_num + to_join.students_num;
	int nearest2pow = nearest2Pow(new_size) - 1;
	int dif = nearest2pow - new_size;
	RankAVLTreeOfStudentsByStr.createEmptyWholeRankAVLTree(nearest2pow);
	RankAVLTreeOfStudentsByStr.removeInorderRightLeft(dif);
	RankAVLTreeOfStudentsByStr.fillInRankAVLTree(c3); //ToDo : check why pointer
	this->strongestStudent = c3[0];
	free(c1);
	free(c2);
	delete[] c3;
}

void Team::joinWith(Team& to_join){
	if (teamNum < 0 || to_join.teamNum < 0){
		throw TeamInvailedInput();
	}
	if (to_join.students_num < 1) return;
	this->joinById(to_join);
	this->joinByLvl(to_join);
	this->students_num += to_join.students_num;
	this->number_of_wins += to_join.number_of_wins;
}

void Team::fightWith(Team& t, int num_of_fighters){
	int num_of_wins1 = num_of_fighters <= students_num ?
			  RankAVLTreeOfStudentsByStr.select(this->students_num-num_of_fighters+1)
			   : RankAVLTreeOfStudentsByStr.getRoot()->getSum();
	int num_of_wins2 = num_of_fighters <= t.students_num ?
			 t.RankAVLTreeOfStudentsByStr.select(t.students_num-num_of_fighters+1):
		     t.RankAVLTreeOfStudentsByStr.getRoot()->getSum();
	if( num_of_wins1 > num_of_wins2){
		this->number_of_wins++;
	} else if( num_of_wins2 > num_of_wins1){
		t.number_of_wins++;
	}
}

int Team::getNumberOfWins(){
	return this->number_of_wins;
}
