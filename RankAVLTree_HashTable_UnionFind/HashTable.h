/*
 * HashTable.h
 *
 *  Created on: 3 αιεπι 2016
 *      Author: lior
 */
#include <iostream>
using std::cout;
using std::endl;
#ifndef HASHTABLE_H_
#define HASHTABLE_H_
#include "AVLTree.h"
#define arrSize 5
template<class type, class HashFunc, class CmpFunc, class treeFunc>
class HashTable {
private:
	AVLTree<type, treeFunc, treeFunc>** arr;
	int size;
	int numOfObject;
	HashFunc func;
	CmpFunc cmpFunc;
public:
	HashTable() {
		arr = new AVLTree<type, treeFunc, treeFunc>*[arrSize];

		for(int i=0; i<arrSize;i++){
			arr[i]= new AVLTree<type,treeFunc,treeFunc>();
		}
		size = arrSize;
		numOfObject = 0;
	}
	void insert(type element) {
		//Todo: check what happens if object is in;
		if (size == numOfObject) {
			size = size * 2;
			//AVLTree<type, treeFunc, treeFunc>** tmp=arr;
			arr=new AVLTree<type, treeFunc, treeFunc>*[size];
			for (int j = 0; j < size/2; j++) {
				AVLTree<type, treeFunc, treeFunc>* tree = arr[j] ;
				type *tmparr=(*tree).returnSortedTreeElementsInOrder();
				int treeSize=(*tree).getSize();
				for (int i = 0; i < treeSize; i++) {
					this->insert(tmparr[i]);
				}
			}
			//delete tmp;
			numOfObject = numOfObject / 2;
		}
		int place = func(element) % size;
		AVLTree<type, treeFunc, treeFunc>* treeAtPlace = arr[place] ;
		if((*treeAtPlace).AVLTreeContain(element)==false) {

			Troll troll=(Troll)element;
			(*treeAtPlace).insert(element);
			return;
		}
	}
	type find(int id) {
		int place = id % size;
		type temp(id,0);
		AVLTree<type, treeFunc, treeFunc>* tree = arr[place] ;
		if((*tree).AVLTreeContain(temp)==true){
				type element((*tree).findElement(temp));
				/*cout<<"kaki4"<<endl;
				cout<<tr.getTrollID();*/
				return element;
				/* AVLTreeNode<type,treeFunc,treeFunc>* kaki=(*tree).find(temp);
				 cout<<"kaki4";
				 kaki->getInfo();*/
		}

		type tmp(-1);
		return tmp;
	}
};

#endif /* HASHTABLE_H_ */
