/***********************************************************************
* Header:
*    LIST
* Summary:
*    The Node Class and List Class.
* Author
*    Chase Busacker
************************************************************************/

#ifndef NODE_H
#define NODE_H

#include <cassert>
#include <iostream>
using namespace std;

template <class T>
class List;
template <class T>
class Node
{
public:

   //Defaut Constructor sets everything to NULL
   Node<T>();

   //Non-default Constructor sets *nextNode to NULL
   //and data to the parameter data.
   Node<T>(T data);

   //The address of our next node.
   Node *pNext;

   //The address of the previous node.
   Node *pPrev;

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
   pNext = NULL;
   pPrev = NULL;
}

/***********************************************************
* NODE
* Non-Default constructor: Sets data to the parameter
***********************************************************/
template <class T>
Node<T>::Node(T data)
{
   this->data = data;
   pPrev = NULL;
   pNext = NULL;
}


/**************************************************
* LIST ITERATOR
* An iterator through the LIST
*************************************************/
template <class T>
class ListIterator
{
friend void List<T>::remove(ListIterator<T> it1) throw (const char *);
friend ListIterator<T> List<T>::insert(ListIterator<T> it1, T data) throw (const char *);
public:
   // default constructor
   ListIterator() : p(NULL) {}

   // initialize to direct p to some item
   ListIterator(Node<T> * p) : p(p) {}


   // not equals operator
   bool operator != (const ListIterator & rhs) const
   {
      return rhs.p != this->p;
   }

   bool operator == (const ListIterator & rhs) const
   {
      return rhs.p == this->p;
   }

   void operator = (const ListIterator & rhs)
   {
      this->p = rhs.p;
   }

   // dereference operator
   T & operator * ()
   {
      return p->data;
   }

   // prefix increment
   ListIterator <T> & operator ++ ()
   {
      p = p->pNext;
      return *this;
   }

   // postfix increment
   ListIterator <T> operator++(int postfix)
   {
      ListIterator tmp(*this);
      p = p-> pNext;
      return tmp;
   }

   ListIterator <T> operator-- ()
   {
      p = p-> pPrev;
      return *this;
   }
   ListIterator <T> operator--(int prefix)
   {
      ListIterator tmp(*this);
      p=p ->pPrev;
      return tmp;
   }
private:
   Node<T> * p;
};


template <class T>
class List
{
public:
   List() throw (const char *);
   List(const List & copyMe) throw (const char *);
   ~List();
   List & operator = (const List & assignMe) throw (const char *);
   int size();
   bool empty();
   void clear();
   void push_back(T item)  throw (const char *);
   void push_front(T item) throw (const char *);
   T & front() throw (const char *);
   T & back() throw (const char *);
   ListIterator<T> insert( ListIterator<T> it1, T data ) throw (const char *);
   void remove(ListIterator<T>  it1) throw (const char *);
   ListIterator<T> begin();
   ListIterator<T> rbegin();
   ListIterator<T> end();
   ListIterator<T> rend();
   //unrequired functions
   void freeData(Node<T> *&pStart);
   Node<T> * copy(Node<T> * pHead) throw (const char *);
   void insertNode(T insertItem, Node<T> *&precedingNode);
   virtual void insertSorted(T item) = 0;
protected:
   int numNodes;
   Node<T> * frontNode;
   Node<T> * backNode;
};

/*******************************************************
 * Default constructor (create an empty list)
 * If allocation is not possible, the following error will be thrown:
 * ERROR: unable to allocate a new node for a list
 *******************************************************/
template <class T>
List<T>::List() throw (const char *)
{
   frontNode = NULL;
   numNodes = 0;
}

/********************************************************
 * copy constructor
 * If allocation is not possible, the following error will be thrown:
 * ERROR: unable to allocate a new node for a list
 ********************************************************/
 template <class T>
List<T>::List(const List & copyMe) throw (const char *)
{
   try
   {
      frontNode = copy(copyMe.frontNode);
      numNodes = copyMe.numNodes;
   }
   catch (bad_alloc)
   {
      throw "ERROR: unable to allocate a new node for a list";
   }
}
/**********************************************************
 * Destructor: When finished, the class should delete all
 *  the allocated memory.
 ****************************************************/
template <class T>
List<T>::~List()
{
   if (frontNode)
      freeData(frontNode);
   numNodes = 0;
   return;
}

