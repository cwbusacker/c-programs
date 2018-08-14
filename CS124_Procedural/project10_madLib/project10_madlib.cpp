/***********************************************************************
* Program:
*    Project 10, Mad Libs          
*    Brother Falin, CS124
* Author:
*    Chase Busacker
* Summary: 
*    MadLib will read in a file that has colon characters to flag questions
*    and special characters. For example: :! for new line and :adjective 
*    for a question. Then, it will prompt for all the questions and display
*    the file with the new words included and the special characters transformed
*    into the respective characters. After displaying, it will ask the user if
*    he/she wants to play again. Then, loop until the user doesn't want to play
*    anymore.
*
*    Estimated:  1.0 hrs   
*    Actual:     3.0 hrs
*      
************************************************************************/

#include <iostream>
#include <fstream>

#ifdef _WIN32
#include <windows.h>
#endif

#ifdef __linux__
#include <unistd.h>
#endif

using namespace std;

/**********************************************************************
 * getFilename will request the name of the file from the user.
 ***********************************************************************/
void getFileName(char filename[])
{
   cout << "Please enter the filename of the Mad Lib: ";
   cin.getline(filename, 128);
}

/**********************************************************************
 * askQuestions will ask questions to the user to get input into the array.
 ***********************************************************************/
void askQuestions(char words[][32], int numwords)
{
   //loop through the words
   for (int i = 0; i < numwords ; i++)
   {
      //If the word is a question, then it will start with a colon and then an alpha character
      if (words[i][0] == ':' && isalpha(words[i][1]))
      {
         //First letter uppercase.
         cout << "\t" << (char)toupper(words[i][1]);
         for (int j = 2; words [i][j] != 0; j++)
         {
            //Lowercase all other words and transform underscore to a space.
            if (words[i][j] != '_')
               cout << (char)tolower(words[i][j]);
            else
               cout << ' ';
         }
         //Output a colon and then save the word in the place
         //of the question.
         cout << ": ";
         cin.getline(words[i], 32);
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

   //if the file failed. Return to main and use -1 to flag a bad file.
   if (fin.fail())
      return -1;
   
   int wordcount = 0;
   
   while (fin >> words[wordcount])
      wordcount++;

   fin.close();

   //Make sure there are not too many words.
   if (wordcount > 256)
      return -1;

   return wordcount;
}

/**********************************************************************
 * addPunctuation will read the file and change punctuation into the
 * correct format.
 ***********************************************************************/
void handlePunctuation(char words[][32], int wordIndex, int numWords)
{
   //Set the current next and previous word pointers.
   char currentPunct = words[wordIndex][1];
   char * nextWord = words[wordIndex + 1];
   char * prevWord = words[wordIndex - 1];

   //Set a space before the punctuation if it is required.
   if (currentPunct == '<' && prevWord[1] != '!' && prevWord[1] != '>')
   {
      cout << " ";
   }

   //All the special characters to display.
   if (currentPunct == '!')
   {
      cout << endl;
   }
   else if (currentPunct == ',')
   {
      cout << ",";
   }
   else if (currentPunct == '.')
   {
      cout << ".";
   }
   else if (currentPunct == '<' || currentPunct == '>')
   {
      cout << "\"";
   }

   //add a space afterwards
   //if the next word neither a closing quote, end line, or the end of the story
   //and the current punctuation isn't an opening quote or end line.
   if (nextWord[1] != '>' && nextWord[1] != '!' && wordIndex != numWords - 1 
&& currentPunct != '<' && currentPunct != '!')
   {
      cout << " ";
   }
}

/**********************************************************************
 * Display will display the words and spaces.
 ***********************************************************************/
void Display(char words[][32], int numwords)
{
   for ( int i = 0; i < numwords; i++)
   {
      //Handle special punctuation.
      if (words[i][0] == ':')
      {
         handlePunctuation(words, i, numwords);
      }

      //include a space.
      else if(words[i + 1][0] != ':' && i != numwords - 1)
      {
         cout << words[i] << " ";
      }

      //don't include a space
      else
      {
         cout << words[i];
      }

   }
}

/**********************************************************************
* askPlayAgain will ask the user if they want to play again. If so return
* to main a variable that will tell it to play again.
***********************************************************************/
char askPlayAgain()
{
   char playagain;
   do
   {
      cout << "Do you want to play again (y/n)? ";
      cin >> playagain;
      playagain = toupper(playagain);
      switch(playagain)
      {
         case 'Y':
         case 'N': 
            break;
         default:
            cout << "ERROR: Invalid Command\n";
            cout << "Please enter Y for Yes or N for No.\n\n";
            break;
      }
   } while (playagain != 'Y' && playagain != 'N');
   
   return playagain;
}

/**********************************************************************
 * main will run each function in the correct order and end
 * the program if it file fails.
 ***********************************************************************/
int main()
{
   //declare variables.
   char playagain;
   char filename[256];
   char words[256][32];
   int numWords;

   //Loop while the user wants to continue playing.
   do
   {
      //request the Filename and read it
      getFileName(filename);
      numWords = readFilename(filename, words);

      //If the filename was invalid, try again.
      if (numWords == -1)
      {
         cout << "ERROR: Invalid Filename\n";
         cout << "Please Try again.\n";
         playagain = 'Y';
         continue;
      }

      //Run the program by asking for the special words, displaying the words, and asking to play again.
      askQuestions(words, numWords);
      cout << endl;
      Display(words, numWords);
      cout << endl;
      playagain = askPlayAgain();
      cin.ignore();
   }
   while (playagain == 'Y');
   cout << "Thank you for playing." << endl;
   
   //Slow down the computer so it doesn't just quit.
   //And the user can see "Thank you for playing."
   #ifdef __linux__
   usleep(2000000); 
   #endif
   
   #ifdef _WIN32
   Sleep(2000);
   #endif
   
   return 0;
}