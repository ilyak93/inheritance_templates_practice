/*
 * AVLTree.h
 *
 *  Created on: 24 бреб 2015
 *      Author:
 */

#ifndef RANKAVLTREENODE_H_
#define RANKAVLTREENODE_H_

#include <stddef.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <math.h>
//class TreeElement is the class of the AVLTree and the class MainComparator is the function object,
//to which the AVLTree is sorted by is generice functor to the user
//to use.
template<class TreeElement, class Comparator, class Getter>
class RankAVLTreeNode {
private:
	TreeElement* info; //the data inside the current node
	RankAVLTreeNode* parent; //pointer to the parent node, NULL if root
	RankAVLTreeNode* left; //pointer to the left son
	RankAVLTreeNode* right; //pointer to the right son
	int height; //the height of the node
	int rank; //the rank of the current data
	int sum; //the sum of the current sub-tree
	//TreeElement* min;

public:
	/**
	 * default constructor for RankAVLTreeNode
	 */
	RankAVLTreeNode();
	/**
	 * copy constructor for RankAVLTreeNode
	 */
	RankAVLTreeNode(const RankAVLTreeNode<TreeElement, Comparator, Getter>& tr);
	/**
	 * copy constructor for RankAVLTreeNode
	 */
	RankAVLTreeNode(const RankAVLTreeNode<TreeElement, Comparator, Getter>* tr);

	/**
	 * returns the data stored in the current RankAVLTreeNode,
	 *  if current is NULL, NULL is returned
	 */
	TreeElement& getInfo() const;

	/**
	 * returns a pointer to the parent node of the current RankAVLTreeNode,
	 *  if current is NULL, NULL is returned
	 */
	RankAVLTreeNode<TreeElement, Comparator, Getter>* getParent() const;

	/**
	 * returns a pointer to the left son of the current RankAVLTreeNode,
	 *  if current is NULL, NULL is returned
	 */
	RankAVLTreeNode<TreeElement, Comparator, Getter>* getLeft() const;

	/**
	 * returns a pointer to the right son of the current RankAVLTreeNode,
	 *  if current is NULL, NULL is returned
	 */
	RankAVLTreeNode<TreeElement, Comparator, Getter>* getRight() const;

	/**
	 * returns the height of the current RankAVLTreeNode,
	 * if current is NULL, 0 is returned
	 */
	const int getHeight() const;

	/**
	 * @param height is the new height, to be applied to the
	 *  current RankAVLTreeNode
	 * sets the current RankAVLTreeNode's height to the given height
	 */
	void setHeight(int height);
	/**
	 * @param right is the new right son, to displace the current
	 * RankAVLTreeNode's right son
	 * sets the current RankAVLTreeNode's right to the given right
	 */
	void setRight(RankAVLTreeNode<TreeElement, Comparator, Getter>* right);
	/**
	 * @param left is the new left son, to displace the current
	 *  RankAVLTreeNode's left son
	 * sets the current RankAVLTreeNode's left to the given left
	 */
	void setLeft(RankAVLTreeNode<TreeElement, Comparator, Getter>* left);
	/**
	 * @param parent is the new parent node, to displace the current
	 *  RankAVLTreeNode's parent
	 * sets the current RankAVLTreeNode's parent to the given parent
	 */
	void setParent(RankAVLTreeNode<TreeElement, Comparator, Getter>* parent);
	/**
	 * @param info is the new data, to displace the current RankAVLTreeNode's data
	 * sets the current RankAVLTreeNode's info to the given info
	 */
	void setInfo(const TreeElement& info);
	/**
	 *@param info is the info of the RankAVLTreeNode we are
	 *@param  looking for in the sub-AVLTree which his root is this RankAVLTreeNode
	 * returns pointer to the RankAVLTreeNode whose info is
	 *  the given info, NULL if doesn't exist
	 */
	RankAVLTreeNode<TreeElement, Comparator, Getter>* find(
			const TreeElement& info);

	/**
		 *@param info is the info of the RankAVLTreeNode we are
		 *@param  looking for in the sub-AVLTree which his root is this RankAVLTreeNode
		 * returns pointer to the RankAVLTreeNode whose info is
		 *  the given info, NULL if doesn't exist
		 */
	int select(int n);