/***********************************************************
 * operator=(): Removes all the items in the current list
 * and copies the contents from the right-hand side (rhs)
 * onto the current list. In the case of an allocation error,
 * the following c-string will be thrown:
 * ERROR: unable to allocate a new node for a list
 ************************************************************/
template <class T>
List<T> & List<T>::operator = (const List<T> & rhs) throw (const char *)
{
   if (frontNode)
      freeData(frontNode);

   try
   {
      frontNode = copy(rhs.frontNode);
   }
   catch (bad_alloc)
   {
      throw "ERROR: unable to allocate a new node for a list";
   }
   return *this;

}

/************************************************
 * empty(): Test whether the list is empty. This method
 * takes no parameters and returns a Boolean value.
 *************************************************/
template <class T>
bool List<T>::empty()
{
   return numNodes == 0;
}

/**************************************************
 * clear(): Empties the list of all items.
 * There are no parameters and no return value.
 **************************************************/
template <class T>
void List<T>::clear()
{
   //set the pointer node to NULL so that
   //it's not pointing to the list anymore.
   //Also probably good idea to delete the list here.
   freeData(frontNode);
   frontNode = NULL;
   backNode = NULL;
   numNodes = 0;
}

/*******************************************************
 * size(): Returns the number of nodes in
 * the list. There are no parameters
 * and the return value is an integer.
 ******************************************************/
template <class T>
int List<T>::size()
{
   return numNodes;
}


/********************************************************
 * push_back(): Adds an item to the back of the list.
 * This method takes a single parameter (the item to be
 * added to the end of the list) and has no return value.
 * In the case of an allocation error, the following
 * c-string exception will be thrown:
 * ERROR: unable to allocate a new node for a list
 ********************************************************/
template <class T>
void List<T>::push_back(T item) throw (const char *)
{
   Node<T> *pNode;
   if (numNodes == 0)
   {
      frontNode = new Node<T>;
      frontNode->data = item;
      backNode = frontNode;
      numNodes++;
   }
   else
   {
      pNode = new Node<T>;
      pNode->data = item;
      pNode->pNext = NULL;
      pNode->pPrev = backNode;
      backNode = pNode;
      pNode->pPrev->pNext = pNode;
      numNodes++;
   }
}

/*********************************************************
 * push_front(): Adds an item to the front of the
 * list exactly the same as push_back()
 ******************************************************/
template <class T>
void List<T>::push_front(T item) throw (const char *)
{
   Node<T> *pNode;
   if (numNodes == 0)
   {
      frontNode = new Node<T>;
      frontNode->data = item;
      backNode = frontNode;
      numNodes++;
   }
   else
   {
      pNode = new Node<T>;
      pNode->data = item;
      pNode->pNext = frontNode;
      pNode->pPrev = NULL;
      frontNode->pPrev = pNode;
      frontNode = pNode;
      numNodes++;
     
   }
}

/******************************************************
 * front() : Returns the item currently at the
 * front of the list.This item is returned by - reference,
 * so the last item can be changed through the front() method.
 * If the list is currently empty, the following exception
 * will be thrown :
 * ERROR: unable to access data from an empty list
 ********************************************************/
template <class T>
T & List<T>::front() throw (const char *)
{
   return frontNode->data;
}

/*************************************************
 * back() : Returns the item currently at the back of
 * the list exactly the same as front()
 ************************************************/
template <class T>
T & List<T>::back() throw (const char *)
{
   return backNode->data;
}

/****************************************************
 * insert(): Inserts an item in the middle of a list.
 * There are two parameters: the data item to be inserted,
 * and a ListIterator pointing to the location in the list
 * where the new item will be inserted before. The return
 * value is an iterator to the newly inserted item.
 * In the case of an allocation error, the following
 * exception will be thrown:
 * ERROR: unable to allocate a new node for a list
 ********************************************************/
template <class T>
ListIterator<T> List<T>::insert( ListIterator<T> it1, T data) throw (const char *)
{
   //this function needs to be written to satisfy a insertion sort.
   try
   {
      if (it1.p != frontNode && it1.p != NULL)
      {
         --it1;
         insertNode(data, it1.p);
         it1++;
      }
      else if (it1.p == frontNode)
      {
         push_front(data);
      }
      else if (it1.p == NULL)
      {
         push_back(data);
      }
      return it1;
   }
   catch (bad_alloc)
   {
      throw "ERROR: unable to allocate a new node for a list";
   }
   numNodes++;
}

