/***********************************************************************
* Program:
*    Week 11, Sorting
*    Brother Ercanbrack, CS 235
* Author:
*    Chase Busacker
* Summary: 
*
************************************************************************/

#include <iostream>        // for CIN and COUT
#include <cstring>         // for strcmp
#include <iomanip>         // for SETW
#include <vector>
#include <list>
#include <fstream>
#include "heap.h"
#include "merge.h"


using namespace std;

/**********************************************************************
 * MAIN
 * Gets the sort type and filename from the command line. If the sort type
 * or filename are not entered on the command line, the user will be
 * prompted  for the sort type and/or filename.
 * Call the appropriate sort to sort the data contained in the vector or
 * linked list and display the sorted data to the console.
 ***********************************************************************/
int main(int argc, const char* argv[])
{
   ifstream fin;
   char sortType[10];
   char fileName[50];

   //get the file name and sort type.
   if (argc == 1)
   {
      cout << "Which sort merge or heap? ";
      cin >> sortType;
      cout << "Enter name of file to sort: ";
      cin >> fileName;
   }

   //get the filename only because sort type has already been received.
   else if (argc == 2)
   {
      strcpy(sortType,argv[1]); 
      cout << "Enter name of file to sort: ";
      cin >> fileName;
   }

   //store file and sort type.
   else if (argc == 3)
   {
      strcpy(sortType,argv[1]);    
      strcpy(fileName,argv[2]);
   }
   
   //if heap was called
   if (strcmp(sortType, "heap") == 0)
   {
      vector<int> heapSortVector;
      int nextInt;
      fin.open(fileName);
      //read in the file
      while (fin.fail())
      {
         cout << "Error Reading File. Please Try Again." << endl;
         cout << "Enter name of file to sort: ";
         cin >> fileName;
         fin.open(fileName);
      }
      heapSortVector.push_back(0);
      //put the info in a vector
      while (fin >> nextInt)
         heapSortVector.push_back(nextInt);
      //sort the vector
      heapSort(heapSortVector);
      //display the sorted vector
      for (int i = 1; i <= heapSortVector.size() -1; i++)
      {
         cout << setw(3) << right << heapSortVector[i];
         if (i % 10 == 0)
            cout << endl;
      }
   }
   else if(strcmp(sortType, "merge") == 0)
   {
      list<int> mergeSortList;
      int nextInt;
      fin.open(fileName);

      //read in the file
      while (fin.fail())
      {
         cout << "Error Reading File. Please Try Again." << endl;
         cout << "Enter name of file to sort: ";
         cin >> fileName;
         fin.open(fileName);
      }

      //put the info in a list
      while (fin >> nextInt)
         mergeSortList.push_back(nextInt);

      //sort the list
      mergeSort(mergeSortList);


      //display the sorted list
      for (int i = 1; !mergeSortList.empty(); i++)
      {
         cout << setw(3) << right << mergeSortList.front();
         mergeSortList.pop_front();
         if (i % 10 == 0)
            cout << endl;
      }
   }
   else
   {
      cout << "\nInvalid sort name - must be 'heap' or 'merge'" << endl;
   }
   
   return 0;
}
