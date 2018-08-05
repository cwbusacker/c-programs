/***********************************************************************
* Program:
*    Week 11, Sorting
*    Brother Ercanbrack, CS 235
*
* Author:
*   Chase Busacker  
* Summary: 
*   This is the heap sort. It treats the vector like a tree and "percolates
*   down" the tree. Then, with the biggest value in front it swaps index 1
*   with the last item that is not sorted., re "percolates down" and repeats
*   the process until the vector is sorted.
*
************************************************************************/
#include <vector>
   
using namespace std;

template <class T> 
void percolateDown(vector<T> &data, int parent, int upperbound, bool isSingle = false);

/*************************************************************************
* This function sorts a vector using a heap sort.
* Input:  data -  Vector to be sorted.
* Output: data -  Vector sorted
**************************************************************************/
template<class T>
void heapSort(vector<T> &data)
{

  //make a heap tree: root is always always the biggest value and the parents are always larger.
  percolateDown(data, data.size()/2, data.size()-1); 
  for (int wall = data.size() - 1; wall != 1; wall--)
  {
     T tempdata = data[1];
     data[1] = data[wall];
     data[wall] = tempdata;
     percolateDown(data, wall / 2, wall);
  }
}


/*************************************************************************
* PERCOLATE DOWN
* When this function is called, it will percolate down everything before
* parent up to the upperbound. It will not change anything with
* the index upperbound or larger.
**************************************************************************/
template<class T>
void percolateDown(vector<T> &data, const int parent, const int upperbound, bool isSingle)
{
   //start maxindex at the parent.
   int maxindex = parent;

   //if the leftchild(parent * 2) is larger and in bounds
   //(no larger than the vector and not outside of upperbound) 
   //set it to maxindex
   if (parent * 2 < data.size() && data[parent] < data[parent * 2] && parent * 2 < upperbound)
      maxindex = parent * 2;
   
   //if the rightchild(parent * 2 + 1) is larger than both 
   //parent and left child and in bounds (no larger than 
   //the vector and not outside of upperbound) 
   //set it to maxindex
   if (parent * 2 + 1 < data.size() && data[maxindex] < data[parent * 2 + 1] && parent * 2 + 1 < upperbound)
      maxindex = parent * 2 + 1;

   //if the parent and maxindex are in the same location
   //then no need to swap
   if (maxindex != parent)
   {
      //swap values so that the parent is the biggest.
      T tempdata = data[parent];
      data[parent] = data[maxindex];
      data[maxindex] = tempdata;

      //percolate down since we edited this trio.
      if (maxindex * 2 < data.size()) //make sure at least one of the children are in bound
         //then check if calling the function is necessary.
         if(data[maxindex] < data[maxindex * 2] || data[maxindex] < data[maxindex * 2 + 1])
      {
         //percolateDown ONLY the children of maxindex.
         percolateDown(data, maxindex, upperbound, true);
      }
   }

   //repeat this function all the way until the root
   //(unless we only needed to change a single Parent's children).
   if (parent > 1 && !isSingle)
      percolateDown(data, parent - 1, upperbound);
}