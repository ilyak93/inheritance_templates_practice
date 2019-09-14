/*
 * AVLTree.h
 *
 *  Created on: 25 бреб 2015
 *      Author:
 */

#ifndef AVLTREE_H_
#define AVLTREE_H_

#include "AVLTreeNode.h"
#include <math.h>
#include "Exceptions.h"

//class T is the class of the AVLTree and the class S is the function object, to which the AVLTree is sorted by
template<class TreeElement, class Comparator, class Operation>
class AVLTree {
private:
	AVLTreeNode<TreeElement, Comparator, Operation>* _root; //pointer to the AVLTreeNode which acts as the root
	/**
	 * performs a LL flip over the current AVLTreeNode, using it as the center of the flip
	 */
	AVLTreeNode<TreeElement, Comparator, Operation>* flipLL(
			AVLTreeNode<TreeElement, Comparator, Operation>* trn);
	/**
	 * performs a RR flip over the current AVLTreeNode, using it as the center of the flip
	 */
	AVLTreeNode<TreeElement, Comparator, Operation>* flipRR(
			AVLTreeNode<TreeElement, Comparator, Operation>* trn);
	/**
	 * performs a LR flip over the current AVLTreeNode, using it as the center of the flip
	 */
	AVLTreeNode<TreeElement, Comparator, Operation>* flipLR(
			AVLTreeNode<TreeElement, Comparator, Operation>* trn);
	/**
	 * performs a RL flip over the current AVLTreeNode, using it as the center of the flip
	 */
	AVLTreeNode<TreeElement, Comparator, Operation>* flipRL(
			AVLTreeNode<TreeElement, Comparator, Operation>* trn);

public:
	/**
	 * default constructor for AVLTree
	 */
	AVLTree();
	/*@param _root is a pointer to the root of the newly created AVLTree
	 * constructor which initializes the root of the AVLTree
	 */
	AVLTree(AVLTreeNode<TreeElement, Comparator, Operation>* _root);
	/**
	 * copy constructor
	 */
	AVLTree(const AVLTree<TreeElement, Comparator, Operation>& tr);
	/**
	 * returns a pointer to the root son of the current AVLTree, if this is NULL, NULL is returned
	 */
	/**
	 *Destructor of the AVLTree
	 */
	~AVLTree();
	AVLTreeNode<TreeElement, Comparator, Operation>* getRoot() const;
	/**
	 *@param root is a pointer to the new root of the current AVLTree
	 * sets the root of the current AVLTree to the given AVLTreeNode pointer
	 */
	void setRoot(AVLTreeNode<TreeElement, Comparator, Operation>* root);
	/**
	 *@param trd is the sub-AVLTree the maximum value will come from
	 * returns the maximum value of the sub-AVLTree, whose root is trd
	 */
	TreeElement maxInAVLTree(
			AVLTreeNode<TreeElement, Comparator, Operation>* trd);
	/**
	 *@param trd is the sub-AVLTree the pointer to the minimum value will come from
	 * returns pointer to the AVLTreeNode which contains the minimum value in the sub-AVLTree, whose root is trd
	 */
	AVLTreeNode<TreeElement, Comparator, Operation>* minPointerInAVLTree(
			AVLTreeNode<TreeElement, Comparator, Operation>* trd);
	/**
	 *@param info is the info field of the AVLTreeNode we are trying to find
	 * returns pointer to the AVLTreeNode contains info, if not found returns NULL
	 */
	AVLTreeNode<TreeElement, Comparator, Operation>* find(
			const TreeElement& info);
	/**
	 *@param n is the number of vertices we want to create a new whole tree
	 which can contain all old vertices (its number of vertices is the nearest
	 pow of 2 which is bigger.
	 */
	void createEmptyWholeAVLTree(int n);
	/**
	 *@param info is the element we want to check in the tree. returns true if
	 *exist, false otherwise.
	 */
	bool AVLTreeContain(const TreeElement& info);

