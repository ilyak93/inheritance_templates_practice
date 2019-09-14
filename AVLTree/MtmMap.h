#ifndef MTMMAP_H_
#define MTMMAP_H_

#include <cassert>
#include <functional>
#include "Exceptions.h"
#include <cstdlib>
#include <assert.h>

namespace mtm {

template<class KeyType, class ValueType, class CompareFunction = std::less<
		KeyType> >
class MtmMap {
public:
	class Pair {
	public:
		Pair(const KeyType& key, const ValueType& value) :
				first(key), second(value) {
		}
		const KeyType first;
		ValueType second;
	};
	struct Node {
		Pair pair;
		Node* next;
	public:
		Node();
		Node(const Node& node) :
				next(NULL), pair(node.pair) {
		}
		Node(const Pair& pair) :
				pair(pair), next(NULL) {
		}
		~Node() {
		}
		;
	};

	class iterator {
	private:
		const MtmMap* mapPtr;
		CompareFunction cmpFunc;
		Node* nodePtr;

	public:
		iterator(const MtmMap* map, CompareFunction cmpFunction, Node* nodePtr) :
				mapPtr(map), cmpFunc(cmpFunction), nodePtr(nodePtr) {
		}

		iterator(const iterator& it) {
		}
		;
		//return the pair which the iterator points
		Pair& operator*() {
			if (nodePtr != NULL) {
				return nodePtr->pair;
			}
			throw MapElementNotFoundException();
		}
		//return the iterator and then moves the iterator to next pair
		iterator& operator++() {
			if (nodePtr != NULL) {
				nodePtr = nodePtr->next;
			}
			return *this;
		}
		//moves the iterator to next pair of the map and the return it.
		iterator operator++(int) { //++iterator
			if (nodePtr == NULL) {
				return *this;
			}
			iterator old_one = *this;
			nodePtr = this->nodePtr->next;
			return old_one;
		}
		//check if the 2 operators are the same
		bool operator==(const iterator& it2) const {
			return (nodePtr == it2.nodePtr && mapPtr == it2.mapPtr);
		}
		//check if the 2 operators are not the same
		bool operator!=(const iterator& it2) const {
			return !(*this == it2);
		}
	};
	MtmMap(const ValueType& default_val) :
			default_val(default_val) {
		head = NULL;
	}
	~MtmMap() { //d'tor
		while (head) {
			Node* tmp = head;
			head = head->next;
			delete tmp;
		}
	}

	MtmMap(const MtmMap& src) :
			default_val(src.default_val), cmpFunc(src.cmpFunc), head(NULL) {

		if (src.head == NULL) {
			return;
		}
		head = new Node(src.head->pair); // copy the pair it self into a new node

		Node* last = head;
		for (iterator it = ++(src.begin()); it != src.end(); ++it) {
			Node* new_one = new Node(*it);
			last->next = new_one;
			//new_one->next = NULL;
			last = last->next;
		}
	}
	//insert a pair to the map, in case the key of the pair is exist it will
	// enter the new pair instead of the old one
	void insert(const Pair pair) {
		Node* new_one = new Node(pair);
		if (containsKey(pair.first)) {
			remove(pair.first);
		}
		Node* start = head;
		if (start == NULL) {
			head = new_one;
			return;
		}
		Node* nextNode = head->next;
		if (cmpFunc(pair.first, start->pair.first)) {
			new_one->next = start;
			head = new_one;
			return;
		}
		if (nextNode == NULL) {
			start->next = new_one;
			return;
		}
		while (cmpFunc(nextNode->pair.first, pair.first)) {
			nextNode = nextNode->next;
			start = start->next;
			if (nextNode == NULL) {
				break;
			}
		}
		new_one->next = nextNode;
		start->next = new_one;
		return;

	}
	void insert(const KeyType& key, const ValueType& val) {
		insert(Pair(key, val));
	}
	//remove a pair with key from the map, if there is no such ke it will
	// throw MapElementNotFoundException();
	void remove(const KeyType& key) {

		Node* p = head;
		Node* prev = NULL;
		while (p) {
			if (cmpFunc(p->pair.first, key) == false
					&& cmpFunc(key, p->pair.first) == false) {
				if (prev != NULL) {
					prev->next = p->next;
					delete p;
				} else {
					head = p->next;
					assert(p != head);
					delete p;
				}
				return;
			}
			prev = p;
			p = p->next;
		}
		throw MapElementNotFoundException();
	}
	//return iterator to the bgin of the map
	iterator begin() const {
		return iterator(this, this->cmpFunc, this->head);
	}
	//return an iterator to the end of map
	iterator end() const {
		return iterator(this, this->cmpFunc, NULL);
	}
	// return true if there is a key in a map
	bool containsKey(KeyType key) const {
		for (iterator it = this->begin(); it != this->end(); it++) {
			if (cmpFunc((*it).first, key) == false
					&& cmpFunc(key, (*it).first) == false) {
				return true;
			}
		}
		return false;
	}
	// return the size of the map
	int size() const {
		int counter = 0;
		for (iterator it = this->begin(); it != this->end(); it++) {
			counter++;
		}
		return counter;
	}
	//copy the second map to the first
	MtmMap& operator=(const MtmMap& map) {
		if (this == &map) {
			return *this;
		}
		Node* tmp = this->head;
		Node* next = this->head;
		while (next != NULL) {
			next = next->next;
			delete tmp;
			tmp = next;
		}
		if (map.head == NULL) {
			return *this;
		}
		head = new Node(map.head->pair); // copy the pair it self into a new node

		Node* last = head;
		for (iterator it = ++(map.begin()); it != map.end(); ++it) {
			Node* new_one = new Node(*it);
			last->next = new_one;
			//new_one->next = NULL;
			last = last->next;
		}
		return *this;
	}
	//return the value according the key, if there is no key it will added a new
	//pair with default value to the map and return this value
	ValueType& operator[](const KeyType& key) {
		for (iterator it = this->begin(); it != this->end(); it++) {
			if (cmpFunc((*it).first, key) == false
					&& cmpFunc(key, (*it).first) == false) {
				return (*it).second;
			}
		}
		this->insert(Pair(key, this->default_val));
		//return this->default_val;
		return (*this)[key];
	}
	//return the value according the key, if there is no key it will return
	//the default value
	const ValueType& operator[](const KeyType& key) const {
		for (iterator it = this->begin(); it != this->end(); it++) {
			if (cmpFunc((*it).first, key) == false
					&& cmpFunc(key, (*it).first) == false) {
				return (*it).second;
			}
		}
		return this->default_val;
	}
//#####################################
	//return an iterator to where a key is hold if there is no key it will
	//return an iterator to the end of a map
	iterator find(KeyType key) const {
		for (iterator it = this->begin(); it != this->end(); it++) {
			if (cmpFunc((*it).first, key) == false
					&& cmpFunc(key, (*it).first) == false) {
				return it;
			}
		}
		return this->end();
	}

//######################################
private:
	const ValueType default_val;
	CompareFunction cmpFunc;
	Node* head;

}
;

}

#endif
