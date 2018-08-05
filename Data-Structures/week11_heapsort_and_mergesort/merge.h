/***********************************************************************
* Program:
*    Week 11, Sorting
*    Brother Ercanbrack, CS 235
*
* Author:
*   Chase Busacker   
* Summary: 
*   This is the merge sort. It takes a template type linked list.
*   and "splits" the list while maintaining each sorted sublist.
*   After splitting, the two lists will merge and then repeat the process
*   until the list is sorted.
************************************************************************/
#include <list>
   
using namespace std;
template <class T>
void merge(list<T> &list1, list<T> &list2, list<T> &data);

template <class T>
void mergeSort(list<T> &data);
/*************************************************************************
* This function sorts a linked list using a Natural Merge Sort.
* Input:  data -  linked list of data to be sorted.
* Output: data -  sorted linked list
* Splits data into two sublists. Each sorted list within data will
* not be broken apart.
**************************************************************************/
template <class T>
void mergeSort(list<T> &data)
{
   //Two sublists that we will use to split data.
   list<T> sublists1;
   list<T> sublists2;

   //Iterate to insert items.
   typename list<T>::iterator it1 = data.begin();

   //Here we do all the work
   while (it1 != data.end())
   {
      sublists1.push_back(*it1);
      it1++;
      //put together the odd sublists and put them in the first list
      while (it1 != data.end() && sublists1.back() <= *it1)
      {
         sublists1.push_back(*it1);
         it1++;
      }
      //if the list is at the end, we have nothing else to insert into the 2nd sublist.
      if (it1 == data.end())
         break;

      //Even Sublists goes into the second sublist 
      sublists2.push_back(*it1);
      it1++;
      while (it1 != data.end() && sublists2.back() <= *it1)
      {
         sublists2.push_back(*it1);
         it1++;
      }
   }
   
   //if sublist2 is empty, then data is already sorted.
   if (sublists2.empty())
      return;

   //oterwise, we need to clear data and merge the two sublists.
   else
   {
      data.clear();
      merge(sublists1, sublists2, data);
   }
}

/*************************************************************************
* MERGE
* Merge two lists. Each list has sorted "sublists" inside. This
* function will merge one sublist at a time. Then send it to the split
* function. Repeat until there's nothing to merge together.
**************************************************************************/
template <class T>
void merge(list<T> &list1, list<T> &list2, list<T> &data)
{
   //2 iterators for the 2 lists.
   typename list<T>::iterator it1 = list1.begin();
   typename list<T>::iterator it2 = list2.begin();

   //some booleans for checking if we've reached the 
   //end of a sorted list within our 2 lists.
   bool endofsublist1;
   bool endofsublist2;

   while (it1 != list1.end() || it2 != list2.end())
   {
      //unless we've reached end of
      //a list, then we are at the beginning
      //of a sorted list within the lists.
      if (it1 != list1.end())
      endofsublist1 = false;
      if (it2 != list2.end())
      endofsublist2 = false;

      //to keep the sorted sublists together, we will run until we are at the end of both of them.
      while (!endofsublist2 || !endofsublist1)
      {
         //if we are at the end of sublist two then we will add the rest of list1 to data
         //Otherwise we can't be at the end of list1, can't be at the end of a sublist in list1, 
         //and it1 has to be less than it2.
         if(endofsublist2 || (it1 != list1.end() && !endofsublist1 && *it1 <= *it2))
         {
            //pushback whats in list1 and iterate up one.
            data.push_back(*it1);
            it1++;

            //if we've reached the end of list1 or the end of data is bigger than the next item we want to insert
            //then we've reached the endofsublist1.
            if (it1 == list1.end() || data.back() > *it1)
               endofsublist1 = true;
         }

         //same as above but opposite since we are working with the other list.
         else if(endofsublist1 || (it2 != list2.end() && !endofsublist2 && *it2 < *it1))
         {
            data.push_back(*it2);
            it2++;
            if (it2 == list2.end() || data.back() > *it2)
               endofsublist2 = true;
         }
      }

   }
   
   //now that we have merged the two lists into one, repeat mergeSort
   //it will repeat until data is sorted.
   mergeSort(data);


}
