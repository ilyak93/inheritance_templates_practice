#include "Troll.h"
#include "HashTable.h"
#include "UnionFind.h"
#include "DST.h"
#include <iostream>
using std::cout;
using std::endl;
//int main(){
	/*HashTable<Troll,getIdForHash,cmpTroll,trollByIDfunc> HT;
	Troll a(6,4);
	Troll b(11,3);
	Troll c(13,42);
	Troll d(14,3);
	Troll e(15,4);
	Troll f(16,17);
	Troll g(123123,1);
	HT.insert(a);
	AVLTree<Troll,trollByIDfunc,trollByIDfunc> tree;
	tree.insert(a);
	tree.insert(b);
	HT.insert(b);
	HT.insert(c);
	HT.insert(d);
	HT.insert(e);
	HT.insert(f);
	HT.insert(g);*/
	/*int k=10;
	UnionFind u(k);
	u.Union(1,2);
	u.Union(6,4);
	u.Union(6,5);
	u.Union(6,1);*/
/*
	DST ds(10);
	ds.DSTaddTroll(1,5);
	ds.DSTaddTroll(2,7);
	ds.DSTaddTroll(3,3);
	ds.DSTaddTroll(15,2);
	ds.DSTaddTroll(18,4);
	ds.DSTaddTroll(19,1);
	ds.DSTassignTroll(19,1);
	ds.DSTassignTroll(15,2);
	ds.DSTassignTroll(18,2);
	ds.DSTassignTroll(3,3);
	ds.DSTjoinGroups(1,2);
	ds.DSTjoinGroups(3,1);
	{
			cout<<"kaki";
		}
		else{
			cout<<"hara";
	}
}
*/

#include "RankAVLTreeNode.h"
#include "RankAVLTree.h"
#include "Exceptions.h"
#include "iostream"

using std::endl;
using std::cout;

class Empty{};

class ComparePointerInt {
public:
	int operator()(int* p1, int* p2) const {
		int num1 = *p1;
		int num2 = *p2;

		if (num1 == num2) {
			return 0;
		}
		if (num1 < num2) {
			return 1;
		}
		return -1;
	}
};

class IntPrinter {
public:
	void operator()(int* p1) const {
		cout << *p1 << endl;
	}
};

template<class ObjectType>
class ContainerTranslator {
private:
	ObjectType* _array;
	int _itr;
	int _size;
public:
	ContainerTranslator<ObjectType>(int size){
		_array = (ObjectType*) malloc(sizeof(ObjectType)*size);
		_itr = 0;
		_size = size;
	}
	void operator()(ObjectType& obj) {
		_array[_itr++] = obj;
	}
	void print(){
		for (int i = 0; i < _size; i++){
			cout << _array[i] << endl;
		}
	}
};

