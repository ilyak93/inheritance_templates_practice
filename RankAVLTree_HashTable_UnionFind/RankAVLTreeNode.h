/*
 * RankRankAVLTreeNode.h
 *
 *  Created on: 7 αιεπι 2016
 *      Author: lior
 */

#ifndef RANKAVLTREENODE_H_
#define RANKAVLTREENODE_H_

#include <stddef.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <math.h>
//class TreeElement is the class of the AVLTree and the class Comparator is the function object,
//to which the AVLTree is sorted by, Operation is generice functor to the user
//to use.
template<class TreeElement, class Comparator, class Operation>
class RankAVLTreeNode {
private:
	TreeElement* data;
	RankAVLTreeNode* parent;
	RankAVLTreeNode* leftSon;
	RankAVLTreeNode* rightSon;
	int height;
	int rank;
public:
	RankAVLTreeNode();
	/**b
	 * copy constructor for Node
	 */
	RankAVLTreeNode(const RankAVLTreeNode<TreeElement, Comparator, Operation>& tr);
	/**
	 * copy constructor for Node
	 */
	RankAVLTreeNode(const RankAVLTreeNode<TreeElement, Comparator, Operation>* tr);
	~RankAVLTreeNode();
	/**
	 * returns the data stored in the Node, if there is no Data return NULL
	 */
	TreeElement& getData() const;

	/**
	 * returns the Parent of the Node
	 */
	RankAVLTreeNode<TreeElement, Comparator, Operation>* getParent() const;

	/**
	 * returns the leftSon
	 */
	RankAVLTreeNode<TreeElement, Comparator, Operation>* getLeftSon() const;

	/**
	 * returns the rightSon
	 */
	RankAVLTreeNode<TreeElement, Comparator, Operation>* getRightSon() const;

	/**
	 * returns the height of the node, default is 0;
	 */
	const int getHeight() const;

	/**
	 * set a new height to the Node;
	 */
	void setHeight(int height);
	/**
	 * set the rightSon to be "right"
	 */
	void setRight(RankAVLTreeNode<TreeElement, Comparator, Operation>* right);
	/**
	 * set the rightSon to be "left"
	 */
	void setLeft(RankAVLTreeNode<TreeElement, Comparator, Operation>* left);
	/**
	 * set the node parent to be "parent"
	 */
	void setParent(RankAVLTreeNode<TreeElement, Comparator, Operation>* parent);
	/**
	 * set the Data of the Element to be "data"
	 */
	void setData(const TreeElement& data);
	/**
	 *locate a the data
	 */
	RankAVLTreeNode<TreeElement, Comparator, Operation>* find(
			const TreeElement& Data);
	/**
	 * delete all the data at the tree under the Node
	*/
		void deletePostOrder();

	/**
	 *@param n is the number of vertices we want to create a new whole tree
	 which can contain all old vertices (its number of vertices is the nearest
	 pow of 2 which is bigger.
	 */
	void createEmptyWholeRankAVLTreeNode(int n);
	/**
	 * returns if a Node is a leaf
	 */
	bool isLeaf();
	/**
	 * checks if there is only one son
	 */
	bool isOneChild();
	/**
	 * @param sorted_array is the array in which will be put
	 *  the TreeElements by InOrder.
	 * @param itr is the iterator on the array
	 * passes on all the vertices in the tree by inorder and
	 *  put them into given array
	 */
	void returnSortedTreeElements(TreeElement* sorted_array, int& itr);
	/**
	 *@param arr is the array we translate to Tree and itr is an aux param
	 */
	void arrayToRankAVLTreeNode(TreeElement* arr, int& itr);
	/**
	 * passes on all the vertices in the tree by inorder and does an
	 *  operation on each data element in it.
	 */
	void operateInOrder(Operation& op);

	/**
	 * Aux function to delete unnececery vertices to make from whole tree
	 *  almost whole tree
	 */
	void deleteInOrderRL(int& n);
	/**
	 * returns the height of rightSon - the height leftSon
	 */
	int calculateBalanceFactor();
	/**
	 * returns max height between 2 nodes, usually will be used to check for 2
	 * sons;
	 */
	int getMaxHeightOfSons(RankAVLTreeNode<TreeElement, Comparator, Operation>* trn1,
			RankAVLTreeNode<TreeElement, Comparator, Operation>* trn2);
	/**
	 * set this Node height, according to it's sons
	 */
	void setHeightBasedOnSons();

