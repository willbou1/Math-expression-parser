#include "queue.h"

queue::queue() {
	m_front = m_back = NULL;
}

void queue::push(string data) {
	if (!m_front)
		m_front = m_back = new item(data);
	else {
		item *temp = m_back;
		m_back = new item(data, temp);
		temp->prev = m_back;
	}
}

void queue::pop() {
	if (!m_front)
		return;
	item *temp = m_front->prev;
	delete m_front;
	if (m_back == m_front)
		m_back = NULL;
	m_front = temp;
	if (temp)
		temp->next = NULL;
}

string queue::front() const {
	if (!m_front)
		return NULL;
	return m_front->data;
}

string queue::back() const {
	if (!m_front)
		return NULL;
	return m_back->data;
}

int queue::size() const {
	if (!m_front)
		return 0;
	item *curr = m_back;
	int s = 1;
	while (curr != m_front) {
		curr = curr->next;
		s++;
	}
	return s;
}

queue::item *queue::getFront() const {
	return m_front;
}

queue::item *queue::getBack() const {
	return m_back;
}