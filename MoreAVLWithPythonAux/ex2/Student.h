/*
 * Student.h
 *
 *  Created on: 3 αιεπι 2016
 *      Author: lior
 */

#ifndef STUDENT_H_
#define STUDENT_H_
#include "Exceptions.h"
class Student{

private:
	int ID;
	int STR;
	int team;
public:
	/*
	 * constructor for illegal Student
	 */
	Student():ID(-1),STR(-1),team(-1){};
	//c'Tor
	Student(int ID,int team, int str){
		if(ID<0 || str < 0){
			throw StudentInvailedInput();
		}
		this->ID=ID;
		this->team=team;
		this->STR=str;
	}

	explicit Student(int ID):ID(ID),STR(-1),team(-1){};
	Student(const Student& a){
		this->ID=a.ID;
		this->team=a.team;
		this->STR=a.STR;
	}
	//d'tor
	~Student(){};
	//return the ID of a Student
	int getStudentID();
	//return the strength of a Student
	int getStudentSTR();
	//return the team of a Student
	int getStudentTeam();
	/*
	 * set the strength of a Student
	 * in case of str to be under 0 it will throw StudentInvailedInput
	 */
	void setStudentSTR(int str);
	/*
	 * set the team of a Student
	 * in case of team to be under 0 it will throw StudentInvailedInput
	 */
	void setStudentTeam(int team);
	//Student operator=(Student& src);
};

//Comparator for Students by likes and secondly by ids
class StudentByPowerFunc {
public:
	int operator()(Student a, Student b) {
		if (a.getStudentSTR() == b.getStudentSTR()) {
			return (b.getStudentID() - a.getStudentID());
		}
		return a.getStudentSTR() - b.getStudentSTR();
	}
};

//Comparator for Students by likes and secondly by ids
class StudentByPowerFuncP {
public:
	int operator()(Student* a, Student* b) {
		if (!a || !b) return a - b;
		if (a->getStudentSTR() == b->getStudentSTR()) {
			return (b->getStudentID() - a->getStudentID());
		}
		return a->getStudentSTR() - b->getStudentSTR();
	}
};

//Comparator for Students by ids
class StudentByStudentIdFunc {
public:
	int operator()(Student a, Student b){
		return (a.getStudentID() - b.getStudentID());
	}
};

//Comparator for Students by ids
class StudentByStudentIdFuncP {
public:
	int operator()(Student* a, Student* b) {
		if (!a || !b) return a - b;
		return (a->getStudentID() - b->getStudentID());
	}
};

//funcion for comparing between two Students
class cmpStudent{
public:
	int operator()(Student a, Student b){
		if(a.getStudentID()==b.getStudentID()){
			return true;
		}
		return false;
	}
};
class getIdForHash{
public:
	int operator()(Student student){
		return student.getStudentID();
	}
};

//funcion for comparing between two Students
class studentGetSTR{
public:
	int operator()(Student a){
		return a.getStudentSTR();
	}
};

class studentGetSTRP {
public:
	int operator()(Student* a) {
		return a->getStudentSTR();
	}
};

#endif /* STUDENT_H_ */
