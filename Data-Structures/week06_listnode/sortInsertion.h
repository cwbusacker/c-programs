/***********************************************************************
 * Header:
 *    INSERTION SORT
 * Summary:
 *    This will contain just the prototype for insertionSortTest(). You may
 *    want to put other class definitions here as well.
 * Author
 *    <your names here>
 ************************************************************************/

#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H

#include "node.h"

/***********************************************
 * INSERTION SORT
 * Sort the items in the array
 **********************************************/
template <class T>
void sortInsertion(T array[], int num)
{
   //make some pointers.
   Node<T> *pHead = NULL;
   Node<T> *insertSpot = NULL;

   //2 "for" loops to loop through pHead and array
   //First "For" loop loops through the data in the array
   for (int i = 0; i < num; i++)
   {
      //Reset insertSpot to NULL
      insertSpot = NULL;
      

      //if the list is just starting OR the data in the 
      //front of the list is bigger then just add it at the front
      if (!pHead || pHead->data > array[i])
      {
         insert(array[i], pHead, true);

      }
      else
      {
         //Loop to find the spot to insert
         for (Node <T> * p = pHead; !insertSpot; p = p->pNext)
         {
            //if we've reached the end of the list or found the spot it goes
            if (( !p->pNext) || (p->data < array[i] && p->pNext->data > array[i]))
            {
               //set the insertspot location
               insertSpot = p;
            } 
         }
         //insert away!
         insert(array[i], insertSpot);
      }
      
   }

   //Replacing the data in the array
   //with the data in the list.
   int i = 0;
   for (Node <T> * p = pHead; p; p = p->pNext)
   {
      array[i] = p->data;
      i++;
   }

   //Don't forget to free the Data.
   freeData(pHead);
}

#endif // INSERTION_SORT_H

