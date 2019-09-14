/*
 * AVLTree.h
 *
 *  Created on: 24 бреб 2015
 *      Author: Ilya Kotlov
 */

#ifndef AVLTREENODE_H_
#define AVLTREENODE_H_

#include <stddef.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <math.h>
//class TreeElement is the class of the AVLTree and the class Comparator is the function object,
//to which the AVLTree is sorted by is generice functor to the user
//to use.
template<class TreeElement, class Comparator>
class AVLTreeNode {
private:
	TreeElement* info; //the data inside the current node
	AVLTreeNode* parent; //pointer to the parent node, NULL if root
	AVLTreeNode* left; //pointer to the left son
	AVLTreeNode* right; //pointer to the right son
	int height; //the height of the node

public:
	/**
	 * default constructor for AVLTreeNode
	 */
	AVLTreeNode();
	/**
	 * copy constructor for AVLTreeNode
	 */
	AVLTreeNode(const AVLTreeNode<TreeElement, Comparator>& tr);
	/**
	 * copy constructor for AVLTreeNode
	 */
	AVLTreeNode(const AVLTreeNode<TreeElement, Comparator>* tr);

	/**
	 * returns the data stored in the current AVLTreeNode,
	 *  if current is NULL, NULL is returned
	 */
	TreeElement& getInfo() const;

	/**
	 * returns a pointer to the parent node of the current AVLTreeNode,
	 *  if current is NULL, NULL is returned
	 */
	AVLTreeNode<TreeElement, Comparator>* getParent() const;

	/**
	 * returns a pointer to the left son of the current AVLTreeNode,
	 *  if current is NULL, NULL is returned
	 */
	AVLTreeNode<TreeElement, Comparator>* getLeft() const;

	/**
	 * returns a pointer to the right son of the current AVLTreeNode,
	 *  if current is NULL, NULL is returned
	 */
	AVLTreeNode<TreeElement, Comparator>* getRight() const;

	/**
	 * returns the height of the current AVLTreeNode,
	 * if current is NULL, 0 is returned
	 */
	const int getHeight() const;

	/**
	 * @param height is the new height, to be applied to the
	 *  current AVLTreeNode
	 * sets the current AVLTreeNode's height to the given height
	 */
	void setHeight(int height);
	/**
	 * @param right is the new right son, to displace the current
	 * AVLTreeNode's right son
	 * sets the current AVLTreeNode's right to the given right
	 */
	void setRight(AVLTreeNode<TreeElement, Comparator>* right);
	/**
	 * @param left is the new left son, to displace the current
	 *  AVLTreeNode's left son
	 * sets the current AVLTreeNode's left to the given left
	 */
	void setLeft(AVLTreeNode<TreeElement, Comparator>* left);
	/**
	 * @param parent is the new parent node, to displace the current
	 *  AVLTreeNode's parent
	 * sets the current AVLTreeNode's parent to the given parent
	 */
	void setParent(AVLTreeNode<TreeElement, Comparator>* parent);
	/**
	 * @param info is the new data, to displace the current AVLTreeNode's data
	 * sets the current AVLTreeNode's info to the given info
	 */
	void setInfo(const TreeElement& info);
	/**
	 *@param info is the info of the AVLTreeNode we are
	 *@param  looking for in the sub-AVLTree which his root is this AVLTreeNode
	 * returns pointer to the AVLTreeNode whose info is
	 *  the given info, NULL if doesn't exist
	 */
	AVLTreeNode<TreeElement, Comparator>* find(
			const TreeElement& info);

	/**
	 *@param n is the number of vertices we want to create a new whole tree
	 which can contain all old vertices (its number of vertices is the nearest
	 pow of 2 which is bigger.
	 */
	void createEmptyWholeAVLTreeNode(int n);
	/**
	 * returns whther the AVLTreeNode is a leaf
	 */
	bool isLeaf();
	/**
	 * returns true if the AVLTreeNode has only on son (Left or Right)
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
	void arrayToAVLTreeNode(TreeElement* arr, int& itr);
	
	/**
	 * passes on all the vertices in the tree by inorder and does an
	 *  operation on each data element in it.
	 */
	//void operateInOrder(Operation& op);
	/**
	 * deallocates every memory allocated in the sub-AVLTree which his root
	 *  is this AVLTreeNode
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
	 * returns the balance factor of the current AVLTreeNode (Height of Left son
	 *  - Height of Right son)
	 */
	int calculateBalanceFactor();
	/**
	 * returns max height between two AVLTreeNodes, if both NULL, -1 is returned
	 */
	int maxHeight(AVLTreeNode<TreeElement, Comparator>* trn1,
			AVLTreeNode<TreeElement, Comparator>* trn2);
	/**
	 * updates this AVLTreeNode height, based on his left and right sons height
	 */
	void updateHeight();
	/**
	 * returns the number of Nodes in the sub-AVLTree which his
	 *  root is this AVLTreeNode
	 */
	int getSize();
	/**
	 * AVLTreeNode destructor
	 */
	~AVLTreeNode();
};

