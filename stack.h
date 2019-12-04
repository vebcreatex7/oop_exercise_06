
#ifndef STACK_H
#define STACK_H 1

#include <memory>
#include <iostream>
#include <iterator>



namespace containers {


template <class T, class Allocator = std::allocator<T>>
class TStack {
private:

	struct Node;

public:
	TStack() = default;

	class forward_iterator {
	public:
		using value_type = T;
        using reference = T&;
        using pointer = T*;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;
		forward_iterator (Node* ptr) : ptr_(ptr) {};
		T& operator* ();
		forward_iterator& operator++ ();
		forward_iterator operator++ (int);
		bool operator== (const forward_iterator& o) const;
		bool operator!= (const forward_iterator& o) const;
		
	private:
		Node* ptr_;
		friend TStack;
	};
	forward_iterator begin();
	forward_iterator end();
	void pop();
	T& top();
	void push(const T& value);
	void erase(const forward_iterator& it);
	void insert(forward_iterator& it, const T& val);
	void advance(forward_iterator& it, int idx);
	bool empty() {
		return head == nullptr;
	}
	void print();


private:
	using allocator_type = typename Allocator::template rebind<Node>::other;
	struct deleter {
		deleter(allocator_type* allocator) : allocator_(allocator) {}
		void operator() (Node* ptr) {
			if (ptr != nullptr) {
                std::allocator_traits<allocator_type>::destroy(*allocator_, ptr);
                allocator_->deallocate(ptr, 1);
			}
		}

	private:
		allocator_type* allocator_;

	};

	using unique_ptr = std::unique_ptr<Node, deleter>;

	struct Node {
		T value;
		unique_ptr following{nullptr, deleter{nullptr}};
		Node(const T& val) : value(val) {}
		forward_iterator next();
		
	};

	allocator_type allocator_{};
	unique_ptr head {nullptr, deleter{nullptr}};


};

template <class T, class Allocator>
typename TStack<T, Allocator>::forward_iterator TStack<T, Allocator>::Node::next() {
	return following.get();
}

template <class T, class Allocator>
typename TStack<T, Allocator>::forward_iterator TStack<T, Allocator>::begin() {
	return head.get();
}

template <class T, class Allocator>
typename TStack<T, Allocator>::forward_iterator TStack<T, Allocator>::end() {
	return nullptr;
}

template <class T, class Allocator>
T& TStack<T, Allocator>::forward_iterator::operator* () {
	return ptr_->value;
}

template <class T, class Allocator>
typename TStack<T, Allocator>::forward_iterator& TStack<T, Allocator>::forward_iterator::operator++ () {
	*this = ptr_->next();
	return *this;
}

template <class T, class Allocator>
typename TStack<T, Allocator>::forward_iterator TStack<T, Allocator>::forward_iterator::operator++ (int) {
	forward_iterator prev =*this;
	++this;
	return prev;
}

template <class T, class Allocator>
bool TStack<T, Allocator>::forward_iterator::operator== (const forward_iterator& o) const{
	return ptr_ == o.ptr_;
}

template <class T, class Allocator>
bool TStack<T, Allocator>::forward_iterator::operator!= (const forward_iterator& o) const{
	return ptr_ != o.ptr_;
}



template <class T, class Allocator>
void TStack<T, Allocator>::push(const T& value) {
	Node* NewNode = this->allocator_.allocate(1);
	std::allocator_traits<allocator_type>::construct(this->allocator_, NewNode, value);
	auto tmp = unique_ptr(NewNode, deleter{&this->allocator_});
	tmp->following = std::move(head);
	head = std::move(tmp);
		
}

template <class T, class Allocator>
void TStack<T, Allocator>::pop() {
	if (head.get() == nullptr) {
		throw std::logic_error("Stack is empty\n");
	} else {
		head = std::move(head->following);
	}
}

template <class T, class Allocator>
T& TStack<T, Allocator>::top() {
	if (head.get() == nullptr) throw std::logic_error("Stack is empty\n");
	return head->value;
}


template <class T, class Allocator>
void TStack<T, Allocator>::print() {
	Node* tmp = head.get();
	
	while (tmp != nullptr) {
		std::cout << tmp->value << " ";
		tmp = tmp->following.get();
	}
}


template <class T, class Allocator>
void TStack<T, Allocator>::insert(forward_iterator& it, const T& value) {
	
	if (it.ptr_ == head.get()) {
		this->push(value);
		return;
	}

	Node* NewNode = this->allocator_.allocate(1);
	std::allocator_traits<allocator_type>::construct(this->allocator_, NewNode, value);
	auto tmp = unique_ptr(NewNode, deleter{&this->allocator_});
	//auto tmp = std::unique_ptr<Node>(new Node{value});
	forward_iterator i = this->begin();
	while (i.ptr_->following.get() != it.ptr_) {
		if (i.ptr_ == nullptr && i.ptr_ != it.ptr_) throw std::logic_error("Out of range\n");
		++i;

	}
	if (i.ptr_->following == nullptr) {
		i.ptr_->following = std::move(tmp);
		return;
	}
	++i;
	tmp->following = std::move(i.ptr_->following);
	i.ptr_->following = std::move(tmp);
	return;

}

template <class T, class Allocator>
void TStack<T, Allocator>::erase(const forward_iterator& it) {
	if (it.ptr_ == head.get()) {
		this->pop();
		return;
	}
	auto i = this->begin();
	while(i.ptr_ != nullptr && i.ptr_->next() != it.ptr_) {
		++i;
	}
	if (i.ptr_ == nullptr) {
		throw std::logic_error ("Out of range\n");
	}
	i.ptr_->following = std::move(it.ptr_->following);

	return;

}



template <class T, class Allocator>
void TStack<T, Allocator>::advance(forward_iterator& it, int idx) {
	it = this->begin();
	if (it.ptr_ == nullptr && idx > 0) throw std::logic_error("Out of range(advance)\n");
	int i = 0;
	while (i < idx) {
		if (it.ptr_->following == nullptr && i < idx - 1) {
			
			throw std::logic_error("Out of range(advance)\n");
		}
		++it;
		++i;
		
	}
}

}

#endif


	




