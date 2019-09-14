/*
 * UnionFind.h
 *
 *  Created on: 6 αιεπι 2016
 *      Author: lior
 */
#include <iostream>
using std::cout;
using std::endl;
#ifndef UNIONFIND_H_
#define UNIONFIND_H_
class UnionFind{
private:
	int *teams;
	int *sizeOfTeams;
public:
	UnionFind(){
		teams=new int[1];
		sizeOfTeams=new int[1];
	}
	//c'tor create a Union/Find DS sized n
	UnionFind(int n){
		teams=new int[n];
		sizeOfTeams=new int[n];
		for(int i=0;i<n;i++){
			sizeOfTeams[i]=1;
			teams[i]=-1;
		}
	}
	//d'tor
	~UnionFind(){};
	//find function of Union/Find DS
	int Find(int group);
	//Union function of Union/Find DS,
	//return the group number of the larger group
	//(which is also the new combined group)
	int Union(int groupA,int groupB);
};



#endif /* UNIONFIND_H_ */