/**
 * default constructor for AVLTreeNode
 */
template<class TreeElement, class Comparator>
AVLTreeNode<TreeElement, Comparator>::AVLTreeNode() {
	this->height = 0;
	this->info = new TreeElement();
	this->left = NULL;
	this->right = NULL;
	this->parent = NULL;
}
/**
 * copy constructor for AVLTreeNode
 */
template<class TreeElement, class Comparator>
AVLTreeNode<TreeElement, Comparator>::AVLTreeNode(
		const AVLTreeNode<TreeElement, Comparator>& tr) {
	this->height = tr.getHeight();
	this->parent = new AVLTreeNode<TreeElement, Comparator>(
			tr.getParent());
	this->info = new TreeElement(tr.getInfo());
	this->right = new AVLTreeNode<TreeElement, Comparator>(
			tr.getRight());
	this->left = new AVLTreeNode<TreeElement, Comparator>(
			tr.getLeft());
}

/**
 * copy constructor for AVLTreeNode*
 */
template<class TreeElement, class Comparator>
AVLTreeNode<TreeElement, Comparator>::AVLTreeNode(
		const AVLTreeNode<TreeElement, Comparator>* tr) {
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
			this->right = new AVLTreeNode<TreeElement, Comparator>(
					tr->getRight());
			(this->getRight())->parent = this;
		}
		if (tr->getLeft() == NULL) {
			this->left = NULL;
		} else {
			this->left = new AVLTreeNode<TreeElement, Comparator>(
					tr->getLeft());
			(this->getLeft())->parent = this;
		}

	}
}

/**
 * returns the height of the current AVLTreeNode,
 *  if current is NULL, 0 is returned
 */
template<class TreeElement, class Comparator>
const int AVLTreeNode<TreeElement, Comparator>::getHeight() const {
	if (this != NULL) {
		return this->height;
	}
	return 0;
}
/**
 * returns the data stored in the current AVLTreeNode,
 *  if current is NULL, NULL is returned
 */
template<class TreeElement, class Comparator>
TreeElement& AVLTreeNode<TreeElement, Comparator>::getInfo() const {
	return *(this->info);
}
/**
 * returns a pointer to the right son of the current AVLTreeNode,
 *  if current is NULL, NULL is returned
 */
template<class TreeElement, class Comparator>
AVLTreeNode<TreeElement, Comparator>* AVLTreeNode<TreeElement,
		Comparator>::getRight() const {
	if (this != NULL) {
		return this->right;
	}
	return NULL;
}
/**
 * returns a pointer to the left son of the current AVLTreeNode,
 *  if current is NULL, NULL is returned
 */
template<class TreeElement, class Comparator>
AVLTreeNode<TreeElement, Comparator>* AVLTreeNode<TreeElement,
		Comparator>::getLeft() const {
	if (this != NULL) {
		return this->left;
	}
	return NULL;
}
/**
 * returns a pointer to the parent node of the current AVLTreeNode,
 *  if current is NULL, NULL is returned
 */
template<class TreeElement, class Comparator>
AVLTreeNode<TreeElement, Comparator>* AVLTreeNode<TreeElement,
		Comparator>::getParent() const {
	if (this != NULL) {
		return this->parent;
	}
	return NULL;
}

/**
 * @param height is the new height, to be applied to the current
 *  AVLTreeNode
 * sets the current AVLTreeNode's height to the given height
 */
template<class TreeElement, class Comparator>
void AVLTreeNode<TreeElement, Comparator>::setHeight(int height) {
	if (this != NULL) {
		this->height = height;
	}
}
/**
 * @param right is the new right son, to displace the current
 *  AVLTreeNode's right son
 * sets the current AVLTreeNode's right to the given right
 */
template<class TreeElement, class Comparator>
void AVLTreeNode<TreeElement, Comparator>::setRight(
		AVLTreeNode<TreeElement, Comparator>* right) {
	if (this != NULL) {
		this->right = right;
	}
}
/**
 * @param left is the new left son, to displace the current
 *  AVLTreeNode's left son
 * sets the current AVLTreeNode's left to the given left
 */
template<class TreeElement, class Comparator>
void AVLTreeNode<TreeElement, Comparator>::setLeft(
		AVLTreeNode<TreeElement, Comparator>* left) {
	if (this != NULL) {
		this->left = left;
	}
}
/**
 * @param parent is the new parent node, to displace the current
 * AVLTreeNode's parent
 * sets the current AVLTreeNode's parent to the given parent
 */
template<class TreeElement, class Comparator>
void AVLTreeNode<TreeElement, Comparator>::setParent(
		AVLTreeNode<TreeElement, Comparator>* parent) {
	if (this != NULL) {
		this->parent = parent;
	}
}
/**
 * @param info is the new data, to displace the current AVLTreeNode's data
 * sets the current AVLTreeNode's info to the given info
 */
template<class TreeElement, class Comparator>
void AVLTreeNode<TreeElement, Comparator>::setInfo(
		const TreeElement& info) {
	if (this != NULL) {
		if (this->info != NULL) {
			delete this->info;
		}
		this->info = new TreeElement(info);
	}
}

