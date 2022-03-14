#include <stdlib.h>
#include "AVL.h"
#include <stdbool.h>

typedef struct Node
{
    int val;
    struct Node *left;
    struct Node *right;
    int height;
} Node;

static int max(int a, int b);
static int height(Node *node);
static int middleVal(Node *node);

static Node *createNode(int val);
static Node *leftRotate(Node *top);
static Node *rightRotate(Node *top);

static Node *insert(Node *node, int val, AVL *tree);
static Node *delete(Node *node, int val, AVL *tree);
static void clear(Node *node);
static bool contains(Node *node, int val);
static void print(Node *node);

///Utility

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

int middleVal(Node *node)
{
    while(node->left != NULL)
        node = node->left;
    return node->val;
}

///Node management

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

///Function logic

Node *insert(Node *node, int val, AVL *tree)
{
    if (node == NULL)
    {
        return createNode(val);
    }
    else if (val > node->val)
    {
        node->right = insert(node->right, val, tree);
    }
    else if (val < node->val)
    {
        node->left = insert(node->left, val, tree);
    }
    else
    {
        tree->count--;
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
            return rightRotate(node);
        }
    }
    return node;
}

Node *delete(Node *node, int val, AVL *tree)
{
    if (node == NULL)
    {
        tree->count++;
        return node;
    }
    else if (val < node->val)
    {
        node->left = delete(node->left, val, tree);
    }
    else if (val > node->val)
    {
        node->right = delete(node->right, val, tree);
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
            node->right = delete(node->right, node->val, tree);
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

void clear(Node *node)
{
    if(node->left != NULL)
        clear(node->left);
    if(node->right != NULL)
        clear(node->right);
    free(node);
}

bool contains(Node *node, int val)
{
    if (node == NULL)
        return 0;
    else if (val < node->val)
        return contains(node->left, val);
    else if (val > node->val)
        return contains(node->right, val);
    else
        return 1;
}

void print(Node *node)
{
    if(node == NULL)
        return 0;
    print(node->left);
    printf("%d ", node->val);
    print(node->right);
}

///User functions

AVL create()
{
    AVL tree;
    tree.count = 0;
    tree.head = NULL;
    return tree;
}

void ins(AVL *tree, int val)
{
    tree->count++;
    tree->head = insert(tree->head, val, tree);
}

void del(AVL *tree, int val)
{
    tree->count--;
    tree->head = delete(tree->head, val, tree);
}

void clr(AVL *tree)
{
    clear(tree->head);
    tree->head = NULL;
    tree->count = NULL;
}

bool exists(AVL tree, int val)
{
    return contains(tree.head, val);
}

bool isEmpty(AVL tree)
{
    if(tree.count == 0)
        return 1;
    return 0;
}

int cnt(AVL tree)
{
    return tree.count;
}

void printAll(AVL tree)
{
    print(tree.head);
}

void printByLevel(AVL tree)
{
    Node *stack[tree.count / 2 + 1][2];
    int pos = 0;
    bool curr = 0;
    if(tree.head != NULL)
        stack[pos++][curr] = tree.head;
    int level = 1;
    while(pos != 0)
    {
        printf("%d: ", level++);
        for(int i = 0; i < pos; i++)
            printf("%d ", stack[i][curr]->val);
        printf("\n");

        curr = !curr;
        int n = pos;
        pos = 0;

        for(int i = 0; i < n; i++)
        {
            if(stack[i][!curr]->left != NULL)
                stack[pos++][curr] = stack[i][!curr]->left;
            if(stack[i][!curr]->right != NULL)
                stack[pos++][curr] = stack[i][!curr]->right;
        }
    }
}
