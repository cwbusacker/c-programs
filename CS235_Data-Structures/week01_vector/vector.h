/***********************************************************************
* Header:
*    Container
* Summary:
*    This class contains the notion of a container: a bucket to hold
*    data for the user. This is just a starting-point for more advanced
*    constainers such as the vector, set, stack, queue, deque, and map
*    which we will build later this semester.
*
*    This will contain the class definition of:
*        Container         : A class that holds stuff
*        ContainerIterator : An interator through Container
* Author
*    Br. Helfrich
************************************************************************/

#ifndef CONTAINER_H
#define CONTAINER_H

#include <cassert>

// forward declaration for VectorIterator
template <class T>
class VectorIterator;

/************************************************
 * Vector
 * A class that holds stuff
 ***********************************************/
template <class T>
class Vector
{
public:
   // default constructor : empty and kinda useless
   Vector() : numItems(0), cap(0), data(NULL)
   {
      T * data = new T[0];
   }

   // copy constructor : copy it
   Vector(const Vector & rhs) throw (const char *);
   
   // non-default constructor : pre-allocate
   Vector(int capacity) throw (const char *);
   
   // destructor : free everything
   ~Vector()        { if (cap) delete [] data; }
   
   // is the container currently empty
   bool empty() const  { return numItems == 0;         }

   // remove all the items from the vector
   void clear()        { numItems = 0;                 }

   // how many items are currently in the vector?
   int size() const    { return numItems;              }

   // add an item to the container
   void push_back(const T & t) throw (const char *);

   int capacity()      {return cap;                    }

   T & operator [] (int index) throw (const char *);

   T & operator [] (int index) const throw (const char *);
   
   // return an iterator to the beginning of the list
   VectorIterator <T> begin() { return VectorIterator<T>(data); }

   // return an iterator to the end of the list
   VectorIterator <T> end() { return VectorIterator<T>(data + numItems);}

   Vector<T> & operator = (const Vector & rhs);
   
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
class VectorIterator
{
  public:
   // default constructor
  VectorIterator() : p(NULL) {}

   // initialize to direct p to some item
  VectorIterator(T * p) : p(p) {}


   // not equals operator
   bool operator != (const VectorIterator & rhs) const
   {
      return rhs.p != this->p;
   }

   void operator = (const VectorIterator & rhs)
   {
      this->p = rhs.p;
   }

   // dereference operator
   T & operator * ()
   {
      return *p;
   }

   // prefix increment
   VectorIterator <T> & operator ++ ()
   {
      p++;
      return *this;
   }

   // postfix increment
   VectorIterator <T> operator++(int postfix)
   {
      VectorIterator tmp(*this);
      p++;
      return tmp;
   }
   
  private:
   T * p;
};

/*******************************************
 * CONTAINER :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
Vector <T> :: Vector(const Vector <T> & rhs) throw (const char *)
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
      throw "ERROR: Unable to allocate buffer";
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
 * CONTAINER : NON-DEFAULT CONSTRUCTOR
 * Preallocate the container to "capacity"
 **********************************************/
template <class T>
Vector <T> :: Vector(int capacity) throw (const char *)
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

   // initialize the container by calling the default constructor
   for (int i = 0; i < capacity; i++)
      data[i] = T();
}

/***************************************************
 * CONTAINER :: Push_Back
 * Insert an item on the end of the container
 **************************************************/
template <class T>
void Vector <T> ::push_back(const T & t) throw (const char *)
{
   T * tempdata;
   if (numItems == cap)
   { 
      if (cap == 0)
      {
         cap = 1;
      }
      else
      {
         cap = 2 * cap;
      }
   
      try
      {
         tempdata = new T[cap];
      }
      catch (std::bad_alloc)
      {
         throw "ERROR: Unable to Allocate Memory";
      }
      for (int i = 0; i < numItems; i++)
      {
         tempdata[i] = data[i];
      }
      delete[] data;
      data = new T[cap];
      for (int i = 0; i < numItems; i++)
      {
         data[i] = tempdata[i];
      }
      delete[] tempdata;
      data[numItems++] = t;
   }
   else
   {
      data[numItems++] = t;
   }
}
template <class T>
Vector <T> & Vector<T>::operator = (const Vector & rhs)
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
      throw "ERROR: Unable to allocate buffer";
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

   return *this;
}

template <class T>
T & Vector<T> ::operator [] (int index) const throw (const char *)
{
   if (index > numItems)
   {
      throw "ERROR: Invalid index";
   }
   else
   {
      return data[index];
   }

}

template <class T>
T & Vector<T> ::operator [] (int index) throw (const char *)
{
   if (index > numItems)
   {
      throw "ERROR: Invalid index";
   }
   else
   {
      return data[index];
   }

}
#endif // CONTAINER_H

