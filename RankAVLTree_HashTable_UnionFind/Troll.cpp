 /*
 * Troll.cpp
 *
 *  Created on: 3 αιεπι 2016
 *      Author: lior
 */
#include "Troll.h"

int Troll::getTrollID(){
	return this->ID;
}
int Troll::getTrollSTR(){
	return this->STR;
}
int Troll::getTrollTeam(){
	return this->Team;
}
void Troll::setTrollSTR(int str){
	if(str<0){
		throw TrollInvailedInput();
	}
	this->STR=str;
}
void Troll::setTrollTeam(int team){
	if(team<0){
		throw TrollInvailedInput();
	}
	this->Team=team;
}
/*
Troll Troll::operator=(Troll src){
	Troll tmp(src.ID,src.STR);
	tmp.setTrollTeam(src.Team);
	return tmp;
}
*/
