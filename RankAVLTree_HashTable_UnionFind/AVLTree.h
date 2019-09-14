
#ifndef AVLTREE_H_
#define AVLTREE_H_

#include "AVLTreeNode.h"
#include <math.h>
#include "Exceptions.h"

template<class TreeElement, class Comparator, class Operation>
class AVLTree {
private:
	AVLTreeNode<TreeElement, Comparator, Operation>* root;

public:
	AVLTree();
	//c'tor initalize  with root as new a tree
	AVLTree(AVLTreeNode<TreeElement, Comparator, Operation>* newRoot);
	//copy constructor to a tree
	AVLTree(const AVLTree<TreeElement, Comparator, Operation>& tr);
	~AVLTree();
	/*
	 * return the root of a tree;
	 */
	AVLTreeNode<TreeElement, Comparator, Operation>* getRoot() const;
	/*
	 * set a root of a tree to the node "root"
	 */
	void setRoot(AVLTreeNode<TreeElement, Comparator, Operation>* root);
	/**
	 *return the max value in the tree
	 */
	TreeElement maxInAVLTree(
			AVLTreeNode<TreeElement, Comparator, Operation>* trd);
	/**
	 *return the min value in a tree
	 */
	AVLTreeNode<TreeElement, Comparator, Operation>* getMinValue(
			AVLTreeNode<TreeElement, Comparator, Operation>* trd);
	/**
	 *return a node which holds the data equal to find according compartor
	 */
	AVLTreeNode<TreeElement, Comparator, Operation>* find(
			const TreeElement& data);
	/**
	 n is the number of vertices we want to create a new whole tree
	 which can contain all old vertices (its number of vertices is the nearest
	 pow of 2 which is bigger.
	 */
	void createEmptyWholeAVLTree(int n);
	/**
	 *@param info is the element we want to check in the tree. returns true if
	 *exist, false otherwise.
	 */
	bool AVLTreeContain(const TreeElement& data);

	/**
	 *return the the the element in the tree which is equal to elemnt info
	 *according to compartor;
	 */
	TreeElement findElement(const TreeElement& data);

	/**
	 * allocates an array of TreeElement elements
	 * passes on all vertices data in the tree by inorder traversal and
	 * and returns the array of the elements
	 */
	TreeElement* returnSortedTreeElementsInOrder();
	/** 
	* fill the AVLTree with elements from sorted array arr
	 *arr is the array we translate to Tree
	 */
	void fillInAVLTree(TreeElement* arr);

	/**
	 *delete an element from the tree which is equal to info according to the
	 *compartor
	 */
	void deleteByInfo(const TreeElement& info);


	//removes all unnececery elements to create an almost whole tree
	void removeInorderRightLeft(int amount);
	/**
	 * deletes an AVLtree (it is not a d'tor)
	 */
	void deleteAVLTree();
	/**
	 *insert a new Element to the tree
	 */
	void insert(TreeElement data);
	/**
	* passes on all vertices data in the tree by inorder traversal and
	* does an operation on each of them.
	*/
		void operateInOrder(Operation& op);
	/**
	 * returns the number of nodes in the tree
	 */
	int getSize();

private:
	/**
	 * private functions for a rotate in the tree
	 * L=left R=Right
	 */
	AVLTreeNode<TreeElement, Comparator, Operation>* rotateToLL(
			AVLTreeNode<TreeElement, Comparator, Operation>* trn);
	AVLTreeNode<TreeElement, Comparator, Operation>* rotateToRR(
			AVLTreeNode<TreeElement, Comparator, Operation>* trn);
	AVLTreeNode<TreeElement, Comparator, Operation>* rotateToLR(
			AVLTreeNode<TreeElement, Comparator, Operation>* trn);
	AVLTreeNode<TreeElement, Comparator, Operation>* rotateToRL(
			AVLTreeNode<TreeElement, Comparator, Operation>* trn);
	//check if the tree is balanced if needed it rotate
	void isNeedToRotate(AVLTreeNode<TreeElement, Comparator, Operation>* trn);
	//insert data to this AVLTree, using trn as his parent
	void insertToTree(TreeElement data,
				AVLTreeNode<TreeElement, Comparator, Operation>* trn);
	/*
	 *delete a node from a tree
	 */
	void deleteNode(AVLTreeNode<TreeElement, Comparator, Operation>* trn);
	/**
	*return true if the is a node in the tree equal to trn;*
	*/
	bool NodeInTree(AVLTreeNode<TreeElement, Comparator, Operation>* trn);
};

