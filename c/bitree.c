#include <stdio.h>
#include <string.h>

typedef struct BiTreeNode_
{
    void *data;
    struct BiTreeNode_ *left;
    struct BiTreeNode_ *right;

} BiTreeNode;

typedef struct BiTree_
{
    int size;
    int (*compare)(const void* key1, const void* key2);
    void (*destroy)(void* data);
    BiTreeNode *root;
} BiTree;

int main(int argc, char* argv[])
{
	printf("--- BiTree demo ---\n");
	
	return 0;
}