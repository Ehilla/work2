#include <iostream>
#include "StackImplementation.h"
#include <list>

class StackVec : public IStackImplementation {
	std::vector<ValueType> data;
public:
	StackVec() {};

	StackVec(const StackVec& other) {
		data = other.data;
	}

	StackVec(const ValueType* valueArray, const size_t arraySize)
		: data(valueArray, valueArray + arraySize) {}

	virtual void push(const ValueType& value) override {
		data.push_back(value);
	}

	virtual void pop() override {
		if (data.size() != 0) {
			data.pop_back();
		} else {
			throw std::runtime_error("No elements");
		}
	}
	
	virtual const ValueType& top() const override {
		if (!data.empty()) {
			return data.back();
		} else {
			throw std::runtime_error("no elements");
		}
	} 	

	virtual bool isEmpty() const override {
		return data.empty();
	}

	virtual size_t size() const override {
		return data.size();
	}

};

class List : public IStackImplementation {
	std::list<ValueType> list;
public:
	List() {};

	List(const List& other) : list(other.list) {}

	List(const ValueType* valueArray, const size_t arraySize) {
		for (size_t i = 0; i < arraySize; i++) {
			list.push_back(valueArray[i]);
		}
	}

	virtual void push(const ValueType& value) override {
		list.push_back(value);
	}

	virtual void pop() override {
		if (list.size() != 0) {
			list.pop_back();
		} else {
			throw std::runtime_error("No elements");
		}
	}
	
	virtual const ValueType& top() const override {
		return list.back();		
	}

	virtual bool isEmpty() const override {
		return list.empty();
	}

	virtual size_t size() const override {
		return list.size();
	}
};

Stack::Stack(StackContainer container) {
	if (container == StackContainer::Vector) {
		pimpl = new StackVec();
	} else if (container == StackContainer::List) {
		pimpl = new List();
	} else {
		throw std::runtime_error("Stack::Stack(StackContainer container)");
	}
	containerType = container;
}
	
Stack::Stack(const ValueType* valueArray,
			 const size_t arraySize, 
			 StackContainer container) {
	if (container == StackContainer::Vector) {
		pimpl = new StackVec(valueArray, arraySize);
	} else if (container == StackContainer::List) {
		pimpl = new List(valueArray, arraySize);
	} else {
		throw std::runtime_error("unknown container from Stack::Stack");
	}
	containerType = container;
}

Stack::Stack(const Stack& copyStack) {
	if (copyStack.containerType == StackContainer::Vector) {
		pimpl = new StackVec(*dynamic_cast<StackVec*>(copyStack.pimpl));
	} else if (copyStack.containerType == StackContainer::List) {
		pimpl = new List(*dynamic_cast<List*>(copyStack.pimpl));
	} else {
		throw std::runtime_error(std::string("unknow container from stack copy constructor ") + std::to_string((int)(copyStack.containerType)));
	}
	containerType = copyStack.containerType;	
}

Stack& Stack::operator=(const Stack& copyStack) {
	if (&copyStack != this) {
		delete pimpl;
		if (copyStack.containerType == StackContainer::Vector) {
			pimpl = new StackVec(*dynamic_cast<StackVec*>(copyStack.pimpl));
		} else if (copyStack.containerType == StackContainer::List) {
			pimpl = new List(*dynamic_cast<List*>(copyStack.pimpl));
		} else {	
			throw std::runtime_error("unknown container");
		}
		containerType = copyStack.containerType;	
	}
	return *this;
}

Stack::Stack(Stack&& moveStack) noexcept {
	pimpl = moveStack.pimpl;
	containerType = moveStack.containerType;	
	moveStack.pimpl = nullptr;
} 

Stack& Stack::operator=(Stack&& moveStack) noexcept {
	if (&moveStack != this) {
		delete pimpl;
		pimpl = moveStack.pimpl;
		containerType = moveStack.containerType;		
		moveStack.pimpl = nullptr;
	}
	return *this;
}

void Stack::push(const ValueType& value) {
	pimpl->push(value);
}

void Stack::pop() {
	pimpl->pop();
}

const ValueType& Stack::top() const {
	return pimpl->top();
} 	

bool Stack::isEmpty() const {
	return pimpl->isEmpty();
}

size_t Stack::size() const {
	if (pimpl == nullptr) {
		throw std::runtime_error("pointer is nullptr");
	}
	return pimpl->size();
}

Stack::~Stack() {
	if (pimpl != nullptr) {
		delete pimpl;
	}
}
