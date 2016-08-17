#ifndef STACK_H
#define STACK_H

#define NULL 0

template <class T>
class stack {
private:
	struct item {
		item(T x, item *y = NULL) : data(x), next(y) {}
		T data;
		item *next;
	};
	item *root;

public:
	stack();
	void push(T);
	void pop();
	T top() const;
	int size() const;
};

#include "stack.cpp"

#endif