#include "list.h"
#include "bnode.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cassert>
#include <iomanip>
using namespace std;


/*************************************************************************
 * FAMILY MEMBER
 * Struct that holds all the variables that will be needed for each family
 * famly member.
 **************************************************************************/
struct familyMember
{
   string id;
   string first;
   string lowerfirst;
   string last;
   string lowerlast;
   string birthMonth;
   string birthDay;
   string birthYear;
   bool hasbirthdate;
};

/*************************************************************************
* fBinaryNode Class
* A Binary Node class of Family Members
* Inherits BinaryNode and has its own findID function.
**************************************************************************/
class fBinaryNode : public BinaryNode<familyMember>
{
public:
   /*************************************************************************
   * Non-Default Constructor
   * Set the data to root and all other pointers to NULL.
   **************************************************************************/
   fBinaryNode(familyMember root)
   {
      data = root;
      pLeft = NULL;
      pRight = NULL;
      pParent = NULL;
   }

   /*************************************************************************
   * findID
   * Returns the BinaryNode with the ID.
   **************************************************************************/
   BinaryNode<familyMember> * findId(familyMember data, BinaryNode<familyMember>* root)
   {
      if (data.id == root->data.id)
         return root;
      BinaryNode<familyMember> *left = NULL;
      BinaryNode<familyMember> *right = NULL;
      if (data.id != root->data.id)
      {
         if (root->pLeft)
            left = findId(data, root->pLeft);
         if (root->pRight && root->data.id != data.id)
            right = findId(data, root->pRight);
      }
      if (left && data.id == left->data.id)
         return left;
      if (right && data.id == right->data.id)
         return right;
   }
};

/*************************************************************************
* fList
* class of a familyMember List. Inherits List and has its own sort function.
**************************************************************************/
class fList : public List<familyMember>
{
public:
   void insertSorted(familyMember member)
   {
      if (size() == 0)
         push_back(member);
      else
      {
         Node<familyMember> * insertHere = frontNode;
         while (insertHere && insertHere->data.lowerlast < member.lowerlast)
         {
            insertHere = insertHere->pNext;
         }
            while (insertHere
                   && insertHere->data.lowerfirst < member.lowerfirst
                   && insertHere->data.lowerlast == member.lowerlast)
               insertHere = insertHere->pNext;
            while (insertHere
                   && insertHere->data.lowerfirst == member.lowerfirst
                   && insertHere->data.lowerlast == member.lowerlast
                   && insertHere->data.birthYear < member.birthYear)
               insertHere = insertHere->pNext;
         if (insertHere != frontNode && insertHere != NULL)
         {
            insertHere = insertHere->pPrev;
            insertNode(member, insertHere);

         }
         else if (insertHere == frontNode)
         {
            push_front(member);
         }
         else if (insertHere == NULL)
         {
            push_back(member);
         }
      }
   }
};


void getGEDfile(char gedFile[]);
fBinaryNode * readInGEDFile(char gedFile[], fList &sortedList, fBinaryNode * root);
void saveSortedDatFile(fList &sortedFamily);
fBinaryNode * convertIDTreeToFamilyTree(fBinaryNode * root, fList &sortedFamily);
void display(fBinaryNode * root);

/*************************************************************************
* MAIN
* Drives the Program.
**************************************************************************/
int main(int argc, const char * argv[])
{
   //gedFile
   char gedFile[200];

   //error check if incorrect number of arguments.
   if (argc == 1)
   {
      getGEDfile(gedFile);
   }
   else if (argc != 2)
   {
      cout << "ERROR: Too Many Arguments for this program. Please try again using \"a.out <GEDfile>\"" << endl;
      return 0;
   }
   else
   {
      strcpy(gedFile, argv[1]);
   }

   //our List and our tree declaration.
   fList sortedList;
   fBinaryNode *root = NULL;

   //readInGEDFile will read in all the information and make the sortedList. 
   //It will also return the root of our family tree.
   root = readInGEDFile(gedFile, sortedList, root);
   
   //transforms the sortedList into sorted.dat.
   saveSortedDatFile(sortedList);

   //the readInGEDFile only builds a tree with IDs with empty family members.
   convertIDTreeToFamilyTree(root, sortedList);

   //display the tree.
   display(root);

   //free up memory
   deleteBinaryTree(root);
}

