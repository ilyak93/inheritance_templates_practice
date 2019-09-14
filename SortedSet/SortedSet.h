#ifndef MTM4_SORTEDSET_H
#define MTM4_SORTEDSET_H

#include <cassert>
#include <functional>
#include "Exceptions.h"
#include <cstdlib>
#include <assert.h>

template<class T, class Compare = std::less<T> >
class SortedSet {
	struct Node {
		T* const data;
		Node* next;
	public:
		Node(T* const data_ptr) : data(data_ptr), next(NULL){}
		//Node(const T data) : data(new T(data)), next(NULL) {}
		Node(const Node& node) :
			data(node.data ? new T(*(node.data)) : NULL), next(NULL) {
		}
		~Node() { if(this->data) delete this->data; }
		;
		friend Node* nodesCopy(Node* src) {
			assert(src != NULL);
			Node* new_head = new Node(*src);
			Node* itr = new_head;
			for (Node* cur_node_src = src->next; cur_node_src != NULL;
					cur_node_src = cur_node_src->next, itr = itr->next) {
				itr->next = new Node(*cur_node_src);
			}
			return new_head;
		}
	};
public:
	class iterator {
	private:
		const SortedSet* sorted_set_ptr;
		Node* node_ptr;

	public:
		iterator(const SortedSet* sorted_set_ptr, Node* node_ptr) :
				sorted_set_ptr(sorted_set_ptr), node_ptr(node_ptr) {
		}
		iterator(const iterator& it) = default;

		iterator& operator=(const iterator&) = default;

		~iterator() = default;

		//return the data which the iterator points
		T& operator*() {
			if (node_ptr != NULL) {
				return *(node_ptr->data);
			}
			throw MapElementNotFoundException();
		}
		//return the iterator and then moves the iterator to next pair
		iterator& operator++() {
			if (node_ptr != NULL) {
				node_ptr = node_ptr->next;
			}
			return *this;
		}
		//moves the iterator to next pair of the map and the return it.
		iterator operator++(int) { //++iterator
			iterator old_one = *this;
			if (node_ptr != NULL) {
				node_ptr = this->node_ptr->next;
			}
			return old_one;
		}
		//check if the 2 operators are the same
		bool operator==(const iterator& it2) const {
			return (node_ptr == it2.node_ptr
					&& sorted_set_ptr == it2.sorted_set_ptr);
		}
		//check if the 2 operators are not the same
		bool operator!=(const iterator& it2) const {
			return !(*this == it2);
		}
	};

	//######################################
private:
	Node* _head;
	int _size;
public:
	SortedSet() :
			_size(0) {
		_head = new Node(NULL);
	}

	SortedSet(const SortedSet& sorted_set) :
			_size(sorted_set._size) { //copy c'tor
		this->_head = nodesCopy(sorted_set._head);
	}

	SortedSet& operator=(const SortedSet& sorted_set) {
		Node* new_head = nodesCopy(sorted_set._head);
		this->~SortedSet();
		this->_head = new_head;
		this->_size = sorted_set._size;
		return *this;
	}

	~SortedSet() { //d'tor
		while (_head) {
			Node* tmp = _head;
			_head = _head->next;
			delete tmp;
		}
	}

	friend SortedSet operator&(const SortedSet& sset1, const SortedSet& sset2) {
		SortedSet set_intersection;
		Node *itr1 = sset1._head->next, *itr2 = sset2._head->next,
				*itr_intersect = set_intersection._head;
		Compare cmpFunc;
		while (itr1 != NULL && itr2 != NULL) {
			if (cmpFunc(*(itr1->data), *(itr2->data)) == false
					&& cmpFunc(*(itr2->data), *(itr1->data)) == false) {
				itr_intersect->next = new Node(new T(*(itr1->data)));
				set_intersection._size++;
				itr1 = itr1->next;
				itr2 = itr2->next;
				itr_intersect = itr_intersect->next;
			} else if (cmpFunc(*(itr1->data), *(itr2->data)) == true) {
				itr1 = itr1->next;
			} else {
				itr2 = itr2->next;
			}
		}
		return set_intersection;
	}

