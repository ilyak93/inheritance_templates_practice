/*
 * RankRankAVLTree.h
 *
 *  Created on: 7 αιεπι 2016
 *      Author: lior
 */

#ifndef RANKAVLTREE_H_
#define RANKAVLTREE_H_


#include "RankAVLTreeNode.h"
#include <math.h>
#include "Exceptions.h"

template<class TreeElement, class Comparator, class Operation>
class RankAVLTree {
private:
	RankAVLTreeNode<TreeElement, Comparator, Operation>* root;

public:
	RankAVLTree();
	//c'tor initalize  with root as new a tree
	RankAVLTree(RankAVLTreeNode<TreeElement, Comparator, Operation>* newRoot);
	//copy constructor to a tree
	RankAVLTree(const RankAVLTree<TreeElement, Comparator, Operation>& tr);
	~RankAVLTree();
	/*
	 * return the root of a tree;
	 */
	RankAVLTreeNode<TreeElement, Comparator, Operation>* getRoot() const;
	/*
	 * set a root of a tree to the node "root"
	 */
	void setRoot(RankAVLTreeNode<TreeElement, Comparator, Operation>* root);
	/**
	 *return the max value in the tree
	 */
	TreeElement maxInRankAVLTree(
			RankAVLTreeNode<TreeElement, Comparator, Operation>* trd);
	/**
	 *return the min value in a tree
	 */
	RankAVLTreeNode<TreeElement, Comparator, Operation>* getMinValue(
			RankAVLTreeNode<TreeElement, Comparator, Operation>* trd);
	/**
	 *return a node which holds the data equal to find according compartor
	 */
	RankAVLTreeNode<TreeElement, Comparator, Operation>* find(
			const TreeElement& data);
	/**
	 n is the number of vertices we want to create a new whole tree
	 which can contain all old vertices (its number of vertices is the nearest
	 pow of 2 which is bigger.
	 */
	void createEmptyWholeRankAVLTree(int n);
	/**
	 *@param info is the element we want to check in the tree. returns true if
	 *exist, false otherwise.
	 */
	bool RankAVLTreeContain(const TreeElement& data);

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
	* fill the RankAVLTree with elements from sorted array arr
	*arr is the array we translate to Tree
	*/
	void fillInRankAVLTree(TreeElement* arr);

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
	void deleteRankAVLTree();
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
	/**
	 *	  return the number of elements in the given range
	 *     represented by two Tree lements constructed with
	 *	  min, max info (min, max]		*
	 *	  @param
	 *	        min_info - TreeElement constructed with min_info
	 max_info - TreeElement constructed with min_info
	 */
	int getRange(const TreeElement& min_info, const TreeElement& max_info);

private:
	/**
	 * private functions for a rotate in the tree
	 * L=left R=Right
	 */
	RankAVLTreeNode<TreeElement, Comparator, Operation>* rotateToLL(
			RankAVLTreeNode<TreeElement, Comparator, Operation>* trn);
	RankAVLTreeNode<TreeElement, Comparator, Operation>* rotateToRR(
			RankAVLTreeNode<TreeElement, Comparator, Operation>* trn);
	RankAVLTreeNode<TreeElement, Comparator, Operation>* rotateToLR(
			RankAVLTreeNode<TreeElement, Comparator, Operation>* trn);
	RankAVLTreeNode<TreeElement, Comparator, Operation>* rotateToRL(
			RankAVLTreeNode<TreeElement, Comparator, Operation>* trn);
	//check if the tree is balanced if needed it rotate
	void isNeedToRotate(
			RankAVLTreeNode<TreeElement, Comparator, Operation>* trn);
	//insert data to this RankAVLTree, using trn as his parent
	void insertToTree(TreeElement data,
			RankAVLTreeNode<TreeElement, Comparator, Operation>* trn);
	/*
	 *delete a node from a tree
	 */
	void deleteNode(RankAVLTreeNode<TreeElement, Comparator, Operation>* trn);
	/**
	 *return true if the is a node in the tree equal to trn;*
	 */
	bool NodeInTree(RankAVLTreeNode<TreeElement, Comparator, Operation>* trn);
	/**
	 * Decreases the rank of all vertices which are on the search path of the
	 *  Node to be deleted.
	 *
	 * @param
	 *    info - element in the tree to arrive and decrease the rank of each
	 *    vertex on the search path to it.
	 *	 trn - vertex from which to search the info. default as root
	 */
	void deleteNodeUpdateRankSearchPath(const TreeElement& info,
			RankAVLTreeNode<TreeElement, Comparator, Operation>* trn);
};