	/**
	 * returns the number of Nodes under this node.
	 */
	int getSize();
	/**
	 * D'tor
	 */
	/**
		 * returns the rank stored in the current RankRankAVLTreeNode, if current is NULL,
		 *  0 is returned as rank of empty son (0(left)+0(right)+0(itself)).
		 *  rank of a leaf is 1, the rank generally is rank of left + rank of right
		 *  + %curent_value
		 */
		int getRank() const;
		/**
		 * sets the new rank in the current RankRankAVLTreeNode, if current is NULL,
		 *  does nothing.
		 */
		 void setRank(int new_rank);
		/**
		* returns the number of elements which are bigger (or equal, depends on the
		* comparator) from given element by some paramaeter defined in comparator
		*
		* @param
		*   element - fiven element with built-in parameter to compare.
		*
		* return
		*  number of elements are bigger
		*/
		int getBigger(const TreeElement& info);
		/**
		* returns the number of elements which are smaller (or equal, depends on the
		* comparator) from given element by some paramaeter defined in comparator
		*
		* @param
		*   element - fiven element with built-in parameter to compare.
		*
		* return
		*  number of elements are smaller
		*/
		int getSmaller(const TreeElement& info);

};

template<class TreeElement, class Comparator, class Operation>
RankAVLTreeNode<TreeElement, Comparator, Operation>::RankAVLTreeNode() {
	this->height = 0;
	this->data = new TreeElement();
	this->leftSon = NULL;
	this->rightSon = NULL;
	this->parent = NULL;
	this->rank=1;
}
/**
 * copy constructor for RankAVLTreeNode
 */
template<class TreeElement, class Comparator, class Operation>
RankAVLTreeNode<TreeElement, Comparator, Operation>::RankAVLTreeNode(
		const RankAVLTreeNode<TreeElement, Comparator, Operation>& tr) {
	this->height = tr.getHeight();
	this->parent = new RankAVLTreeNode<TreeElement, Comparator, Operation>(
			tr.getParent());
	this->data = new TreeElement(tr.getData());
	this->rightSon = new RankAVLTreeNode<TreeElement, Comparator, Operation>(
			tr.getRightSon());
	this->leftSon = new RankAVLTreeNode<TreeElement, Comparator, Operation>(
			tr.getLeftSon());
	this->rank=tr->getRank();
}

/**
 * copy constructor
 */
template<class TreeElement, class Comparator, class Operation>
RankAVLTreeNode<TreeElement, Comparator, Operation>::RankAVLTreeNode(
		const RankAVLTreeNode<TreeElement, Comparator, Operation>* tr) {
	if(this == NULL || tr == NULL) return;
	if (this != NULL && tr != NULL) {
		this->height = tr->getHeight();
		if (tr->getParent() == NULL) {
			this->parent = NULL;
		}
		this->data = new TreeElement(tr->getData());
		if (tr->getRightSon() == NULL) {
			this->rightSon = NULL;
		} else {
			this->rightSon = new RankAVLTreeNode<TreeElement, Comparator, Operation>(
					tr->getRightSon());
			(this->getRightSon())->parent = this;
		}
		if (tr->getLeftSon() == NULL) {
			this->leftSon = NULL;
		} else {
			this->leftSon = new RankAVLTreeNode<TreeElement, Comparator, Operation>(
					tr->getLeftSon());
			(this->getLeftSon())->parent = this;
		}
		this->rank=tr->getRank();
	}
}
template<class TreeElement, class Comparator, class Operation>
RankAVLTreeNode<TreeElement, Comparator, Operation>::~RankAVLTreeNode() {
	if (this == NULL) {
		return;
		}
	delete this->data;
}

template<class TreeElement, class Comparator, class Operation>
TreeElement& RankAVLTreeNode<TreeElement, Comparator, Operation>::getData() const {
	return *(this->data);
}

template<class TreeElement, class Comparator, class Operation>
const int RankAVLTreeNode<TreeElement, Comparator, Operation>::getHeight() const {
	if (this == NULL) {
		return 0;
	}
	return this->height;

}

template<class TreeElement, class Comparator, class Operation>
RankAVLTreeNode<TreeElement, Comparator, Operation>* RankAVLTreeNode<TreeElement,
		Comparator, Operation>::getRightSon() const {
	if (this == NULL) {
		return NULL;
	}
	return this->rightSon;

}

template<class TreeElement, class Comparator, class Operation>
RankAVLTreeNode<TreeElement, Comparator, Operation>* RankAVLTreeNode<TreeElement,
		Comparator, Operation>::getLeftSon() const {
	if (this == NULL) {
		return NULL;
	}
	return this->leftSon;

}

template<class TreeElement, class Comparator, class Operation>
RankAVLTreeNode<TreeElement, Comparator, Operation>* RankAVLTreeNode<TreeElement,
		Comparator, Operation>::getParent() const {
	if (this == NULL) {
		return NULL;;
	}
	return this->parent;

}

