#ifndef STACK_H
#define STACK_H

#define NULL 0

template <class T>
class stack {
private:
	struct item {
		item(T data, item *next = NULL) : data(data), next(next) {}
		T data;
		item *next;
	};
	item *root;

public:
	stack();
	void push(T);
	T pop();
	T top() const;
	int size() const;
};

#include "stack.cpp"

#endif