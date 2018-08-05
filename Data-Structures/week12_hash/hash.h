/***********************************************************************
* Module:
*    Week 12, Hash Class
*    Brother Ercanbrack, CS 235
* Author:
*    Chase Busacker
* Summary:
*    This program will implement the hash class.
************************************************************************/
//For spellcheck Hash! add up all the letters
#ifndef HASH_H
#define HASH_H

#include <list>
using namespace std;

template <class T>
class Hash
{
public:
   Hash();
   Hash(int numBuckets) throw (const char *);
   Hash(const Hash<T> & rhs) throw(const char *);
   ~Hash();
   Hash<T> & operator = (const Hash<T> & rhs) throw (const char *);
   bool empty();
   int size() const;
   int capacity() const;
   void clear();
   bool find(T & findMe);
   void insert(T insertMe);
   int virtual hash(const T & findMe) const = 0;
//private:
   list<T> * data;
   int numBuckets;
   int numItems;
};

/*******************************************
* DEFAULT CONSTRUCTOR
* Set the size and capacity to 0 and data to NULL.
******************************************/
template <class T>
Hash<T>::Hash()
{
   numBuckets = 0;
   numItems = 0;
   data = NULL;
}

/*******************************************
* NON-DEFAULT CONSTRUCTOR
* Takes a number of buckets allocates an array that size.
******************************************/
template <class T>
Hash<T>::Hash(int numBuckets) throw (const char *)
{
   this->numBuckets = numBuckets;
   numItems = 0;
   try
   {
      data = new list<T>[numBuckets];
   }
   catch (bad_alloc)
   {
      throw "ERROR: Unable to allocate memory for the hash.";
   }
}

/*******************************************
* COPY CONSTRUCTOR
* Copies the array into an new array.
******************************************/
template <class T>
Hash<T>::Hash(const Hash<T> & rhs) throw(const char *)
{
   try
   {
      data = new list<T>[rhs.capacity()];
   }
   catch(bad_alloc)
   {
      throw "ERROR: Uable to allocate memory for the hash.";
   }
   list<T> listcopy;
   for (int i = 0; i < rhs.capacity(); i++)
   {
      listcopy = rhs.data[i];;
      data[i] = listcopy;
   }
   numItems = rhs.size();
   numBuckets = rhs.capacity();
}

/*******************************************
* DESTRUCTOR
* Frees the Allocated array and resets the
* capacity back to 0.
******************************************/
template <class T>
Hash<T>::~Hash()
{
   clear();

}

/*******************************************
* ASSIGNMENT OPERATOR
* Clears the allocated array of data.
* Reallocates and copies each item in the array.
******************************************/
template <class T>
Hash <T> & Hash<T>::operator = (const Hash<T> & rhs) throw (const char *)
{
   if (numItems > 0)
      clear();
   try
   {
      data = new list<T>[rhs.capacity()];
   }
   catch (bad_alloc)
   {
      throw "ERROR: Unable to allocate memory for the hash.";
   }
   list<T> listcopy;
   for (int i = 0; i < rhs.capacity(); i++)
   {
      listcopy = rhs.data[i];;
      data[i] = listcopy;
   }
   numItems = rhs.numItems;
   numBuckets = rhs.numBuckets;
   return *this;
}
/*******************************************
* EMPTY
* Returns true if the there are no items in the array
* or False if there are.
******************************************/
template <class T>
bool Hash<T>::empty()
{
   return numItems == 0;
}

/*******************************************
* SIZE
* Tells how many items are in the Hash.
******************************************/
template <class T>
int Hash<T>::size() const
{
   return numItems;
}

/*******************************************
* CAPACITY
* Returns the size of the Allocated array.
******************************************/
template <class T>
int Hash<T>::capacity() const
{
   return numBuckets;
}

/*******************************************
* CLEAR
* Frees the data of the array.
******************************************/
template <class T>
void Hash<T>::clear()
{
   for (int i = 0; i < numBuckets; i++)
      data[i].clear();
   if (data)
   {
      delete[] data;
      data = NULL;
   }
   numItems = 0;
   numBuckets = 0;
}

/*******************************************
* FIND
* Finds an item in the Hash. Returns true if
* found, false if not found.
******************************************/
template <class T>
bool Hash<T>::find(T & findMe)
{
   bool found = false;
   typename list<T>:: iterator it = data[hash(findMe)].begin();
   while (it != data[hash(findMe)].end())
   {
      if (*it == findMe)
      {
         found = true;
         break;
      }
      else
         it++;
   }
   return found;
   
}

/*******************************************
* INSERT
* Inserts an item by getting the hash value
* and pushing it back onto the list at the
* hash value index.
******************************************/
template <class T>
void Hash<T>::insert(T insertMe)
{
   data[hash(insertMe)].push_back(insertMe);
   numItems++;
}

#endif // SPELL_CHECK_H