	/**
		*@param info is the info of the RankAVLTreeNode we are
		*  looking for the sub-AVLTree which all it's elements bigger or even
		*  the info by the MainComparator
		* returns pointer to the relevant RankAVLTreeNode,
		* NULL if doesn't exist
	*/
	void findEvenOrBigger(const TreeElement& info,
						  TreeElement& min_by_alter_compare);

	/**
	 *@param n is the number of vertices we want to create a new whole tree
	 which can contain all old vertices (its number of vertices is the nearest
	 pow of 2 which is bigger.
	 */
	void createEmptyWholeRankAVLTreeNode(int n);
	/**
	 * returns whther the RankAVLTreeNode is a leaf
	 */
	bool isLeaf();
	/**
	 * returns true if the RankAVLTreeNode has only on son (Left or Right)
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
	* @param sorted_array is the array in which will be put
	*  the TreeElements by InOrder.
	* @param itr is the iterator on the array
	* passes on all the vertices in the tree by inorder and
	*  put them into given array
	*/
	void returnSortedTreeElementsRL(TreeElement* sorted_array, int& itr);
	/**
		*@param arr is the array we translate to Tree and itr is an aux param
	*/
	void arrayToRankAVLTreeNode(TreeElement* arr, int& itr);
	
	/**
	 * passes on all the vertices in the tree by inorder and does an
	 *  operation on each data element in it.
	 */
	//void operateInOrder(Operation& op);
	/**
	 * deallocates every memory allocated in the sub-AVLTree which his root
	 *  is this RankAVLTreeNode
	 */
	void deletePostOrder();
	/**
	 * Aux function to delete unnececery vertices to make from whole tree
	 *  almost whole tree
	 *  	n = number of vertices to delete
	 *  	no return
	 */
	void deleteInOrderRL(int& n);
	/**
	 * returns the balance factor of the current RankAVLTreeNode (Height of Left son
	 *  - Height of Right son)
	 */
	int calculateBalanceFactor();
	/**
	 * returns max height between two RankAVLTreeNodes, if both NULL, -1 is returned
	 */
	int maxHeight(RankAVLTreeNode<TreeElement, Comparator, Getter>* trn1,
			RankAVLTreeNode<TreeElement, Comparator, Getter>* trn2);
	/**
	 * updates this RankAVLTreeNode height, based on his left and right sons height
	 */
	void updateHeight();
	/**
	 * returns the number of Nodes in the sub-AVLTree which his
	 *  root is this RankAVLTreeNode
	 */
	int getSize();
	/**
	 	 * returns the rank stored in the current RankRankRankAVLTreeNode, if current is NULL,
	 	 *  0 is returned as rank of empty son (0(left)+0(right)+0(itself)).
	 	 *  rank of a leaf is 1, the rank generally is rank of left + rank of right
	 	 *  + %curent_value
	*/
	int getRank() const;
	/**
	 	 * sets the new rank in the current RankRankRankAVLTreeNode, if current is NULL,
	 	 *  does nothing.
	 */
	void setRank(int new_rank);

	/**
		 	 * returns the rank stored in the current RankRankRankAVLTreeNode, if current is NULL,
		 	 *  0 is returned as rank of empty son (0(left)+0(right)+0(itself)).
		 	 *  rank of a leaf is 1, the rank generally is rank of left + rank of right
		 	 *  + %curent_value
		*/
		int getSum() const;
		/**
		 	 * sets the new rank in the current RankRankRankAVLTreeNode, if current is NULL,
		 	 *  does nothing.
		 */
		void setSum(int new_sum);
	/**
	 	 * gets the new min element of the SubRankTree which root is the current RankAVLTreeNode
	 	 * if current is NULL, does nothing.
	*/
	//TreeElement getMin()const;
	/**
	 	 * sets the new min element of the SubRankTree which root is the current RankAVLTreeNode
	 	 *  in the current RankRankRankAVLTreeNode, if current is NULL,
		 *  does nothing.
	*/
	//void setMin(const TreeElement& min);
	/**
		 * RankAVLTreeNode destructor
	*/
	~RankAVLTreeNode();
};

/**
 * default constructor for RankAVLTreeNode
 */
