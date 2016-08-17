#include "stack.h"

template <class T>
stack<T>::stack() {
	root = NULL;
}

template <class T>
void stack<T>::push(T data) {
	if (root) {
		item *temp = root;
		root = new item(data, temp);
	}
	else
		root = new item(data);
}

template <class T>
void stack<T>::pop() {
	if (root == NULL)
		return;
	item *temp = root->next;
	delete root;
	root = temp;
}

template <class T>
T stack<T>::top() const {
	if (root == NULL)
		return NULL;
	return root->data;
}

template <class T>
int stack<T>::size() const {
	if (root == NULL)
		return 0;
	item *curr = root;
	int s = 0;
	while (curr) {
		curr = curr->next;
		s++;
	}
	return s;
}