/*************************************************************
 * remove(): Removes an item from the middle of a list.
 * There is one parameter: a ListIterator pointing to the item
 * to be removed. In the case of an iterator pointing to end(),
 * the following exception will be thrown:
 * ERROR: unable to remove from an invalid location in a list
 *************************************************************/
template <class T>
void List<T>::remove(ListIterator<T> it1) throw (const char *)
{
   try
   {
      if (it1.p == backNode)
      {
         backNode = it1.p->pPrev;
         it1.p->pPrev->pNext = NULL;
      }
      else if (it1.p == frontNode)
      {
         it1.p->pNext->pPrev = NULL;
         frontNode = it1.p->pNext;
      }
      else
      {
         it1.p->pPrev->pNext = it1.p->pNext;
         it1.p->pNext->pPrev = it1.p->pPrev;
      }

      delete it1.p;
      it1.p = NULL;
      numNodes--;
   }
   catch (...)
   {
      throw "ERROR: unable to remove from an invalid location in a list";
   }
}

/**********************************************************
 * begin(): Return an iterator to the first element in the list.
 * It takes no parameters and returns a ListIterator
*************************************************************/
template <class T>
ListIterator<T> List<T>::begin()
{
   ListIterator<T> firstElement(frontNode);
   return firstElement;
}

/********************************************************
 * rbegin(): Return an iterator to the last element in the list.
 * It takes no parameters and returns a ListIterator.
 *********************************************************/
template <class T>
ListIterator<T> List<T>::rbegin()
{
   ListIterator<T> reverseBegin(backNode);
   return reverseBegin;
}

/**********************************************************
 * end(): Return an iterator referring to the past-the-end element
 * in the list. The past-the-end element is the theoretical element
 * that would follow the last element in the container. It does not
 * point to any element, so it must not be de-referenced.
 ***********************************************************/
template <class T>
ListIterator<T> List<T>::end()
{
  
   ListIterator<T> backElement(NULL);
   return backElement;
}

/**********************************************************
 * rend(): Return an iterator referring to the past-the-front
 * element in the list. The past-the-front element is the 
 * theoretical element that would preceed the first element 
 * in the container. It does not point to any element, so it 
 * must not be de-referenced. 
***********************************************************/
template <class T>
ListIterator<T> List<T>::rend()
{
   ListIterator<T> reverseEnd (NULL);
   return reverseEnd;
}

/**********************************************************
* freeData(): takes a Node and deletes the List behind it.
* returns nothing.
***********************************************************/
template <class T>
void List<T>::freeData(Node<T> *&pFront)
{

   if (!pFront)
   {
      return;
   }
   else
   {
      if (pFront->pNext)
      {
         freeData(pFront->pNext);
      }
      delete pFront;
      pFront = NULL;
   
      return;
   }
}
/**********************************************************
* copy() takes a Node and copies all of the Nodes behind it.
***********************************************************/
template <class T>
Node<T> * List<T>::copy(Node<T> * pHead) throw (const char *)
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
      backNode = pcopy;
      return pcopy;
   }
   else
   {
      pcopy->data = pHead->data;
      pcopy->pNext = copy(pHead->pNext);
      pcopy->pNext->pPrev = pcopy;
      return pcopy;
   }
}

/**********************************************************
* insertNode(): inserts an item at a certain location.
* Takes the item and a Node as parameters. The Node passed
* is the node before the location where we want to insert
* the Node.
***********************************************************/
template <class T>
void List<T>::insertNode(T insertItem, Node<T> *&precedingNode)
{

   //make a pointer that will be used for inserting.
   Node<T> *insertNode;

   //dynamically allocate the node and insert the data.
   insertNode = new Node<T>;
   insertNode->data = insertItem;

   //if the the preceding exists...
   if (precedingNode)
   {
      //set the insertNode's pNext address to the preceding Node's pNext address
      insertNode->pNext = precedingNode->pNext;
      insertNode->pPrev = precedingNode;
      //and then change precedingNode's pNext to the insertNode address
      //which inserts the insertNode between precedingNode and precedingNode.pNext.
      precedingNode->pNext = insertNode;
      if (insertNode->pNext == NULL)
      {
         backNode = insertNode;
      }
      if (insertNode->pNext)
         insertNode->pNext->pPrev = insertNode;

   }
   //Preceding Node doesn't exist so...
   else
   {
      //the insertNode will become the precedingNode.
      insertNode->pNext = NULL;
      precedingNode = insertNode;
   }
   numNodes++;
}

#endif