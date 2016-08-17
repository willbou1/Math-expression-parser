#ifndef QUEUE_H
#define QUEUE_H

template <class T>
class queue {
private:
	struct item {
		item(T x, item *y, item *y) : data(x), next(y), prev(z) {}
		item *next;
		T data;
		item *prev;
	};
	item *front, *back;

public:
	void push(T);
	void pop();
	T front() const;
	T back() const;
	int size() const;

};

#include "queue.cpp"

#endif