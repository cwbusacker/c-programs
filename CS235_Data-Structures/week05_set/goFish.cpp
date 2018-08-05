/***********************************************************************
* Program:
*    Assignment 01, Go Fish
*    Brother Helfrich, CS 235
* Author:
*    <your names here>
* Summary: 
*    This is all the functions necessary to play Go Fish!
*
*    Estimated:  0.0 hrs   
*    Actual:     0.0 hrs
*      Please describe briefly what was the most difficult part.
************************************************************************/

#include <iostream>
#include <string>
#include <iomanip>
#include "set.h"
#include "card.h"
#include "goFish.h"
#include <fstream>
using namespace std;

#define ROUNDS 5
/**********************************************************************
 * GO FISH
 * The function which starts it all
 ***********************************************************************/
void goFish()
{
   int location;
   Set<Card> player1;
   Card filereading;
   ifstream fin("/home/cs235e/week05/hand.txt");
   if (fin.fail())
   {
      cout << "Error reading file\n";
   }
   else
   {
      while (fin >> filereading)
      {
         player1.insert(filereading);
      }
      fin.close();
   }
   //The cards we are comparing.
   cin.ignore(256, '\n');
   Card guess;
   int matches = 0;
   cout << "We will play 5 rounds of Go Fish.  Guess the card in the hand" << endl;
   for (int i = 0; i < ROUNDS; i++)
   {
      cout << "round " << i + 1 << ": ";
      cin >> guess;
      location = player1.find(guess);
      
      if (location >= 0)
      {
         cout << "\tYou got a match!" << endl;
         player1.erase(location);
         matches++;
      }
      else
         cout << "\tGo Fish!" << endl;
   }
   cout << "You have " << matches << " matches!" << endl;
   cout << "The remaining cards: ";
   SetIterator <Card> it;
   for (it = player1.begin(); it != player1.end(); it)
   {
      cout << *it;
      if (++it != player1.end())
         cout << ", ";
      else
         cout << endl;
   }
   return;
}