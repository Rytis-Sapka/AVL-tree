#ifndef AVL_H_INCLUDED
#define AVL_H_INCLUDED

/**
 *  FILE NAME: AVL.h
 *
 *  PURPOSE: header for an AVL tree
 *  AUTHOR: Rytis Kasparas Šapka
 *  UNIVERSITY: Vilnius University
 *  DATE: 2002/02/17
**/

#include <stdbool.h>

/**
 *                              USER MANUAL
 *
 *  To create a tree: create an AVL variable and initialize with create()
 *          AVL var_name = create();
 *
 *  To insert or delete an element use ins/del and pass the address of your tree
 *          ins(&var_name, value);
 *          del(&var_name, value);
 *
 *  To See all elements in the tree you can use printAll() or printByLevel()
 *          printAll(var_name);
 *          printByLevel(var_name);
 *
 *  To get element count use cnt(var_name)
 *          int n = cnt(car_name);
 *
 *  Bool functions:
 *          Check for element with exists(var_name);
 *          Check if empty with isEmpty(var_name);
**/

//Structure of the tree
typedef struct AVL
{
    struct Node *head;
    int count;
} AVL;

//Initializer function
AVL create();

//Insertion function
//A value will NOT be inserted if it is already in the tree
void ins(AVL *tree, int val);

//Deletion function
void del(AVL *tree, int val);

//Function to clear all elements of tree
void clr(AVL *tree);

//Function to check if an element with a given value is in the tree
bool exists(AVL tree, int val);

//Check if tree is empty
bool isEmpty(AVL tree);

//Get the number of elements in tree
int cnt(AVL tree);

//Print all elements in increasing order
void printAll(AVL tree);

//Print all elements by their level in the tree
void printByLevel(AVL tree);

#endif // AVL_H_INCLUDED
