/***********************************************************************
* Header:
*    Set
* Summary:
*    This class contains the notion of a set. A set can also be found in
*    the standard template library.
*
*    This will contain the class definition of:
*        Set         : A class that holds only one of each item.
*        SetIterator : An interator through Set
* Author
*    Chase Busacker
************************************************************************/

#ifndef SET_H
#define SET_H

#include <cassert>
#include <iostream>
using namespace std;

// forward declaration for SetIterator
template <class T>
class SetIterator;

/************************************************
* SET
* A class that holds only one.
***********************************************/
template <class T>
class Set
{
public:
   // default constructor : empty and useless
   Set() : numItems(0), cap(0), data(NULL) {}

   // copy constructor : copy it
   Set(const Set & rhs) throw (const char *);

   // non-default constructor : pre-allocate
   Set(int capacity) throw (const char *);

   // destructor : free everything
   ~Set() { if (cap) delete[] data; }

   //Assignment Operator
   Set<T> & operator = (const Set & rhs);

   // is the set currently empty?
   bool empty() const { return numItems == 0; }

   // how many items are currently in the set?
   int size() const { return numItems; }

   //returns to number of elements the set can store without realloc.
   int capacity() { return cap; }

   // remove all the items from the set
   void clear() { numItems = 0; }

   // add an item to the Set
   void insert(const T & t) throw (const char *);

   // remove an item from the set
   void erase(int location);

   // returns the integer index of the item
   int find(const T & t);

   void resize(int newcap) throw (const char *);

   void resizeCheck() throw (const char *);

   Set<T> operator && (const Set<T> & rhs);

   Set<T> operator || (const Set<T> & rhs);

   // return an iterator to the beginning of the list
   SetIterator <T> begin() { return SetIterator<T>(data); }

   // return an iterator to the end of the list
   SetIterator <T> end() { return SetIterator<T>(data + numItems); }

 

private:
   T * data;          // dynamically allocated array of T
   int numItems;      // how many items are currently in the Container?
   int cap;           // how many items can I put on the Container before full?
};

/**************************************************
* CONTAINER ITERATOR
* An iterator through Container
*************************************************/
template <class T>
class SetIterator
{
public:
   // default constructor
   SetIterator() : p(NULL) {}

   // initialize to direct p to some item
   SetIterator(T * p) : p(p) {}


   // not equals operator
   bool operator != (const SetIterator & rhs) const
   {
      return rhs.p != this->p;
   }

   void operator = (const SetIterator & rhs)
   {
      this->p = rhs.p;
   }

   // dereference operator
   T & operator * ()
   {
      return *p;
   }

   // prefix increment
   SetIterator <T> & operator ++ ()
   {
      p++;
      return *this;
   }

   // postfix increment
   SetIterator <T> operator++(int postfix)
   {
      SetIterator tmp(*this);
      p++;
      return tmp;
   }

private:
   T * p;
};

/*******************************************
* SET :: COPY CONSTRUCTOR
*******************************************/
template <class T>
Set <T> ::Set(const Set <T> & rhs) throw (const char *)
{
   assert(rhs.cap >= 0);

   // do nothing if there is nothing to do
   if (rhs.cap == 0)
   {
      cap = numItems = 0;
      data = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[rhs.cap];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a new buffer for Set";
   }

   // copy over the capacity and size
   assert(rhs.numItems >= 0 && rhs.numItems <= rhs.cap);
   cap = rhs.cap;
   numItems = rhs.numItems;

   // copy the items over one at a time using the assignment operator
   for (int i = 0; i < numItems; i++)
      data[i] = rhs.data[i];

   // the rest needs to be filled with the default value for T
   for (int i = numItems; i < cap; i++)
      data[i] = T();
}

/**********************************************
* SET : NON-DEFAULT CONSTRUCTOR
* Preallocate the container to "capacity"
**********************************************/
template <class T>
Set <T> ::Set(int capacity) throw (const char *)
{
   assert(capacity >= 0);

   // do nothing if there is nothing to do
   if (capacity == 0)
   {
      this->cap = this->numItems = 0;
      this->data = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[capacity];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }


   // copy over the stuff
   this->cap = capacity;
   this->numItems = 0;
}

/**********************************************
* SET : ASSIGNMENT OPERATOR
* ASSIGNS *this* to the rhs.
**********************************************/
template <class T>
Set <T> & Set<T>::operator = (const Set & rhs)
{
   assert(rhs.cap >= 0);

   // do nothing if there is nothing to do
   if (rhs.cap == 0)
   {
      cap = numItems = 0;
      data = NULL;
      return *this;
   }

   // attempt to allocate
   try
   {
      data = new T[rhs.cap];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate new buffer for Set";
   }

   // copy over the capacity and size
   assert(rhs.numItems >= 0 && rhs.numItems <= rhs.cap);
   cap = rhs.cap;
   numItems = rhs.numItems;

   // copy the items over one at a time using the assignment operator
   for (int i = 0; i < numItems; i++)
      data[i] = rhs.data[i];

   return *this;
}

/**********************************************
* INSERT
* Inserts an item
**********************************************/

