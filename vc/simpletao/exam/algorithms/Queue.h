#ifndef __QUEUE_H__
#define __QUEUE_H__

template <typename T>
class Queue
{
private:
	struct Item{
		Item(const T&);
		T item;
		Item* next;
	};
	Item* m_pHead;
	Item* m_pTail;

};

#endif