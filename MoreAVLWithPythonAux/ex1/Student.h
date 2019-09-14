/*
 * Student.h
 *
 *  Created on: 26 באפר׳ 2016
 *      Author: Ilya Kotlov
 */

#ifndef Student_H_
#define Student_H_
#include <iostream>
#include <string>
using std::istream;
using std::ostream;

class Student {

private:

	int student_ID;
	int grade;
	int power;
	void* ptr_to_team;

public:

	Student(int student_ID = -1, int grade = -1, int power = -1);

	~Student() {}

	Student(const Student& student);
	//edit the Student power.
	void setPower(int power);
	// return power.
	int getPower();
	//return the StudentID.
	int getStudentID();
	// return grade.
	int getGrade();
	// return grade.
	void setGrade(int new_grade);
	// sets the address of the team
	void setTeam(void* ptr);
	// return the team ptr
	void* getTeam();
	//print student
	 friend ostream& operator<<(ostream& os, const Student& c);
};

#endif /* Student_H_ */

