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

const int arrSize = 5;

template<class type, class HashFunc, class CmpFunc, class treeFunc>
class HashTable {
private:
	AVLTree<type, treeFunc>** arr;
	int size;
	int numOfObject;
	HashFunc func;
	CmpFunc cmpFunc;
public:
	HashTable() {
		arr = new AVLTree<type, treeFunc>*[arrSize];

		for(int i=0; i<arrSize;i++){
			arr[i]= new AVLTree<type,treeFunc>();
		}
		size = arrSize;
		numOfObject = 0;
	}
	~HashTable(){
		for(int i=0; i<size;i++){
			delete arr[i];
		}
		delete[] arr;
	}
	void insert(type element) {
		//Todo: check what happens if object is in;
		if (size == numOfObject) {
			size = size * 2;
			//AVLTree<type, treeFunc, treeFunc>** tmp=arr;
			arr=new AVLTree<type, treeFunc>*[size];
			for (int j = 0; j < size/2; j++) {
				AVLTree<type, treeFunc>* tree = arr[j] ;
				type *tmparr=(*tree).returnSortedTreeElementsInOrder();
				int treeSize=(*tree).getSize();
				for (int i = 0; i < treeSize; i++) {
					this->insert(tmparr[i]);
				}
			}
			//delete tmp;
			//numOfObject = numOfObject / 2;
		}
		int place = func(element) % size;
		AVLTree<type, treeFunc>* treeAtPlace = arr[place] ;
		if((*treeAtPlace).AVLTreeContain(element)==false) {

			(*treeAtPlace).insert(element);
			return;
		}
	}
	type* find(int id) {
		int place = id % size;
		type temp(id, 0, 0);
		AVLTree<type, treeFunc>* tree = arr[place] ;
		if((*tree).AVLTreeContain(temp)==true){
			type& element = (((*tree).find(temp))->getInfo());
			return &element;
		}

		//type tmp(-1);
		//return tmp;
		return NULL;
	}
	void remove(int id) {
		(*(arr[id % size])).deleteByInfo((*(arr[id % size])).find(type(id,0,0))
			->getInfo());
		numOfObject--;
		if (size / 4 == numOfObject) {
					size = size / 2;
					//AVLTree<type, treeFunc, treeFunc>** tmp=arr;
					arr=new AVLTree<type, treeFunc>*[size];
					for (int j = 0; j < size*2 + size%2; j++) {
						AVLTree<type, treeFunc>* tree = arr[j] ;
						type *tmparr=(*tree).returnSortedTreeElementsInOrder();
						int treeSize=(*tree).getSize();
						for (int i = 0; i < treeSize; i++) {
							this->insert(tmparr[i]);
						}
					}
					//delete tmp;
					//numOfObject = numOfObject / 2;
				}
	}
};

#endif /* HASHTABLE_H_ */
