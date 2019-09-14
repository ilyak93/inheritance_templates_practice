/*
 * Team.h
 *
 *  Created on: 4 αιεπι 2016
 *      Author: lior
 */

#ifndef TEAM_H_
#define TEAM_H_
#include "Student.h"
#include "AVLTree.h"
#include "RankAVLTree.h"
class Team{
private:
	RankAVLTree<Student, StudentByPowerFunc, studentGetSTR> RankAVLTreeOfStudentsByStr;
	AVLTree<Student, StudentByStudentIdFunc> AVLTreeOfStudentsById;
	Student strongestStudent;
	int teamNum;
	int groupName;
	bool onAGroup;
	int number_of_wins;
	int students_num;
	void joinById(Team& to_join);
	void joinByLvl(Team& to_join);
public:
	/*c'tor for default team, note that you should use set team in order to
	 * change it to a specific one.
	 */
	Team(){
		Student tmp(-1);
		strongestStudent=tmp;
		teamNum=0;
		groupName=0;
		onAGroup=false;
		number_of_wins = 0;
		students_num= 0;
	}
	/*Team(const Team& s) {
		this->AVLTreeOfStudentsById = s.AVLTreeOfStudentsById;
		this->RankAVLTreeOfStudentsByStr = s.RankAVLTreeOfStudentsByStr;
		this->groupName = s.groupName;
		this->number_of_wins = s.number_of_wins;
		this->onAGroup = s.onAGroup;
		this->strongestStudent = s.strongestStudent;
		this->students_num = s.students_num;
		this->teamNum = s.teamNum;
	}*/
	~Team(){};
	/*
	 *The function gets i, which used to set a default team in to a specific one
	 *if i is under zero it will throw TeamInavailedInput exception.
	 */
	void setTeam(int i);
	/*
	 * return the team number
	 */
	int getTeamNum();
	/*
	 * return the group name, used if the number and and name is not the same
	 */
	int getGroupName();
	/*
	 * return the strongest troll on the team, in case there are none or
	 * any other reason it will return default troll with -1 values.
	 */
	Student getStrongestStudent();
	/*
	 * return true if the team is a part of a group
	 */
	bool isOnAGroup();
	/*
	 * set the strongestStudent to a new troll.
	 */
	void setStrongestStudent(Student t);
	/*
	 * set the strongestStudent to a new troll.
	 */
	//void updateStrongestStudent();

	void addStudent(Student& s);
	void removeStudent(Student& s);
	/*
		 * set the strongestStudent to a new troll.
		 */
	void joinWith(Team& t);
	/*
	 * set the group name to be the i number, in case i is under 0
	 * it will throw TeamInvailedInput.
	 */
	void setGroupName(int i);
	/*
			 * set the strongestStudent to a new troll.
			 */
	void fightWith(Team& t, int num_of_fighters);

	int getNumberOfWins();
};



#endif /* TEAM_H_ */