template<class TreeElement, class Comparator, class Getter>
RankAVLTreeNode<TreeElement, Comparator, Getter>::RankAVLTreeNode() {
	this->height = 0;
	this->info = new TreeElement();
	this->left = NULL;
	this->right = NULL;
	this->parent = NULL;
//	this->min = NULL;
	this->rank=1;
	this->sum = 0;
}
/**
 * copy constructor for RankAVLTreeNode
 */
template<class TreeElement, class Comparator, class Getter>
RankAVLTreeNode<TreeElement, Comparator, Getter>::RankAVLTreeNode(
		const RankAVLTreeNode<TreeElement, Comparator, Getter>& tr) {
	if(this == &tr) return;
	this->height = tr.getHeight();
	this->parent = new RankAVLTreeNode<TreeElement, Comparator, Getter>(
			tr.getParent());
	this->info = new TreeElement(tr.getInfo());
	this->right = new RankAVLTreeNode<TreeElement, Comparator, Getter>(
			tr.getRight());
	this->left = new RankAVLTreeNode<TreeElement, Comparator, Getter>(
			tr.getLeft());
	this->rank = tr.getRank();
	//delete(this->min);
	//this->min = tr.min;
	this->sum = tr.sum;
}

/**
 * copy constructor for RankAVLTreeNode*
 */
template<class TreeElement, class Comparator, class Getter>
RankAVLTreeNode<TreeElement, Comparator, Getter>::RankAVLTreeNode(
		const RankAVLTreeNode<TreeElement, Comparator, Getter>* tr) {
	if(this == tr) return;
	if (this != NULL && tr != NULL) {
		this->height = tr->getHeight();
		if (tr->getParent() == NULL) {
			this->parent = NULL;
		}
		//if not it was already initialized
		this->info = new TreeElement(tr->getInfo());
		if (tr->getRight() == NULL) {
			this->right = NULL;
		} else {
			this->right = new RankAVLTreeNode<TreeElement, Comparator, Getter>(
					tr->getRight());
			(this->getRight())->parent = this;
		}
		if (tr->getLeft() == NULL) {
			this->left = NULL;
		} else {
			this->left = new RankAVLTreeNode<TreeElement, Comparator, Getter>(
					tr->getLeft());
			(this->getLeft())->parent = this;
		}
		this->rank=tr->getRank();
		//delete this->min;
		//this->min = tr->min;
		this->sum = tr->sum;
	}
}

/**
 * returns the height of the current RankAVLTreeNode,
 *  if current is NULL, 0 is returned
 */
template<class TreeElement, class Comparator, class Getter>
const int RankAVLTreeNode<TreeElement, Comparator, Getter>::getHeight() const {
	if (this != NULL) {
		return this->height;
	}
	return 0;
}
/**
 * returns the data stored in the current RankAVLTreeNode,
 *  if current is NULL, NULL is returned
 */
template<class TreeElement, class Comparator, class Getter>
TreeElement& RankAVLTreeNode<TreeElement, Comparator, Getter>::getInfo() const {
	return *(this->info);
}
/**
 * returns a pointer to the right son of the current RankAVLTreeNode,
 *  if current is NULL, NULL is returned
 */
template<class TreeElement, class Comparator, class Getter>
RankAVLTreeNode<TreeElement, Comparator, Getter>* RankAVLTreeNode<TreeElement,
				 Comparator, Getter>::getRight() const {
	if (this != NULL) {
		return this->right;
	}
	return NULL;
}
/**
 * returns a pointer to the left son of the current RankAVLTreeNode,
 *  if current is NULL, NULL is returned
 */
template<class TreeElement, class Comparator, class Getter>
RankAVLTreeNode<TreeElement, Comparator, Getter>* RankAVLTreeNode<TreeElement,
		Comparator, Getter>::getLeft() const {
	if (this != NULL) {
		return this->left;
	}
	return NULL;
}
/**
 * returns a pointer to the parent node of the current RankAVLTreeNode,
 *  if current is NULL, NULL is returned
 */
template<class TreeElement, class Comparator, class Getter>
RankAVLTreeNode<TreeElement, Comparator, Getter>* RankAVLTreeNode<TreeElement,
		Comparator, Getter>::getParent() const {
	if (this != NULL) {
		return this->parent;
	}
	return NULL;
}

