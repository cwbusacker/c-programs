/***********************************************************************
* Header:
*    Stack
* Summary:
*    This is what a stack class might look like in the Standard Template
*    Library.
* Author
*    Chase Busacker
************************************************************************/
#ifndef STACK_H
#define STACK_H

#include <cassert>

template <class T>
class Stack
{
private:
   int cap;
   int numItems;
   T * data;
public:
   /*****************************************************
   * Default Constructor
   *****************************************************/
   Stack() : numItems(0), cap(0), data(NULL) {}

   Stack(int capacity);

   Stack(const Stack & rhs) throw (const char *);

   ~Stack();

   Stack<T> & operator = (const Stack<T> & rhs);
   /*****************************************************
   * empty() return if the stack is empty.
   *****************************************************/
   bool empty()   {return numItems == 0;}
   /*****************************************************
   *size() returns the size of the stack.
   *****************************************************/
   int size()     {return numItems;             }
   /*****************************************************
   * capacity() returns the capacity of the stack.
   *****************************************************/
   int capacity() { return cap;                 }\
   /*****************************************************
   * clear() sets the size of the stack to 0.
   *****************************************************/
   void clear()   { numItems = 0;               }
   void push(const T & item) throw (const char *);
   void pop() throw (const char *);
   T & top() throw (const char *);
};

/*****************************************************
* NONDEFAULT CONSTRUCTOR
* Create a stack given a capacity.
*****************************************************/
   template <class T>
   Stack<T>::Stack(int capacity)
   {
      numItems = 0;
      cap = capacity;
      data = new T[cap];
   }

   /*****************************************************
   * COPY CONSTRUCTOR
   * Copies the stack into given a stack parameter.
   *****************************************************/
   template <class T>
   Stack<T>::Stack(const Stack & rhs) throw (const char *)
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

   /*****************************************************
   * DESTRUCTOR-Frees memory
   *****************************************************/
   template<class T>
   Stack<T>::~Stack()
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
   Stack<T> & Stack<T>::operator = (const Stack<T> & rhs)
   {
      // attempt to allocate
      try
      {
         delete[] data;
         data = NULL;
         data = new T[rhs.numItems];
      }
      catch (std::bad_alloc)
      {
         throw "ERROR: Unable to allocate buffer";
      }

      // copy over the capacity and size
      cap = rhs.numItems;
      numItems = rhs.numItems;

      // copy the items over one at a time using the assignment operator
      for (int i = 0; i < numItems; i++)
         data[i] = rhs.data[i];

      return *this;
   }

   /*****************************************************
   * PUSH
   * Push the given item onto the top of the Stack.
   *****************************************************/
   template <class T>
   void Stack<T>::push(const T & item) throw (const char *)
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
            data = tempdata;
            tempdata = NULL;
      }
      data[numItems++] = item;
   }

/*****************************************************
* POP
* Error check, then remove the top item.
*****************************************************/
template <class T>
void Stack<T>::pop() throw (const char *)
{
   if (numItems == 0)
   {
      throw "ERROR: Unable to pop from an empty Stack";
   }
   else
   {
      --numItems;
   }
}

/*****************************************************
* TOP
* Return the top item.
*****************************************************/
template <class T>
T & Stack<T>::top() throw (const char *)
{
   if (numItems != 0)
      return data[numItems - 1];
   else
      throw "ERROR: Unable to reference the element from an empty Stack";

}
   
   

#endif //STACK_H
