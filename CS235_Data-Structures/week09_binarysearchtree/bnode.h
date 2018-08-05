/***********************************************************************
*    Week 08, Binary Node class
* Author:
*    Chase Busacker
* Summary:
*    This program will implement the Binary Noden class
************************************************************************/
#ifndef BNODE_H
#define BNODE_H

#include <iostream> 
#include <cassert>
using namespace std;

/*****************************************************************
 * BINARY NODE
 * A single node in a binary tree.  Note that the node does not know
 * anything about the properties of the tree so no validation can be done.
 *****************************************************************/
template <class T>
class BinaryNode
{
public:
   BinaryNode();
   BinaryNode(T item);
   // return size (i.e. number of nodes in tree)
   int size() const
   {
            return 1 +
               (pLeft== NULL? 0 : pLeft->size()) +
               (pRight == NULL ? 0 : pRight->size());
   }
   
   // add a node to the left/right
   void addLeft (BinaryNode <T> * pNode);
   void addRight(BinaryNode <T> * pNode);

   // create a node and add it to the left/right
   void addLeft (const T & t) throw (const char *);
   void addRight(const T & t) throw (const char *);
   
   // since no validation is done, everything is public
   BinaryNode <T> * pLeft;
   BinaryNode <T> * pRight;
   BinaryNode <T> * pParent;
   T data;
};

/************************************************************
 * DEFAULT CONSTRUCTOR
 * Setting pLeft, pRight, and pParent to NULL
 ************************************************************/
template <class T>
BinaryNode<T>::BinaryNode()
{
   pLeft = NULL;
   pRight = NULL;
   pParent = NULL;
}

/************************************************************
 * NON-DEFAULT CONSTRUCTOR
 * Takes a template variable as a parameter and assigns all 
 * the pointers to NULL).
************************************************************/
template <class T>
BinaryNode<T>::BinaryNode(T item)
{
   data = item;
   pLeft = NULL;
   pRight = NULL;
   pParent = NULL;

}

/************************************************************
* ADDLEFT
* Adds a node to the left of the current node. Takes a 
* BinaryNode * as a parameter. The parameter node will be 
* used. pLeft of the current node will point to the new 
* node, and pParent of the new node will point to the 
* current node. The return value is void.
************************************************************/
template <class T>
void BinaryNode<T>::addLeft(BinaryNode <T> * pNode)
{
   this->pLeft = pNode;
   if (pNode)
      pNode->pParent = this;
}

/************************************************************
 * ADDLEFT
 * Adds a node to the left of the current node. Takes a 
 * template variable as a parameter. A new node will be 
 * allocated. pLeft of the current node will point to the new 
 * node, and pParent of the new node will point to the 
 * current node. The return value is void.  In the case of 
 * an allocation error, the following c-string exception 
 * will be thrown:
 * ERROR: Unable to allocate a node
************************************************************/
template <class T>
void BinaryNode<T>::addLeft(const T & t) throw (const char *)
{
   BinaryNode<T> * pNode;
   try
   {
      pNode = new BinaryNode<T>;
      
   }
   catch (bad_alloc)
   {
      throw "ERROR: Unable to allocate a node";
   }
   pNode->data = t;
   this->pLeft = pNode;
   pNode->pParent = this;
}

/************************************************************
* ADDRIGHT
* Adds a node to the right of the current node. Takes a
* BinaryNode * as a parameter. The parameter node will be
* used. pRight of the current node will point to the new
* node, and pParent of the new node will point to the
* current node. The return value is void.
************************************************************/
template <class T>
void BinaryNode<T>::addRight(BinaryNode <T> * pNode)
{
   this->pRight = pNode;
   if (pNode)
      pNode->pParent = this;
}

/************************************************************
* ADDRIGHT
* Adds a node to the right of the current node. Takes a
* template variable as a parameter. A new node will be
* allocated. pLeft of the current node will point to the new
* node, and pParent of the new node will point to the
* current node. The return value is void.  In the case of
* an allocation error, the following c-string exception
* will be thrown:
* ERROR: Unable to allocate a node
************************************************************/
template <class T>
void BinaryNode<T>::addRight(const T & t) throw (const char *)
{
   BinaryNode<T> * pNode;
   try
   {
      pNode = new BinaryNode<T>;
      
   }
   catch (bad_alloc)
   {
      throw "ERROR: Unable to allocate a node";
   }
   pNode->data = t;
   this->pRight = pNode;
   pNode->pParent = this;
}

/************************************************************
* DELETEBINARYTREE: NONMEMBER FUNCTION
* Takes a BinaryNode as a parameter and deletes all the 
* children and itself. This is a recursive function.
************************************************************/
template <class T>
void deleteBinaryTree(BinaryNode<T> * deleteMe)
{
   if (deleteMe == NULL)
      return;
   if (deleteMe->pLeft)
      deleteBinaryTree(deleteMe->pLeft);
   if (deleteMe->pRight)
      deleteBinaryTree(deleteMe->pRight);
   delete deleteMe;
   deleteMe = NULL;

}

/************************************************************
 *INSERTION OPERATOR
 * Takes a constant BinaryNode * as a parameter and displays 
 * the tree under the passed parameter.This is a recursive 
 * function traversing the tree in infix order.A single
 *  space will be displayed after every element.
************************************************************/
template <class T>
ostream & operator << (ostream & out, const BinaryNode<T> * input)
{
   //Infix Traversal: LVR
   if (input->pLeft)
       out << input->pLeft; //Recursion occurs here.
   out << input->data << " "; //Display Data
   if (input->pRight)      
      out << input->pRight; //Recursion occurs here.
   return out;
}
#endif // BNODE_H
