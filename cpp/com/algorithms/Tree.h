#pragma once

typedef unsigned int UINT;

typedef struct DoubleNode_st {
	struct DoubleNode_st* pNext;
	struct DoubleNode_st* pPrev;
	void* pData;
} DoubleNode;

typedef struct DoubleList_st {
	DoubleNode* pHead;
	DoubleNode* pTail;
	DoubleNode* pCur;
	UINT uCount;
} DoubleList;

typedef struct Tree_st {
  DoubleList* pLeafList;
  DoubleList* pSubTreeList;
  void* pProperties;
} Tree, *LpTree;


template <typename T>
class BinaryTree
{
public:
	BinaryTree(void);
	~BinaryTree(void);
	void insert(const T& t);
private:

	struct BinaryTreeNode
	{
		BinaryTreeNode(const T& t);
		bool operator < (const T& t);
		void insert_value(const T& t);

		T data;
		int count;
		BinaryTreeNode* lChild;
		BinaryTreeNode* rChild;
	};
	BinaryTreeNode* pRoot;
};

template <typename T>
BinaryTree<T>::BinaryTreeNode::BinaryTreeNode(const T& t)
	:data(t),count(1),lChild(NULL),rChild(NULL)
{

}

template <typename T>
void BinaryTree<T>::insert(const T& t):pRoot(NULL)
{

}

template <typename T>
BinaryTree<T>::BinaryTree()
{

}
template <typename T>
BinaryTree<T>::~BinaryTree()
{

}