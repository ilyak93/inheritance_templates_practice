/*
 * Team.cpp
 *
 *  Created on: 4 αιεπι 2016
 *      Author: lior
 */
#include "Team.h"
int Team::getGroupName(){
	return this->groupName;
}
int Team::getTeamNum(){
	return this->teamNum;
}
Troll Team::getStrongestTroll(){
	return this->strongestTroll;
}
bool Team::isOnAGroup(){
	return this->onAGroup;
}
void Team::setStrongestTroll(Troll t){
	this->strongestTroll=t;
}
void Team::setGroupName(int i){
	groupName=i;
	onAGroup=true;
}
void Team::setTeam(int i){
	if(i<0) throw TeamInvailedInput();
	teamNum=i;
	groupName=i;

}
