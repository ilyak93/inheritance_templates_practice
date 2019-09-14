/*
 * Student.cpp
 *
 *  Created on: 26 באפר׳ 2016
 *      Author: Ilya Kotlov
 */

#include <iostream>
#include <string>

#include "Student.h"

Student::Student(int student_ID, int grade, int power) :
		student_ID(student_ID),
		grade(grade),
		power(power),
		ptr_to_team(NULL)  {}

Student::Student(const Student& student) {
	this->student_ID = student.student_ID;
	this->grade = student.grade;
	this->power = student.power;
	this->ptr_to_team = student.ptr_to_team;
}

void Student::setPower(int power){
	this->power=power;
}

int Student::getPower(){
	return this->power;
}

void Student::setGrade(int new_grade){
	this->grade = new_grade;
}

int Student::getGrade(){
	return this->grade;
}

int Student::getStudentID(){
	return this->student_ID;
}


void Student::setTeam(void* ptr){
	if(!ptr) return;
	this->ptr_to_team = ptr;
}

void* Student::getTeam(){
	return this->ptr_to_team;
}

ostream& operator<<(ostream& os, const Student& c){
	os <<"ID:" << c.student_ID << " " << "power:" << c.power << std::endl;
	return os;
}



