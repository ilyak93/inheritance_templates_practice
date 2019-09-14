/*
 * UnionFind.cpp
 *
 *  Created on: 6 αιεπι 2016
 *      Author: lior
 */
#include "UnionFind.h"
int UnionFind::Find(int group){
	int tmpGroup=group;
	while(this->teams[group]!=-1){
		group=teams[group];
	}
	while(this->teams[tmpGroup]!=-1){
		teams[tmpGroup]=group;
		tmpGroup=teams[tmpGroup];
	}
	return group;
}
int UnionFind::Union(int groupA,int groupB){
	int A=this->Find(groupA);
	int B=this->Find(groupB);
	if(this->sizeOfTeams[A]>sizeOfTeams[B]){
		teams[B]=A;
		sizeOfTeams[A]=sizeOfTeams[A]+sizeOfTeams[B];
		this->groupName[B]=-1;
		sizeOfTeams[B]=-1;
		return A;
	}else{
		teams[A]=B;
		sizeOfTeams[B]=sizeOfTeams[A]+sizeOfTeams[B];
		this->groupName[B]=groupName[A];
		this->groupName[A]=-1;
		sizeOfTeams[A]=-1;
		return B;
	}
}
int UnionFind::findGroupName(int team){
	return groupName[this->Find(team)];
}

