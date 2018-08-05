/***********************************************************************
 * Implementation:
 *    FIBONACCI
 * Summary:
 *    This will contain the implementation for fibonacci() as well as any
 *    other function or class implementations you may need
 * Author
 *    <your names here>
 **********************************************************************/

#include <iostream>
#include "fibonacci.h"   // for fibonacci() prototype
#include "list.h"        // for LIST
#include <iomanip>
using namespace std;
List<unsigned int> generateFibonacci(int number);
void display(List<unsigned int> fiboNum);
int getNumberForList();
int getNumberForSingle();
/************************************************
 * FIBONACCI
 * The interactive function allowing the user to
 * display Fibonacci numbers
 ***********************************************/
void fibonacci()
{

   //request the amount of fibonacci numbers to display
   unsigned int number;
   List<unsigned int> fiboList;
   number = getNumberForList();

   //generate the numbers
   for(int  i = 1; i <= number; i++)
   {
      fiboList = generateFibonacci(i);
      display(fiboList);
   }
   number = getNumberForSingle();
   fiboList = generateFibonacci(number);
   display(fiboList);
   
}

/************************************************
* GENERATEFIBONACCI
* This is where most of the work is done.
* An integer is a parameter that tells the function
* which Fibonacci number we are looking for.
* It will then loop to calculate that number.
***********************************************/
List< unsigned int > generateFibonacci(int number)
{
   List <unsigned int> Fibo;
   if (number < 3)
   {
      Fibo.push_back(1);
   }
   else
   {
      number = number - 2;
      List<unsigned int> Fibo1;
      List<unsigned int> Fibo2;
      ListIterator<unsigned int> it1;
      ListIterator<unsigned int> it2;
      int newint = 0;
      Fibo1.push_back(1);
      Fibo2.push_back(1);
      bool addone = 0;
      it2 = Fibo2.rbegin();
      while (number)
      {
         
         for (it1 = Fibo1.rbegin(); it1 != Fibo1.rend() || addone; --it1)
         {
            if (it1 == Fibo1.rend()|| it2 == Fibo2.rend())  //If the nodes that we are looking at is NULL
            {                                               //and we are still going through this list
               Fibo1.push_front(0);                         //then we better give them something to play with
               it1 = Fibo1.begin();                         //otherwise seg fault :(
               Fibo2.push_front(0);
               it2 = Fibo2.begin();
            }
            if (*it2 == 0 && it1 == 0 && addone)
            {
               Fibo.push_front(1); //if both items are zero now, but we still need to addone
               break;              //we do it here and leave the loop.
            }
            if (*it1 + *it2 + addone >= 1000) //if the number in this set is more than one thousand
               Fibo.push_front(*it1 + *it2 - 1000 + addone); //we have to carry the one. (addone is set later)
            else
               Fibo.push_front( *it1 + *it2 + addone); //otherwise just add up all the numbers.
            if (*it1 + *it2 + addone >= 1000)
               addone = true; //adding one next time!
            else
               addone = false; //no need to carry the one.
            it2--;
         }
         Fibo1 = Fibo2;
         Fibo2 = Fibo;
         it2 = Fibo2.rbegin();
         number--;
         if (number != 0)
            Fibo.clear(); //clear Fibo for next time
                          //if this wasn't the last time going through the loop.
                          //we need Fibo to be something new each time.
         
      }
      
   }
   return Fibo;
}

/************************************************
* Display:
* Handle displaying the number found in the List.
***********************************************/
void display(List < unsigned int >  displayList)
{
   
   ListIterator <unsigned int> it;
   cout << "\t";
   for (it = displayList.begin(); it != displayList.end(); it++)
   {
      assert(*it < 1000);
      if (displayList.front() == displayList.back() && it == displayList.begin())
      {
         cout << *it; //If the number is less than 3 digits, just display it.
      }
      else if (it == displayList.begin())
      {
         cout << *it << ","; //if it's the first in the list, we don't want 0 fillers
      }
      else if (it != displayList.rbegin())
      {
         cout << setw(3) << setfill('0') << *it << ","; //0 fillers for numbers in the middle
      }
      else
      {
         cout << setw(3) << setfill('0') << *it; //last number to display.
      }
      
   }
   cout << endl;
}
int getNumberForSingle()
{
   int number;
   // prompt for a single large Fibonacci
   cout << "Which Fibonacci number would you like to display? ";
   cin >> number;
   return number;
}
int getNumberForList()
{
   int number;
   cout << "How many Fibonacci numbers would you like to see? ";
   cin >> number;
   return number;
}

