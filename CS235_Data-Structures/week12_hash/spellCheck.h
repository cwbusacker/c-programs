/***********************************************************************
 * Module:
 *    Week 12, Spell Check
 *    Brother Helfrich, CS 235
 * Author:
 *    Br. Helfrich
 * Summary:
 *    This program will implement the spellCheck() function
 ************************************************************************/

#ifndef SPELL_CHECK_H
#define SPELL_CHECK_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "hash.h"
using namespace std;


class SHash : public Hash <string>
{
public:
   SHash(int numBuckets)    throw (const char *) : Hash <string>(numBuckets) {}
   SHash(const SHash & rhs) throw (const char *) : Hash <string>(rhs) {}

   // hash function to find the index for each word in the dictionary.
private:
   /*******************************************************
   * HASH
   * This Hash creates a index value for the string that is 
   * passed in. 
   *
   *  It adds together each ASCII value, but weights each
   * letter depending on its location in the word
   *
   * Let n equal the length of the word:
   * Let A[1] equal the ASCII value of the first character. 
   * 19 is a arbitrary prime value.
   *
   * hash = (A[1] + (19*A[2]*1 + 19*A[3]*2 ... 19*A[n]*(n-1)) + A[n]*n) % capacity()
   * 
   * This only gives 144 lists that are size 0 (about 12%)
   * and 16 that are larger than 5. (less than 2%)
   * None are above length 8.
   ************************************************************/
   int hash(const string & word) const
   {

      //start with the first and the last character's characters ASCII value
      int value = word[0] + word.size() * word[word.size() - 1];
      for (int i = 0; i < word.size(); i++)
      {
         //each ASCII value is muliplied times 19*i. This will make every word's value very unique.
         value += word[i] * 19 * i;
      }
      return value % capacity();
   }
};

void getDictionary(vector<string> &dictionary);
void readDictionaryIntoHash(vector<string> &dictionary, SHash &dictHash);
void readFile(vector<string> &wordsToCheck, string Filename);
string getFileName();
void display(vector<string> wordsToCheck, SHash &dictHash);
void spellCheck();

#endif // SPELL_CHECK_H