/**
 * @param height is the new height, to be applied to the current
 *  RankAVLTreeNode
 * sets the current RankAVLTreeNode's height to the given height
 */
template<class TreeElement, class Comparator, class Getter>
void RankAVLTreeNode<TreeElement, Comparator, Getter>::setHeight(int height) {
	if (this != NULL) {
		this->height = height;
	}
}
/**
 * @param right is the new right son, to displace the current
 *  RankAVLTreeNode's right son
 * sets the current RankAVLTreeNode's right to the given right
 */
template<class TreeElement, class Comparator, class Getter>
void RankAVLTreeNode<TreeElement, Comparator, Getter>::setRight(
		RankAVLTreeNode<TreeElement, Comparator, Getter>* right) {
	if (this != NULL) {
		this->right = right;
	}
}
/**
 * @param left is the new left son, to displace the current
 *  RankAVLTreeNode's left son
 * sets the current RankAVLTreeNode's left to the given left
 */
template<class TreeElement, class Comparator, class Getter>
void RankAVLTreeNode<TreeElement, Comparator, Getter>::setLeft(
		RankAVLTreeNode<TreeElement, Comparator, Getter>* left) {
	if (this != NULL) {
		this->left = left;
	}
}
/**
 * @param parent is the new parent node, to displace the current
 * RankAVLTreeNode's parent
 * sets the current RankAVLTreeNode's parent to the given parent
 */
template<class TreeElement, class Comparator, class Getter>
void RankAVLTreeNode<TreeElement, Comparator, Getter>::setParent(
		RankAVLTreeNode<TreeElement, Comparator, Getter>* parent) {
	if (this != NULL) {
		this->parent = parent;
	}
}
/**
 * @param info is the new data, to displace the current RankAVLTreeNode's data
 * sets the current RankAVLTreeNode's info to the given info
 */
template<class TreeElement, class Comparator, class Getter>
void RankAVLTreeNode<TreeElement, Comparator, Getter>::setInfo(
		const TreeElement& info) {
	if (this != NULL) {
		if (this->info != NULL) {
			delete this->info;
		}
		this->info = new TreeElement(info);
	}
}

template<class TreeElement, class Comparator, class Getter>
RankAVLTreeNode<TreeElement, Comparator, Getter>* RankAVLTreeNode<TreeElement,
		Comparator, Getter>::find(const TreeElement& info) {
	if (this == NULL) {
		return NULL;
	}
	Comparator compare;
	if (compare(this->getInfo(), info) == 0) {
		return this;
	}
	if (compare(info, this->getInfo()) > 0) {
		return (this->getLeft())->find(info);
	}
	return (this->getRight())->find(info);
}

/*
template<class TreeElement, class Comparator, class Getter>
void
RankAVLTreeNode<TreeElement, Comparator, Getter>::findEvenOrBigger(
					const TreeElement& info, TreeElement& min_by_alter_compare){
	if (this == NULL) {
			return;
	}
	Comparator compare;
	if (compare(info, this->getInfo()) > 0) {
		if (compare3(info, this->getInfo()) == 0) {
			TreeElement tmp = min_by_alter_compare;
			min_by_alter_compare = compare2(this->getInfo(), (this->getLeft())->getMin()) < 0 ? (this->getLeft())->getMin() : this->getInfo();
			min_by_alter_compare = compare2(tmp, min_by_alter_compare) < 0 ? min_by_alter_compare : tmp;
		}
		(this->getLeft())->findEvenOrBigger(info, min_by_alter_compare);
	} else {
		TreeElement tmp = min_by_alter_compare;
		min_by_alter_compare = compare2(this->getInfo(), (this->getLeft())->getMin()) < 0 ? (this->getLeft())->getMin() : this->getInfo();
		min_by_alter_compare = compare2(tmp, min_by_alter_compare) < 0 ? min_by_alter_compare : tmp;
		(this->getRight())->findEvenOrBigger(info, min_by_alter_compare);
	}
}
*/

/**
 * returns whther the RankAVLTreeNode is a leaf
 */
template<class TreeElement, class Comparator, class Getter>
bool RankAVLTreeNode<TreeElement, Comparator, Getter>::isLeaf() {
	return this->getLeft() == NULL && this->getRight() == NULL;
}

