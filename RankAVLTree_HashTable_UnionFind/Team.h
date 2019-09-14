/*
 * Team.h
 *
 *  Created on: 4 αιεπι 2016
 *      Author: lior
 */

#ifndef TEAM_H_
#define TEAM_H_
#include "Troll.h"
class Team{
private:
	Troll strongestTroll;
	int teamNum;
	int groupName;
	bool onAGroup;
public:
	/*c'tor for default team, note that you should use set team in order to
	 * change it to a specific one.
	 */
	Team(){
		Troll tmp(-1);
		strongestTroll=tmp;
		teamNum=0;
		groupName=0;
		onAGroup=false;
	}
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
	Troll getStrongestTroll();
	/*
	 * return true if the team is a part of a group
	 */
	bool isOnAGroup();
	/*
	 * set the strongestTroll to a new troll.
	 */
	void setStrongestTroll(Troll t);
	/*
	 * set the group name to be the i number, in case i is under 0
	 * it will throw TeamInvailedInput.
	 */
	void setGroupName(int i);
};



#endif /* TEAM_H_ */
