#ifndef QUEUE_H
#define QUEUE_H

#include <string>

using namespace std;

class queue {
public:
	struct item {
		item(string x, item *y = NULL, item *z = NULL) : data(x), next(y), prev(z) {}
		item *next;
		string data;
		item *prev;
	};
	queue();
	void push(string);
	void pop();
	string front();
	string back();
	item *getFront();
	item *getBack();
	int size();

private:
	item *m_front, *m_back;

};

#endif