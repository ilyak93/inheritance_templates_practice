/*
 * Team.cpp
 *
 *  Created on: 26 באפר׳ 2016
 *      Author: Ilya
 */

#include <assert.h>
#include "Team.h"

/*
 * The function receive two ordered arrays of Students and merged to 1 sorted
 * array
 * Note: the order is determined by the sorted function of the Students tree
 */


/*
 *The function receive an array, its size and the a factor,
 *and return the amount of Students in the array with StudentID % S == 0
 *
 */

/*
 * The function get a src array of Students which is not ordered, yet it can be
 * divided to 2 sorted "mini" arrays which are does which can be determined by
 * the StudentCode (S) of "update likes". Also we have  the size those 2 mini
 * array (to_factor_size and not_to_factor_size).
 * the Function divides this Student array to the 2 arrays and also flip the
 *  order.
 *
 */

/*
static Student** mergeById(Student** p1, Student** p2, int size1, int size2) {
	//assert(p1 && p2);
	int itr = 0, itr1 = 0, itr2 = 0;
	StudentByStudentIdFunc cmp;
	Student** merged = new Student*[size1 + size2];
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

*/

static Student** mergeByLvl(Student** p1, Student** p2, int size1, int size2) {
	//assert(p1 && p2);
	int itr = 0, itr1 = 0, itr2 = 0;
	StudentByPowerFunc cmp;
	Student** merged = new Student*[size1 + size2];
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

int Team::getTeamID(){
	return this->TeamID;
}

Student Team::getMostPowerful(){
	return this->maxStudentByPower;
}

void Team::addStudent(Student* student_ptr){
	if(!student_ptr) throw TeamInvailedInput();
	/*if(this->StudentsByStudentID.AVLTreeContain(student_ptr))
		throw TeamStudentExist();*/
	this->StudentsByStudentID.insert(student_ptr);
	this->StudentsByPower.insert(student_ptr);
	if(StudentByPowerFunc()(&maxStudentByPower,student_ptr) < 0){
		this->maxStudentByPower = *student_ptr;
	}
	this->numberOfStudents++;
}

/*
void Team::addStudentToTeam(Student* student_ptr){
	if(student_ptr == NULL) throw TeamInvailedInput();
	if(this->StudentsByStudentID.AVLTreeContain(student_ptr)) // what if he already in?"
		return;
	this->StudentsByStudentID.insert(student_ptr);
	this->StudentsByPower.insert(student_ptr);
}
*/

int Team::getNumOfStudents(){
	return this->numberOfStudents;
}

void Team::removeStudent(int ID){ // update max Student
	Student tmp(ID);
	if(this->numberOfStudents  == 0){
		throw TeamNoStudents();
	}
	if(!this->StudentsByStudentID.AVLTreeContain(&tmp)){
		throw TeamStudentDoesntExist();
	}
	Student* student_ptr = this->StudentsByStudentID.findElement(&tmp);
	this->StudentsByStudentID.deleteByInfo(student_ptr);
	this->StudentsByPower.deleteByInfo(student_ptr);
	AVLTreeNode<Student*, StudentByPowerFunc>* max =
			this->StudentsByPower.minPointerInAVLTree(
			this->StudentsByPower.getRoot());
	this->maxStudentByPower = max ? (*(max->getInfo())) : Student();
	this->numberOfStudents--;
}

Student** Team::getAllStudentsSortedByPower(){
	return this->StudentsByPower.returnSortedTreeElementsInOrder();
}

/*
static int nearest2Pow(int x) {
	int power = 1;
	while (power <= x) {
		power *= 2;
	}
	return power;
}
*/
//check leaks
void Team::increaseLevel(int grade) {
	if (!this || this->numberOfStudents == 0 || sorted) return;
	if (this->numberOfStudents == 1) {
		this->maxStudentByPower = *(this->StudentsByPower.getRoot()->getInfo());
	}
	Student** students_by_power = this->StudentsByPower.returnSortedTreeElementsInOrderRL();
	bool non = true;
	int len1 = 0, len2 = 0;
	Student** p1 = new Student*[this->numberOfStudents];
	Student** p2 = new Student*[this->numberOfStudents];
	for (int i = 0; i < this->numberOfStudents; ++i) {
		if (students_by_power[i]->getGrade() == grade) {
			p1[len1++] = students_by_power[i];
			non = false;
		}
		else p2[len2++] = students_by_power[i];
	}
	if (non) {
		delete[]p1;
		delete[]p2;
		free(students_by_power);
		return;
	}
	if (!non) {
		//printf("\n first =");
		//for (int i = 0; i < len1; ++i) printf(" %d", p1[ i]->getPower());
		//printf("\n second =");
		//for (int i = 0; i < len2; ++i) printf(" %d", p2[i]->getPower());
		//printf("\n");
		Student** merged = mergeByLvl(p1, p2, len1, len2);
		//this->StudentsByPower.~AVLTree();
		//int nearest2pow = nearest2Pow(this->numberOfStudents) - 1;
		//int dif = nearest2pow - this->numberOfStudents;
		//StudentsByPower.createEmptyWholeAVLTree(nearest2pow);
		//StudentsByPower.removeInorderRightLeft(dif);
		this->StudentsByPower.fillInAVLTree(merged); // TODO: check leaks
		this->maxStudentByPower = *(merged[0]);
		delete[](merged);
	}
	delete(p1);
	delete(p2);
	free(students_by_power);
	sorted = true;
}

Student** Team::getStudentSortedByID(){
		return this->StudentsByStudentID.returnSortedTreeElementsInOrder();
}

void Team::setSorted(bool flag){
	if(this){
		this->sorted = flag;
	}
}

/*

void Team::joinById(Team to_join) {
	Student** c1 = getStudentSortedByID();
	Student** c2 = to_join.getStudentSortedByID();
	for(int i = 0; i < to_join.getNumOfStudents(); ++i) {
		c2[i]->setTeam(this);
	}
	Student** c3 = mergeById(c1, c2, getNumOfStudents(),
						 to_join.getNumOfStudents());
	int new_size = getNumOfStudents() + to_join.getNumOfStudents();
	this->StudentsByStudentID.~AVLTree();
	int nearest2pow = nearest2Pow(new_size) - 1;
	int dif = nearest2pow - new_size;
	StudentsByStudentID.createEmptyWholeAVLTree(nearest2pow);
	StudentsByStudentID.removeInorderRightLeft(dif);
	StudentsByStudentID.fillInAVLTree(c3);
	free(c1);
	free(c2);
	delete(c3);
}
void Team::joinByLvl(Team to_join) {
	Student** c1 = getAllStudentsSortedByPower();
	Student** c2 = to_join.getAllStudentsSortedByPower();
	for (int i = 0; i < to_join.getNumOfStudents(); ++i) {
		c2[i]->setTeam(this);
	}
	Student** c3 = mergeByLvl(c1, c2, getNumOfStudents(),
		to_join.getNumOfStudents());
	this->StudentsByPower.~AVLTree();
	int new_size = getNumOfStudents() + to_join.getNumOfStudents();
	int nearest2pow = nearest2Pow(new_size) - 1;
	int dif = nearest2pow - new_size;
	StudentsByPower.createEmptyWholeAVLTree(nearest2pow);
	StudentsByPower.removeInorderRightLeft(dif);
	StudentsByPower.fillInAVLTree(c3);
	this->maxStudentByPower = *(c3[0]);
	free(c1);
	free(c2);
	delete(c3);
}

void Team::joinTeams(Team to_join){
	if (TeamID <= 0 || to_join.TeamID <= 0 || TeamID == to_join.TeamID ){
		throw TeamInvailedInput();
	}
	if (to_join.getNumOfStudents() < 1) return;
	this->joinById(to_join);
	this->joinByLvl(to_join);
	this->numberOfStudents = this->StudentsByStudentID.getSize();
}


*/
