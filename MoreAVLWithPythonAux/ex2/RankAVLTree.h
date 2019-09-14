/*
 * RankAVLTree.h
 *
 *  Created on: 25 бреб 2015
 *      Author:
 */

#ifndef RANKAVLTREE_H_
#define RANKAVLTREE_H_

#include "RankAVLTreeNode.h"
#include <math.h>
#include "Exceptions.h"

//class T is the class of the RankAVLTree and the class S is the function object, to which the RankAVLTree is sorted by
template<class TreeElement, class Comparator, class Getter>
class RankAVLTree {
private:
	//static TreeElement* new_min;
	RankAVLTreeNode<TreeElement, Comparator, Getter>* _root; //pointer to the RankAVLTreeNode which acts as the root
	/**
	 * performs a LL flip over the current RankAVLTreeNode, using it as the center of the flip
	 */
	RankAVLTreeNode<TreeElement, Comparator, Getter>* flipLL(
			RankAVLTreeNode<TreeElement, Comparator, Getter>* trn);
	/**
	 * performs a RR flip over the current RankAVLTreeNode, using it as the center of the flip
	 */
	RankAVLTreeNode<TreeElement, Comparator, Getter>* flipRR(
			RankAVLTreeNode<TreeElement, Comparator, Getter>* trn);
	/**
	 * performs a LR flip over the current RankAVLTreeNode, using it as the center of the flip
	 */
	RankAVLTreeNode<TreeElement, Comparator, Getter>* flipLR(
			RankAVLTreeNode<TreeElement, Comparator, Getter>* trn);
	/**
	 * performs a RL flip over the current RankAVLTreeNode, using it as the center of the flip
	 */
	RankAVLTreeNode<TreeElement, Comparator, Getter>* flipRL(
			RankAVLTreeNode<TreeElement, Comparator, Getter>* trn);

public:
	/**
	 * default constructor for RankAVLTree
	 */
	RankAVLTree();
	/*@param _root is a pointer to the root of the newly created RankAVLTree
	 * constructor which initializes the root of the RankAVLTree
	 */
	RankAVLTree(RankAVLTreeNode<TreeElement, Comparator, Getter>* _root);
	/**
	 * copy constructor
	 */
	RankAVLTree(const RankAVLTree<TreeElement, Comparator, Getter>& tr);
	/**
	 * returns a pointer to the root son of the current RankAVLTree, if this is NULL, NULL is returned
	 */
	/**
	 *Destructor of the RankAVLTree
	 */
	~RankAVLTree();
	RankAVLTreeNode<TreeElement, Comparator, Getter>* getRoot() const;
	/**
	 *@param root is a pointer to the new root of the current RankAVLTree
	 * sets the root of the current RankAVLTree to the given RankAVLTreeNode pointer
	 */
	void setRoot(RankAVLTreeNode<TreeElement, Comparator, Getter>* root);
	/**
	 *@param trd is the sub-RankAVLTree the maximum value will come from
	 * returns the maximum value of the sub-RankAVLTree, whose root is trd
	 */
	TreeElement maxInRankAVLTree(
			RankAVLTreeNode<TreeElement, Comparator, Getter>* trd);
	/**
	 *@param trd is the sub-RankAVLTree the pointer to the minimum value will come from
	 * returns pointer to the RankAVLTreeNode which contains the minimum value in the sub-RankAVLTree, whose root is trd
	 */
	RankAVLTreeNode<TreeElement, Comparator, Getter>* minPointerInRankAVLTree(
			RankAVLTreeNode<TreeElement, Comparator, Getter>* trd);
	/**
	 *@param info is the info field of the RankAVLTreeNode we are trying to find
	 * returns pointer to the RankAVLTreeNode contains info, if not found returns NULL
	 */
	RankAVLTreeNode<TreeElement, Comparator, Getter>* find(
			const TreeElement& info);
	/**
		 *@param info is the info field of the RankAVLTreeNode we are trying to find
		 * returns pointer to the RankAVLTreeNode contains info, if not found returns NULL
		 */ //TODO: update comment
	TreeElement findMinBySecondOfAllEvenOrBiggerByFirst(
								const TreeElement& info);
	/**
	 *@param n is the number of vertices we want to create a new whole tree
	 which can contain all old vertices (its number of vertices is the nearest
	 pow of 2 which is bigger.
	 */
	void createEmptyWholeRankAVLTree(int n);
	/**
	 *@param info is the element we want to check in the tree. returns true if
	 *exist, false otherwise.
	 */
	bool RankAVLTreeContain(const TreeElement& info);

