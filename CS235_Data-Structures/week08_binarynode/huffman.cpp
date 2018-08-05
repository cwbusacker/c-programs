/***********************************************************************
 * Module:
 *    Week 08, Huffman
 *    Brother Ercanbrack, CS 235
 * Author:
 *    Chase Busacker
 * Summary:
 *    This program will implement the huffman() function.
 ************************************************************************/

#include "huffman.h"       // for HUFFMAN() prototype

 /*******************************************
 * operator <
 * returns a boolean saying if the left side
 * is smaller than the right side.
 * This is needed for list.sort().
 *******************************************/
bool operator < (const huffmanTree & tree1, const huffmanTree & tree2)
{
   return tree1.thisbNode->data.second < tree2.thisbNode->data.second;
}

/*******************************************
* HUFFMAN
* Handles everything needed to display
* the Huffman codes of each letter in a file.
*******************************************/
void huffman(string filename)
{
   //Open the file
   ifstream fin(filename.c_str());
   while (fin.fail() && filename != "quit")//If the file fails. Loop until quitting or the file works..
   {

      cout << "ERROR: " << filename << " was not able to be opened.\n Please Try Again." << endl;
      cout << "Enter the filename containing the value frequencies.\n";
      cout << "Enter \"quit quit\" now to end the program.\n";
      cout << "> ";
      cin >> filename;
      fin.open(filename.c_str());
   }
   if (filename == "quit")
      return;

   //make some variables for reading in the file.
   Pair<char, float> pair;
   list<huffmanTree> hufftreelist;
   list<huffmanTree> hufflinklist;
   charflo data;

   //Read in the data and create two lists: one that will turn into a tree
   //and one that will be used for displaying later.
   while (fin >> data)
   {
      huffmanTree newtree(data);
      hufftreelist.push_back(newtree);
      hufflinklist.push_back(newtree);
   }
   fin.close();
   charflo bNode1;
   pbNode pNewNode;
   float sum;

   //This loop is creating the tree in the correct format.
   while(hufftreelist.size() != 1)
   {
      //sorts the list everytime. Uses the operator < found above to sort.
      hufftreelist.sort();
      //make the node that combines the two nodes.
      pNewNode = new bNode;
      //add the smaller node to the left of the new node.
      pNewNode->addLeft(hufftreelist.front().thisbNode);
      //Sum starts at the smallest weight.
      sum = hufftreelist.front().thisbNode->data.getSecond();
      //we are done with the smallest node so get rid of it.
      hufftreelist.pop_front();
      //add the second smallest to the right side of the new node
      pNewNode->addRight(hufftreelist.front().thisbNode);
      //combine this 
      sum += hufftreelist.front().thisbNode->data.getSecond();
      //the new frequency of this node is the sum of the two nodes that are attached.
      pNewNode->data.second = sum;
      //don't need the front node anymore...
      hufftreelist.pop_front();
      //make the pNewNode a type huffmanTree with the non-default constructor
      huffmanTree newtree(pNewNode);
      //push the new node onto the list before starting the loop over again.
      hufftreelist.push_back(newtree);
     
   }

   //The root node we will use will be the only node that is in hufftreelist.
   pbNode root = hufftreelist.front().thisbNode;
   //This string will be used to display the huffman code of each number.
   string numbers;

   //We are going to loop until the hufflinklist is empty(popping each time we display).
   while (!hufflinklist.empty())
   {
      //First cout the letter and an equal sign.
      cout << hufflinklist.front().thisbNode->data.first << " = ";

      //Numbers string will be created by the search function.
      string numbers = search(root, hufflinklist.front().thisbNode->data.first);

      //The search function returned the numbers we want, but backward.
      //This for loop reverses that string and removes any '-' which
      //was used to compute the numbers.
      for (int i = numbers.length()-1; i >= 0; i--)
      {
         //take care of 'imputities' found in the string.
         if (numbers[i] != '-')
         {
            cout << numbers[i];
         }
      }
      cout << endl;
      //The letter has been displayed! Don't need it anymore so pop.
      hufflinklist.pop_front();
   }

   //Don't Forget to Delete the root after outputting!
   deleteBinaryTree(root);
   
   return;
}
/***************************************************************
 * SEARCH
 * Returns a string of 1's and 0's to give the path from the 
 * FindMe character to the root. (The string will be backward)
****************************************************************/
string search(pbNode root, char findMe)
{
   string numbers;
   //until we've found findMe, we don't want to add any 0s or 1s to the numbers string.
   bool found = false;
      //Infix Traversal: LVR
   if (root->pLeft && !found)
   {
      //Search the left side of the tree.
      numbers += search(root->pLeft, findMe);
      //if it's in there, the length will no longer be 0.
      found = numbers.length() > 0;
      //if statement is the equivalent of going left. so add a "0" to the string.
      if (found)
         numbers += "0";
   }
   //test if the location we are at holds the findMe.
   if (root->data.first == findMe)
   {
      //make the length of the string longer with this
      //these will be removed when displaying.
      numbers += '-';
   }

   //check the right branch
   if (root->pRight && !found)
   {  
      //search the right tree for the findMe.
      numbers += search(root->pRight, findMe);

      //set found boolean if its found.
      found = numbers.length() > 0;
      //if it is found, then we will add a one to the string.
      if (found)
         numbers += "1";
   }
   return numbers;
}