/***********************************************************************
 * Implementation:
 *    STOCK
 * Summary:
 *    This will contain the implementation for stocksBuySell() as well
 *    as any other function or class implementation you need
 * Author
 *    <your names here>
 **********************************************************************/

#include <iostream>    // for ISTREAM, OSTREAM, CIN, and COUT
#include <string>      // for STRING
#include <cassert>     // for ASSERT
#include "stock.h"     // for STOCK_TRANSACTION
#include "queue.h"     // for QUEUE
using namespace std;

struct Transaction
{
   int shares;
   Dollars money;
   Dollars profit;
};

Queue<Transaction> buyingTransactions;
Queue<Transaction> sellingTransactions;
void buyStocks();
void sellStocks();
void displayStocks();



/************************************************
 * STOCKS BUY SELL
 * The interactive function allowing the user to
 * buy and sell stocks
 ***********************************************/
void stocksBuySell()
{
   // instructions
   cout << "This program will allow you to buy and sell stocks. "
        << "The actions are:\n";
   cout << "  buy 200 $1.57   - Buy 200 shares at $1.57\n";
   cout << "  sell 150 $2.15  - Sell 150 shares at $2.15\n";
   cout << "  display         - Display your current stock portfolio\n";
   cout << "  quit            - Display a final report and quit the program\n";
   // Run the function based on the instruction.
   string instruction;
   do
   {
      cout << "> ";
      cin >> instruction;


      if (instruction == "buy")
      {
         buyStocks();
      }
      else if (instruction == "sell")
      {
         sellStocks();
      }
      else if (instruction == "display")
      {
         displayStocks();
      }
      else if (instruction != "quit")
      {
         cout << "ERROR: Invalid Instruction! Exiting..." << endl;
         return;
      }
      
   } while (instruction != "quit");
   return;
}
/*****************************************************
* BUYSTOCKS
* Adds a transaction to the buyingTransactions Queue
* based on the parameters sent in by user.
*****************************************************/
void buyStocks()
{
   
   Transaction buy;
   cin >> buy.shares;
   cin >> buy.money;
   buy.profit = 0;
   buyingTransactions.push(buy);
   
}

/*****************************************************
* SELLSTOCK
* Cycles through the buyingTransactions until all
* stocks have been "SOLD" or the user runs out of
* stocks to sell. If the user runs out of stocks to
* sell. Notify the user that there are not enough
* stocks to be sold.
*****************************************************/
void sellStocks()
{
   //Transaction sell is what the user wants to sell
   //and for how much.
   Transaction sell;
   cin >> sell.shares;
   cin >> sell.money;

   //Transaction sold is the information that will
   //be saved in the sellingTransactions Queue.
   Transaction sold;
   sold.money = 0;
   sold.profit = 0;
   sold.shares = 0;
   sold.money = sell.money;

   //Loop through until we have "sold" all that the user
   // requests to sell.
   while (sell.shares != 0)
   {
      //If buyingTransactions is empty,
      //the user cannot sell anything.
      if (buyingTransactions.empty())
      {
         //Notify the user how many stocks he couldn't sell since he ran out.
         cout << "You are out of stocks to sell!" << endl;
         cout << "You were not able to sell " << sell.shares
            << " shares." << endl;
         return;
      }
      else
      {
         //If the amount of shares in the front of the queue doesn't
         //equal zero, the user can sell from that set of stocks.
         if (buyingTransactions.front().shares != 0)
         {
            
            sold.profit = (sold.profit + sell.money - buyingTransactions.front().money);
            //one less share to buy/sell, one more sold.
            buyingTransactions.front().shares -= 1;
            sold.shares += 1;
            sell.shares -= 1;
         }
         //But if the amount of shares is zero, we need to pop it off
         //the queue, save the sold transaction, and start over.
         else if (buyingTransactions.front().shares == 0)
         {
            buyingTransactions.pop();
            sellingTransactions.push(sold);
            sold.profit = 0;
            sold.shares = 0;
         }  
      }
      
   }
   //Once we finish, no matter how many are left
   //we need to add the most recent set of sold transactions
   //to the queue.
      sellingTransactions.push(sold);

      //If there are no more shares in the front buyingTransactions
      //then we don't need it anymore.
      if (buyingTransactions.front().shares == 0)
         buyingTransactions.pop();
   
   
}
void displayStocks()
{
   //Since we only want to display what's in the buyingTransactions
   //we will only use a copy to cout it. Otherwise, we
   //will be manipulating our Transactions when we don't want to.
   Queue<Transaction> displayCopy = buyingTransactions;

   /*****************************************************
   * DISPLAYING STOCKS CURRENTLY HELD HERE ONLY IF WE
   * CURRENTLY OWN SOME STOCK.
   *****************************************************/
   //If the copy isn't empty...
   if (!displayCopy.empty())
   {
      //display this:
      cout << "Currently held:" << endl;

      //Until the copy is empty...
      while (!displayCopy.empty())
      {
         //Display all the shares that we still own.
         cout << "\tBought " << displayCopy.front().shares
            << " shares at " << displayCopy.front().money << endl;
         //Once displayed, we don't need it anymore so pop it!
         displayCopy.pop();
      }
   }
   

   /*****************************************************
   * DISPLAYING SOLD HISTORY IF WE HAVE A SOLD HISTORY.
   *****************************************************/
   displayCopy = sellingTransactions;
   //If our SOLD HISTORY is not empty...
   if (!displayCopy.empty())
   {
      //Display the sold history until it is...
      cout << "Sell History:" << endl;
      while (!displayCopy.empty())
      {
         cout << "\tSold " << displayCopy.front().shares
            << " shares at " << displayCopy.front().money
            << " for a profit of " << displayCopy.front().profit << endl;
         displayCopy.pop(); 
      }
   }

   //ALWAYS DISPLAY TOTAL PROFIT! (EVEN IF IT'S $0.00)
   cout << "Proceeds: ";
      displayCopy = sellingTransactions;
      Dollars totalProfit = 0;

      //Add up all the profits from each set of sold shares
      while (!displayCopy.empty())
      {
         totalProfit += displayCopy.front().profit;
         displayCopy.pop();
      }
      cout << totalProfit << endl;
   
}