	/**
	 *@param info is the element we want to find in the tree. returns correct
	 element if it exist and defalut constructored element otherwise.
	 */
	TreeElement findElement(const TreeElement& info);
	/**
	 *@param trn is the RankAVLTreeNode we are trying to check if exists in this RankAVLTree
	 *returns true if trn is in this RankAVLTree, otherwise - false
	 */
	bool isInTree(RankAVLTreeNode<TreeElement, Comparator, Getter>* trn);
	/**
	 * allocates an array of TreeElement elements
	 * passes on all vertices data in the tree by inorder traversal and
	 * and returns the array of the elements
	 */
	TreeElement* returnSortedTreeElementsInOrder();
	/**
	* allocates an array of TreeElement elements
	* passes on all vertices data in the tree by inorder traversal and
	* and returns the array of the elements
	*/
	TreeElement* returnSortedTreeElementsInOrderRL();
	/**
		* fill the RankAVLTree with elements from sorted array arr
		 *arr is the array we translate to Tree
		 */
	void fillInRankAVLTree(TreeElement* arr);
	/**
	 *@param arr is the array we translate to Tree and itr is an aux param
	 */
	//void arrayToTree(TreeElement* arr);
	/**
	 * passes on all vertices data in the tree by inorder traversal and
	 * does an operation on each of them.
	 */
	//void operateInOrder(Operation& op);
	/**
	 *@param info is the info of the RankAVLTreeNode we want to delete from this RankAVLTree
	 * deletes the RankAVLTreeNode with the given info from this RankAVLTree, does nothing if no RankAVLTreeNode contains info
	 */
	void deleteByInfo(const TreeElement& info);
	/**
	 *@param trn is pointer to the RankAVLTreeNode we want to
	 *@param  delete from this RankAVLTree
	 * deletes the given RankAVLTreeNode, does nothing if the pointer
	 *  is to a RankAVLTreeNode not in the RankAVLTree
	 */
	RankAVLTreeNode<TreeElement, Comparator, Getter>*
		deleteNode(RankAVLTreeNode<TreeElement, Comparator, Getter>* trn);

	//removes all unnececery elements to create an almost whole tree
	void removeInorderRightLeft(int amount);
	/**
	 * deletes all the allocated memory of this RankAVLTree
	 */
	void deleteRankAVLTree();
	/**
	 *@param data is the data to add to this RankAVLTree
	 * inserts a new node with data as its info to this RankAVLTree
	 */
	void insert(TreeElement data);
	//insert data to this RankAVLTree, using trn as his parent
	void insertToTree(TreeElement data,
			RankAVLTreeNode<TreeElement, Comparator, Getter>* trn);
	/*operates on the parent of the node that was inserted/removed.
	 makes a rotate if there is a rotate to make.*/
	void isNeedToRotate(RankAVLTreeNode<TreeElement, Comparator, Getter>* trn);
	/**
	 * returns the number of RankAVLTreeNode in the RankAVLTree
	 */
	int getSize();

	/**
		 * returns the number of RankAVLTreeNode in the RankAVLTree
		 */
		int select(int n);

};

template<class TreeElement, class Comparator, class Getter>
RankAVLTree<TreeElement, Comparator, Getter>::RankAVLTree() {
	this->_root = NULL; // create a deme node
}