template<class TreeElement, class Comparator, class Operation>
AVLTree<TreeElement, Comparator, Operation>::AVLTree() {
	this->root = NULL;
}

template<class TreeElement, class Comparator, class Operation>
AVLTree<TreeElement, Comparator, Operation>::AVLTree(
		AVLTreeNode<TreeElement, Comparator, Operation>* root) {
	this->root = root;
}

template<class TreeElement, class Comparator, class Operation>
AVLTree<TreeElement, Comparator, Operation>::AVLTree(
		const AVLTree<TreeElement, Comparator, Operation>& tr) {
	if (tr.getRoot() != NULL) {
		this->root = new AVLTreeNode<TreeElement, Comparator, Operation>
		(tr.root);
		return;
	} else {
		this->root = NULL;
	}
}

template<class TreeElement, class Comparator, class Operation>
AVLTree<TreeElement, Comparator, Operation>::~AVLTree() {
	this->deleteAVLTree();
}

template<class TreeElement, class Comparator, class Operation>
AVLTreeNode<TreeElement, Comparator, Operation>* AVLTree<TreeElement,
		Comparator, Operation>::rotateToLL(
		AVLTreeNode<TreeElement, Comparator, Operation>* trn) {
	AVLTreeNode<TreeElement, Comparator, Operation> *root = trn;
	AVLTreeNode<TreeElement, Comparator, Operation> *rootParent =
			root->getParent();
	AVLTreeNode<TreeElement, Comparator, Operation> *leftSon =
			root->getLeftSon();
	AVLTreeNode<TreeElement, Comparator, Operation> *leftSonRightSon =
			leftSon->getRightSon();
	root->setParent(leftSon);
	leftSon->setParent(rootParent);
	leftSonRightSon->setParent(root);
	leftSon->setRight(root);
	root->setLeft(leftSonRightSon);
	root->setHeightBasedOnSons();
	if (rootParent != NULL) {
		if (rootParent->getRightSon() == root) {
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
		Comparator, Operation>::rotateToRR(
		AVLTreeNode<TreeElement, Comparator, Operation>* trn) {
	AVLTreeNode<TreeElement, Comparator, Operation>* root = trn;
	AVLTreeNode<TreeElement, Comparator, Operation> *rootParent =
			root->getParent();
	AVLTreeNode<TreeElement, Comparator, Operation> *rightSon =
			root->getRightSon();
	AVLTreeNode<TreeElement, Comparator, Operation> *rightLeftSon =
			rightSon->getLeftSon();
	root->setParent(rightSon);
	rightSon->setParent(rootParent);
	rightLeftSon->setParent(root);
	rightSon->setLeft(root);
	root->setRight(rightLeftSon);
	root->setHeightBasedOnSons();
	if (rootParent != NULL) {
		if (rootParent->getRightSon() == root) {
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
		Comparator, Operation>::rotateToLR(
		AVLTreeNode<TreeElement, Comparator, Operation>* trn) {
	this->rotateToRR(trn->getLeftSon());
	return this->rotateToLL(trn);
}

template<class TreeElement, class Comparator, class Operation>
AVLTreeNode<TreeElement, Comparator, Operation>* AVLTree<TreeElement,
		Comparator, Operation>::rotateToRL(
		AVLTreeNode<TreeElement, Comparator, Operation>* trn) {
	this->rotateToLL(trn->getRightSon());
	return this->rotateToRR(trn);
}

template<class TreeElement, class Comparator, class Operation>
AVLTreeNode<TreeElement, Comparator, Operation>* AVLTree<TreeElement,
		Comparator, Operation>::getRoot() const {
	if (this == NULL) {
		return NULL;
	}
	return (this->root);
}

template<class TreeElement, class Comparator, class Operation>
void AVLTree<TreeElement, Comparator, Operation>::setRoot(
		AVLTreeNode<TreeElement, Comparator, Operation>* root) {
	if (this != NULL) {
		this->root = root;
	}
}

template<class TreeElement, class Comparator, class Operation>
TreeElement AVLTree<TreeElement, Comparator, Operation>::maxInAVLTree(
		AVLTreeNode<TreeElement, Comparator, Operation>* tree) {
	if (tree == NULL) {
		return TreeElement();
	}
	if (tree->getRightSon() == NULL)
		return tree->getData();
	return maxInAVLTree(tree->getRightSon());
}

template<class TreeElement, class Comparator, class Operation>
AVLTreeNode<TreeElement, Comparator, Operation>* AVLTree<TreeElement,
		Comparator, Operation>::getMinValue(
		AVLTreeNode<TreeElement, Comparator, Operation>* trd) {
	if (trd->getLeftSon() == NULL)
		return trd;
	return getMinValue(trd->getLeftSon());
}

template<class TreeElement, class Comparator, class Operation>
AVLTreeNode<TreeElement, Comparator, Operation>* AVLTree<TreeElement,
		Comparator, Operation>::find(const TreeElement& data) {
	if (this == NULL) {
		return NULL;
	}else{
	  return (this->getRoot())->find(data);
	}
}

template<class TreeElement, class Comparator, class Operation>
TreeElement AVLTree<TreeElement, Comparator, Operation>::findElement(
		const TreeElement& data) {
	if (this != NULL) {
		AVLTreeNode<TreeElement, Comparator, Operation>* found =
				this->getRoot()->find(data);
		if (found)
			return found->getData();
	}
	return TreeElement();
}

template<class TreeElement, class Comparator, class Operation>
bool AVLTree<TreeElement, Comparator, Operation>::AVLTreeContain(
		const TreeElement& data) {
	if (this != NULL && this->getSize() != 0) {
		Comparator cmp;
		return !cmp(this->findElement(data), data);
	}
	return false;
}

template<class TreeElement, class Comparator, class Operation>
bool AVLTree<TreeElement, Comparator, Operation>::NodeInTree(
		AVLTreeNode<TreeElement, Comparator, Operation>* trn) {
	if (trn == NULL) {
		return false;
	} else if (this == NULL) {
		return false;
	}
	if (trn->getParent() == this->getRoot())
		return true;
	else if (trn == this->getRoot()) {
		return true;
	}
	return this->NodeInTree(trn->getParent());
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
void AVLTree<TreeElement, Comparator, Operation>::removeInorderRightLeft(
		int amount) {
	(this->getRoot())->deleteInOrderRL(amount);
}

template<class TreeElement, class Comparator, class Operation>
TreeElement* AVLTree<TreeElement, Comparator, Operation>::
	returnSortedTreeElementsInOrder() {
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
		if (!(trn->isLeaf() || trn->isOneChild())) {
			AVLTreeNode<TreeElement, Comparator, Operation>
				*minimumSubRightAVLTree =getMinValue(trn->getRightSon());
			TreeElement orgInfo = trn->getData();
			trn->setInfo(minimumSubRightAVLTree->getData());
			minimumSubRightAVLTree->setInfo(orgInfo);
			this->deleteNode(minimumSubRightAVLTree);
			return;
		}
		if (trn->isLeaf()==true) {
			AVLTreeNode<TreeElement, Comparator, Operation> *trnParent =
					trn->getParent();
			if (trnParent != NULL) {
				if (trnParent->getRightSon() == trn) {
					trnParent->setRight(NULL);
				} else {
					trnParent->setLeft(NULL);
				}
			} else {
				this->setRoot(NULL);
			}
			trn->setParent(NULL);
			delete trn;
			this->isNeedToRotate(trnParent);

		} else {
			AVLTreeNode<TreeElement, Comparator, Operation> *trnParent =
					trn->getParent();
			if (trn->getRightSon() == NULL) {
				AVLTreeNode<TreeElement, Comparator, Operation> *trnLeftSon =
						trn->getLeftSon();
				trnLeftSon->setParent(trnParent);
				if (trnParent != NULL) {
					if (trnParent->getRightSon() == trn) {
						trnParent->setRight(trnLeftSon);
					} else {
						trnParent->setLeft(trnLeftSon);
					}
				} else {
					this->setRoot(trnLeftSon);
				}
				trn->setRight(NULL);
				trn->setLeft(NULL);
				trn->setParent(NULL);
				delete trn;
			} else {
				AVLTreeNode<TreeElement, Comparator, Operation> *trnRightSon =
						trn->getRightSon();
				trnRightSon->setParent(trnParent);
				if (trnParent != NULL) {
					if (trnParent->getRightSon() == trn) {
						trnParent->setRight(trnRightSon);
					} else {
						trnParent->setLeft(trnRightSon);
					}
				} else {
					this->setRoot(trnRightSon);
				}
				trn->setLeft(NULL);
				trn->setRight(NULL);
				trn->setParent(NULL);
				delete trn;
			}
			this->isNeedToRotate(trnParent);
		}
	}
}


template<class TreeElement, class Comparator, class Operation>
void AVLTree<TreeElement, Comparator, Operation>::deleteAVLTree() {
	if (this != NULL) {
		if (this->getRoot() != NULL) {
			(this->getRoot())->deletePostOrder();
		}
	}
}

template<class TreeElement, class Comparator, class Operation>
void AVLTree<TreeElement, Comparator, Operation>::insert(TreeElement data) {
	if (this->getRoot() == NULL) {
		AVLTreeNode<TreeElement, Comparator, Operation> *toInsert =
				new AVLTreeNode<TreeElement, Comparator, Operation>();
		toInsert->setData(data);
		this->setRoot(toInsert);
		return;
	}
	insertToTree(data, (this->getRoot()));
}

template<class TreeElement, class Comparator, class Operation>
void AVLTree<TreeElement, Comparator, Operation>::insertToTree(TreeElement data,
		AVLTreeNode<TreeElement, Comparator, Operation>* trn) {
	Comparator compare;
	if (compare(trn->getData(), data) == 0) {
		return;
	}
	if ((compare(trn->getData(), data) < 0)) {
		if (trn->getLeftSon()) {
			insertToTree(data, (trn->getLeftSon()));
			return;
		}
		AVLTreeNode<TreeElement, Comparator, Operation> *toInsertLeft =
				new AVLTreeNode<TreeElement, Comparator, Operation>();
		toInsertLeft->setData(data);
		trn->setLeft(toInsertLeft);
		toInsertLeft->setParent(trn);
		this->isNeedToRotate(trn);
		return;
	}
	if (trn->getRightSon()) {
		insertToTree(data, (trn->getRightSon()));
		return;
	}
	AVLTreeNode<TreeElement, Comparator, Operation> *toInsertRight =
			new AVLTreeNode<TreeElement, Comparator, Operation>();
	toInsertRight->setData(data);
	trn->setRight(toInsertRight);
	toInsertRight->setParent(trn);
	this->isNeedToRotate(trn);
	return;
}

template<class TreeElement, class Comparator, class Operation>
void AVLTree<TreeElement, Comparator, Operation>::fillInAVLTree(TreeElement* arr) {
	int itr = 0;
	this->getRoot()->arrayToAVLTreeNode(arr, itr);
}

template<class TreeElement, class Comparator, class Operation>
void AVLTree<TreeElement, Comparator, Operation>::isNeedToRotate(
		AVLTreeNode<TreeElement, Comparator, Operation>* trn) {
	if (trn == NULL) {
		return;
	}
	int balanceFactor = trn->calculateBalanceFactor();
	if (balanceFactor == 2) {
		int leftBalanceFactor = (trn->getLeftSon())->calculateBalanceFactor();
		if (leftBalanceFactor >= 0) {
			this->isNeedToRotate((this->rotateToLL(trn)));
			return;
		} else if (leftBalanceFactor == -1) {
			this->isNeedToRotate(this->rotateToLR(trn));
			return;
		}
	} else if (balanceFactor == -2) {
		int rightBalanceFactor = (trn->getRightSon())->calculateBalanceFactor();
		if (rightBalanceFactor <= 0) {
			this->isNeedToRotate(this->rotateToRR(trn));
			return;
		} else if (rightBalanceFactor == 1) {
			this->isNeedToRotate(this->rotateToRL(trn));
			return;
		}
	} else {
		trn->setHeightBasedOnSons();
		this->isNeedToRotate(trn->getParent());
		return;
	}
}

template<class TreeElement, class Comparator, class Operation>
int AVLTree<TreeElement, Comparator, Operation>::getSize() {
	if (this != NULL) {
		return ((this->getRoot())->getSize());
	}
	return -1;
}

#endif /* AVLTREE_H_ */