	/**
	 *@param info is the element we want to find in the tree. returns correct
	 element if it exist and defalut constructored element otherwise.
	 */
	TreeElement findElement(const TreeElement& info);
	/**
	 *@param trn is the AVLTreeNode we are trying to check if exists in this AVLTree
	 *returns true if trn is in this AVLTree, otherwise - false
	 */
	bool isInTree(AVLTreeNode<TreeElement, Comparator, Operation>* trn);
	/**
	 * allocates an array of TreeElement elements
	 * passes on all vertices data in the tree by inorder traversal and
	 * and returns the array of the elements
	 */
	TreeElement* returnSortedTreeElementsInOrder();
	/**
	 *@param arr is the array we translate to Tree and itr is an aux param
	 */
	void arrayToTree(TreeElement* arr);
	/**
	 * passes on all vertices data in the tree by inorder traversal and
	 * does an operation on each of them.
	 */
	void operateInOrder(Operation& op);
	/**
	 *@param info is the info of the AVLTreeNode we want to delete from this AVLTree
	 * deletes the AVLTreeNode with the given info from this AVLTree, does nothing if no AVLTreeNode contains info
	 */
	void deleteByInfo(const TreeElement& info);
	/**
	 *@param trn is pointer to the AVLTreeNode we want to
	 *@param  delete from this AVLTree
	 * deletes the given AVLTreeNode, does nothing if the pointer
	 *  is to a AVLTreeNode not in the AVLTree
	 */
	void deleteNode(AVLTreeNode<TreeElement, Comparator, Operation>* trn);

	//removes all unnececery elements to create an almost whole tree
	void removeInorderRightLeft(int amount);
	/**
	 * deletes all the allocated memory of this AVLTree
	 */
	void deleteAVLTree();
	/**
	 *@param data is the data to add to this AVLTree
	 * inserts a new node with data as its info to this AVLTree
	 */
	void insert(TreeElement data);
	//insert data to this AVLTree, using trn as his parent
	void insertToTree(TreeElement data,
			AVLTreeNode<TreeElement, Comparator, Operation>* trn);
	/*operates on the parent of the node that was inserted/removed.
	 makes a rotate if there is a rotate to make.*/
	void isNeedToRotate(AVLTreeNode<TreeElement, Comparator, Operation>* trn);
	/**
	 * returns the number of AVLTreeNode in the AVLTree
	 */
	int getSize();

};

template<class TreeElement, class Comparator, class Operation>
AVLTree<TreeElement, Comparator, Operation>::AVLTree() {
	this->_root = NULL; // create a deme node
}

template<class TreeElement, class Comparator, class Operation>
AVLTree<TreeElement, Comparator, Operation>::AVLTree(
		AVLTreeNode<TreeElement, Comparator, Operation>* root) {
	this->_root = root; /// bad copy
}

template<class TreeElement, class Comparator, class Operation>
AVLTree<TreeElement, Comparator, Operation>::AVLTree(
		const AVLTree<TreeElement, Comparator, Operation>& tr) {
	if (tr.getRoot() != NULL) {
		this->_root = new AVLTreeNode<TreeElement, Comparator, Operation>(
				tr._root);
	} else {
		this->_root = NULL;
	}
}

template<class TreeElement, class Comparator, class Operation>
AVLTree<TreeElement, Comparator, Operation>::~AVLTree() {
	this->deleteAVLTree();
}

template<class TreeElement, class Comparator, class Operation>
AVLTreeNode<TreeElement, Comparator, Operation>* AVLTree<TreeElement,
		Comparator, Operation>::flipLL(
		AVLTreeNode<TreeElement, Comparator, Operation>* trn) {
	AVLTreeNode<TreeElement, Comparator, Operation> *root = trn;
	AVLTreeNode<TreeElement, Comparator, Operation> *rootParent =
			root->getParent();
	AVLTreeNode<TreeElement, Comparator, Operation> *leftSon = root->getLeft();
	AVLTreeNode<TreeElement, Comparator, Operation> *leftSonRightSon =
			leftSon->getRight();
	root->setParent(leftSon);
	leftSon->setParent(rootParent);
	leftSonRightSon->setParent(root);
	leftSon->setRight(root);
	root->setLeft(leftSonRightSon);
	root->updateHeight();
	if (rootParent != NULL) {
		if (rootParent->getRight() == root) {
			rootParent->setRight(leftSon);
		} else {
			rootParent->setLeft(leftSon);
		}
	} else {
		this->setRoot(leftSon);
	}
	return leftSon;
}