template<class TreeElement, class Comparator, class Getter>
bool RankAVLTreeNode<TreeElement, Comparator, Getter>::isOneChild() {
	return (this->getLeft() == NULL && this->getRight() != NULL)
			|| (this->getLeft() != NULL && this->getRight() == NULL);
}

/*template<class TreeElement, class Comparator, class Getter>
void RankAVLTreeNode<TreeElement, Comparator, Getter>::operateInOrder(
		Operation& op) {
	if (this != NULL) {
		(this->getLeft())->operateInOrder(op);
		op(this);
		(this->getRight())->operateInOrder(op);
	}
}*/

template<class TreeElement, class Comparator, class Getter>
void RankAVLTreeNode<TreeElement, Comparator, Getter>::createEmptyWholeRankAVLTreeNode(
		int n) {
	if (n < 2) {
		this->setLeft(NULL);
		this->setRight(NULL);
		this->setHeight(0);
		return;
	}
	RankAVLTreeNode<TreeElement, Comparator, Getter>* left = new RankAVLTreeNode<
			TreeElement, Comparator, Getter>;
	left->setParent(this);
	this->setLeft(left);
	RankAVLTreeNode<TreeElement, Comparator, Getter>* right = new RankAVLTreeNode<
			TreeElement, Comparator, Getter>;
	right->setParent(this);
	this->setRight(right);

	n /= 2;
	left->createEmptyWholeRankAVLTreeNode(n);
	right->createEmptyWholeRankAVLTreeNode(n);
	this->setHeight(log(n) + 1);
	this->rank=this->left->rank + this->right->rank+1;
}

template<class TreeElement, class Comparator, class Getter>
void RankAVLTreeNode<TreeElement, Comparator, Getter>::returnSortedTreeElements(
		TreeElement* sorted_array, int& itr) {
	if (this != NULL) {
		(this->getLeft())->returnSortedTreeElements(sorted_array, itr);
		sorted_array[itr++] = this->getInfo();
		(this->getRight())->returnSortedTreeElements(sorted_array, itr);
	}
}

template<class TreeElement, class Comparator, class Getter>
void RankAVLTreeNode<TreeElement, Comparator, Getter>::returnSortedTreeElementsRL(
	TreeElement* sorted_array, int& itr) {
	if (this != NULL) {
		(this->getRight())->returnSortedTreeElements(sorted_array, itr);
		sorted_array[itr++] = this->getInfo();
		(this->getLeft())->returnSortedTreeElements(sorted_array, itr);
	}
}

template<class TreeElement, class Comparator, class Getter>
void RankAVLTreeNode<TreeElement, Comparator, Getter>::deletePostOrder() {
	if (this != NULL) {
		(this->getLeft())->deletePostOrder();
		(this->getRight())->deletePostOrder();
		delete this;
	}
}

