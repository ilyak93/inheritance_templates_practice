/*
 * UnionFind.h
 *
 *  Created on: 6 αιεπι 2016
 *      Author: lior
 */

#ifndef UNIONFIND_H_
#define UNIONFIND_H_
#include "stdio.h"
#include "stdlib.h"
class UnionFind{
private:
	int *teams;
	int *sizeOfTeams;
	int *groupName;
public:
	UnionFind(){
		int *kaki=NULL;
		teams=kaki;
		sizeOfTeams=kaki;
		groupName=kaki;
	}
	//c'tor create a Union/Find DS sized n
	UnionFind(int n){
		teams=new int[n];
		sizeOfTeams=new int[n];
		groupName=new int[n];
		for(int i=0;i<n;i++){
			sizeOfTeams[i]=1;
			teams[i]=-1;
			groupName[i]=i;
		}
	}
	//d'tor
	~UnionFind(){};
	void Destroyer(){
		delete[] teams;
		delete[] sizeOfTeams;
		delete[] groupName;
	}
	//find function of Union/Find
	int Find(int group);
	//Union function of Union/Find DS,
	//return the group number of the larger group
	//(which is also the new combined group)
	int Union(int groupA,int groupB);
	//return the name of a groupName
	int findGroupName(int team);
};



#endif /* UNIONFIND_H_ */