template<class TreeElement, class Comparator, class Operation>
AVLTreeNode<TreeElement, Comparator, Operation>* AVLTree<TreeElement,
		Comparator, Operation>::flipRR(
		AVLTreeNode<TreeElement, Comparator, Operation>* trn) {
	AVLTreeNode<TreeElement, Comparator, Operation>* root = trn;
	AVLTreeNode<TreeElement, Comparator, Operation> *rootParent =
			root->getParent();
	AVLTreeNode<TreeElement, Comparator, Operation> *rightSon =
			root->getRight();
	AVLTreeNode<TreeElement, Comparator, Operation> *rightLeftSon =
			rightSon->getLeft();
	root->setParent(rightSon);
	rightSon->setParent(rootParent);
	rightLeftSon->setParent(root);
	rightSon->setLeft(root);
	root->setRight(rightLeftSon);
	root->updateHeight();
	if (rootParent != NULL) {
		if (rootParent->getRight() == root) {
			rootParent->setRight(rightSon);
		} else {
			rootParent->setLeft(rightSon);
		}
	} else {
		this->setRoot(rightSon);
	}
	return rightSon;
}

template<class TreeElement, class Comparator, class Operation>
AVLTreeNode<TreeElement, Comparator, Operation>* AVLTree<TreeElement,
		Comparator, Operation>::flipLR(
		AVLTreeNode<TreeElement, Comparator, Operation>* trn) {
	this->flipRR(trn->getLeft());
	return this->flipLL(trn);
}

template<class TreeElement, class Comparator, class Operation>
AVLTreeNode<TreeElement, Comparator, Operation>* AVLTree<TreeElement,
		Comparator, Operation>::flipRL(
		AVLTreeNode<TreeElement, Comparator, Operation>* trn) {
	this->flipLL(trn->getRight());
	return this->flipRR(trn);
}

template<class TreeElement, class Comparator, class Operation>
AVLTreeNode<TreeElement, Comparator, Operation>* AVLTree<TreeElement,
		Comparator, Operation>::getRoot() const {
	if (this != NULL) {
		//if (this->_root != NULL) {
		return this->_root;
		//}
	}
	return NULL;
}

template<class TreeElement, class Comparator, class Operation>
void AVLTree<TreeElement, Comparator, Operation>::setRoot(
		AVLTreeNode<TreeElement, Comparator, Operation>* root) {
	if (this != NULL) {
		this->_root = root;
	}
}

template<class TreeElement, class Comparator, class Operation>
TreeElement AVLTree<TreeElement, Comparator, Operation>::maxInAVLTree(
		AVLTreeNode<TreeElement, Comparator, Operation>* trd) {
	if (trd == NULL) {
		return TreeElement();
	}
	if (trd->getRight() == NULL)
		return trd->getInfo();
	return maxInAVLTree(trd->getRight());
}

template<class TreeElement, class Comparator, class Operation>
AVLTreeNode<TreeElement, Comparator, Operation>* AVLTree<TreeElement,
		Comparator, Operation>::minPointerInAVLTree(
		AVLTreeNode<TreeElement, Comparator, Operation>* trd) {
	if (trd->getLeft() == NULL)
		return trd;
	return minPointerInAVLTree(trd->getLeft());
}

template<class TreeElement, class Comparator, class Operation>
AVLTreeNode<TreeElement, Comparator, Operation>* AVLTree<TreeElement,
		Comparator, Operation>::find(const TreeElement& info) {
	if (this != NULL) {
		return (this->getRoot())->find(info);
	}
	return NULL;
}

template<class TreeElement, class Comparator, class Operation>
TreeElement AVLTree<TreeElement, Comparator, Operation>::findElement(
		const TreeElement& info) {
	if (this != NULL) {
		AVLTreeNode<TreeElement, Comparator, Operation>* found =
				this->getRoot()->find(info);
		if (found)
			return found->getInfo();
	}
	return TreeElement();
}

template<class TreeElement, class Comparator, class Operation>
bool AVLTree<TreeElement, Comparator, Operation>::AVLTreeContain(
		const TreeElement& info) {
	if (this != NULL && this->getSize() != 0) {
		Comparator cmp;
		return !cmp(this->findElement(info), info);
	}
	return false;
}

template<class TreeElement, class Comparator, class Operation>
bool AVLTree<TreeElement, Comparator, Operation>::isInTree(
		AVLTreeNode<TreeElement, Comparator, Operation>* trn) {
	if (trn == NULL || this == NULL) {
		return false;
	}
	if (trn->getParent() == this->getRoot() || trn == this->getRoot()) {
		return true;
	}
	return this->isInTree(trn->getParent());
}

