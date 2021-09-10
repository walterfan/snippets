#ifndef __WF_DS_H__
#define __WF_DS_H__

#include <iostream>
using namespace std;

template <typename T>
class SingleLinkedList
{
public:
	struct Node {
		Node(T d, Node* pn=NULL):data(d), next(pn) {}
		T data;
		Node* next;
	};

	SingleLinkedList():m_nSize(0),m_pHead(NULL) {}


	void pushBack(Node* pNode) {
		m_nSize++;
		if(!m_pHead) {
			m_pHead = pNode;
			return;
		}
		Node* pLast, *pTail;
		pLast = pTail = m_pHead;

		while(pTail != NULL && pLast->next != NULL) {
			pLast = pLast->next;
			pTail = pLast->next;
			if(pTail == pLast) break;
		}
		pLast->next = pNode;
	}
	bool hasCycle() {
		Node* pFast, *pSlow;
		pFast = pSlow = m_pHead;

		while(pFast != NULL && pFast->next != NULL) {
			//two steps
			pFast = pFast->next->next;
			//one step
			pSlow = pSlow->next;
			if(pFast == pSlow) return true;
		}
		return false;
	}

	
	friend std::ostream& operator<<(std::ostream& os, const SingleLinkedList& aList) {
		    os << "SingleLinkedList: " << aList.m_nSize << ": " <<endl;
			Node* pNode = aList.m_pHead;
			while(pNode != NULL) {
				os << pNode->data << endl;
				pNode = pNode->next;
				if(pNode == aList.m_pHead) break;
			}
			
			return os;
	}
private:
	int m_nSize;
	Node* m_pHead;
};


template <typename T>
class DoubleLinkedList
{
public:
	struct Node {
		Node(const T& d, Node* p = NULL, Node* n = NULL )
		: data(d), prev(p), next(n) { }
		T data;
		Node* prev;
		Node* next;
	};

	bool hasCycle();
private:
	int m_nSize;
	Node* m_pHead;
	Node* m_pTail;

};

#endif