int main() {
	/*int a = 1;
	int b = 0;
	Map<int, int> map(-1);
	map.insert(a,a);
	map.insert(b,b);
	for(Map<int, int>::iterator itr = map.begin(); itr != map.end(); ++itr) {
				cout << (*itr).first << " ";
	}
	*/
	/*
	 int a = 4;
	 int b = 6;
	 int c = 2;
	 int d = 7;
	 int e = 5;
	 int f = 3;
	 int g = 1;
	 RankAVLTreeNode<int*, ComparePointerInt, ContainerPusher<int>> tr1 = RankAVLTreeNode<int*, ComparePointerInt, ContainerPusher<int>>();
	 tr1.setInfo(&a);
	 tr1.setHeight(0);
	 RankAVLTreeNode<int*, ComparePointerInt, ContainerPusher<int>> tr2 = RankAVLTreeNode<int*, ComparePointerInt, ContainerPusher<int>>();
	 tr2.setInfo(&b);
	 tr2.setHeight(1);
	 tr1.setRight(&tr2);
	 RankAVLTreeNode<int*, ComparePointerInt, ContainerPusher<int>> tr3 = RankAVLTreeNode<int*, ComparePointerInt, ContainerPusher<int>>();
	 tr3.setInfo(&c);
	 tr3.setHeight(1);
	 tr1.setLeft(&tr3);
	 tr3.setParent(&tr1);
	 tr2.setParent(&tr1);

	 RankAVLTreeNode<int*, ComparePointerInt, ContainerPusher<int>> tr4 = RankAVLTreeNode<int*, ComparePointerInt, ContainerPusher<int>>();
	 tr4.setInfo(&d);
	 tr4.setHeight(2);
	 tr4.setParent(&tr2);
	 RankAVLTreeNode<int*, ComparePointerInt, ContainerPusher<int>> tr5 = RankAVLTreeNode<int*, ComparePointerInt, ContainerPusher<int>>();
	 tr5.setInfo(&e);
	 tr5.setHeight(2);
	 tr5.setParent(&tr2);
	 RankAVLTreeNode<int*, ComparePointerInt, ContainerPusher<int>> tr6 = RankAVLTreeNode<int*, ComparePointerInt, ContainerPusher<int>>();
	 tr6.setInfo(&f);
	 tr6.setHeight(2);
	 tr6.setParent(&tr3);
	 RankAVLTreeNode<int*, ComparePointerInt, ContainerPusher<int>> tr7 = RankAVLTreeNode<int*, ComparePointerInt, ContainerPusher<int>>();
	 tr7.setInfo(&g);
	 tr7.setHeight(2);
	 tr7.setParent(&tr3);

	 tr2.setRight(&tr4);
	 tr2.setLeft(&tr5);
	 tr3.setRight(&tr6);
	 tr3.setLeft(&tr7);
	 */
	 /*
	 tr1.printTree(&tr1, 0);

	 std::cout << "is tree full:  " << tr1.isFull() << std::endl;

	 tr1.printTree(tr1.find(&b),0);
	 */
	DST ds(3);
	ds.DSTaddTroll(1,1);
	ds.DSTaddTroll(2,2);
	ds.DSTaddTroll(3,3);
	ds.DSTassignTroll(1, 2);
	ds.DSTassignTroll(2, 2);
	ds.DSTassignTroll(3, 2);
	ds.DSTteamUpgrade(2, 3);



	RankAVLTree<Troll, trollBySTRFunc, Empty> TTree;
	Troll t1(1, 1);
	Troll t2(3, 2);
	Troll t3(2, 3);
	Troll same_str_t1(2, 1);
	TTree.insert(t1);
	TTree.insert(t2);
	TTree.insert(t3);
	int a = 10;
	 int b = 9;
	 int c = 8;
	 int d = 7;
	 int e = 6;
	 int f = 5;
	 int g = 4;
	 int h = 3;
	 int l = 2;


	//int a = 1;
	//int b = 2;
	//int c = 3;

	RankAVLTree<int*, ComparePointerInt, IntPrinter> tr1 = RankAVLTree<int*, ComparePointerInt, IntPrinter>();
	tr1.insert(&a);
	tr1.insert(&b);
	tr1.insert(&c);
	tr1.deleteByInfo(&c);
	 tr1.insert(&c);
	 tr1.insert(&d);
	 tr1.insert(&e);
	 tr1.insert(&f);
	 tr1.insert(&g);
	 tr1.insert(&h);
	 tr1.insert(&l);
	 int range = tr1.getRange(&e, &b);
	 cout<<range<<endl;
	 cout<<"kkkkkkkkkkkkkk"<<endl;
	 tr1.deleteByInfo(&l);
	 tr1.deleteByInfo(&h);
	 tr1.deleteByInfo(&g);
	 tr1.deleteByInfo(&f);
	 tr1.deleteByInfo(&e);
	 tr1.deleteByInfo(&d);
	 int** sorted_array = tr1.returnSortedTreeElementsInOrder();
	 int size = tr1.getSize();
	 for (int i = 0; i < size; i++) {
		 cout << *(sorted_array[i]) << endl;
	 }
	 IntPrinter printer;
	 tr1.operateInOrder(printer);



	return 0;
}
