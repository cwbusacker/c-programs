/***********************************************************************
* Header:
*    NODE
* Summary:
*    The Node Class as well as non-member functions to insert into a list.
* Author
*    Chase Busacker
************************************************************************/

#ifndef NODE_H
#define NODE_H

#include <cassert>
#include <iostream>
using namespace std;

template <class T>
class Node
{
public:

   //Defaut Constructor sets everything to NULL
   Node<T>();

   //Non-default Constructor sets *nextNode to NULL
   //and data to the parameter data.
   Node<T> (T data);

   //The address of our next node.
   Node *pNext;
   
   //The data in the node.
   T data;
};

/***********************************************************
 * NODE
 * Default constructor
 ***********************************************************/
template <class T>
Node<T>::Node()
{
   data = T();
   pNext = NULL; 
}

/***********************************************************
* NODE
* Non-Default constructor: Sets data to the parameter
***********************************************************/
template <class T>
Node<T>::Node(T data)
{
   pNext = NULL;
   this->data = data;
}

/***********************************************************
* COPY
* Make a Copy of the list.
***********************************************************/
template <class T>
Node<T> * copy(Node<T> * pHead) throw (const char *)
{
   //If pHead doesn't exits, throw error
   if (pHead == NULL)
   {
      throw "ERROR: Cannot Copy a NULL Node";
   }
   Node<T> * pcopy = new Node<T>;

   if (pHead->pNext == NULL)
   {
      pcopy->data = pHead->data;
      return pcopy;
   }
   else
   {
      pcopy->data = pHead->data;
      pcopy->pNext = copy(pHead->pNext);
      return pcopy;
   }
   
  
}

template <class T>
void insert(T insertItem, Node<T> *&precedingNode, bool isHead = false)
{
   //make a pointer that will be used for inserting.
   Node<T> *insertNode;
   
   //dynamically allocate the node and insert the data.
   insertNode = new Node<T>;
   insertNode->data = insertItem;

   //if the the preceding node does not exist...
   if (!precedingNode)
   {
      //the insertNode will become the precedingNode.
      insertNode->pNext = NULL;
      precedingNode = insertNode;
   }

   //Preceding Node exists so...
   else
   {

      if (!isHead)
         //the item is not meant to be the new head...
      {



         //set the insertNode's pNext address to the preceding Node's pNext address
         insertNode->pNext = precedingNode->pNext;
         //and then change precedingNode's pNext to the insertNode address
         //which inserts the insertNode between precedingNode and precedingNode.pNext.
         precedingNode->pNext = insertNode;
      }
      else
         //the item is supposed to be the head.
      {
         //the precedingNode address is actually the old pHead address
         //so the address for insertNode is the precedingNode
         insertNode->pNext = precedingNode;
         precedingNode = insertNode; 

      }
   }
  
   
}

/***********************************************************
* FIND
* Find the value in the list.
***********************************************************/
template<class T>
Node<T> * find(Node<T> *pHead, T findValue)
{
   Node<T> *findAddress = NULL;
   for (Node <T> * p = pHead; !findAddress; p = p->pNext)
   {
      if (p)
      {
         if (p->data == findValue)
            findAddress = p;
      }
      else
         break;
   }
   return findAddress;
}

/***********************************************************
* operator <<
* Ostream the contents in the list.
***********************************************************/
template <class T>
ostream & operator << (ostream & out, Node<T> * rhs)
{
   
   for (Node <T> * p = rhs; p; p = p->pNext)
   {
      out << p->data;
      if (p->pNext)
      {
         out << ", ";
      }
     
   } 
   return out;
}

/***********************************************************
* FreeData
* Free the data that is dynamically allocated.
***********************************************************/
template <class T>
void freeData(Node<T> *&pFront)
{

   if (!pFront)
      return;
   else
   {
      freeData(pFront->pNext);
      delete pFront;
      pFront = NULL;
      return;
   }
}
#endif