#ifndef QUEUE_H
#define QUEUE_H

#include <memory>
#include <iostream>
#include <iterator>
#include <exception>

namespace containers {

	template <class T>
	class TQueue {
	private:
		struct Node;
		std::shared_ptr<Node> head = nullptr;
		std::shared_ptr<Node> tail = nullptr;
	public:
		class forward_iterator {
		public:
			using value_tipe = T;
			using reference = T&;
			using pointer = T*;
			using difference_type = std::ptrdiff_t;
			using iterator_category = std::forward_iterator_tag;
			forward_iterator(Node* ptr) : ptr_(ptr) {}
			T& operator* ();
			forward_iterator& operator++ ();
			forward_iterator operator++ (int);
			bool operator == (const forward_iterator& f) const;
			bool operator != (const forward_iterator& f) const;
		private:
			Node* ptr_ = nullptr;
			friend TQueue;
 		};
 		forward_iterator begin();
 		forward_iterator end();
 		void pop();
 		T& top();
 		void push(const T& value);
 		bool empty();
 		//void erase(const forward_iterator& it);
 		//void insert(const forward_iterator& it, const T& value);
 		//void advance(forward_iterator& it, int idx);

 		void print();
 	private:
 		struct Node {
 			T value;
 			std::shared_ptr<Node> following = nullptr;
 			forward_iterator next();
 			Node(const T& val, std::shared_ptr<Node> nxt) : 
 				value(val), following(nxt) {}
 		};
	};
	template <class T>
	typename TQueue<T>::forward_iterator TQueue<T>::Node::next() {
		return following.get();
	}

	template <class T>
	typename TQueue<T>::forward_iterator TQueue<T>::begin() {
		return head.get();
	}

	template <class T>
	typename TQueue<T>::forward_iterator TQueue<T>::end() {
		return nullptr;
	}

	template <class T>
	T& TQueue<T>::forward_iterator::operator* () {
		return ptr_->value;
	}

	template <class T>
	typename TQueue<T>::forward_iterator& TQueue<T>::forward_iterator::operator++ () {
		*this = ptr_->next();
		return *this;
	}

	template <class T>
	typename TQueue<T>::forward_iterator TQueue<T>::forward_iterator::operator++ (int) {
		forward_iterator prev = *this;
		++this;
		return prev;
		
	}

	template <class T>
	bool TQueue<T>::forward_iterator::operator== (const forward_iterator& f) const {
		return ptr_ == f.ptr_;
	}

	template <class T>
	bool TQueue<T>::forward_iterator::operator!= (const forward_iterator& f) const {
		return ptr_ != f.ptr_;
	}

	template <class T>
	void TQueue<T>::push(const T& value) {
		std::shared_ptr<Node> NewNode(new Node(value, nullptr));
		if (this->empty()) {
			tail = NewNode;
			head = NewNode;
		} else {
			tail->following = NewNode;
			tail = NewNode;
		}
	}
	template <class T>
	void TQueue<T>::pop() {
		if (head.get() == nullptr) {
			throw std::logic_error("Queue is empty\n");
		} else {
			head = head->following;
		}
	}

	template <class T>
	T& TQueue<T>::top() {
		if (head.get() == nullptr) {
			throw std::logic_error("Queue is empty\n");
		} else {
			return head->value;
		}
	}

	template <class T>
	bool TQueue<T>::empty() {
		if (head.get() == nullptr && tail.get() == nullptr) {
			return true;
		}
		return false;
	}

	template <class T>
	void TQueue<T>::print() {
		std::shared_ptr<Node> tmp = head;
		while (tmp != nullptr) {
			std::cout << tmp->value << " ";
			tmp = tmp->following;
		}
	}
/*
	template <class T>
	void TQueue<T>::insert(const forward_iterator& it, const T& value) {
		std::shared_ptr<Node> NewNode(new Node(value, nullptr));
		auto tmp = this->begin();
		auto prev = tmp;
		if (this->empty()) {
			this->push(value);
			return;
		}
		if (it.ptr_ == head.get()) {
			NewNode->following = head;
			head = NewNode;
			return;
		}
		
		while (tmp!= it) {
			if (tmp == nullptr && tmp != it)
				throw std::logic_error("Out of range\n");
			prev.ptr_ = tmp.ptr_;
			++tmp;
		}
		NewNode->following = prev.ptr_->following;
		prev.ptr_->following = NewNode;
		return;
	}

	template <class T>
	void TQueue<T>::erase(const forward_iterator& it) {
		auto tmp = this->begin();
		auto prev = tmp;
		if (this->empty()) {
			throw std::logic_error("Que is empty\n");
			return;
		}
		if (it.ptr_ == head.get()) {
			this->pop();
			return;
		
		} else if (head.get() == tail.get()) {
			head = nullptr;
			tail = nullptr;
		}
		
		while (tmp != it) {
			prev.ptr_ = tmp.ptr_;
			++tmp;
			if (tmp.ptr_ == nullptr)
				throw std::logic_error("Out of range\n");
		}
		prev.ptr_->following  =tmp.ptr_->following;
		return;
	}

	template <class T>
	void TQueue<T>::advance(forward_iterator& it, int idx) {
		it = this->begin();
		int i = 0;
		if (it == nullptr && idx > 0)
			throw std::logic_error("Index is out of range\n");
		while (i < idx) {
			if (it.ptr_->following == nullptr && i < idx - 1)
				throw std::logic_error("Out of range\n");
			++it;
			++i;
		}

	}
	*/

}

#endif