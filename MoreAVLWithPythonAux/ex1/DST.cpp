/*
 * DS.cpp


 *
 *  Created on: 28 באפר׳ 2016
 *      Author: Ilya Kotlov
 */
#include "DST.h"
#include <iostream>
using std::cout;

static Student** mergeByLvl(Student** p1, Student** p2, int size1, int size2) {
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

void DST::addTeam(int teamID) {
	if(teamID <= 0){
		throw DSTInvailedInput();
	}
	Team* m = new Team(teamID); //TODO: update destructor;
	if(this->TeamsByID.AVLTreeContain(m)){
		delete m;
		throw DSTTeamAlreadyExist();
	}
	this->TeamsByID.insert(m);
	this->numberOfTeams++;
}

void DST::addStudent(int student_ID,int grade, int power) {
	if (student_ID <= 0 || grade < 0 || power <= 0 ){
		throw DSTInvailedInput();
	}
	Student* student = new Student(student_ID, grade, power);
	if(this->StudentsByStudentID.AVLTreeContain(student)){
		delete student;
		throw DSTStudentAllreadyExist();
	}
	this->StudentsByStudentID.insert(student);
	this->StudentsByPower.insert(student);
	if(StudentByPowerFunc()(&maxStudentByPower, student) < 0){
		this->maxStudentByPower = *student;
	}
	this->numberOfStudents++;
}

void DST::addStudentToTeam(int student_ID,int team_id){
	if(student_ID <= 0 || team_id <= 0) throw DSTInvailedInput();
	Team t(team_id);
	Team* team_ptr = this->TeamsByID.findElement(&t);
	Student s(student_ID);
	Student* student_ptr = this->StudentsByStudentID.findElement(&s);
	if(!team_ptr || !student_ptr) throw DSTTeamDoesNotExist();
	if(team_ptr == (Team*)(student_ptr->getTeam())) return;
	if(student_ptr->getTeam() != NULL){
		((Team*)(student_ptr->getTeam()))->removeStudent(student_ID);
	}
	student_ptr->setTeam((void*)(team_ptr));
	this->TeamsByID.findElement(&t)->addStudent(student_ptr);
}

void DST::removeStudent(int student_ID) {
	if (student_ID <= 0){
		throw DSTInvailedInput();
	}
	Student s(student_ID);
	if (!this->StudentsByStudentID.AVLTreeContain(&s)){
		throw DSTStudentDoesNotExist();
	}
	Student* student_ptr = this->StudentsByStudentID.findElement(&s);
	Team* t = static_cast<Team*> (student_ptr->getTeam());
	if(t) t->removeStudent(student_ID);
	this->StudentsByStudentID.deleteByInfo(student_ptr);
	this->StudentsByPower.deleteByInfo(student_ptr);
	AVLTreeNode<Student*, StudentByPowerFunc>* max =
			this->StudentsByPower.minPointerInAVLTree(
					this->StudentsByPower.getRoot());
	this->maxStudentByPower = max ? (*(max->getInfo())) : Student();
	delete student_ptr;
	this->numberOfStudents--;
}

Student** DST::getAllStudentsByPower(int teamId, int* numOfStudents) {
	if(numOfStudents==NULL || teamId==0){
		throw DSTInvailedInput();
	}
	Student** arrayOfStudents = NULL;
	if(teamId<0){
		if(this->numberOfStudents==0){
			assert(arrayOfStudents==NULL);
			*numOfStudents = 0;
			return NULL;
		}
		assert(this->numberOfStudents>0);
		arrayOfStudents = this->
				StudentsByPower.returnSortedTreeElementsInOrder();
		if(arrayOfStudents!=NULL){
			*numOfStudents = numberOfStudents;
		}
		return arrayOfStudents;
	}
	Team tmp(teamId);
	if(this->TeamsByID.find(&tmp)==NULL){
		assert(arrayOfStudents==NULL);
		throw DSTTeamDoesNotExist();
	}
	if(this->TeamsByID.find(&tmp)->getInfo()->getNumOfStudents()==0){
		assert(arrayOfStudents==NULL);
		*numOfStudents = 0;
		return NULL;
	}
	assert(this->TeamsByID.find(&tmp)!=NULL);
	arrayOfStudents = this->TeamsByID.find(&tmp)->
			getInfo()->getAllStudentsSortedByPower();
	if(arrayOfStudents!=NULL){
		*numOfStudents = this->TeamsByID.find(&tmp)->
				getInfo()->getNumOfStudents();
	}
	assert(*numOfStudents>0);
	return arrayOfStudents;
}

/*
void DST::replaceMagizooligst(int teaml_ID, int replace_ID) {
	if(teaml_ID <= 0 || replace_ID <= 0 || teaml_ID == replace_ID)
		throw TeamInvailedInput();
	Team mag_id(teaml_ID);
	Team mag_rep(replace_ID);
	if(!this->TeamsByID.AVLTreeContain(&mag_id) ||
	   !this->TeamsByID.AVLTreeContain(&mag_rep))
			throw DSTTeamDoesNotExist();
	Team* reciever = this->TeamsByID.findElement(&mag_rep);
	Team* giver = this->TeamsByID.findElement(&mag_id);
	this->TeamsByID.deleteByInfo(&mag_id);
	if (giver->getNumOfStudents() < 1) {
		delete giver;
		return;
	}
	reciever->joinTeams(*giver);
	delete giver;
}
*/

int DST::getNumOfStudents() {
	return this->numberOfStudents;
}

int DST::getNumOfTeams() {
	return this->numberOfTeams;
}

/*
static int nearest2Pow(int x) {
	int power = 1;
	while (power <= x) {
		power *= 2;
	}
	return power;
}

static int devideSortedArray(Student** students_by_power, int size, int first_index, Student ***res_arr) {
	assert(students_by_power != NULL || res_arr != NULL);
	int i = first_index, ind = 0;
	while (i < size - 1) {
		while (i < size-1 && (students_by_power[i]->getPower() > students_by_power[i + 1]->getPower() ||
			students_by_power[i]->getPower() == students_by_power[i + 1]->getPower())) {
			(*res_arr)[ind++] = students_by_power[i++];
		}
		(*res_arr)[ind++] = students_by_power[i++];
		for (; (i < size-1 && (students_by_power[i]->getPower() > students_by_power[i + 1]->getPower() ||
			students_by_power[i]->getPower() == students_by_power[i + 1]->getPower())); ++i);
	}
	return ind;
}
	
*/
/*
void DST::increaseLevel(int grade, int power_increase) {
	if(grade < 0 || power_increase <= 0) throw DSTInvailedInput();
	if (this->numberOfStudents == 0) return;
	if (this->numberOfStudents == 1) {
		if (this->StudentsByStudentID.getRoot()->getInfo()->getGrade() == grade)
			this->StudentsByStudentID.getRoot()->getInfo()->setPower(
				this->StudentsByStudentID.getRoot()->getInfo()->getPower() + power_increase);
		return;
	}
	Student** students_by_power =
			this->StudentsByPower.returnSortedTreeElementsInOrderRL();
	bool non = true;
	for(int i = 0; i < this->numberOfStudents; ++i)
		if(students_by_power[i]->getGrade() == grade){
			students_by_power[i]->setPower(students_by_power[i]->getPower() +
															power_increase);
			non = false;
		}
	if (non) {
		free(students_by_power);
		return;
	}
	Student** p1 = new Student*[this->numberOfStudents];
	Student** p2 = new Student*[this->numberOfStudents];
	int len1 = 1, len2 = 0;
	p1[0] = students_by_power[0];
	int k = 0;
	non = true;
	for (; (k < this->numberOfStudents - 1 && students_by_power[k]->getPower() > students_by_power[k + 1]->getPower()) || 
		   (k < this->numberOfStudents - 1 && students_by_power[k]->getPower() == students_by_power[k + 1]->getPower()); ++k);
	if (k < this->numberOfStudents - 1) {
		non = false;
		p2[0] = students_by_power[k + 1];
		len2++;
	}
	if (!non) {
		for (int i = 1; i < this->numberOfStudents; ++i) {
			if (students_by_power[i] == p2[0]) continue;
			if(students_by_power[i]->getPower() == p1[len1 - 1]->getPower()) p1[len1++] = students_by_power[i];
			if (students_by_power[i]->getPower() == p2[len2 - 1]->getPower()) p2[len2++] = students_by_power[i];
			if (students_by_power[i]->getPower() > p1[len1 - 1]->getPower() && students_by_power[i]->getPower() < p2[len2 - 1]->getPower())
				p2[len2++] = students_by_power[i];
			else if (students_by_power[i]->getPower() < p1[len1 - 1]->getPower() && students_by_power[i]->getPower() > p2[len2 - 1]->getPower())
				p1[len1++] = students_by_power[i];
			else if (students_by_power[i]->getPower() < p1[len1 - 1]->getPower() && students_by_power[i]->getPower() < p2[len2 - 1]->getPower()) {
				if (p1[len1 - 1]->getPower() < p2[len2 - 1]->getPower()) p1[len1++] = students_by_power[i];
				else p2[len2++] = students_by_power[i];
			}
		}
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
	Team** teams = this->TeamsByID.returnSortedTreeElementsInOrderRL();
	for(int i = 0; i < this->numberOfTeams; ++i) teams[i]->increaseLevel();
	delete[] (teams);
	delete[] (p1);
	delete[] (p2);
	free(students_by_power);
	
	
}

*/


void DST::increaseLevel(int grade, int power_increase) {
	if (grade < 0 || power_increase <= 0) throw DSTInvailedInput();
	if (this->numberOfStudents == 0) return;
	if (this->numberOfStudents == 1) {
		if (this->StudentsByStudentID.getRoot()->getInfo()->getGrade() == grade) {
			this->StudentsByStudentID.getRoot()->getInfo()->setPower(
			this->StudentsByStudentID.getRoot()->getInfo()->getPower() + power_increase);
		}
		this->maxStudentByPower = *(this->StudentsByPower.getRoot()->getInfo());
		return;
	}
	Student** students_by_power =
		this->StudentsByPower.returnSortedTreeElementsInOrderRL();
	bool non = true;
	int len1 = 0, len2 = 0;
	Student** p1 = new Student*[this->numberOfStudents];
	Student** p2 = new Student*[this->numberOfStudents];
	for (int i = 0; i < this->numberOfStudents; ++i) {
		if (students_by_power[i]->getGrade() == grade) {
			students_by_power[i]->setPower(students_by_power[i]->getPower() +
				power_increase);
			p1[len1++] = students_by_power[i];
			non = false;
			(static_cast<Team*> (students_by_power[i]->getTeam()))->setSorted(false);
		} else p2[len2++] = students_by_power[i];
	}
	if (non) {
		delete[]p1;
		delete[]p2;
		free(students_by_power);
		return;
	}
	
	if (!non) {
		Student** merged = mergeByLvl(p1, p2, len1, len2);
		this->StudentsByPower.fillInAVLTree(merged);
		this->maxStudentByPower = *(merged[0]);
		delete[](merged);
	}
	for (int i = 0; i < this->numberOfStudents; ++i)
		(static_cast<Team*>(students_by_power[i]->getTeam()))->increaseLevel(grade);
	delete[](p1);
	delete[](p2);
	free(students_by_power);

}

Student DST::getMostPowerful(int teaml_ID) {
	if(teaml_ID < 0) return this->maxStudentByPower;
	if(teaml_ID == 0) throw DSTInvailedInput();
	Team team_id(teaml_ID);
	if(!this->TeamsByID.AVLTreeContain(&team_id))
		throw DSTTeamDoesNotExist();
	return this->TeamsByID.findElement(&team_id)->getMostPowerful();
}

/*
int DST::getNumOfStudentsOfTeam(int teaml_ID) {
	if(teaml_ID <= 0) throw DSTInvailedInput();
	Team team_id(teaml_ID);
	if(!this->TeamsByID.AVLTreeContain(&team_id))
		throw DSTTeamDoesNotExist();
	return this->StudentsByStudentID.getSize();
}
 */

bool DST::containTeam(int teaml_ID) {
	Team mag_id(teaml_ID);
	return this->TeamsByID.AVLTreeContain(&mag_id);
}

Student** DST::getAllStudentOrderedByID(int teamId, int* numOfStudents) {
	if (numOfStudents == NULL || teamId == 0) {
		throw DSTInvailedInput();
	}
	Team mag_id(teamId);
	Student** arrayOfStudents = NULL;
	if (teamId<0) {
		if (this->numberOfStudents == 0) {
			assert(arrayOfStudents == NULL);
			numOfStudents = 0;
			return NULL;
		}
		assert(this->numberOfStudents>0);
		arrayOfStudents = this->StudentsByStudentID
			.returnSortedTreeElementsInOrder();
		if (arrayOfStudents != NULL) {
			*numOfStudents = numberOfStudents;
		}
		return arrayOfStudents;
	}
	if (this->TeamsByID.find(&mag_id) == NULL) {
		assert(arrayOfStudents == NULL);
		throw DSTTeamDoesNotExist();
	}
	if (this->TeamsByID.find(&mag_id)->getInfo()->getNumOfStudents() == 0) {
		assert(arrayOfStudents == NULL);
		*numOfStudents = 0;
		return NULL;
	}
	assert(this->TeamsByID.find(&mag_id) != NULL);
	arrayOfStudents = this->TeamsByID.find(&mag_id)->
		getInfo()->getStudentSortedByID();
	if (arrayOfStudents != NULL) {
		*numOfStudents = this->TeamsByID.find(&mag_id)->
			getInfo()->getNumOfStudents();
	}
	assert(*numOfStudents>0);
	return arrayOfStudents;
}
