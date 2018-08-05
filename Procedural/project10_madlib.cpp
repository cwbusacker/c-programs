B/***********************************************************************
* Program:
*    Project 10, Mad Libs          
*    Brother Falin, CS124
* Author:
*    Chase Busacker
* Summary: 
*    This is the start of the dumbest program ever, Mad libs project!
*
*    Estimated:  1.0 hrs   
*    Actual:     2.0 hrs
*      Understanding double dimensional arrays. Also, getting the program
*      to read the file properly and send it into the array properly.
************************************************************************/

#include <iostream>
#include <fstream>
using namespace std;

char askPlayAgain();

/**********************************************************************
 * getFilename will request the name of the file from the user.
 ***********************************************************************/
void getFileName(char filename[])
{
   cout << "Please enter the filename of the Mad Lib: ";
   cin >> filename;
}

/**********************************************************************
 * askQuestions will ask questions to the user to get input into the array.
 ***********************************************************************/
void askQuestions(char words[][32], int numwords)
{
   cin.ignore();

   for (int i = 0; i < numwords ; i++)
   {

      if (words[i][0] == '<' && isalpha(words[i][1]))
      {
         cout << "\t" << (char)toupper(words[i][1]);
         for (int j = 2; words [i][j] != '>'; j++)
         {
            if (words[i][j] != '_')
               cout << words[i][j];
            else
               cout << ' ';
         }
         cout << ": ";
         cin.getline(words[i], 32);
         //        for(int k = 0; k < numwords; k++)
         // cerr << words[k] << " ";

      }
   }
}


/**********************************************************************
* readFilename will read the file into an array.
***********************************************************************/
int readFilename(char filename[], char words[][32])
{
   ifstream fin;
   fin.open(filename);
   int i = 0;

   if (fin.fail())
      return -1;
   
   int wordcount = 0;
   
   while (fin >> words[wordcount])
      wordcount++;

   fin.close();

   if (wordcount > 256)
      return -1;

   return wordcount;
}

/**********************************************************************
 * addPunctuation will read the file and change punctuation into the
 * correct format.
 ***********************************************************************/
void addPunctuation(char words[][32], int numwords)

{
   for (int i = 0; i < numwords ; i++)
   {

      if (words[i][0] == '<' && (words[i][1]) == '#' )
      {
         words[i][0] = '\n';
         words [i][1] = '\0';
         words [i][2] = '\0';
      }
      else if (words[i][0] == '<' && (words[i][1]) == '{')
      {
         if (words[i - 1][0] == '\n')
         {
            words [i][0] = '"';
            words [i][1] = '\0';
            words [i][2] = '\0';
         }
         else if (words[i - 1][0] != '\n')
         {
            words [i][0] = ' ';
            words [i][1] = '"';
            words [i][2] = '\0';
         }
      }
      else if (words[i][0] == '<' && (words[i][1]) == '}')
      {
         words [i][0] = '"';
         words[i][1] = '\0';
         words[i][2] = '\0';
      }
      else if (words[i][0] == '<' && (words[i][1]) == '[')
      {
         if (words[i - 1][0] != '\n')
         {
            words [i][0] = ' ';
            words [i][1] = '\'';
            words [i][2] = '\0';
         }
         else if (words[i - 1][0] == '\n')
            
         {
            words[i][0] = '\'';
            words[i][1] = '\0';
            words[i][2] = '\0';
         }

      }
      else if (words[i][0] == '<' && (words[i][1]) == ']')
      {
         words [i][0] = '\'';
         words [i][1] = '\0';
         words [i][2] = '\0';
      }
   }
}

/**********************************************************************
 * Display will display the words and spaces.
 ***********************************************************************/
void Display(char words[][32], int numwords)
{
   for ( int i = 0; i < numwords; i++)
   {
      //These are special cases for spaces where spaces should NOT happen.
      if (i > 0 && isalpha(words[i][0])
          && words[i - 1][0] != '\n'
          && words[i - 1][1] != '"'
          && words[i - 1][1] != '\'' ||(words[i - 1][0] == '"' || words[i - 1][0] == '\''))
               cout << " ";
            
      //for (int j = 0; words[i][j]; j++)
      //{
      cout << words[i];//[j];
         //}

   }
}

/**********************************************************************
 * main will run each function in the correct order and end
 * the program if it file fails.
 ***********************************************************************/
int main()
{
   char playagain = 'y';
   while (playagain == 'y')
   {
      char filename[256];
      getFileName(filename);
      char words [256][32];
      int numwords = readFilename(filename, words);
      if (numwords == -1)
         return 0;
//      Display(words, numwords);
//      cout << endl;
      askQuestions(words, numwords);
      cout << endl;
      addPunctuation(words, numwords);
      Display(words, numwords);
      cout << endl;
      playagain = askPlayAgain();
   }
   cout << "Thank you for playing." << endl;
   return 0;
}

/**********************************************************************
 * askPlayAgain will ask the user if they want to play again. If so return
 * to main a variable that will tell it to play again.
 ***********************************************************************/
char askPlayAgain()
{
   char playagain;
   cout << "Do you want to play again (y/n)? ";
   cin >> playagain;
   return playagain;
}
