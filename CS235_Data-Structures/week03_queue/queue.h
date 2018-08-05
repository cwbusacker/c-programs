/***********************************************************************
* Header:
*    Queue
* Summary:
*    This is what a queue class might look like in the Standard Template
*    Library.
* Author
*    Chase Busacker
************************************************************************/
#ifndef QUEUE_H
#define QUEUE_H

#include <cassert>

template <class T>
class Queue
{
private:
   int cap;
   int frontItem;
   int backItem;
   int numItems;
   T * data;
public:
   /*****************************************************
   * Default Constructor
   *****************************************************/
   Queue() : numItems(0), cap(0),  frontItem(0), backItem(0), data(NULL) {}

   Queue(int capacity) throw (const char *);

   Queue(const Queue & rhs) throw (const char *);

   ~Queue();

   Queue<T> & operator = (const Queue<T> & rhs);
   /*****************************************************
   * empty() return if the stack is empty.
   *****************************************************/
   bool empty()   {return numItems == 0;}
   /*****************************************************
   *size() returns the size of the queue.
   *****************************************************/
   int size()     {return numItems;             }
   /*****************************************************
   * capacity() returns the capacity of the queue.
   *****************************************************/
   int capacity() { return cap;                 }
   /*****************************************************
   * clear() sets the size of the stack to 0.
   *****************************************************/
   void clear()   { numItems = 0;               }
   void push(const T & item) throw (const char *);
   void pop() throw (const char *);
   void resize(int newcap) throw (const char *);
   T & front() throw (const char *);
   T & back() throw(const char *);
};

/*****************************************************
* NONDEFAULT CONSTRUCTOR
* Create a stack given a capacity.
*****************************************************/
   template <class T>
   Queue<T>::Queue(int capacity) throw (const char *)
   {
      numItems = 0;
      frontItem = 0;
      backItem = 0;
      cap = capacity;
      
      try
      {
         data = new T[cap];
      }
      catch (std::bad_alloc)
      {
         throw "ERROR: Unable to allocate buffer";
      }
   }

   /*****************************************************
   * COPY CONSTRUCTOR
   * Copies the queue into given a queue parameter.
   *****************************************************/
   template <class T>
   Queue<T>::Queue(const Queue & rhs) throw (const char *)
   {
      assert(rhs.cap >= 0);

      // do nothing if there is nothing to do
      if (rhs.cap == 0)
      {
         cap = numItems = frontItem = backItem = 0;
         data = NULL;
         return;
      }
      
      // attempt to allocate
      try
      {
         this->data = new T[rhs.cap];
      }
      catch (std::bad_alloc)
      {
         throw "ERROR: Unable to allocate buffer";
      }

      // copy over the capacity and size
      assert(rhs.numItems >= 0 && rhs.numItems <= rhs.cap);
      cap = rhs.cap;
      numItems = rhs.numItems;
      frontItem = rhs.frontItem;
      backItem = rhs.backItem;

      // copy the items over one at a time using the assignment operator
      for (int i = 0; i < numItems; i++)
      {
         data[i] = rhs.data[(frontItem + i) % cap];
      }
      frontItem = 0;
      backItem = numItems;
   }

   /*****************************************************
   * DESTRUCTOR-Frees memory
   *****************************************************/
   template<class T>
   Queue<T>::~Queue()
   {
      if (cap)
      {
         delete[] data;
      }
   }

   /*****************************************************
   * Assignment Operator
   * Sets lhs equal to rhs.
   *****************************************************/
   template <class T>
   Queue<T> & Queue<T>::operator = (const Queue<T> & rhs)
   {
      assert(rhs.cap >= 0);

      // do nothing if there is nothing to do
      if (rhs.cap == 0)
      {
         cap = numItems = frontItem = backItem = 0;
         if (data != NULL)
         {
            delete[] data;
         }
         data = NULL;
         return *this;
      }

      // attempt to allocate
      try
      {
         if (data == NULL)
            data = new T[rhs.cap];
         else
         {
            delete[] data;
            data = new T[rhs.cap];
         }
      }
      catch (std::bad_alloc)
      {
         throw "ERROR: Unable to allocate buffer";
      }

      // copy over the capacity and size
      assert(rhs.numItems >= 0 && rhs.numItems <= rhs.cap);
      cap = rhs.cap;
      numItems = rhs.numItems;
      frontItem = rhs.frontItem;
      backItem = rhs.backItem;
      
      // copy the items over one at a time using the assignment operator
      for (int i = 0; i < numItems; i++)
      {
         data[i] = rhs.data[(frontItem + i) % cap];
      }
      frontItem = 0;
      backItem = numItems - 1;
      return *this;
   }
   

   /*****************************************************
   * PUSH
   * Push the given item onto the top of the Queue.
   *****************************************************/
   template <class T>
   void Queue<T>::push(const T & item) throw (const char *)
   {

      //If the data isn't there or is full, then reallocate.
      if (data == NULL || (numItems == cap))
      {
         if (cap == 0)
         {
            resize(1);
         }
         else
         {
            resize(2 * cap);
         }
         //After realloacation, place the next item in the array.
         data[backItem++] = item;


      }
      //The array is NOT full, but backItem has reached the end of the array.
      else if (backItem == cap & frontItem != 0) 
      {
         //So, the new location moves to 0.
         backItem = 0;
         data[backItem++] = item;
         
      }
      else
      {
         //If there are no special cases, just add the item to the array.
         data[backItem++] = item;

      }
      //Another item is added to the array, so numItems increases.
      numItems++;
      
   }

/*****************************************************
* POP
* Error check, then remove the top item.
*****************************************************/
template <class T>
void Queue<T>::pop() throw (const char *)
{
   if (numItems == 0)
   {
      throw "ERROR: attempting to pop from an empty queue";
   }
   else
   {
      //subtract the number of items and add to the frontItem
      //to "eliminate" the space that is being used
      if (frontItem != cap - 1)
      {
         frontItem++;
         numItems--;
      }
      //If the frontItem has reached the end,
      //restart at the beginning.
      else
      {
         frontItem = 0;
         numItems--;
      }
   }
}

/*****************************************************
* FRONT
* Return the Front item.
*****************************************************/
template <class T>
T & Queue<T>::front() throw (const char *)
{
   if (numItems != 0)
      return data[frontItem];
   else
      throw "ERROR: attempting to access an item in an empty queue";

}

/*****************************************************
* BACK
* Return the Back item.
*****************************************************/
template <class T>
T & Queue<T>::back() throw (const char *)
{
   if (numItems != 0)
      return data[backItem - 1];
   else
      throw "ERROR: attempting to access an item in an empty queue";

}
 
/*****************************************************
* RESIZE
* Reallocate the memory to allow for a bigger queue.
*****************************************************/
template <class T>
void Queue<T>::resize(int newcap) throw (const char *)
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
      tempdata[i] = data[(frontItem + i) % cap];
   }
   frontItem = 0;
   backItem = numItems;
   if (data != NULL)
   {
      delete[] data;
      data = NULL;
   }
   data = tempdata;
   tempdata = NULL;
   cap = newcap;
}
   
   
#endif //STACK_H