template<class TreeElement, class Comparator, class Getter>
RankAVLTree<TreeElement, Comparator, Getter>::RankAVLTree(
		RankAVLTreeNode<TreeElement, Comparator, Getter>* root) {
	this->_root = root; /// bad copy
}

template<class TreeElement, class Comparator, class Getter>
RankAVLTree<TreeElement, Comparator, Getter>::RankAVLTree(
		const RankAVLTree<TreeElement, Comparator, Getter>& tr) {
	if (tr.getRoot() != NULL) {
		this->_root = new RankAVLTreeNode<TreeElement, Comparator, Getter>(
				tr._root);
	} else {
		this->_root = NULL;
	}
}

template<class TreeElement, class Comparator, class Getter>
RankAVLTree<TreeElement, Comparator, Getter>::~RankAVLTree() {
	this->deleteRankAVLTree();
	this->_root = NULL;
}

template<class TreeElement, class Comparator, class Getter>
RankAVLTreeNode<TreeElement, Comparator, Getter>* RankAVLTree<TreeElement,
		Comparator, Getter>::flipLL(
		RankAVLTreeNode<TreeElement, Comparator, Getter>* trn) {
	trn->setRank(
				1 + (trn->getRight())->getRank()
						+ ((trn->getLeft())->getRight())->getRank());

		(trn->getLeft())->setRank(
				2 + ((trn->getLeft())->getLeft())->getRank()
						+ ((trn->getLeft())->getRight())->getRank()
						+ (trn->getRight())->getRank());

		trn->setSum(
			Getter()(trn->getInfo()) + (trn->getRight())->getSum()
								+ ((trn->getLeft())->getRight())->getSum());

		(trn->getLeft())->setSum(
			Getter()(trn->getLeft()->getInfo())
			//+ ((trn->getRight() == NULL) ? 0 : Getter()(trn->getRight()->getInfo()))
			+ ((trn->getLeft())->getLeft())->getSum()
			//+ ((trn->getLeft())->getRight())->getSum()
			//+ (trn->getRight())->getSum());
			+ (trn->getSum()));

		RankAVLTreeNode<TreeElement, Comparator, Getter> *root = trn;
		RankAVLTreeNode<TreeElement, Comparator, Getter> *rootParent =
				root->getParent();
		RankAVLTreeNode<TreeElement, Comparator, Getter> *leftSon =
				root->getLeft();
		RankAVLTreeNode<TreeElement, Comparator, Getter> *leftSonRightSon =
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
		/*
		Comparator cmp2;
		TreeElement min_LsRs_RsR = cmp2((root->getRight())->getMin(),
										(root->getLeft())->getMin()) < 0
										 ? (root->getLeft())->getMin()
										 : (root->getRight())->getMin();
		root->setMin(cmp2(min_LsRs_RsR, root->getInfo()) < 0 ? root->getInfo() : min_LsRs_RsR); //TODO: check correctness

		TreeElement min_lsl_r = cmp2((leftSon->getRight())->getMin(),
								leftSon->getLeft()->getMin()) < 0
								? leftSon->getLeft()->getMin()
								: leftSon->getRight()->getMin();
		leftSon->setMin(cmp2(min_lsl_r, leftSon->getInfo()) > 0 ? min_lsl_r : leftSon->getInfo()); //TODO: check correctness
		*/
		return leftSon;
}

