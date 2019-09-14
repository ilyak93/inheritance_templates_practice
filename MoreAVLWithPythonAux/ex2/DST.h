/*
 * DS.h
 *
 *  Created on: 4 αιεπι 2016
 *      Author: lior
 */
#include "AVLTree.h"
#include "HashTable.h"
#include "Team.h"
#include "UnionFind.h"
#include "RankAVLTree.h"
#include "Student.h"
class DST{
private:
	RankAVLTree<Student, StudentByPowerFunc, studentGetSTR> RankAVLTreeOfStudentsByStr;
	AVLTree<Student,StudentByStudentIdFunc> AVLTreeOfStudentsById;
	HashTable<Student,getIdForHash,cmpStudent,StudentByStudentIdFunc> HT;
	Team *teams;
	int size;
	int students_num; //Todo: update everywhere Students_num
	UnionFind UF;
	int *groupNameToOwner;
	void updateTreeById(int S, int factor);
	// An auxulary funcion to update the Strength Tree
	Student updateRankTreeByStr(int S, int factor);
	// An auxulary funcion to update the ID Tree
	void updateTreeByID(int S, int factor);
public:
	/*
	 * c'tor for creating a new data structure with amounts of team n
	 * in case of n under 2 it will throw DSTInvalidInput
	 */
	DST(int n){
		if(n<1) throw DSTInvailedInput(); //ToDo: check fight and join
		teams=new Team[n];
		groupNameToOwner=new int[n];
		for(int i=0;i<n;i++){
			teams[i].setTeam(i);
			groupNameToOwner[i]=i;
		}
		size=n;
		UF.~UnionFind();
		UnionFind temp1(n);
		UF=temp1;
		this->students_num = 0;
	}
	~DST(){
		delete[] teams;
		delete[] groupNameToOwner;
		UF.Destroyer();
	}
	/*
	 * Adds a new Student to the DS, if id or str are under 0 it will throw
	 * DSTInavalidInput. if there is already a Student with that name it will
	 * throw DSTFAILURE
	 */
	void DSTaddStudent(int id, int team, int str);
	/*
	 * Assign a Student to a group if id or str are under 0 it will throw
	 * DSTInvaliedInput.if there is no Student with id or it already has different
	 * it will throw DSTFAILURE
	 */
	//void DSTassignStudent(int id, int team);
	/*
	 * Get Student ID and delete the Student with the ID;
	 */
	void DSTremoveStudent(int student_ID);
	/*
	 * merge the teams of the group of t2 into the group of t1
	 * if t1 or t2 are under 0 or the t are over n it will throw DSTInvalidInput
	 * if teams are at the same group it will throw DSTFAILURE
	 */
	void DSTjoinTeams(int t1, int t2);
	/*
	 * return the name of the group which the trool with id is belongs to.
	 * if id is under 0 it will throw DSTInvalidInput
	 * if the Student has no group or not in the DS it throw DSTFAILURE
	 */
	int DSTgetGroup(int id);
	/*
	 * multiply all the Students strength with factor
	 * if teamId is under 0, or factor under 1 or teamId is over n-1
	 * it will throw DSTInvalidInput
	 */
	int DSTteamUpgrade(int teamID, int factor);
	/*
		 * multiply all the Students strength with factor
		 * if teamId is under 0, or factor under 1 or teamId is over n-1
		 * it will throw DSTInvalidInput
		 */
	void DSTteamFight(int team1, int team2, int num_of_fighters);
	/*
		 * return the strongest Student of a group with id;
		 * if id  is under 0 or over n-1 it will throw DSTInvailedInput
		 */
	int DSTgetNumOfWins(int team);
	/*
	 * return the strongest Student of a group with id;
	 * if id  is under 0 or over n-1 it will throw DSTInvailedInput
	 */
	int DSTgetStudentTeamLeader(int id);
	/*
	 * return the number of Students at DS which there strength is over min and
	 * under max+1;
	 */
	int DSTgetNumberOfStudentsInRange(int min_str, int max_str);
	//return the number of teams in the DST
	int DSTGetSize();
	//return the team of a Student, (if there is no Student or there is no team -1)
	int getStudentTeam(int id);
	//check if a Student Exist
	bool isStudentExist(int id);
	//return true if t1,t2 is at the same group, it return false if t1 or t2
	//is out of range
	bool isOnSameGroup(int t1, int t2);
};



