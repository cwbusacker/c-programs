/***********************************************************************
* Program:
*    Project 04, Monthly Budget          
*    Brother Falin, CS124
* Author:
*    Chase Busacker
* Summary: 
*    This program will give you the monthly budget after requesting the
*    inputs from the user.
*
*    Estimated:  2.0 hrs   
*    Actual:     1.0 hrs
*      The hardest part was realizing that the tax had to be multiplied by
*      twelve before being tested what tax bracket was to be used.
*      
*      
************************************************************************/

#include <iostream>
#include <iomanip>
using namespace std;

/*
 *  getIncome will get the income from the user.
 */
double getIncome()
{
   double income;
   cout << "\tYour monthly income: ";
   cin >> income;

   return (income);
}

/*
 * getBudgetLiving() will get the user's Budgeted living expenses.
 */
double getBudgetLiving()
{ 
   double budgetlivingexpense;
   cout << "\tYour budgeted living expenses: ";
   cin >> budgetlivingexpense;
   return (budgetlivingexpense);
}

/*
 * getActualLiving() will get the actual living
 * expenses the user spent in the month.
 */
double getActualLiving()
{
   double actuallivingexpense;
   cout << "\tYour actual living expenses: ";
   cin >> actuallivingexpense;
   return (actuallivingexpense);
}

/*
 * getActualTax() will get the Actual amount of Tax deducted from
 * user's paycheck.
 */
double getActualTax()
{
   double taxes;
   cout << "\tYour actual taxes withheld: ";
   cin >> taxes;
   return (taxes);
}

/*
 * getActualTithing() will get the user's tithing paid to the church.
 */
double getActualTithing()
{
   double tithe;
   cout << "\tYour actual tithe offerings: ";
   cin >> tithe;
   return (tithe);
}

/*
 * getActualOther() will get the expenses that the user spent 
 */
double getActualOther()
{
   double other;
   cout << "\tYour actual other expenses: ";
   cin >> other;
   return (other);
}

/*
 * computeTithing will take the amount of income the user received and
 * multiply it times 10%.
 */
double computeTithing(double income)
{
   cout.setf(ios::fixed);
   cout.setf(ios::showpoint);
   cout.precision(2);
   
   double budgettithe = income * 0.1;
   return (budgettithe);
}

/*
 * computeyearlyTax will determine how much tax the user must pay
 * per year.
 */
double computeyearlyTax(double income)
{
   double yearlyincome = income * 12;
   
   if (yearlyincome > 0 && yearlyincome < 15100)
      return yearlyincome * 0.1;
   else if (yearlyincome >= 15100 && yearlyincome < 61300)
      return 1510 + 0.15 * (yearlyincome - 15100);
   else if (yearlyincome >= 61300 && yearlyincome < 123700)
      return 8440 + 0.25 * (yearlyincome - 61300);
   else if (yearlyincome >= 123700 && yearlyincome < 188450)
      return 24040 + 0.28 * (yearlyincome - 123700);
   else if (yearlyincome >= 123700 && yearlyincome < 336550)
      return 42170 + 0.33 * (yearlyincome - 188450);
   else if (yearlyincome >= 336550)
      return 91043 + 0.35 * (yearlyincome - 336550);
}

/*
 * computemonthlytax will calculate what is owed each month for taxes
 * by dividing the yearly tax by twelve
 */
double computemonthlytax(double yearlytax)
{
   return yearlytax / 12;
}

/*
 * Display() will take all the information that main received from
 * all the other functions, and it will output them in the form
 * of a chart.
 */
void Display(double income, double budgetlivingexpense, double tax,
             double tithe, double actuallivingexpense, double other,
             double budgettithing, double budgetmonthlytax)
{
   cout.setf(ios::fixed);
   cout.setf(ios::showpoint);
   cout.precision(2);

   float zero = 0.00;
      
   cout << "\nThe following is a report on your monthly expenses\n";

   cout << "\t" << setw(15) << left << "Item";
   cout << setw(7) << left << " ";
   cout << setw(6) << left << "Budget";
   cout << setw(10) << left << " ";
   cout << setw(6) << left << "Actual\n";
      
   cout << "\t=============== =============== ===============\n";

   cout << "\t" << setw(15) << left << "Income";
   cout << setw(2) << right << "$";
   cout << setw(11) << right << income;
   cout << setw(5) << right << "$";
   cout << setw(11) << right << income << endl;

   cout << "\t" << setw(15) << left << "Taxes";
   cout << setw(2) << right << "$";
   cout << setw(11) << right << budgetmonthlytax;
   cout << setw(5) << right << "$";
   cout << setw(11) << right << tax << endl;

   cout << "\t" << setw(15) << left << "Tithing";
   cout << setw(2) << right << "$";
   cout << setw(11) << right << budgettithing;
   cout << setw(5) << right << "$";
   cout << setw(11) << right << tithe << endl;

   cout << "\t" << setw(15) << left << "Living";
   cout << setw(2) << right << "$";
   cout << setw(11) << right << budgetlivingexpense;
   cout << setw(5) << right << "$";
   cout << setw(11) << right << actuallivingexpense << endl;

   cout << "\t" << setw(15) << left << "Other";
   cout << setw(2) << right << "$";
   cout << setw(11) << right << income - (budgettithing + budgetlivingexpense
                                          + budgetmonthlytax);
   cout << setw(5) << right << "$";
   cout << setw(11) << right << other  << endl;

   cout << "\t=============== =============== ===============\n";

   cout << "\t" << setw(15) << left << "Difference";
   cout << setw(2) << right << "$";
   cout << setw(11) << right << zero;
   cout << setw(5) << right << "$";
   cout << setw(11) << right << (income - tax - tithe
                                 - actuallivingexpense - other) << endl;
}

/*
 * Main() will be in charge of calling each function in the right order.
 * and then ask Display() to actually display the information.
 */
int main()
{
   cout << "This program keeps track of your monthly budget\n";
   cout << "Please enter the following:\n";

   double income = getIncome();
   double budgetliving = getBudgetLiving();
   double actualliving = getActualLiving();
   double actualTax = getActualTax();
   double actualTithing = getActualTithing();
   double actualOther = getActualOther();
   double budgettithing = computeTithing(income);
   double budgetyearlytax = computeyearlyTax(income);
   double budgetmonthlytax = computemonthlytax(budgetyearlytax);
   Display(income, budgetliving, actualTax,
           actualTithing, actualliving, actualOther, budgettithing,
           budgetmonthlytax);
   return 0;
}