template<class TreeElement, class Comparator>
AVLTreeNode<TreeElement, Comparator>* AVLTreeNode<TreeElement,
		Comparator>::find(const TreeElement& info) {
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

/**
 * returns whther the AVLTreeNode is a leaf
 */
template<class TreeElement, class Comparator>
bool AVLTreeNode<TreeElement, Comparator>::isLeaf() {
	return this->getLeft() == NULL && this->getRight() == NULL;
}

template<class TreeElement, class Comparator>
bool AVLTreeNode<TreeElement, Comparator>::isOneChild() {
	return (this->getLeft() == NULL && this->getRight() != NULL)
			|| (this->getLeft() != NULL && this->getRight() == NULL);
}

/*template<class TreeElement, class Comparator>
void AVLTreeNode<TreeElement, Comparator>::operateInOrder(
		Operation& op) {
	if (this != NULL) {
		(this->getLeft())->operateInOrder(op);
		op(this);
		(this->getRight())->operateInOrder(op);
	}
}*/

template<class TreeElement, class Comparator>
void AVLTreeNode<TreeElement, Comparator>::createEmptyWholeAVLTreeNode(
		int n) {
	if (n < 2) { //TODO: check correctness
		this->setLeft(NULL);
		this->setRight(NULL);
		this->setHeight(0);
		return;
	}
	AVLTreeNode<TreeElement, Comparator>* left = new AVLTreeNode<
			TreeElement, Comparator>;
	left->setParent(this);
	this->setLeft(left);
	AVLTreeNode<TreeElement, Comparator>* right = new AVLTreeNode<
			TreeElement, Comparator>;
	right->setParent(this);
	this->setRight(right);

	n /= 2;
	left->createEmptyWholeAVLTreeNode(n);
	right->createEmptyWholeAVLTreeNode(n);
	this->setHeight(log(n) + 1);
}

template<class TreeElement, class Comparator>
void AVLTreeNode<TreeElement, Comparator>::returnSortedTreeElements(
		TreeElement* sorted_array, int& itr) {
	if (this != NULL) {
		(this->getLeft())->returnSortedTreeElements(sorted_array, itr);
		sorted_array[itr++] = this->getInfo();
		(this->getRight())->returnSortedTreeElements(sorted_array, itr);
	}
}

template<class TreeElement, class Comparator>
void AVLTreeNode<TreeElement, Comparator>::returnSortedTreeElementsRL(
	TreeElement* sorted_array, int& itr) {
	if (this != NULL) {
		(this->getRight())->returnSortedTreeElements(sorted_array, itr);
		sorted_array[itr++] = this->getInfo();
		(this->getLeft())->returnSortedTreeElements(sorted_array, itr);
	}
}

template<class TreeElement, class Comparator>
void AVLTreeNode<TreeElement, Comparator>::deletePostOrder() {
	if (this != NULL) {
		(this->getLeft())->deletePostOrder();
		(this->getRight())->deletePostOrder();
		delete this;
	}
}

template<class TreeElement, class Comparator>
void AVLTreeNode<TreeElement, Comparator>::deleteInOrderRL(int& n) {
	if (this != NULL) {
		(this->getRight())->deleteInOrderRL(n);
		if (this->isLeaf() && n > 0) {
			AVLTreeNode<TreeElement, Comparator>* tmp =
					this->getParent();
			//Comparator cmp;
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

template<class TreeElement, class Comparator>
void AVLTreeNode<TreeElement, Comparator>::arrayToAVLTreeNode(
		TreeElement* arr, int& itr) {
	if (this != NULL) {
		(this->getLeft())->arrayToAVLTreeNode(arr, itr);
		this->setInfo(arr[itr++]);
		(this->getRight())->arrayToAVLTreeNode(arr, itr);
	}
}

template<class TreeElement, class Comparator>
int AVLTreeNode<TreeElement, Comparator>::calculateBalanceFactor() {
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
 * returns max height between two AVLTreeNodes, if both NULL, -1 is returned
 */
template<class TreeElement, class Comparator>
int AVLTreeNode<TreeElement, Comparator>::maxHeight(
		AVLTreeNode<TreeElement, Comparator>* trn1,
		AVLTreeNode<TreeElement, Comparator>* trn2) {
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

template<class TreeElement, class Comparator>
void AVLTreeNode<TreeElement, Comparator>::updateHeight() {
	this->setHeight(1 + maxHeight(this->getRight(), this->getLeft()));
}

template<class TreeElement, class Comparator>
int AVLTreeNode<TreeElement, Comparator>::getSize() {
	if (this == NULL) {
		return 0;
	}
	return ((this->getLeft())->getSize()) + 1 + ((this->getRight())->getSize());
}

template<class TreeElement, class Comparator>
AVLTreeNode<TreeElement, Comparator>::~AVLTreeNode() {
	if (this != NULL) {
		delete this->info;
	}
}

#endif /* AVLTREENODE_H_ */