template<class TreeElement, class Comparator, class Operation>
void RankAVLTreeNode<TreeElement, Comparator, Operation>::setHeight(int height) {
	if(height < 0)return;
	if (this != NULL) {
		this->height = height;
	}else{
		return;
	}
}
template<class TreeElement, class Comparator, class Operation>
void RankAVLTreeNode<TreeElement, Comparator, Operation>::setRight(
		RankAVLTreeNode<TreeElement, Comparator, Operation>* right) {
	if (this != NULL) {
		this->rightSon = right;
	}else{
		return;
	}
}

template<class TreeElement, class Comparator, class Operation>
void RankAVLTreeNode<TreeElement, Comparator, Operation>::setLeft(
		RankAVLTreeNode<TreeElement, Comparator, Operation>* left) {
	if (this != NULL) {
		this->leftSon = left;
	}else{
		return;
	}
}

template<class TreeElement, class Comparator, class Operation>
void RankAVLTreeNode<TreeElement, Comparator, Operation>::setParent(
		RankAVLTreeNode<TreeElement, Comparator, Operation>* parent) {
	if (this != NULL) {
		this->parent = parent;
	}else{
		return;
	}
}

template<class TreeElement, class Comparator, class Operation>
void RankAVLTreeNode<TreeElement, Comparator, Operation>::setData(
		const TreeElement& data) {
	if (this != NULL) {
		if (this->data != NULL) {
			delete this->data;
		}
		this->data = new TreeElement(data);
	}else{
		return;
	}
}

template<class TreeElement, class Comparator, class Operation>
RankAVLTreeNode<TreeElement, Comparator, Operation>* RankAVLTreeNode<TreeElement,
		Comparator, Operation>::find(const TreeElement& info) {

	if (this == NULL) {
		return NULL;
	}
	Comparator compare;
	if (compare(this->getData(), info) == 0) {
		return this;
	}
	else if (compare(info, this->getData()) > 0) {
		return (this->getLeftSon())->find(info);
	}else{
	return (this->getRightSon())->find(info);
	}
}
template<class TreeElement, class Comparator, class Operation>
void RankAVLTreeNode<TreeElement, Comparator, Operation>::deletePostOrder() {
	if (this != NULL) {
		(this->getLeftSon())->deletePostOrder();
		(this->getRightSon())->deletePostOrder();
		delete this;
	}
}

template<class TreeElement, class Comparator, class Operation>
bool RankAVLTreeNode<TreeElement, Comparator, Operation>::isLeaf() {
	if (this->getLeftSon() == NULL && this->getRightSon() == NULL)
		{return true;}
	else{
		return false;
	}
}

template<class TreeElement, class Comparator, class Operation>
bool RankAVLTreeNode<TreeElement, Comparator, Operation>::isOneChild() {
	if ((this->getLeftSon() == NULL && this->getRightSon() != NULL)
		|| (this->getLeftSon() != NULL && this->getRightSon() == NULL)){
		return true;
	}else{
		return false;
	}
}

template<class TreeElement, class Comparator, class Operation>
void RankAVLTreeNode<TreeElement, Comparator, Operation>::operateInOrder(
		Operation& op) {
	if (this != NULL) {
		(this->getLeftSon())->operateInOrder(op);
		op(this->getData());
		(this->getRightSon())->operateInOrder(op);
	}
}

template<class TreeElement, class Comparator, class Operation>
void RankAVLTreeNode<TreeElement, Comparator, Operation>::createEmptyWholeRankAVLTreeNode(
		int n) {
	if (n <= 2) {
		this->setLeft(NULL);
		this->setRight(NULL);
		this->setHeight(0);
		return;
	}
	RankAVLTreeNode<TreeElement, Comparator, Operation>* left = new RankAVLTreeNode<
			TreeElement, Comparator, Operation>;
	left->setParent(this);
	this->setLeft(left);
	RankAVLTreeNode<TreeElement, Comparator, Operation>* right = new RankAVLTreeNode<
			TreeElement, Comparator, Operation>;
	right->setParent(this);
	this->setRight(right);

	n /= 2;
	left->createEmptyWholeRankAVLTreeNode(n);
	right->createEmptyWholeRankAVLTreeNode(n);
	this->setHeight(log(n) + 1);
	this->rank=this->leftSon.rank + this->rightSon.rank+1;
}

template<class TreeElement, class Comparator, class Operation>
void RankAVLTreeNode<TreeElement, Comparator, Operation>::returnSortedTreeElements(
		TreeElement* sorted_array, int& itr) {
	if (this != NULL) {
		(this->getLeftSon())->returnSortedTreeElements(sorted_array, itr);
		sorted_array[itr++] = this->getData();
		(this->getRightSon())->returnSortedTreeElements(sorted_array, itr);
	}
}



