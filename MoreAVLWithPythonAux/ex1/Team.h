/*
 * Team.h
 *
 *  Created on: 26 áàôø× 2016
 *      Author: Ilya
 */
#include "AVLTree.h"
#include "AVLTreeNode.h"
#include <math.h>
#include "Exceptions.h"
#include "Student.h"

using std::endl;
using std::cout;


//Comparator for Students by likes and secondly by ids
class StudentByPowerFunc {
public:
	int operator()(Student* a, Student* b) {
		if(!a || !b) return a - b;
		if (a->getPower() == b->getPower()) {
			return (b->getStudentID() - a->getStudentID());
		}
		return a->getPower() - b->getPower();
	}
};

//Comparator for Students by ids
class StudentByStudentIdFunc {
public:
	int operator()(Student* a, Student* b)
	{
		if (!a || !b) return a - b;
		return (a->getStudentID() - b->getStudentID());
	}
};

#ifndef Team_H_
#define Team_H_

#include "AVLTree.h"
class Team {
private:
	int TeamID;
	int numberOfStudents;
	Student maxStudentByPower;
	AVLTree<Student*, StudentByPowerFunc> StudentsByPower;
	AVLTree<Student*, StudentByStudentIdFunc> StudentsByStudentID;
	bool sorted;
	void joinById(Team to_join);
	void joinByLvl(Team to_join);
public:
	Team(int teamID=-1) : TeamID(teamID), numberOfStudents(0),sorted(false) {}
	~Team(){}
	;
	//return the Team ID;
	int getTeamID();
	//add a Student to the Team
	void addStudent(Student* student_ptr);
	//add a Student to the Team
	//void addStudentToTeam(Student* student_ptr);
	// delete a Student with the Student Id
	void removeStudent(int ID);
	//return the Student with maximum risk rank;
	Student getMostPowerful();
	//return an array of the Team Student sorted by risk rank;
	Student** getAllStudentsSortedByPower();
	//return an array of the Team Student sorted by ID;
	Student** getStudentSortedByID();
	//Increase risk rank to a Student with StudentID;
	void increaseLevel(int grade);
	//return the number of Students the Team holds
	int getNumOfStudents();
	//joins Team's to_join creatures to this Team creatures
	//void joinTeams(Team to_join);
	void setSorted(bool);

};

#endif /* Team_H_ */