template <class T>
void Set<T>::insert(const T & t) throw (const char *)
{

   if (numItems == cap)
   {
      if (cap == 0) { resize(1); }
      else { resize(cap * 2); }
   }
   if (find(t) >= 0)
   {
      return;
   }
   if (numItems == 0 || data[numItems - 1] < t)
      data[numItems++] = t;

   else
   {
      int upLimit = numItems;
      int lowLimit = 0;
      int insertLocation = 0;
      for (int i = numItems / 2; upLimit != lowLimit; i)
      {
         if (data[i] > t)
         {
            upLimit = i;
            i = (upLimit + lowLimit) / 2;
         }
         else if (data[i] < t)
         {
            lowLimit = i + 1;
            i = (upLimit + lowLimit) / 2;
         }
         if (upLimit == lowLimit)
            insertLocation = upLimit;

      }
      //if the loop got all the way to the end without inserting
      for (int i = numItems; i != insertLocation; i--)
      {
         data[i] = data[i - 1];
      }
      data[insertLocation] = t;
      numItems++;
   }
}

template <class T>
void Set<T>::erase(int location)
{
   for (int i = location; i < numItems - 1; i++)
   {
      data[i] = data[i + 1];
   }
   numItems--;
}

template <class T>
int Set<T>::find(const T & t)
{
   int location = -1;
   //-1 means not found.
   int upLimit = numItems - 1;
   int lowLimit = 0;
   int i;
   while (/*i != 0 && i != numItems && */ upLimit >= lowLimit && location < 0)
   {
      i = (upLimit + lowLimit) / 2;
      if (data[i] == t)
      {
         location = i;
      }
      else if (data[i] > t)
      {
         upLimit = i - 1;
      }
      else if (data[i] < t)
      {
         lowLimit = i + 1;
      }
      //i != 0 : We've tested all the way to 0 and the item is still smaller.
      //i != numItems : We've tested all the way to the end of the list and it's still bigger.
      //location < 0: The item has been found!
      //upLimit >= lowLimit: upLimit is smaller than lowLimit? The item is not here!
   }
   return location;
}

template <class T>
Set<T> Set<T>::operator && (const Set<T> & rhs)
{
   Set<T> Intersection;
   int j = 0;
   int i = 0;
   while (i < numItems && j < rhs.numItems)
   {
      Intersection.resizeCheck();
      if (data[i] < rhs.data[j])
         i++;
      else if (data[i] > rhs.data[j])
         j++;
      else if (data[i] == rhs.data[j])
      {
         Intersection.data[Intersection.numItems] = rhs.data[j];
         j++;
         i++;
         Intersection.numItems++;
      }
   }
   return Intersection;
}

template <class T>
Set<T> Set<T>::operator || (const Set<T> & rhs)
{
   Set<T> Union;
   int rhsindex = 0;
   int lhsindex = 0;
   while (lhsindex < numItems || rhsindex < rhs.numItems)
   {
      //The end of the lhs has been reached, just add on the rest of rhs.
      if (lhsindex == numItems)
      {
         while (rhsindex < rhs.numItems)
         {
            Union.resizeCheck();
            Union.data[Union.numItems++] = rhs.data[rhsindex++];
         }
      }
      //The end of rhs has been reached, just add on the rest of lhs.
      else if (rhsindex == rhs.numItems)
      {
         while (lhsindex < numItems)
         {
            Union.resizeCheck();
            Union.data[Union.numItems++] = data[lhsindex++];
         }
      }
      //Add lhs information until the rhs becomes bigger
      else if (data[lhsindex] < rhs.data[rhsindex])
      {
         while (data[lhsindex] < rhs.data[rhsindex] && lhsindex != numItems)
         {
            Union.resizeCheck();
            Union.data[Union.numItems++] = data[lhsindex++];
         }
      }
      //Add rhs information until the lhs becomes bigger.
      else if (data[lhsindex] > rhs.data[rhsindex] ) 
      {
         while (data[lhsindex] > rhs.data[rhsindex] && rhsindex != rhs.numItems)
         {
            Union.resizeCheck();
            Union.data[Union.numItems++] = rhs.data[rhsindex++];
         }
      }
      //If they are equal add it on to the Set and move on to the next 2 comparisons
      else if (data[lhsindex] == rhs.data[rhsindex])
      {
         Union.resizeCheck();
         Union.data[Union.numItems++] = rhs.data[rhsindex++];
         lhsindex++;
      }
      
   }
   return Union;
}

template <class T>
void Set<T>::resize(int newcap) throw (const char *)
{
   T * tempdata;
   try
   {
      tempdata = new T[newcap];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a new buffer for queue";
   }
   //Read items into the array that will be used for data.
   for (int i = 0; i < numItems; i++)
   {
      tempdata[i] = data[i];
   }
   if (data != NULL)
   {
      delete[] data;
      data = NULL;
   }
   data = tempdata;
   cap = newcap;
}
template <class T>
void Set<T>::resizeCheck() throw (const char *)
{
   if (numItems == cap)
   {
      if (cap == 0) { resize(1); }
      else { resize(cap * 2); }
   }
}
#endif //STACK_H