template<class TreeElement, class Comparator, class Getter>
void RankAVLTreeNode<TreeElement, Comparator, Getter>::deleteInOrderRL(int& n) {
	if (this != NULL) {
		(this->getRight())->deleteInOrderRL(n);
		if (this->isLeaf() && n > 0) {
			RankAVLTreeNode<TreeElement, Comparator, Getter>* tmp =
					this->getParent();
			//MainComparator cmp;
			//bool right_to_delete = !cmp(tmp->getRight()->getInfo(), this->getInfo());
			bool right_to_delete = (tmp->getRight() == this);
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
		(this->getLeft())->deleteInOrderRL(n);
	}
}

template<class TreeElement, class Comparator, class Getter>
void RankAVLTreeNode<TreeElement, Comparator, Getter>::arrayToRankAVLTreeNode(
		TreeElement* arr, int& itr) {
	if (this != NULL) {
		(this->getLeft())->arrayToRankAVLTreeNode(arr, itr);
		this->setInfo(arr[itr]);
		this->setSum(this->getLeft()->getSum() + Getter()(arr[itr++]));
		this->setRank(this->getLeft()->getRank()+1);
		(this->getRight())->arrayToRankAVLTreeNode(arr, itr);
		this->setSum(this->getSum() + this->getRight()->getSum());
		this->setRank(this->getRank() + this->getRight()->getRank());
	}
}

template<class TreeElement, class Comparator, class Getter>
int RankAVLTreeNode<TreeElement, Comparator, Getter>::calculateBalanceFactor() {
	if (this != NULL) {
		if (this->getRight() == NULL && this->getLeft() == NULL) {
			return 0;
		}
		if (this->getRight() == NULL) {
			return (this->getLeft())->getHeight() - (-1);
		}
		if (this->getLeft() == NULL) {
			return -1 - (this->getRight())->getHeight();
		}
		return (this->getLeft())->getHeight() - (this->getRight())->getHeight();
	}
	return 0;
}

/**
 * returns max height between two RankAVLTreeNodes, if both NULL, -1 is returned
 */
template<class TreeElement, class Comparator, class Getter>
int RankAVLTreeNode<TreeElement, Comparator, Getter>::maxHeight(
		RankAVLTreeNode<TreeElement, Comparator, Getter>* trn1,
		RankAVLTreeNode<TreeElement, Comparator, Getter>* trn2) {
	if (trn1 == NULL && trn2 == NULL) {
		return -1;
	}
	if (trn1 == NULL) {
		return trn2->getHeight();
	}
	if (trn2 == NULL) {
		return trn1->getHeight();
	}
	return trn1->getHeight() > trn2->getHeight() ?
			trn1->getHeight() : trn2->getHeight();
}

template<class TreeElement, class Comparator, class Getter>
void RankAVLTreeNode<TreeElement, Comparator, Getter>::updateHeight() {
	this->setHeight(1 + maxHeight(this->getRight(), this->getLeft()));
}

template<class TreeElement, class Comparator, class Getter>
int RankAVLTreeNode<TreeElement, Comparator, Getter>::getSize() {
	if (this == NULL) {
		return 0;
	}
	return ((this->getLeft())->getSize()) + 1 + ((this->getRight())->getSize());
}

template<class TreeElement, class Comparator, class Getter>
int RankAVLTreeNode<TreeElement, Comparator, Getter>::getRank() const{
	if (this != NULL) {
		return this->rank;
	}
	return 0;
}

template<class TreeElement, class Comparator, class Getter>
 void RankAVLTreeNode<TreeElement, Comparator, Getter>::setRank(int new_rank){
	if (this != NULL) {
		this->rank = new_rank;
	}
	return;
}

template<class TreeElement, class Comparator, class Getter>
int RankAVLTreeNode<TreeElement, Comparator, Getter>::getSum() const{
	if (this != NULL) {
		return this->sum;
	}
	return 0;
}

template<class TreeElement, class Comparator, class Getter>
 void RankAVLTreeNode<TreeElement, Comparator, Getter>::setSum(int new_sum){
	if (this != NULL) {
		this->sum = new_sum;
	}
	return;
}

template<class TreeElement, class Comparator, class Getter> //ToDo:: check func
int RankAVLTreeNode<TreeElement, Comparator, Getter>::select(int n){
	if(this->getRight()->getRank() == n - 1) return this->getLeft()->getSum() + Getter()(this->getInfo());
	if(n <= this->getRight()->getRank()) return  this->getLeft()->getSum() + Getter()(*(this->info)) + this->getRight()->select(n);
	else return this->getLeft()->select(n - this->getRight()->getRank() - 1);
}

/*
template<class TreeElement, class Comparator, class Getter>
TreeElement RankAVLTreeNode<TreeElement, Comparator, Getter>::getMin() const{
	if (this != NULL) {
		return *(this->min); //TODO: check empty tree
	}
	return TreeElement();
}


template<class TreeElement, class Comparator, class Getter>
void RankAVLTreeNode<TreeElement, Comparator, Getter>::setMin(
		const TreeElement& min) {
	if (this != NULL) {
		if (this->min != NULL) {
			delete this->min;
		}
		this->min = new TreeElement(min);
	}
}
*/

template<class TreeElement, class Comparator, class Getter>
RankAVLTreeNode<TreeElement, Comparator, Getter>::~RankAVLTreeNode() {
	if (this != NULL) {
		delete this->info;
//		delete this->min;
	}
}

#endif /* RANKAVLTREENODE_H_ */

