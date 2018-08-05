/***********************************************************************
 * Module:
 *    Week 02, Stack
 *    Brother Helfrich, CS 235
 * Author:
 *    <your name here>
 * Summary:
 *    This program will implement the testInfixToPostfix()
 *    and testInfixToAssembly() functions
 ************************************************************************/

#include <iostream>    // for ISTREAM and COUT
#include <string>      // for STRING
#include <cassert>     // for ASSERT
#include "stack.h"     // for STACK
#include <sstream>     // for STRINGSTREAM
using namespace std;

/*****************************************************
 * CONVERT INFIX TO POSTFIX
 * Convert infix equation "5 + 2" into postifx "5 2 +"
 *****************************************************/
string convertInfixToPostfix(const string & infix)
{
   string postfix = " ";
   Stack <char> operators;
   int parent = 0;
   for(int i = 0; i < infix.length(); i++)
   {
      try
      {
         switch (infix[i])
         {
         case '(':
            operators.push(infix[i]);
            parent++;
            break;
         case ')':
            if (!operators.empty())
            {
               while (operators.top() != '(')
               {
                  postfix += ' ';
                  postfix += operators.top();
                  operators.pop();
                  
               }
            }
            operators.pop();
            parent--;
            break;
         case '^':
            postfix += ' ';
            operators.push(infix[i]);
            break;
         case '*':
         case '/':
            postfix += ' ';
            if (parent != 0)
            {
               operators.push(infix[i]);
            }
            else if (!operators.empty())
            {
               while (operators.top() == '*' || operators.top() == '/' || operators.top() == '^')
               {
                  if (operators.top() == '^')
                  {
                     postfix += operators.top();
                     operators.pop();
                     postfix += ' ';
                  }
                  else if (operators.top() == '*' || operators.top() == '/')
                  {
                     postfix += operators.top();
                     operators.pop();
                     postfix += ' ';
                  }
               }
               operators.push(infix[i]);
            }
            else
            {
               operators.push(infix[i]);
            }
            break;
         case '+':
         case '-':
            postfix += ' ';
            if (parent != 0)
            {
               operators.push(infix[i]);
            }
            else
            {
               while (!operators.empty())
               {
                  postfix += operators.top();
                  operators.pop();
                  postfix += ' ';
               }
               operators.push(infix[i]);
            }
            
            break;
         case ' ':
            break;
         default:
            postfix += infix[i];
         }
      }
      catch (const char * sError)
      {
         cout << sError << endl;
      }
      
      

   }
   
   for (int i = 0; !operators.empty(); i++)
   {
      postfix += ' ';
      postfix += operators.top();
      operators.pop();
   }
   return postfix;
}

/*****************************************************
 * TEST INFIX TO POSTFIX
 * Prompt the user for infix text and display the
 * equivalent postfix expression
 *****************************************************/
void testInfixToPostfix()
{
   string input;
   cout << "Enter an infix equation.  Type \"quit\" when done.\n";
   
   do
   {
      // handle errors
      if (cin.fail())
      {
         cin.clear();
         cin.ignore(256, '\n');
      }
      
      // prompt for infix
      cout << "infix > ";
      getline(cin, input);

      // generate postfix
      if (input != "quit")
      {
         string postfix = convertInfixToPostfix(input);
         cout << "\tpostfix: " << postfix << endl << endl;
      }
   }
   while (input != "quit");
}

/**********************************************
 * CONVERT POSTFIX TO ASSEMBLY
 * Convert postfix "5 2 +" to assembly:
 *     LOAD 5
 *     ADD 2
 *     STORE VALUE1
 **********************************************/
string convertPostfixToAssembly(const string & postfix)
{
   string assembly;

   return assembly;
}

/*****************************************************
 * TEST INFIX TO ASSEMBLY
 * Prompt the user for infix text and display the
 * resulting assembly instructions
 *****************************************************/
void testInfixToAssembly()
{
   string input;
   cout << "Enter an infix equation.  Type \"quit\" when done.\n";

   do
   {
      // handle errors
      if (cin.fail())
      {
         cin.clear();
         cin.ignore(256, '\n');
      }
      
      // prompt for infix
      cout << "infix > ";
      getline(cin, input);
      
      // generate postfix
      if (input != "quit")
      {
         string postfix = convertInfixToPostfix(input);
         cout << convertPostfixToAssembly(postfix);
      }
   }
   while (input != "quit");
      
}
