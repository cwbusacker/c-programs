/***********************************************************************
* Module:
*    Week 08, HuffmanTree Class
*    Chase Busacker
* Author:
*    Chase Busacker
* Summary:
*    This program will implements the HuffmanTree class. It allows for
*    an easier sort.
************************************************************************/
#include "pair.h"
#include "list.h"
#include "bnode.h"

typedef Pair<char, float> charflo;
typedef BinaryNode<charflo> * pbNode;
typedef BinaryNode<charflo> bNode;

class huffmanTree
{
public:
   //default set the node pointer to NULL
   huffmanTree() { thisbNode = NULL; } 
   
   //non default that makes a new node for the data and sets the data.
   huffmanTree(charflo data) { pbNode newbNode = new bNode(data); thisbNode = newbNode; }

   //non default that makes sets a parameter to thisbNode;
   huffmanTree(pbNode p1) {thisbNode = p1;}

   //a binary node pointer to store the data that this function holds.
   pbNode thisbNode;

};