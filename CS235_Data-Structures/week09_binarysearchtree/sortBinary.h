/***********************************************************************
 * Module:
 *    Week 09, Sort Binary
 *    Brother Ercanbrack, CS 235
 * Author:
 *    Chase Busacker
 * Summary:
 *    This program sorts items in an array using a BST.
 ************************************************************************/

#ifndef SORT_BINARY_H
#define SORT_BINARY_H

#include "bst.h"

/*****************************************************
 * SORT BINARY
 * Perform the binary tree sort
 ****************************************************/
template <class T>
void sortBinary(T array[], int num)
{
   int i;
   BST<T> sortTree;

   //here we will insert each item that is in the array into the BST
   for (i = 0; i < num; i++)
      sortTree.insert(array[i]);
   BSTIterator<T> it1;
   i = 0;

   //iterate through the BST and put it back into the array sorted.
   for (it1 = sortTree.begin(); it1 != sortTree.end(); it1++)
      array[i++] = *it1;
}


#endif // SORT_BINARY_H
