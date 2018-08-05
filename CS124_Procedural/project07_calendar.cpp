/***********************************************************************
* Program:
*    Project 07, Calendar Project         
*    Brother Falin, CS124
* Author:
*    Chase Busacker
* Summary: 
*    This program will ask the user for a month and year and display the
*    format of days for that month and year.
*
*    Estimated:  2.0 hrs   
*    Actual:     3.5 hrs
*      Getting the loop to work properly with the leap year.
*      Troubleshooting issues with calculating the offset.
************************************************************************/

#include <iostream>
#include <iomanip>
using namespace std;

/**********************************************************************
 * getMonth will get the desired month the user would like to display.
 ***********************************************************************/
int getMonth()
{
   int month = 0;
   
   cout << "Enter a month number: ";
   cin >> month;
   
   while (month < 1 || month > 12)
   {
      cout << "Month must be between 1 and 12.\n";
      cout << "Enter a month number: ";
      cin >> month;
      
   }

   return month;
}

/**********************************************************************
 * getYear will get the desired year the user would like to display.
 ***********************************************************************/
int getYear()
{
   int year = 0;

   cout << "Enter year: ";
   cin >> year;
   
   while (year < 1753 || year > 2100)
   {
      cout << "Year must be 1753 or later.\n";
      cout << "Enter year: ";
      cin >> year;
   }
         
   return year;
}

/**********************************************************************
 * isLeapyear will test if the desired year to display is a leap year
 * or not.
 ***********************************************************************/
bool isLeapyear(int year)
{
   if ((year % 4) != 0)
      return false;
   else if ((year % 100) != 0)
      return true;
   else if ((year % 400) != 0)
      return false;
   else
      return true;
         
}

/**********************************************************************
 * computeOffset will first add all the days of previous years together.
 * This includes determining if a year is a leap year or not and adding
 * either 366 if it is a leap year or 365 if it is a common year. After
 * previous years have been added on to the totaldays, computeOffset
 * will add any previous months in the current year. At the end,
 * computeOffset will modulus the total previous days to determine the
 * Offset.
 ***********************************************************************/
int computeOffset(int month, int year, int isleapyear)
{
   int totaldays = 0;
   int y;
   int yisleapyear = 0;
   
   
   for (int y = 1753; y < year; y++)
   {
      if ((y % 4) != 0)
         yisleapyear = 0;
      else if ((y % 100) != 0)
         yisleapyear = 1;
      else if ((y % 400) != 0)
         yisleapyear = 0;
      else
         yisleapyear = 1;

      if (yisleapyear == 0)
         totaldays += 365;
      else
         totaldays += 366;
      cout << totaldays << endl;
   }

   if (month > 1)
      totaldays += 31;
   if (month > 2 && isleapyear == 1)
      totaldays += 29;
   if (month > 2 && isleapyear == 0) 
      totaldays += 28;
   if (month > 3)
      totaldays += 31;
   if (month > 4)
      totaldays += 30;
   if (month > 5)
      totaldays += 31;
   if (month > 6)
      totaldays += 30;
   if (month > 7)
      totaldays += 31;
   if (month > 8)
      totaldays += 31;
   if (month > 9)
      totaldays += 30;
   if (month > 10)
      totaldays += 31;
   if (month > 11)
      totaldays += 30;

   
   int offset = totaldays % 7;

   return offset;

}

/**********************************************************************
 * computeNumdays will determine the number of days in the desired month.
 ***********************************************************************/
int computeNumDays(int month, int isleapyear)
{
   if (month == 1)
      return 31;
   else if (month == 2 && isleapyear == 1)
      return 29;
   else if (month == 2)
      return 28;
   else if (month == 3)
      return 31;
   else if (month == 4)
      return 30;
   else if (month == 5)
      return 31;
   else if (month == 6)
      return 30;
   else if (month == 7)
      return 31;
   else if (month == 8)
      return 31;
   else if (month == 9)
      return 30;
   else if (month == 10)
      return 31;
   else if (month == 11)
      return 30;
   else if (month == 12)
      return 31;
   else
      return 0;
   
}

/**********************************************************************
 * Display will display the month to the screen in the month format.
 ***********************************************************************/
void Display(int month, int year, int offset, int numdays)
{
   cout << "\n";

   if (month == 1)
      cout << "January, ";
   else if (month == 2)
      cout << "February, ";
   else if (month == 3)
      cout << "March, ";
   else if (month == 4)
      cout << "April, ";
   else if (month == 5)
      cout << "May, ";
   else if (month == 6)
      cout << "June, ";
   else if (month == 7)
      cout << "July, ";
   else if (month == 8)
      cout << "August, ";
   else if (month == 9)
      cout << "September, ";
   else if (month == 10)
      cout << "October, ";
   else if (month == 11)
      cout << "November, ";
   else if (month == 12)
      cout << "December, ";

   cout << year << endl;


   cout << setw(4) << right << "Su";
   cout << setw(4) << right << "Mo";
   cout << setw(4) << right << "Tu";
   cout << setw(4) << right << "We";
   cout << setw(4) << right << "Th";
   cout << setw(4) << right << "Fr";
   cout << setw(4) << right << "Sa" << endl;

   if (offset >=  0 && offset < 6)
      cout << setw(4 + (offset) * 4) << right << "";
   else;

   for (int i = 1; i < numdays; i++)
   {
      cout << setw(4) << right << i;
      if ( ( i + offset + 1) % 7 == 0)
         cout << endl;
 
 
















   }
   cout << setw(4) << numdays << endl;
}

/**********************************************************************
 * main will be in charge of asking for  variables from the
 * different functions. Then it will allow Display to run.
 ***********************************************************************/
int main()
{
   int month = getMonth();
   int year = getYear();
   int isleapyear = isLeapyear(year);
   int numdays = computeNumDays(month, isleapyear);
   int offset = computeOffset(month, year, isleapyear);
   Display(month, year, offset, numdays);
   return 0;
}
