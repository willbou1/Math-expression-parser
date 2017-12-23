#ifndef QUEUE_H
#define QUEUE_H

#include <string>

using namespace std;

class queue {
public:
	struct item {
		item(string data, item *next = NULL, item *prev = NULL) : data(data), next(next), prev(prev) {}
		item *next;
		string data;
		item *prev;
	};
	queue();
	void push(string);
	void pop();
	string front() const;
	string back() const;
	item *getFront() const;
	item *getBack() const;
	int size() const;

private:
	item *m_front, *m_back;

};

#endif