template<class TreeElement, class Comparator, class Operation>
void AVLTree<TreeElement, Comparator, Operation>::createEmptyWholeAVLTree(
		int n) {
	AVLTreeNode<TreeElement, Comparator, Operation>* root = new AVLTreeNode<
			TreeElement, Comparator, Operation>;
	this->setRoot(root);
	this->getRoot()->setHeight(log(n));
	n--;
	(this->getRoot())->createEmptyWholeAVLTreeNode(n);
}

template<class TreeElement, class Comparator, class Operation>
void AVLTree<TreeElement, Comparator, Operation>::arrayToTree(
		TreeElement* arr) {
	//int size = this->getSize();
	int itr = 0;
	(this->getRoot())->arrayToAVLTreeNode(arr, itr);
}

template<class TreeElement, class Comparator, class Operation>
void AVLTree<TreeElement, Comparator, Operation>::removeInorderRightLeft(
		int amount) {
	(this->getRoot())->deleteInOrderRL(amount);
}

template<class TreeElement, class Comparator, class Operation>
TreeElement* AVLTree<TreeElement, Comparator, Operation>::returnSortedTreeElementsInOrder() {
	int size = this->getSize();
	TreeElement* sorted_array = (TreeElement*) malloc(
			sizeof(TreeElement) * size);
	int itr = 0;
	(this->getRoot())->returnSortedTreeElements(sorted_array, itr);
	return sorted_array;
}

template<class TreeElement, class Comparator, class Operation>
//can be modified to return a value of operation
void AVLTree<TreeElement, Comparator, Operation>::operateInOrder(
		Operation& op) {
	(this->getRoot())->operateInOrder(op);
}

template<class TreeElement, class Comparator, class Operation>
void AVLTree<TreeElement, Comparator, Operation>::deleteByInfo(
		const TreeElement& info) {
	this->deleteNode(this->find(info));
}

template<class TreeElement, class Comparator, class Operation>
void AVLTree<TreeElement, Comparator, Operation>::deleteNode(
		AVLTreeNode<TreeElement, Comparator, Operation>* trn) {
	if (trn != NULL && this != NULL) {
		//if (/*this->isInTree(trn) == */true) {
		if (!(trn->isLeaf() || trn->isOneChild())) {
			//two childs
			//finds minimum in right son and switching between them, then it knows how to treat a leaf or 1 child
			AVLTreeNode<TreeElement, Comparator, Operation> *minimumSubRightAVLTree =
					minPointerInAVLTree(trn->getRight());
			TreeElement orgInfo = trn->getInfo();
			trn->setInfo(minimumSubRightAVLTree->getInfo());
			minimumSubRightAVLTree->setInfo(orgInfo);
			this->deleteNode(minimumSubRightAVLTree);
			return;
		}
		if (trn->isLeaf()) {
			AVLTreeNode<TreeElement, Comparator, Operation> *trnParent =
					trn->getParent();
			if (trnParent != NULL) {
				if (trnParent->getRight() == trn) {
					//trn is right son of trnParent
					trnParent->setRight(NULL);
				} else {
					//trn is left son of trnParent
					trnParent->setLeft(NULL);
				}
			} else {					//deleting root
				this->setRoot(NULL);
			}
			trn->setParent(NULL);
			delete trn;
			this->isNeedToRotate(trnParent);

		} else {					//one child
			AVLTreeNode<TreeElement, Comparator, Operation> *trnParent =
					trn->getParent();
			if (trn->getRight() == NULL) {
				//only left child
				AVLTreeNode<TreeElement, Comparator, Operation> *trnLeftSon =
						trn->getLeft();
				trnLeftSon->setParent(trnParent);
				if (trnParent != NULL) {
					if (trnParent->getRight() == trn) {
						trnParent->setRight(trnLeftSon);
					} else {
						//trn is left son of parent
						trnParent->setLeft(trnLeftSon);
					}
				} else {					//trn is root
					this->setRoot(trnLeftSon);
				}
				trn->setRight(NULL);
				trn->setLeft(NULL);
				trn->setParent(NULL);
				delete trn;
			} else {
				//only right child
				AVLTreeNode<TreeElement, Comparator, Operation> *trnRightSon =
						trn->getRight();
				trnRightSon->setParent(trnParent);
				if (trnParent != NULL) {
					if (trnParent->getRight() == trn) {
						trnParent->setRight(trnRightSon);
					} else {
						//trn is left son of parent
						trnParent->setLeft(trnRightSon);
					}
				} else {					//trn is Root
					this->setRoot(trnRightSon);
				}
				trn->setLeft(NULL);
				trn->setRight(NULL);
				trn->setParent(NULL);
				delete trn;
			}
			this->isNeedToRotate(trnParent);
		}
		//}
	}
}

