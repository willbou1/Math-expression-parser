#include "queue.h"

queue::queue() {
	m_front = m_back = NULL;
}

void queue::push(string data) {
	if (!m_front && !m_back)
		m_front = m_back = new item(data);
	else {
		item *temp = m_back;
		m_back = new item(data, temp);
		temp->prev = m_back;
	}
}

void queue::pop() {
	if (!m_front && !m_back)
		return;
	item *temp = m_front->prev;
	delete m_front;
	if (m_back == m_front)
		m_back = NULL;
	m_front = temp;
	if (temp)
		temp->next = NULL;
}

string queue::front() {
	if (!m_front && !m_back)
		return NULL;
	return m_front->data;
}

string queue::back() {
	if (!m_front && !m_back)
		return NULL;
	return m_back->data;
}

int queue::size() {
	if (!m_front && !m_back)
		return 0;
	item *curr = m_back;
	int s = 1;
	while (curr != m_front) {
		curr = curr->next;
		s++;
	}
	return s;
}

queue::item *queue::getFront() {
	return m_front;
}

queue::item *queue::getBack() {
	return m_back;
}