/***********************************************************************
* Program:
*    Assignment 10, Hello World
*    Brother Falin, CS124
* Author:
*    Chase Busacker
* Summary: 
*    This program will put "Hello World" on the screen,
*    and will pass style checker.
*
*    Estimated:  0.50 hrs   
*    Actual:     0.80 hrs
*     The most difficult part was making styleChecker agree with everything.
*     I wasn't sure what everything means, but it didn't look important.
*     So, I just decided to turn it in. I'm not sure if any of the styleChecker
*     stuff was important to change. Unsure of how to fix it. Maybe we can go
*     over it in class.
************************************************************************/

#include <iostream>
#include <vector>
#include <string>
using namespace std;


bool isoperator(string test);
/*********************************************************************
 * The function main tells the program where to begin execution.
 * After main the program is told to display "Hello World" and
 * then end the program.
 ***********************************************************************/
int main()
{
   string next= "";
   string fullline;
   vector<string> prefix;
   cout << "Please enter the prefix notation you'd like evaluated:";
   getline(cin, fullline);
   for(int i = 0; i < fullline.size(); i++)
   {
      if(fullline[i] == ' ')
         i++;
      if(!isdigit(fullline[i]))
      {
         next = fullline[i];
         prefix.push_back(next);
         i++;
         next = "";
      }
      else if(isdigit(fullline[i]))
      {
         while(isdigit(fullline[i]))
         {
            next += fullline[i];
            i++;
         }
         prefix.push_back(next);
         next = "";
      }
   }
   /*cout << "Vector: { ";
   for (int i = 0; i < prefix.size(); i++)
      {
         cout << prefix[i];
         cout << " ";
      }
   cout << "}";
   */

   //string nextoperator;
   int num1;
   int num2;
   int newnum;
   for(int i = 0; prefix.size() != 1; i++)
   {
      //cerr << "s:" << prefix.size();


      if(isoperator(prefix[i]) && !isoperator(prefix[i+1]) && !isoperator (prefix[i + 2]))
      {
         num1 = stoi(prefix[i+1]);
         num2 = stoi(prefix[i+2]);
         if(prefix[i] == "+")
         {
            newnum = num1 + num2;
            prefix[i] = to_string(newnum);
            prefix.erase(prefix.begin()+(i+1), prefix.begin()+(i+3));
            i = -1;  
         }
         else if(prefix[i] == "-")
         {
            newnum = num1 - num2;
            prefix[i] = to_string(newnum);
            prefix.erase(prefix.begin()+(i+1), prefix.begin()+(i+3));
            i = -1;
         }
         else if(prefix[i] == "*")
         {
            newnum = num1 * num2;
            prefix[i] = to_string(newnum);
            prefix.erase(prefix.begin()+(i+1), prefix.begin()+(i+3));
            i = -1;
         }
         else if(prefix[i] == "/")
         {
            newnum = num1 / num2;
            prefix[i] = to_string(newnum);
            prefix.erase(prefix.begin()+(i+1), prefix.begin()+(i+3));
            i = -1;
            
         }     
            
      }
   }
   cout << "Result: " << prefix[0];
   
   return 0;
}

bool isoperator(string test)
{
      bool isop;
      if(test == "*" ||test == "/" ||test == "+" ||test == "-" )
         isop = true;
      else
         isop = false;
      return isop;
}
      