template<class TreeElement, class Comparator, class Operation>
void RankAVLTreeNode<TreeElement, Comparator, Operation>::deleteInOrderRL(int& n) {
	if (this != NULL) {
		(this->getRightSon())->deleteInOrderRL(n);
		if (this->isLeaf() && n > 0) {
			RankAVLTreeNode<TreeElement, Comparator, Operation>* tmp =
					this->getParent();
			//Comparator cmp;
			//bool right_to_delete = !cmp(tmp->getRight()->getData(), this->getData());
			bool right_to_delete = (tmp->getRightSon() == this);
			//bool left_to_delete = !cmp(tmp.getLeft(), this);
			delete this;
			n--;
			if (right_to_delete) {
				tmp->setRight(NULL);
			} else {
				tmp->setLeft(NULL);
			}

			return;
		}
		(this->getLeftSon())->deleteInOrderRL(n);
	}
}

template<class TreeElement, class Comparator, class Operation>
void RankAVLTreeNode<TreeElement, Comparator, Operation>::arrayToRankAVLTreeNode(
		TreeElement* arr, int& itr) {
	if (this != NULL) {
		(this->getRightSon())->arrayToRankAVLTreeNode(arr, itr);
		this->setData(arr[itr++]);
		(this->getLeftSon())->arrayToRankAVLTreeNode(arr, itr);
	}
}

template<class TreeElement, class Comparator, class Operation>
int RankAVLTreeNode<TreeElement, Comparator, Operation>::calculateBalanceFactor() {
	if (this != NULL) {
		if (this->getRightSon() == NULL && this->getLeftSon() == NULL) {
			return 0;
		}
		if (this->getRightSon() == NULL) {
			return (this->getLeftSon())->getHeight() - (-1);
		}
		if (this->getLeftSon() == NULL) {
			return -1 - (this->getRightSon())->getHeight();
		}
		return (this->getLeftSon())->getHeight() - (this->getRightSon())->getHeight();
	}
	return 0;
}

template<class TreeElement, class Comparator, class Operation>
int RankAVLTreeNode<TreeElement, Comparator, Operation>::getMaxHeightOfSons(
		RankAVLTreeNode<TreeElement, Comparator, Operation>* trn1,
		RankAVLTreeNode<TreeElement, Comparator, Operation>* trn2) {
	if (trn1 == NULL && trn2 == NULL) {
		return -1;
	}
	if (trn1 == NULL) {
		return trn2->getHeight();
	}
	if (trn2 == NULL) {
		return trn1->getHeight();
	}
	else{
		if(trn1->getHeight() > trn2->getHeight()) return trn1->getHeight();
		return trn2->getHeight();
	}
}

template<class TreeElement, class Comparator, class Operation>
void RankAVLTreeNode<TreeElement, Comparator, Operation>::setHeightBasedOnSons() {
	this->setHeight(1 + getMaxHeightOfSons(this->getRightSon(), this->getLeftSon()));
}

template<class TreeElement, class Comparator, class Operation>
int RankAVLTreeNode<TreeElement, Comparator, Operation>::getSize() {
	if (this == NULL) {
		return 0;
	}
	return ((this->getLeftSon())->getSize()) + 1 + ((this->getRightSon())->getSize());
}

template<class TreeElement, class Comparator, class Operation>
int RankAVLTreeNode<TreeElement, Comparator, Operation>::getRank() const{
	if (this != NULL) {
		return this->rank;
	}
	return 0;
}

template<class TreeElement, class Comparator, class Operation>
 void RankAVLTreeNode<TreeElement, Comparator, Operation>::setRank(int new_rank){
	if (this != NULL) {
		this->rank = new_rank;
	}
	return;
}

 template<class TreeElement, class Comparator, class Operation>
 int RankAVLTreeNode<TreeElement, Comparator, Operation>::
						getBigger(const TreeElement& info) {
	 if (this == NULL) return 0;
	 Comparator compare;
	 int result = compare(info, this->getData());
	 if (result == 0) return this->getRightSon()->getRank();
	 if (result > 0) {
		 return 1 + this->getRightSon()->getRank() + this->getLeftSon()->getBigger(info);
	 }
	 return this->getRightSon()->getBigger(info);
 }

 template<class TreeElement, class Comparator, class Operation>
 int RankAVLTreeNode<TreeElement, Comparator, Operation>::
				getSmaller(const TreeElement& info) {
	 if (this == NULL) return 0;
	 Comparator compare;
	 int result = compare(info, this->getData());
	 if (result == 0) {
		 return 1 + this->getLeftSon()->getRank();
	 } else if (result < 0) {
		 return 1 + this->getLeftSon()->getRank() + this->getRightSon()->getSmaller(info);
	 }
	 return this->getLeftSon()->getSmaller(info);
 }








#endif /* RANKAVLTREENODE_H_ */