template<class TreeElement, class Comparator, class Getter>
RankAVLTreeNode<TreeElement, Comparator, Getter>* RankAVLTree<TreeElement,
		Comparator, Getter>::flipRR(
		RankAVLTreeNode<TreeElement, Comparator, Getter>* trn) {
	trn->setRank(
				1 + (trn->getLeft())->getRank()
						+ ((trn->getRight())->getLeft())->getRank());
		(trn->getRight())->setRank(
				2 + ((trn->getRight())->getLeft())->getRank()
						+ ((trn->getRight())->getRight())->getRank()
						+ (trn->getLeft())->getRank());

		trn->setSum(
						Getter()(trn->getInfo()) + (trn->getLeft())->getSum()
								+ ((trn->getRight())->getLeft())->getSum());
		(trn->getRight())->setSum(
			Getter()(trn->getRight()->getInfo())
			//	+ ((trn->getRight())->getLeft())->getSum()
				//+ (trn->getLeft() == NULL ? 0 : Getter()(trn->getLeft()->getInfo()))
			+ ((trn->getRight())->getRight())->getSum()
			//+ (trn->getLeft())->getSum());
			+ (trn->getSum()));

		RankAVLTreeNode<TreeElement, Comparator, Getter>* root = trn;
		RankAVLTreeNode<TreeElement, Comparator, Getter> *rootParent =
				root->getParent();
		RankAVLTreeNode<TreeElement, Comparator, Getter> *rightSon =
				root->getRight();
		RankAVLTreeNode<TreeElement, Comparator, Getter> *rightLeftSon =
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
		/*Comparator cmp2;
		TreeElement min_RLs_rL = cmp2((root->getLeft())->getMin(),
										  rightLeftSon->getMin()) > 0
											? root->getLeft()->getMin()
											: rightLeftSon->getMin();
		root->setMin(cmp2(root->getMin(), min_RLs_rL) > 0 ? root->getMin() : min_RLs_rL); //TODO: check correctness
		TreeElement min_rsr_r = cmp2((rightSon->getRight())->getMin(),
										root->getMin()) > 0
										? rightSon->getRight()->getMin()
										: root->getMin();
		rightSon->setMin(cmp2(rightSon->getMin(), min_rsr_r) > 0 ? rightSon->getMin() : min_rsr_r); //TODO: check correctness
		*/
		return rightSon;
}

template<class TreeElement, class Comparator, class Getter>
RankAVLTreeNode<TreeElement, Comparator, Getter>* RankAVLTree<TreeElement,
		Comparator, Getter>::flipLR(
		RankAVLTreeNode<TreeElement, Comparator, Getter>* trn) {
	this->flipRR(trn->getLeft());
	return this->flipLL(trn);
}

template<class TreeElement, class Comparator, class Getter>
RankAVLTreeNode<TreeElement, Comparator, Getter>* RankAVLTree<TreeElement,
		Comparator, Getter>::flipRL(
		RankAVLTreeNode<TreeElement, Comparator, Getter>* trn) {
	this->flipLL(trn->getRight());
	return this->flipRR(trn);
}

template<class TreeElement, class Comparator, class Getter>
RankAVLTreeNode<TreeElement, Comparator, Getter>* RankAVLTree<TreeElement,
		Comparator, Getter>::getRoot() const {
	if (this != NULL) {
		//if (this->_root != NULL) {
		return this->_root;
		//}
	}
	return NULL;
}

template<class TreeElement, class Comparator, class Getter>
void RankAVLTree<TreeElement, Comparator, Getter>::setRoot(
		RankAVLTreeNode<TreeElement, Comparator, Getter>* root) {
	if (this != NULL) {
		this->_root = root;
	}
}

template<class TreeElement, class Comparator, class Getter>
TreeElement RankAVLTree<TreeElement, Comparator, Getter>::maxInRankAVLTree(
		RankAVLTreeNode<TreeElement, Comparator, Getter>* trd) {
	if (trd == NULL) {
		return TreeElement();
	}
	if (trd->getRight() == NULL)
		return trd->getInfo();
	return maxInRankAVLTree(trd->getRight());
}

template<class TreeElement, class Comparator, class Getter>
RankAVLTreeNode<TreeElement, Comparator, Getter>* RankAVLTree<TreeElement,
		Comparator, Getter>::minPointerInRankAVLTree(
		RankAVLTreeNode<TreeElement, Comparator, Getter>* trd) {
	if (trd->getLeft() == NULL)
		return trd;
	return minPointerInRankAVLTree(trd->getLeft());
}

template<class TreeElement, class Comparator, class Getter>
RankAVLTreeNode<TreeElement, Comparator, Getter>* RankAVLTree<TreeElement,
		Comparator, Getter>::find(const TreeElement& info) {
	if (this != NULL) {
		return (this->getRoot())->find(info);
	}
	return NULL;
}