template<class TreeElement, class Comparator, class Operation>
RankAVLTree<TreeElement, Comparator, Operation>::RankAVLTree() {
	this->root = NULL;
}

template<class TreeElement, class Comparator, class Operation>
RankAVLTree<TreeElement, Comparator, Operation>::RankAVLTree(
		RankAVLTreeNode<TreeElement, Comparator, Operation>* root) {
	this->root = root;
}

template<class TreeElement, class Comparator, class Operation>
RankAVLTree<TreeElement, Comparator, Operation>::RankAVLTree(
		const RankAVLTree<TreeElement, Comparator, Operation>& tr) {
	if (tr.getRoot() != NULL) {
		this->root = new RankAVLTreeNode<TreeElement, Comparator, Operation>(
				tr.root);
		return;
	} else {
		this->root = NULL;
	}
}

template<class TreeElement, class Comparator, class Operation>
RankAVLTree<TreeElement, Comparator, Operation>::~RankAVLTree() {
	this->deleteRankAVLTree();
}

template<class TreeElement, class Comparator, class Operation>
RankAVLTreeNode<TreeElement, Comparator, Operation>* RankAVLTree<TreeElement,
		Comparator, Operation>::rotateToLL(
		RankAVLTreeNode<TreeElement, Comparator, Operation>* trn) {
	trn->setRank(
			1 + (trn->getRightSon())->getRank()
					+ ((trn->getLeftSon())->getRightSon())->getRank());

	(trn->getLeftSon())->setRank(
			2 + ((trn->getLeftSon())->getLeftSon())->getRank()
					+ ((trn->getLeftSon())->getRightSon())->getRank()
					+ (trn->getRightSon())->getRank());

	RankAVLTreeNode<TreeElement, Comparator, Operation> *root = trn;
	RankAVLTreeNode<TreeElement, Comparator, Operation> *rootParent =
			root->getParent();
	RankAVLTreeNode<TreeElement, Comparator, Operation> *leftSon =
			root->getLeftSon();
	RankAVLTreeNode<TreeElement, Comparator, Operation> *leftSonRightSon =
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
RankAVLTreeNode<TreeElement, Comparator, Operation>* RankAVLTree<TreeElement,
		Comparator, Operation>::rotateToRR(
		RankAVLTreeNode<TreeElement, Comparator, Operation>* trn) {
	trn->setRank(
			1 + (trn->getLeftSon())->getRank()
					+ ((trn->getRightSon())->getLeftSon())->getRank());
	(trn->getRightSon())->setRank(
			2 + ((trn->getRightSon())->getLeftSon())->getRank()
					+ ((trn->getRightSon())->getRightSon())->getRank()
					+ (trn->getLeftSon())->getRank());
	RankAVLTreeNode<TreeElement, Comparator, Operation>* root = trn;
	RankAVLTreeNode<TreeElement, Comparator, Operation> *rootParent =
			root->getParent();
	RankAVLTreeNode<TreeElement, Comparator, Operation> *rightSon =
			root->getRightSon();
	RankAVLTreeNode<TreeElement, Comparator, Operation> *rightLeftSon =
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
RankAVLTreeNode<TreeElement, Comparator, Operation>* RankAVLTree<TreeElement,
		Comparator, Operation>::rotateToLR(
		RankAVLTreeNode<TreeElement, Comparator, Operation>* trn) {
	this->rotateToRR(trn->getLeftSon());
	return this->rotateToLL(trn);
}

template<class TreeElement, class Comparator, class Operation>
RankAVLTreeNode<TreeElement, Comparator, Operation>* RankAVLTree<TreeElement,
		Comparator, Operation>::rotateToRL(
		RankAVLTreeNode<TreeElement, Comparator, Operation>* trn) {
	this->rotateToLL(trn->getRightSon());
	return this->rotateToRR(trn);
}

template<class TreeElement, class Comparator, class Operation>
RankAVLTreeNode<TreeElement, Comparator, Operation>* RankAVLTree<TreeElement,
		Comparator, Operation>::getRoot() const {
	if (this == NULL) {
		return NULL;
	}
	return (this->root);
}

template<class TreeElement, class Comparator, class Operation>
void RankAVLTree<TreeElement, Comparator, Operation>::setRoot(
		RankAVLTreeNode<TreeElement, Comparator, Operation>* root) {
	if (this != NULL) {
		this->root = root;
	}
}

template<class TreeElement, class Comparator, class Operation>
TreeElement RankAVLTree<TreeElement, Comparator, Operation>::maxInRankAVLTree(
		RankAVLTreeNode<TreeElement, Comparator, Operation>* tree) {
	if (tree == NULL) {
		return TreeElement();
	}
	if (tree->getRightSon() == NULL)
		return tree->getData();
	return maxInRankAVLTree(tree->getRightSon());
}

template<class TreeElement, class Comparator, class Operation>
RankAVLTreeNode<TreeElement, Comparator, Operation>* RankAVLTree<TreeElement,
		Comparator, Operation>::getMinValue(
		RankAVLTreeNode<TreeElement, Comparator, Operation>* trd) {
	if (trd->getLeftSon() == NULL)
		return trd;
	return getMinValue(trd->getLeftSon());
}

template<class TreeElement, class Comparator, class Operation>
RankAVLTreeNode<TreeElement, Comparator, Operation>* RankAVLTree<TreeElement,
		Comparator, Operation>::find(const TreeElement& data) {
	if (this == NULL) {
		return NULL;
	} else {
		return (this->getRoot())->find(data);
	}
}

template<class TreeElement, class Comparator, class Operation>
TreeElement RankAVLTree<TreeElement, Comparator, Operation>::findElement(
		const TreeElement& data) {
	if (this != NULL) {
		RankAVLTreeNode<TreeElement, Comparator, Operation>* found =
				this->getRoot()->find(data);
		if (found)
			return found->getData();
	}
	return TreeElement();
}

template<class TreeElement, class Comparator, class Operation>
bool RankAVLTree<TreeElement, Comparator, Operation>::RankAVLTreeContain(
		const TreeElement& data) {
	if (this != NULL && this->getSize() != 0) {
		Comparator cmp;
		return !cmp(this->findElement(data), data);
	}
	return false;
}

template<class TreeElement, class Comparator, class Operation>
bool RankAVLTree<TreeElement, Comparator, Operation>::NodeInTree(
		RankAVLTreeNode<TreeElement, Comparator, Operation>* trn) {
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
void RankAVLTree<TreeElement, Comparator, Operation>::createEmptyWholeRankAVLTree(
		int n) {
	RankAVLTreeNode<TreeElement, Comparator, Operation>* root =
			new RankAVLTreeNode<TreeElement, Comparator, Operation>;
	this->setRoot(root);
	this->getRoot()->setHeight(log(n));
	n--;
	(this->getRoot())->createEmptyWholeRankAVLTreeNode(n);
}

template<class TreeElement, class Comparator, class Operation>
void RankAVLTree<TreeElement, Comparator, Operation>::removeInorderRightLeft(
		int amount) {
	(this->getRoot())->deleteInOrderRL(amount);
}

template<class TreeElement, class Comparator, class Operation>
TreeElement* RankAVLTree<TreeElement, Comparator, Operation>::returnSortedTreeElementsInOrder() {
	int size = this->getSize();
	TreeElement* sorted_array = (TreeElement*) malloc(
			sizeof(TreeElement) * size);
	int itr = 0;
	(this->getRoot())->returnSortedTreeElements(sorted_array, itr);
	return sorted_array;
}

template<class TreeElement, class Comparator, class Operation>
//can be modified to return a value of operation
void RankAVLTree<TreeElement, Comparator, Operation>::operateInOrder(
		Operation& op) {
	(this->getRoot())->operateInOrder(op);
}

template<class TreeElement, class Comparator, class Operation>
void RankAVLTree<TreeElement, Comparator, Operation>::deleteByInfo(
		const TreeElement& info) {
	this->deleteNodeUpdateRankSearchPath(info, this->getRoot());
	this->deleteNode(this->find(info));

}

template<class TreeElement, class Comparator, class Operation>
void RankAVLTree<TreeElement, Comparator, Operation>::deleteNode(
		RankAVLTreeNode<TreeElement, Comparator, Operation>* trn) {
	if (trn != NULL && this != NULL) {
		if (!(trn->isLeaf() || trn->isOneChild())) {
			RankAVLTreeNode<TreeElement, Comparator, Operation> *minimumSubRightRankAVLTree =
					getMinValue(trn->getRightSon());
			TreeElement orgInfo = trn->getData();
			trn->setData(minimumSubRightRankAVLTree->getData());
			minimumSubRightRankAVLTree->setData(orgInfo);
			this->deleteNode(minimumSubRightRankAVLTree);
			return;
		}
		if (trn->isLeaf() == true) {
			RankAVLTreeNode<TreeElement, Comparator, Operation> *trnParent =
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
			RankAVLTreeNode<TreeElement, Comparator, Operation> *trnParent =
					trn->getParent();
			if (trn->getRightSon() == NULL) {
				RankAVLTreeNode<TreeElement, Comparator, Operation> *trnLeftSon =
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
				RankAVLTreeNode<TreeElement, Comparator, Operation> *trnRightSon =
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
void RankAVLTree<TreeElement, Comparator, Operation>::deleteRankAVLTree() {
	if (this != NULL) {
		if (this->getRoot() != NULL) {
			(this->getRoot())->deletePostOrder();
		}
	}
}

template<class TreeElement, class Comparator, class Operation>
void RankAVLTree<TreeElement, Comparator, Operation>::insert(TreeElement data) {
	if (this->getRoot() == NULL) {
		RankAVLTreeNode<TreeElement, Comparator, Operation> *toInsert =
				new RankAVLTreeNode<TreeElement, Comparator, Operation>();
		toInsert->setData(data);
		this->setRoot(toInsert);
		return;
	}
	insertToTree(data, (this->getRoot()));
}

template<class TreeElement, class Comparator, class Operation>
void RankAVLTree<TreeElement, Comparator, Operation>::insertToTree(
		TreeElement data,
		RankAVLTreeNode<TreeElement, Comparator, Operation>* trn) {
	Comparator compare;
	trn->setRank(trn->getRank()+1);
	if (compare(trn->getData(), data) == 0) {
		return;
	}
	if ((compare(trn->getData(), data) < 0)) {
		if (trn->getLeftSon()) {
			insertToTree(data, (trn->getLeftSon()));
			return;
		}
		RankAVLTreeNode<TreeElement, Comparator, Operation> *toInsertLeft =
				new RankAVLTreeNode<TreeElement, Comparator, Operation>();
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
	RankAVLTreeNode<TreeElement, Comparator, Operation> *toInsertRight =
			new RankAVLTreeNode<TreeElement, Comparator, Operation>();
	toInsertRight->setData(data);
	trn->setRight(toInsertRight);
	toInsertRight->setParent(trn);
	this->isNeedToRotate(trn);
	return;
}

template<class TreeElement, class Comparator, class Operation>
void RankAVLTree<TreeElement, Comparator, Operation>::fillInRankAVLTree(TreeElement* arr) {
	int itr = 0;
	this->getRoot()->arrayToRankAVLTreeNode(arr, itr);
}

template<class TreeElement, class Comparator, class Operation>
void RankAVLTree<TreeElement, Comparator, Operation>::isNeedToRotate(
		RankAVLTreeNode<TreeElement, Comparator, Operation>* trn) {
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
int RankAVLTree<TreeElement, Comparator, Operation>::getSize() {
	if (this != NULL) {
		return ((this->getRoot())->getSize());
	}
	return -1;
}
template<class TreeElement, class Comparator, class Operation>
int RankAVLTree<TreeElement, Comparator, Operation>::
getRange(const TreeElement& min_info, const TreeElement& max_info) {
	int lesser_equal_min = this->getRoot()->getSmaller(min_info);
	int bigger_max = this->getRoot()->getBigger(max_info); // you Idiot you sent him minimu, now change   cause i dont understand fucking russion
	return this->getRoot()->getRank() - lesser_equal_min - bigger_max;
}

template<class TreeElement, class Comparator, class Operation>
void  RankAVLTree<TreeElement, Comparator, Operation>::
	deleteNodeUpdateRankSearchPath(const TreeElement& info,
		RankAVLTreeNode<TreeElement, Comparator, Operation >* trn) {
	Comparator compare;
	if (compare(trn->getData(), info) == 0) {
		return;
	}
	trn->setRank(trn->getRank() - 1);
	if ((compare(trn->getData(), info) < 0)) {
		if (trn->getLeftSon()) {
			deleteNodeUpdateRankSearchPath(info, (trn->getLeftSon()));
			return;
		}
	}
	if (trn->getRightSon()) {
		deleteNodeUpdateRankSearchPath(info, (trn->getRightSon()));
		return;
	}
}

#endif /* RANKAVLTREE_H_ */
