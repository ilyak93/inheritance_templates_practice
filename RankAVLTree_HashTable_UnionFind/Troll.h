/*
 * Troll.h
 *
 *  Created on: 3 αιεπι 2016
 *      Author: lior
 */

#ifndef TROLL_H_
#define TROLL_H_
#include "Exceptions.h";
class Troll{

private:
	int ID;
	int STR;
	int Team;
public:
	/*
	 * constructor for illegal troll
	 */
	Troll():ID(-1),STR(-1),Team(-1){
		ID=-1;
	};
	//c'Tor
	Troll(int ID, int str){
		if(ID<0 || str < 0){
			throw TrollInvailedInput();
		}
		this->ID=ID;
		this->STR=str;
		this->Team=-1;
	}

	Troll(int n):ID(-1),STR(-1),Team(-1){};
	Troll(const Troll& a){
		this->ID=a.ID;
		this->STR=a.STR;
		this->Team=a.Team;
	}
	//d'tor
	~Troll(){};
	//return the ID of a troll
	int getTrollID();
	//return the strength of a troll
	int getTrollSTR();
	//return the team of a troll
	int getTrollTeam();
	/*
	 * set the strength of a troll
	 * in case of str to be under 0 it will throw TrollInvailedInput
	 */
	void setTrollSTR(int str);
	/*
	 * set the team of a troll
	 * in case of team to be under 0 it will throw TrollInvailedInput
	 */
	void setTrollTeam(int team);
	//Troll operator=(Troll& src);
};
//function for trees to compare between troll by ID
class trollByIDfunc{
public:
	int operator()(Troll a, Troll b){
		return b.getTrollID()-a.getTrollID();
	}
};
//function for trees to compare between troll by strength and then by ID
class trollBySTRFunc{
public:
	int operator()(Troll a, Troll b){
		if(a.getTrollSTR()==b.getTrollSTR()){
			return b.getTrollID()-a.getTrollID(); /// maybe a-b 
		}
		return b.getTrollSTR()-a.getTrollSTR();
	}
};
//funcion for comparing between two trolls
class cmpTroll{
public:
	int operator()(Troll a, Troll b){
		if(a.getTrollID()==b.getTrollID()){
			return true;
		}
		return false;
	}
};
class getIdForHash{
public:
	int operator()(Troll troll){
		return troll.getTrollID();
	}
};
#endif /* TROLL_H_ */