template<class TreeElement, class Comparator, class Getter>
TreeElement RankAVLTree<TreeElement, Comparator, Getter>::findElement(
		const TreeElement& info) {
	if (this != NULL) {
		RankAVLTreeNode<TreeElement, Comparator, Getter>* found =
				this->getRoot()->find(info);
		if (found)
			return found->getInfo();
	}
	return TreeElement();
}

template<class TreeElement, class Comparator, class Getter>
TreeElement RankAVLTree<TreeElement, Comparator, Getter>::
								findMinBySecondOfAllEvenOrBiggerByFirst(
	const TreeElement& info) {
	TreeElement min;
	if (this != NULL) {
		(this->getRoot())->findEvenOrBigger(info, min);
		
	}
	return min;
}

template<class TreeElement, class Comparator, class Getter>
bool RankAVLTree<TreeElement, Comparator, Getter>::RankAVLTreeContain(
		const TreeElement& info) {
	if (this != NULL && this->getSize() != 0) {
		Comparator cmp;
		return !cmp(this->findElement(info), info);
	}
	return false;
}

template<class TreeElement, class Comparator, class Getter>
bool RankAVLTree<TreeElement, Comparator, Getter>::isInTree(
		RankAVLTreeNode<TreeElement, Comparator, Getter>* trn) {
	if (trn == NULL || this == NULL) {
		return false;
	}
	if (trn->getParent() == this->getRoot() || trn == this->getRoot()) {
		return true;
	}
	return this->isInTree(trn->getParent());
}

template<class TreeElement, class Comparator, class Getter>
void RankAVLTree<TreeElement, Comparator, Getter>::createEmptyWholeRankAVLTree(
		int n) {
	RankAVLTreeNode<TreeElement, Comparator, Getter>* root = new RankAVLTreeNode<
			TreeElement, Comparator, Getter>;
	this->setRoot(root);
	this->getRoot()->setHeight(log(n));
	n--;
	(this->getRoot())->createEmptyWholeRankAVLTreeNode(n);
}

/*template<class TreeElement, class Comparator, class Getter>
void RankAVLTree<TreeElement, Comparator, Getter>::arrayToTree(
		TreeElement* arr) {
	//int size = this->getSize();
	int itr = 0;
	(this->getRoot())->arrayToRankAVLTreeNode(arr, itr);
}*/

template<class TreeElement, class Comparator, class Getter>
void RankAVLTree<TreeElement, Comparator, Getter>::removeInorderRightLeft(
		int amount) {
	(this->getRoot())->deleteInOrderRL(amount);
	if(amount >= 1) {
		(this->getRoot())->getRight()->~RankAVLTreeNode();
		(this->getRoot())->setRight(NULL);
	} else if(amount >= 2) {
		(this->getRoot())->getLeft()->~RankAVLTreeNode();
		(this->getRoot())->setLeft(NULL);
	} else if (amount >= 3) {
		(this->getRoot())->~RankAVLTreeNode();
		this->setRoot(NULL);
	} else {}
}

template<class TreeElement, class Comparator, class Getter>
TreeElement* RankAVLTree<TreeElement, Comparator, Getter>::returnSortedTreeElementsInOrder() {
	int size = this->getSize();
	if(size < 1) return NULL;
	TreeElement* sorted_array = (TreeElement*) malloc(
			sizeof(TreeElement) * size);
	if(!sorted_array){
		return NULL;
	}
	int itr = 0;
	(this->getRoot())->returnSortedTreeElements(sorted_array, itr);
	return sorted_array;
}

/*template<class TreeElement, class Comparator, class Getter>
//can be modified to return a value of operation
void RankAVLTree<TreeElement, Comparator, Getter>::operateInOrder(
		Operation& op) {
	(this->getRoot())->operateInOrder(op);
}*/