/*************************************************************************
* getGEDfile
* retrieves the file from the user if it wasn't included in arcv.
**************************************************************************/
void getGEDfile(char gedFile[])
{
   cout << "Please enter the GEDCOM file: ";
   cin >> gedFile;
}

/*************************************************************************
* readInGEDFile
* reads the file using ifstream. Builds a linked List of alphabetically
* sorted familyMembers and also builds a root with IDs only.
**************************************************************************/
fBinaryNode * readInGEDFile(char gedFile[], fList &sortedFamily, fBinaryNode * root)
{
   ifstream fin(gedFile);
   while (fin.fail())
   {
      cout << "ERROR: File could not be opened!" << endl;
      cout << "Please enter the GEDCOM file:";
      cin >> gedFile;
      fin.open(gedFile);
   }
   string fileStuff;
   familyMember indi;
   indi.hasbirthdate = false;
   familyMember idonly;
   string idLeft;
   string idRight;
   string idRoot;

   BinaryNode<familyMember> *next;
   while (fin >> fileStuff)
   {
      if (fileStuff[0] == '@' && fileStuff[1] == 'I')
      {
         indi.id = fileStuff;
         indi.birthDay = "";
         indi.birthMonth = "";
         indi.birthYear = "";
         indi.first = "";
         indi.lowerfirst = "";
         indi.last = "";
         indi.lowerlast = "";
         while (fin >> fileStuff)
         {
            //Read in given name Surname and birthday of individuals.
            if (fileStuff == "GIVN")
            {
               getline(fin, indi.first);
               indi.lowerfirst = indi.first;
               for (int i = 0; i < indi.first.size(); i++)
                  indi.lowerfirst[i] = tolower(indi.lowerfirst[i]);
            }
            if (fileStuff == "SURN")
            {
               getline(fin, indi.last);
               indi.lowerlast = indi.last;
               for (int i = 0; i < indi.last.size(); i++)
                  indi.lowerlast[i] = tolower(indi.lowerlast[i]);
            }
            if (fileStuff == "BIRT")
            {
               while (fin >> fileStuff)
               {
                  if (fileStuff == "DATE")
                  {
                     fin >> fileStuff;
                     if (fileStuff == "AFT")
                        fin >> fileStuff;
                     if (isdigit(fileStuff[0]) && fileStuff.size() < 3)
                     {
                        indi.birthDay = fileStuff;
                        fin >> indi.birthMonth;
                        fin >> indi.birthYear;
                     }
                     else if (isalpha(fileStuff[0]))
                     {
                        indi.birthMonth = fileStuff;
                        fin >> indi.birthYear;
                     }
                     else
                     {
                        indi.birthYear = fileStuff;
                     }
                     indi.hasbirthdate = true;
                     break;
                  }
                  if (fileStuff == "PLAC" || indi.hasbirthdate)
                     break;
               }

            }
            if (fileStuff == "0" || indi.hasbirthdate)
               break;

         }
         //insert the individual
         sortedFamily.insertSorted(indi);
         //the next individual's birthdate has not been set. Reset to false.
         indi.hasbirthdate = false;


      }
      //In the file, I found this word was a good divider of the individual and family records.
      else if (fileStuff == "DIV")
      {


         while (fin >> fileStuff)
         {
            while (fin >> fileStuff)
            {
               //read in the IDS for the husband wife and child.
               if (fileStuff == "HUSB")
                  fin >> idLeft;
               if (fileStuff == "WIFE")
                  fin >> idRight;
               if (fileStuff == "CHIL")
                  fin >> idRoot;
               if (idRoot != "")
                  break;
            }
            //make the root of the tree if it's null.
            if (!root)
            {

               idonly.id = idRoot;
               root = new fBinaryNode(idonly);
               if (idLeft != "")
               {
                  idonly.id = idLeft;
                  root->addLeft(idonly);
               }
               if (idRight != "")
               {
                  idonly.id = idRight;
                  root->addRight(idonly);
               }
            }
            //otherwise add to the root of the tree.
            else
            {
               idonly.id = idRoot;
               next = root->findId(idonly, root);
               if (idLeft != "")
               {
                  idonly.id = idLeft;
                  next->addLeft(idonly);
               }
               if (idRight != "")
               {
                  idonly.id = idRight;
                  next->addRight(idonly);
               }
            }

            //now that we've added to the tree, we are restarting with blank ids.
            idRoot = "";
            idLeft = "";
            idRight = "";
         }
      }
   }
   fin.close();
   return root;
}

