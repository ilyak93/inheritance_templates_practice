/*
 * DS.h
 *
 *  Created on: 27 באפר׳ 2016
 *      Author: Ilya Kotlov
 */

#ifndef DST_H_
#define DST_H_
#include <assert.h>
#include "Team.h"

//Comparator for Students by ids
class TeamByTeamIDFunc {
public:

	int operator()(Team* a, Team* b) {
		if(!a || !b) return a - b;
		return (a->getTeamID() - b->getTeamID());
	}
};

class DST {
private:
	Student maxStudentByPower;
	int numberOfStudents;
	int numberOfTeams;
	AVLTree<Student*, StudentByStudentIdFunc> StudentsByStudentID;
	AVLTree<Student*, StudentByPowerFunc> StudentsByPower;
	AVLTree<Team*, TeamByTeamIDFunc> TeamsByID;
public:
	//noParam Ctor
	DST() : numberOfStudents(0), numberOfTeams(0) {}
	;
	//Dtor
	~DST() {

		int st_size = StudentsByPower.getSize();
		if(st_size != 0){
			Student**st_to_delete=StudentsByPower.returnSortedTreeElementsInOrder();
			for(int i = 0; i < st_size; ++i) {
				delete st_to_delete[i];
			}
			free(st_to_delete);
		}
		int tm_size = TeamsByID.getSize();
		if(tm_size == 0) return;
		Team **tm_to_delete = TeamsByID.returnSortedTreeElementsInOrder();
		for (int i = 0; i < tm_size; ++i) {
			delete tm_to_delete[i];
		}
		free(tm_to_delete);
	}
	/*
	 * return array Students ordered by risk rank
	 * throw exception in case of problem
	 */

	Student** getAllStudentsByPower(int magiId, int* numOfStudents);

	/*
		 * return array Students ordered by ids
		 * throw exception in case of problem
		 */
	Student** getAllStudentOrderedByID(int magiId, int* numOfStudents);


	/*
	 * Get Student ID and and risk rank to increase, it adds the Student with Student ID the
	 * number of rank
	 */
	void increaseLevel(int grade, int power_increase);
	/*
	 * Get Student ID and delete the Student with the ID;
	 */
	void removeStudent(int student_ID);
	/*
	 	* Gets 2 Ids and adds all the students of  team_ID to another replace_ID
	*/
	//void replaceMagizooligst(int team_ID, int replace_ID);
	/*
	 * add a new Student with the Student ID to its owner TeamID and rank
	 * to the system. make sure there is no Student like it and the Team exists
	 * and the rank is positive.
	 */
	void addStudent(int student_ID,int team_id, int level);
	/*
		 * add a new Student with the Student ID to its owner TeamID and rank
		 * to the system. make sure there is no Student like it and the Team exists
		 * and the rank is positive.
		 */
	void addStudentToTeam(int student_ID,int team_id);
	//The function add a new Team to the DS, make sure the Team is not exist
	// and the TeamID is positive;
	void addTeam(int TeamID);
	//return the the Student of Team with Team ID with maximum danger rank;
	Student getMostPowerful(int TeamID);
	//return the numb1er of Students of the DS;
	int getNumOfStudents();
        //return the number of Students of a Team;
        //int getNumOfStudentsOfTeam(int TeamID);
	//return the number teams;
	int getNumOfTeams();
	//checks if the Team is already exist
	bool containTeam(int TeamID);
	//checks if the Student is already exist;
	//bool containStudent(int StudentID);

};

#endif /* DST_H_ */
