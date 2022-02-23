#include <stdlib.h>
#include "AVL.h"
#include <stdbool.h>

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int height(Node *node)
{
    if(node == NULL)
        return 0;
    else
        return node->height;
}

Node *createNode(int val)
{
    Node *node = (Node*)malloc(sizeof(Node));
    node->height = 1;
    node->left = NULL;
    node->right = NULL;
    node->val = val;
    return node;
}

/**
     a               b
    / \             / \
   b        <--        a
  / \                 / \
     c               c
    / \             / \
*/
Node *leftRotate(Node *top)
{
    Node *mid = top->right;
    Node *bot = mid->left;

    mid->left = top;
    top->right = bot;

    top->height = max(height(top->left), height(top->right))+1;
    mid->height = max(height(mid->left), height(mid->right))+1;

    return mid;
}

/**
     a               b
    / \             / \
   b        -->        a
  / \                 / \
     c               c
    / \             / \
*/
Node *rightRotate(Node *top)
{
    Node *mid = top->left;
    Node *bot = mid->right;

    mid->right = top;
    top->left = bot;

    top->height = max(height(top->left), height(top->right))+1;
    mid->height = max(height(mid->left), height(mid->right))+1;


    return mid;
}

void ins(Node **node, int val)
{
    *node = insert(*node, val);
}

Node *insert(Node *node, int val)
{
    if (node == NULL)
    {
        return createNode(val);
    }
    else if (val > node->val)
    {
        node->right = insert(node->right, val);
    }
    else if (val < node->val)
    {
        node->left = insert(node->left, val);
    }
    else
    {
        return node;
    }

    node->height = max(height(node->left), height(node->right)) + 1;
    int balance = height(node->left) - height(node->right);

    if (balance < -1)   //DAUGIAU DESINEJ
    {
        //DESINE DESINE
        if(val > node->right->val)
        {
            return leftRotate(node);
        }
        //DESINE KAIRE
        else
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    }
    else if (balance > 1) //DAUGIAU KAIREJ
    {
        //KAIRE KAIRE
        if(val < node->left->val)
        {
            return rightRotate(node);
        }
        //KAIRE DESINE
        else
        {
            node->left = leftRotate(node->left);
            return rightRotate(node->right);
        }
    }
    return node;
}

Node *delete(Node *node, int val)
{
    if (node == NULL)
    {
        return node;
    }
    else if (val < node->val)
    {
        node->left = delete(node->left, val);
    }
    else if (val > node->val)
    {
        node->right = delete(node->right, val);
    }
    else
    {
        if (node->left == NULL && node->right == NULL)
        {
            free(node);
            node = NULL;
            return node;
        }
        else if (node->left == NULL)
        {
            *node = *(node->right);
            free(node->right);
            node->right = NULL;
        }
        else if(node->right == NULL)
        {
            *node = *(node->left);
            free(node->left);
            node->left = NULL;
        }
        else
        {
            node->val = middleVal(node->right);
            node->right = delete(node->right, node->val);
        }
    }

    node->height = max(height(node->left), height(node->right)) + 1;
    int balance = height(node->left) - height(node->right);

    if (balance < -1)   //DAUGIAU DESINEJ
    {
        //DESINE DESINE
        if (height(node->right->left) -
            height(node->right->right) <= 0)
        {
            return leftRotate(node);
        }
        //DESINE KAIRE
        else
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    }
    else if (balance > 1) //DAUGIAU KAIREJ
    {
        //KAIRE KAIRE
        if (height(node->left->left) -
            height(node->left->right) >= 0)
        {
            return rightRotate(node);
        }
        //KAIRE DESINE
        else
        {
            node->left = leftRotate(node->left);
            return rightRotate(node->right);
        }
    }
    return node;
}

int middleVal(Node *node)
{
    while(node->left != NULL)
        node = node->left;
    return node->val;
}

void del(Node **node, int val)
{
    *node = delete(*node, val);
}

bool exists(Node *node, int val)
{
    if (node == NULL)
        return 0;
    else if (val < node->val)
        return exists(node->left, val);
    else if (val > node->val)
        return exists(node->right, val);
    else
        return 1;
}

void clr(Node **node)
{
    clear(*node);
    *node = NULL;
}

void clear(Node *node)
{
    if(node->left != NULL)
        clear(node->left);
    if(node->right != NULL)
        clear(node->right);
    free(node);
}