	friend SortedSet operator|(const SortedSet& sset1, const SortedSet& sset2) {
		SortedSet set_union;
		Compare cmpFunc;
		Node *itr1 = sset1._head->next, *itr2 = sset2._head->next, *itr_union =
				set_union._head;
		while (itr1 != NULL && itr2 != NULL) {
			if (cmpFunc(*(itr1->data), *(itr2->data)) == false
					&& cmpFunc(*(itr2->data), *(itr1->data)) == false) {
				itr_union->next = new Node(new T(*(itr1->data)));
				itr_union = itr_union->next;
				itr1 = itr1->next;
				itr2 = itr2->next;
			} else if (cmpFunc(*(itr1->data), *(itr2->data)) == true) {
				itr_union->next = new Node(new T(*(itr1->data)));
				itr_union = itr_union->next;
				itr1 = itr1->next;
			} else {
				itr_union->next = new Node(new T(*(itr2->data)));
				itr_union = itr_union->next;
				itr2 = itr2->next;
			}
		}
		for (; itr1 != NULL; itr1 = itr1->next, itr_union = itr_union->next) {
			itr_union->next = new Node(new T(*(itr1->data)));
		}
		for (; itr2 != NULL; itr2 = itr2->next, itr_union = itr_union->next) {
			itr_union->next = new Node(new T((*(itr2->data))));
		}
		return set_union;
	}

	friend SortedSet operator-(const SortedSet& sset1, const SortedSet& sset2) {
		SortedSet set_complement = sset1, set_intersection = sset1 & sset2;
		Node *itr_intersect = set_intersection._head->next, *previous =
				set_complement._head;
		if (set_intersection.size() != 0) {
			Compare cmpFunc;
			for (Node* itr_complement = set_complement._head->next;
					itr_complement !=
					NULL; itr_complement = itr_complement->next) {
				if (cmpFunc(*(itr_complement->data), *(itr_intersect->data))
						== false && cmpFunc(*(itr_intersect->data),
								*(itr_complement->data)) == false) {
					previous->next = itr_complement->next;
					delete itr_complement;
					if ((itr_intersect = itr_intersect->next) == NULL) {
						break;
					}
					itr_complement = previous;
					continue;
				}
				previous = itr_complement;
			}
		}
		return set_complement;
	}

	friend SortedSet operator^(const SortedSet& sset1, const SortedSet& sset2) {
		return SortedSet((sset1 - sset2) | (sset2 - sset1));
	}

	/*insert a data to the sorted set, in case the data is exist it will
	 return false without changes, otherwise insert the new data and return
	 true*/
	bool insert(const T data) {
		Compare cmpFunc;
		Node* previous = _head;
		for (Node* itr = _head->next; itr != NULL && cmpFunc(*(itr->data), data);
				itr = itr->next) {
			previous = itr;
		}
		if (previous->next && cmpFunc(*(previous->next->data), data) == false
				&& cmpFunc(data, *(previous->next->data)) == false) {
			return false; // if previous equal to data return false
		} else {
			Node* tmp = previous->next;
			previous->next = new Node(new T(data));
			previous->next->next = tmp;
		}
		_size++;
		return true;
	}

	/*remove an element with given data from the sorted set and return true,
	 if there is no such return false */
	bool remove(const T& data) {
		Node* prev = _head;
		Compare cmpFunc;
		for (Node* itr = _head->next; itr != NULL; itr = itr->next) {
			if (cmpFunc(*(itr->data), data) == false
					&& cmpFunc(data, *(itr->data)) == false) {
				prev->next = itr->next;
				delete itr;
				_size--;
				return true;
			}
			prev = itr;
		}
		return false;
	}
	//return iterator to the bgin of the map
	iterator begin() const {
		return iterator(this, this->_head->next);
	}
	//return an iterator to the end of map
	iterator end() const {
		return iterator(this, NULL);
	}
	// return the size of the map
	int size() const {
		return _size;
	}

	//#####################################
	//return an iterator to where a data is hold if there is no key it will
	//return an iterator to the end of a map
	iterator find(const T& data) const {
		Compare cmpFunc;
		for (iterator it = this->begin(); it != this->end(); ++it) {
			if (cmpFunc(*it, data) == false && cmpFunc(data, *it) == false) {
				return it;
			}
		}
		return this->end();
	}

};

#endif
