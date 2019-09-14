 /*
 * Student.cpp
 *
 *  Created on: 3 αιεπι 2016
 *      Author: lior
 */
#include "Student.h"

int Student::getStudentID(){
	return this->ID;
}
int Student::getStudentSTR(){
	return this->STR;
}
int Student::getStudentTeam(){
	return this->team;
}
void Student::setStudentSTR(int str){
	if(str<0){
		throw StudentInvailedInput();
	}
	this->STR=str;
}
void Student::setStudentTeam(int team){
	if(team<0){
		throw StudentInvailedInput();
	}
	this->team=team;
}
/*
Student Student::operator=(Student src){
	Student tmp(src.ID,src.STR);
	tmp.setStudentTeam(src.Team);
	return tmp;
}
*/