/*************************************************************************
* SaveSortedDatFile
* Takes the sortedFamily and saves to "sorted.dat".
**************************************************************************/
void saveSortedDatFile(fList &sortedFamily)
{

   ofstream fout;
   fout.open("sorted.dat");

   familyMember indi;
   for (ListIterator<familyMember> it = sortedFamily.begin(); it != sortedFamily.end(); it++)
   {

      indi = *it;
      indi.first.erase(0, 1);
      if (indi.first != "")
         fout << indi.first;
      else
         indi.last.erase(0, 1);
      if (indi.last != "")
         fout << indi.last;

      if (indi.hasbirthdate)
      {
         fout << ", b. ";
         if (indi.birthDay != "")
            fout << indi.birthDay << " ";
         if (indi.birthMonth != "")
            fout << indi.birthMonth << " ";
         if (indi.birthYear != "")
            fout << indi.birthYear;
      }

      fout << endl;
   }
}


/*************************************************************************
* convertIDTreeToFamilyTree
* Traverses through the "ID ONLY" tree and sets the names and birthdays
* after finding the ID in the tree.
**************************************************************************/
fBinaryNode * convertIDTreeToFamilyTree(fBinaryNode * root, fList &sortedFamily)
{
   BinaryNode<familyMember> *temp;
   for (ListIterator<familyMember> it = sortedFamily.begin(); it != sortedFamily.end(); it++)
   {
      temp = root->findId(*it, root);
      temp->data = *it;
   }
   return root;
}

/*************************************************************************
* display
* Displays the Tree in Level Order and prints out a name for each generation.
**************************************************************************/
void display(fBinaryNode * root)
{
   const int MAX = 500; //This would have to be redefined depending on the number of relatives.
   BinaryNode<familyMember> *queue[MAX];
   BinaryNode<familyMember> *temp;
   familyMember indi;
   int front = 0;
   int back = 0;
   int gencount = 1;
   int newgen = 1;
   queue[back++] = root;
   cout << "The Ancestors of" << root->data.first << root->data.last << ":" << endl;
   while (front != back)
   {

      temp = queue[front];


      front = (front + 1);
      if (temp != NULL)
      {
         // visit

         if (temp != root)
         {
            indi = temp->data;
            cout << setw(7) << "";
            if (indi.first != "")
               cout << indi.first;
            if (indi.last != "")
               cout << indi.last;

            if (indi.hasbirthdate)
            {
               cout << ", b. ";
               if (indi.birthDay != "")
                  cout << indi.birthDay << " ";
               if (indi.birthMonth != "")
                  cout << indi.birthMonth << " ";
               if (indi.birthYear != "")
                  cout << indi.birthYear;
            }
            cout << endl;
         }

         // end Visit        
         queue[back] = temp->pLeft;
         back = (back + 1);
         queue[back] = temp->pRight;
         back = (back + 1);
         if (newgen == front && queue[front + 1] != NULL)
         {
            if (gencount == 1)
               cout << "Parents:" << endl;
            else if (gencount == 2)
               cout << "Grandparents:" << endl;
            else if (gencount == 3)
               cout << "Great Grandparents:" << endl;
            else if (gencount > 3)
            {
               cout << gencount - 2;
               if ((gencount - 2) % 100 < 21 && (gencount - 2) % 100 > 4)
                  cout << "th ";
               else if ((gencount - 2) % 10 == 1)
                  cout << "st ";
               else if ((gencount - 2) % 10 == 2)
                  cout << "nd ";
               else if ((gencount - 2) % 10 == 3)
                  cout << "rd ";
               else
                  cout << "th ";
               cout << "Great Grandparents:" << endl;
            }
            newgen = back;
            gencount++;
         }
      }
   }
}
