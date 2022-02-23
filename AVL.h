#ifndef AVL_H_INCLUDED
#define AVL_H_INCLUDED

#include <stdbool.h>

typedef struct Node
{
    int val;
    struct Node *left;
    struct Node *right;
    int height;
} Node;

int max(int a, int b);
int height(Node *node);
Node *createNode(int val);
Node *leftRotate(Node *top);
Node *rightRotate(Node *top);
void ins(Node **node, int val);
Node *insert(Node *node, int val);
void del(Node **node, int val);
Node *delete(Node *node, int val);
int middleVal(Node *node);
bool exists(Node *node, int val);
void clr(Node **node);
void clear(Node *node);

#endif // AVL_H_INCLUDED
