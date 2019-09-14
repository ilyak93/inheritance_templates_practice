#ifndef MTMMAP_H_
#define MTMMAP_H_

#include <cassert>
#include <functional>
#include "Exceptions.h"

namespace mtm {

	template <typename DataType>
	class Node {
	private:
		DataType data;
		Node<DataType> *next;
	public:
		Node<DataType>(const DataType& data) : data(data) {
			next = nullptr;
		}
		Node<DataType>& operator=(const Node<DataType>& node) = default;
		void SetData(const DataType& aData) { data = aData; };
		void SetNext(Node<DataType>* aNext) {
			next = aNext;
		}
		DataType& Data() { return data; }
		Node<DataType>* Next() { return next; }

		Node<DataType>* nodesCopy() {
			Node<DataType> *new_head = nullptr;
			if (this) {
				new_head = new Node<DataType>(this->Data());
				Node<DataType> *itr = new_head;
				for (Node<DataType> *ptr = this; ptr != nullptr;
				ptr = ptr->Next()) {
					Node<DataType> *next = ptr->Next();
					if (next) {
						DataType new_pair = ptr->Next()->Data();
						Node<DataType>* new_node = new Node<DataType>(new_pair);
						itr->SetNext(new_node);
						itr = itr->Next();
					}
					else {
						itr->SetNext(next);
					}
				}
			}
			return new_head;
		}

		void nodesDestroy() {
			Node<DataType>* _this = this;
			while (_this) {
				Node<DataType> *tmp = _this;
				_this = _this->Next();
				delete tmp;
			}
		}
	};


	template <class KeyType, class ValueType,
	class CompareFunction = std::less<KeyType> >
	class MtmMap {

	public:
		class Pair {
		public:
			Pair(const KeyType& key, const ValueType& value)
				: first(key), second(value) {}

			const KeyType first;
			ValueType second;
		};

		class iterator {
		private:
			Node<Pair>* _ptr;
			const MtmMap<ValueType, KeyType, CompareFunction>* _map_ptr;

		public:

			iterator(Node<Pair>* ptr, const MtmMap<ValueType, KeyType,
					CompareFunction>* mtm_ptr) : _ptr(ptr), _map_ptr(mtm_ptr){}

			iterator(const iterator& itr) = default;

			~iterator() = default;

			iterator& operator=(const iterator&) = default;

			iterator operator++(int) {
				Node<Pair> *cur = this->_ptr;
				if (this->_ptr) {
					this->_ptr = _ptr->Next();
				}
				return iterator(cur, this->_map_ptr);
			}

			iterator& operator++() {
				if (this->_ptr) {
					this->_ptr = _ptr->Next();
				}
				return *this;
			}

			Pair& operator*(){
				if (!this->_ptr) {
					throw MapElementNotFoundException();
				}
				return this->_ptr->Data();
			}

			bool operator==(const iterator& itr) const {
				if ((this->_map_ptr == itr._map_ptr) &&
						((this->_ptr == nullptr && itr._ptr == nullptr) ||
					(this->_ptr == itr._ptr))) {
					return true;
				}
				return false;
			}
			bool operator!=(const iterator& itr) {
				return !(*this == itr);
			}
		};

		//class MtmMap
	private:
		Node<Pair> *_head;
		ValueType _default;
		int _size;
	public:
		explicit MtmMap(const ValueType& value) :_default(value) {
			this->_head = nullptr;
			this->_size = 0;
		}

		MtmMap(const MtmMap& map) {
			this->_head = map._head->nodesCopy();
			this->_size = map._size;
			this->_default = map._default;
		}
		~MtmMap() {
			this->_head->nodesDestroy();
			this->_head = nullptr;
		}

		MtmMap& operator=(const MtmMap& map) {
			Node<Pair>* tmp = nullptr;
			if (map._head) {
				tmp = map._head->nodesCopy();
			}
			this->_head->nodesDestroy();
			this->_head = tmp;
			this->_size = map.size();
			this->_default = map._default;
			return *this;
		}

		iterator begin() const {
			return iterator(this->_head, this);
		}

		iterator end() const {
			return iterator(nullptr, this);
		}

		void insert(const Pair& pair) {
			if (this->containsKey(pair.first)) {
				(*this)[pair.first] = pair.second;
				return;
			}
			CompareFunction cmp;
			Node<Pair> *newNode = new Node<Pair>(pair);
			Node<Pair> *tmp = this->_head;
			if (tmp != nullptr) {
				while (tmp->Next() && cmp(tmp->Next()->Data().first,pair.first)){
					tmp = tmp->Next();
				}
				if (tmp == _head && !cmp(tmp->Data().first, pair.first)) {
					newNode->SetNext(_head);
					_head = newNode;
				}
				else {
					newNode->SetNext(tmp->Next());
					tmp->SetNext(newNode);
				}
			}
			else {
				this->_head = newNode;
			}
			this->_size++;
		}

		void insert(const KeyType& key, const ValueType& value) {
			this->insert(Pair(key, value));
		}

		void remove(const KeyType& key) {
			for (iterator it = this->begin(); it != this->end(); ++it) {
				Pair cur_pair = *it;
				if (cur_pair.first == key) {
					Node<Pair> *tmp = this->_head;
					if (tmp == nullptr) {
						return;
					}
					else if (tmp->Data().first == key) {
						this->_head = this->_head->Next();
						delete tmp;
					}
					else {
						Node<Pair> *prev;
						do {
							prev = tmp;
							tmp = tmp->Next();
						} while (tmp->Data().first != cur_pair.first);

						prev->SetNext(tmp->Next());
						delete tmp;
					}
					this->_size--;
					return;
				}
			}
			throw MapElementNotFoundException();
		}

		bool containsKey(const KeyType& key) const {
			Node<Pair> *cur_node = this->_head;
			while (cur_node != nullptr) {
				if (cur_node->Data().first == key) {
					return true;
				}
				cur_node = cur_node->Next();
			}
			return false;
		}

		int size() const {
			return this->_size;
		}

		ValueType& operator[](const KeyType& key) {
			if (this->containsKey(key)) {
				Node<Pair> *cur_node = this->_head;
				while (cur_node != nullptr) {
					if (cur_node->Data().first == key) {
						return cur_node->Data().second;
					}
					cur_node = cur_node->Next();
				}
			}
			this->insert(Pair(key, this->_default));
			return (*this)[key];
		}

		const ValueType& operator[](const KeyType& key) const {
			Node<Pair> *cur_node = this->_head;
			while (cur_node != nullptr) {
				if (cur_node->Data().first == key) {
					return cur_node->Data().second;
				}
				cur_node = cur_node->Next();
			}
			return this->_default;
		}
	};
}
#endif