template<class TreeElement, class Comparator, class Getter>
TreeElement* RankAVLTree<TreeElement, Comparator, Getter>::returnSortedTreeElementsInOrderRL() {
	int size = this->getSize();
	if (size < 1) return NULL;
	TreeElement* sorted_array = (TreeElement*)malloc(
		sizeof(TreeElement) * size);
	if (!sorted_array) {
		return NULL;
	}
	int itr = 0;
	(this->getRoot())->returnSortedTreeElements(sorted_array, itr);
	return sorted_array;
}

template<class TreeElement, class Comparator, class Getter>
void RankAVLTree<TreeElement, Comparator, Getter>::deleteByInfo(
		const TreeElement& info) {
	RankAVLTreeNode<TreeElement, Comparator, Getter>*
		parent_of_deleted = this->deleteNode(this->find(info));
	//int str_of_deleted = parent_of_deleted == NULL ? 0 : Getter()(parent_of_deleted->getInfo());
	while (parent_of_deleted) {
		/*
		Comparator cmp2;
		TreeElement min = cmp2(parent_of_deleted->getRight()->getMin(), 
			(parent_of_deleted->getLeft())->getMin()) < 0 ? 
			(parent_of_deleted->getLeft())->getMin() : 
			parent_of_deleted->getRight()->getMin();
		min = cmp2(parent_of_deleted->getInfo(), min) < 0 ? min : 
									parent_of_deleted->getInfo();
		parent_of_deleted->setMin(min);
		*/
		parent_of_deleted->setRank(parent_of_deleted->getRight()->getRank()+ parent_of_deleted->getLeft()->getRank() + 1); //Todo :: check
		parent_of_deleted->setSum(parent_of_deleted->getRight()->getSum() + parent_of_deleted->getLeft()->getSum() + Getter()(parent_of_deleted->getInfo())); //Todo :: check
		parent_of_deleted = parent_of_deleted->getParent();
	}
}

/*template<class TreeElement, class Comparator, class Getter>
TreeElement* RankAVLTree<class TreeElement, class MainComparator, class AlterComparator>::new_min = new TreeElement();
*/