/**
 * deallocating all the memory allocated to this AVLTree
 */
template<class TreeElement, class Comparator, class Operation>
void AVLTree<TreeElement, Comparator, Operation>::deleteAVLTree() {
	if (this != NULL) {
		if (this->getRoot() != NULL) {
			(this->getRoot())->deletePostOrder();
		}
	}
}

/**
 * inserts a new AVLTreeNode with the info data
 */
template<class TreeElement, class Comparator, class Operation>
void AVLTree<TreeElement, Comparator, Operation>::insert(TreeElement data) {
	if (this->getRoot() == NULL) { //if we have an empty tree and we need to insert the root.
		AVLTreeNode<TreeElement, Comparator, Operation> *toInsert =
				new AVLTreeNode<TreeElement, Comparator, Operation>();
		toInsert->setInfo(data);
		this->setRoot(toInsert);
		return;
	}
	insertToTree(data, (this->getRoot()));

}
/**
 * inserts the AVLTreeNode with the info data to the Sub-AVLTree with the root trn
 */
template<class TreeElement, class Comparator, class Operation>
void AVLTree<TreeElement, Comparator, Operation>::insertToTree(TreeElement data,
		AVLTreeNode<TreeElement, Comparator, Operation>* trn) {
	Comparator compare;
	if (compare(trn->getInfo(), data) == 0) {
		return;
	}
	if ((compare(trn->getInfo(), data) < 0)) {
		if (trn->getLeft()) {
			insertToTree(data, (trn->getLeft()));
			return;
		}
		AVLTreeNode<TreeElement, Comparator, Operation> *toInsertLeft =
				new AVLTreeNode<TreeElement, Comparator, Operation>();
		toInsertLeft->setInfo(data);
		trn->setLeft(toInsertLeft);
		toInsertLeft->setParent(trn);
		this->isNeedToRotate(trn);
		return;
	}
	if (trn->getRight()) {
		insertToTree(data, (trn->getRight()));
		return;
	}
	AVLTreeNode<TreeElement, Comparator, Operation> *toInsertRight =
			new AVLTreeNode<TreeElement, Comparator, Operation>();
	toInsertRight->setInfo(data);
	trn->setRight(toInsertRight);
	toInsertRight->setParent(trn);
	this->isNeedToRotate(trn);
	return;
}
/*operates on the parent of the node that was inserted/removed.
 makes a rotate if there is a rotate to make.*/
template<class TreeElement, class Comparator, class Operation>
void AVLTree<TreeElement, Comparator, Operation>::isNeedToRotate(
		AVLTreeNode<TreeElement, Comparator, Operation>* trn) {
	if (trn == NULL) {
		//parent of root, no more possible flips
		return;
	}
	int balanceFactor = trn->calculateBalanceFactor();
	if (balanceFactor == 2) { //means that LL/LR rotate is needed.
		int leftBalanceFactor = (trn->getLeft())->calculateBalanceFactor();
		if (leftBalanceFactor >= 0) { //means that LL rotate.
			this->isNeedToRotate((this->flipLL(trn)));
			return;
		} else if (leftBalanceFactor == -1) { //means that LR rotate.
			this->isNeedToRotate(this->flipLR(trn));
			return;
		}
	} else if (balanceFactor == -2) {
		int rightBalanceFactor = (trn->getRight())->calculateBalanceFactor();
		if (rightBalanceFactor <= 0) { //means that RR rotate.
			this->isNeedToRotate(this->flipRR(trn));
			return;
		} else if (rightBalanceFactor == 1) { //means that RL rotate
			this->isNeedToRotate(this->flipRL(trn));
			return;
		}
	} else { //means that no rotate is needed.
		trn->updateHeight();
		this->isNeedToRotate(trn->getParent());
		return;
	}
}
/**
 * returns the size of this AVLTree
 */
template<class TreeElement, class Comparator, class Operation>
int AVLTree<TreeElement, Comparator, Operation>::getSize() {
	if (this == NULL) {
		return -1;
	}
	return (this->getRoot())->getSize();
}

#endif /* AVLTREE_H_ */