template<class TreeElement, class Comparator, class Getter>
RankAVLTreeNode<TreeElement, Comparator, Getter>*
RankAVLTree<TreeElement, Comparator, Getter>::deleteNode(
		RankAVLTreeNode<TreeElement, Comparator, Getter>* trn) {
	if (trn != NULL && this != NULL) {
		//if (/*this->isInTree(trn) == */true) {
		if (!(trn->isLeaf() || trn->isOneChild())) {
			//two childs
			//finds minimum in right son and switching between them, then it knows how to treat a leaf or 1 child
			RankAVLTreeNode<TreeElement, Comparator, Getter> *minimumSubRightRankAVLTree =
					minPointerInRankAVLTree(trn->getRight());
			TreeElement orgInfo = trn->getInfo();
			trn->setInfo(minimumSubRightRankAVLTree->getInfo());
			minimumSubRightRankAVLTree->setInfo(orgInfo); //TODO: maybe update by AlterCompare
			RankAVLTreeNode<TreeElement, Comparator, Getter>* prnt
				= minimumSubRightRankAVLTree->getParent();
			this->deleteNode(minimumSubRightRankAVLTree);
			return prnt;
		}
		if (trn->isLeaf()) {
			RankAVLTreeNode<TreeElement, Comparator, Getter> *trnParent =
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
			return trnParent;

		} else {					//one child
			RankAVLTreeNode<TreeElement, Comparator, Getter> *trnParent =
					trn->getParent();
			if (trn->getRight() == NULL) {
				//only left child
				RankAVLTreeNode<TreeElement, Comparator, Getter> *trnLeftSon =
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
				RankAVLTreeNode<TreeElement, Comparator, Getter> *trnRightSon =
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
			return trnParent;
		}
		//}
	}
	return NULL; //TODO: non-reach
}

/**
 * deallocating all the memory allocated to this RankAVLTree
 */
template<class TreeElement, class Comparator, class Getter>
void RankAVLTree<TreeElement, Comparator, Getter>::deleteRankAVLTree() {
	if (this != NULL) {
		if (this->getRoot() != NULL) {
			(this->getRoot())->deletePostOrder();
		}
	}
}

/**
 * inserts a new RankAVLTreeNode with the info data
 */
template<class TreeElement, class Comparator, class Getter>
void RankAVLTree<TreeElement, Comparator, Getter>::insert(TreeElement data) {
	if (this->getRoot() == NULL) { //if we have an empty tree and we need to insert the root.
		RankAVLTreeNode<TreeElement, Comparator, Getter> *toInsert =
				new RankAVLTreeNode<TreeElement, Comparator, Getter>();
		toInsert->setInfo(data);
		//toInsert->setMin(data);
		toInsert->setSum(Getter()(data));
		this->setRoot(toInsert);
		return;
	}
	insertToTree(data, (this->getRoot()));

}
/**
 * inserts the RankAVLTreeNode with the info data to the Sub-RankAVLTree with the root trn
 */
template<class TreeElement, class Comparator, class Getter>
void RankAVLTree<TreeElement, Comparator, Getter>::insertToTree(TreeElement data,
		RankAVLTreeNode<TreeElement, Comparator, Getter>* trn) {
	Comparator compare;
	trn->setRank(trn->getRank()+1);
	trn->setSum(trn->getSum()+Getter()(data));
	//Comparator compare2;
	if (compare(trn->getInfo(), data) == 0) {
		return;
	}
	/*if (compare2(trn->getMin(),data) < 0) {
		trn->setMin(data); //TODO: check if ptr good and correctness
	}*/
	if ((compare(trn->getInfo(), data) < 0)) {
		if (trn->getLeft()) {
			insertToTree(data, (trn->getLeft()));
			return;
		}
		RankAVLTreeNode<TreeElement, Comparator, Getter> *toInsertLeft =
				new RankAVLTreeNode<TreeElement, Comparator, Getter>();
		toInsertLeft->setInfo(data);
//		toInsertLeft->setMin(data);
		toInsertLeft->setSum(Getter()(data));
		trn->setLeft(toInsertLeft);
		toInsertLeft->setParent(trn);
		this->isNeedToRotate(trn);
		return;
	}
	if (trn->getRight()) {
		insertToTree(data, (trn->getRight()));
		return;
	}
	RankAVLTreeNode<TreeElement, Comparator, Getter> *toInsertRight =
			new RankAVLTreeNode<TreeElement, Comparator, Getter>();
	toInsertRight->setInfo(data);
//	toInsertRight->setMin(data);
	toInsertRight->setSum(Getter()(data));
	trn->setRight(toInsertRight);
	toInsertRight->setParent(trn);
	this->isNeedToRotate(trn);
	return;
}

template<class TreeElement, class Comparator, class Getter>
void RankAVLTree<TreeElement, Comparator, Getter>::fillInRankAVLTree(TreeElement* arr) {
	int itr = 0;
	this->getRoot()->arrayToRankAVLTreeNode(arr, itr);
}

/*operates on the parent of the node that was inserted/removed.
 makes a rotate if there is a rotate to make.*/
template<class TreeElement, class Comparator, class Getter>
void RankAVLTree<TreeElement, Comparator, Getter>::isNeedToRotate(
		RankAVLTreeNode<TreeElement, Comparator, Getter>* trn) {
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
 * returns the size of this RankAVLTree
 */
template<class TreeElement, class Comparator, class Getter>
int RankAVLTree<TreeElement, Comparator, Getter>::getSize() {
	if (this == NULL) {
		return -1;
	}
	return (this->getRoot())->getSize();
}

template<class TreeElement, class Comparator, class Getter> //ToDo:: check func
int RankAVLTree<TreeElement, Comparator, Getter>::select(int n){
	if (this == NULL || n < 1) {
			return -1;
	}
	return this->_root->select(n);
}

#endif /* AVLTREE_H_ */
