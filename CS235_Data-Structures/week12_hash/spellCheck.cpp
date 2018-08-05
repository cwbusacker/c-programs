/***********************************************************************
 * Module:
 *    Week 12, Spell Check
 *    Brother Helfrich, CS 235
 * Author:
 *    Chase Busacker
 * Summary:
 *    This program will implement the spellCheck() function which
 *    reads a dictionary file and a user inputted file and finds
 *    any words that are misspelled.
 ************************************************************************/

#include "spellCheck.h"

/*****************************************
 * SPELL CHECK
 * Checks the spelling of words in a file
 * by comparing it to the dictionary.
 ****************************************/
void spellCheck()
{
   //make a vector to store the dictionary.
   vector<string> dictionary;

   //getDictionary will read in the dictionary from the files.
   getDictionary(dictionary);
   
   //I chose to make the half of the amount because it
   //made an ideal amount of lists with 0 in it as well
   //as a minimum size for the lists in each index.
   //144/1161 are empty areas which is about 12%
   //16/1161 have more than 5 items in their lists which is less than 2%
   SHash dictHash(dictionary.size()/2);

   //Transform the vector into the hash
   readDictionaryIntoHash(dictionary, dictHash);

   //get the file the user wants to check for spelling errors.
   string fileName = getFileName();

   //create a vector that will store the words in the file
   vector<string> wordsToCheck;

   //read in the file to the vector.
   readFile(wordsToCheck, fileName);

   //display any words that are misspelled. I also find misspelled words in the display function.
   display(wordsToCheck, dictHash);

   
}

/*****************************************
* READ FILE
* Read the File that was inputted by the
* user and store the words in a vector.
****************************************/
void readFile(vector<string> &wordsToCheck, string fileName)
{
   //open the inputted filename.
   ifstream fin(fileName.c_str());

   //while it doesn't open right, keep trying to open it.
   while (fin.fail())
   {
      cout << "File did not open correctly." << endl;
      cout << "Please enter a file to check?" << endl;
      getline(cin, fileName);
      fin.open(fileName.c_str());
   }

   //read in the file here.
   string nextWord;
   while (fin >> nextWord)
   {
      wordsToCheck.push_back(nextWord);
   }
}

/*****************************************
* DISPLAY
* Checks if any words are misspelled
* and displays them.
****************************************/
void display(vector<string> wordsToCheck, SHash &dictHash)
{
   //Some booleans to tell us what has been found.
   bool Onewordfound = false;
   bool spelledRight = false;
   //We will transform each word to lowercase and store it in lowerWord.
   string lowerWord;
   
   //loop through each word.
   for (int i = 0; i < wordsToCheck.size(); i++)
   {
      //lowerWord is now the next word.
      lowerWord = wordsToCheck[i];

      //Make all the letters lowercase.
         for (int j = 0; j < lowerWord.size(); j++)
            lowerWord[j]= tolower(lowerWord[j]);
      
         //find lowerWord in the dictionaryHash and set spelledRight to true if found.
         spelledRight = dictHash.find(lowerWord);
      
         // if it's not spelled right and one word has not been found yet we need to display the following: 
         if (!spelledRight && !Onewordfound)
      {
            //Misspelled: <FIRSTMISSPELLED WORD>
         cout << "Misspelled: " << wordsToCheck[i];
         //Our first word has been displayed so we sent onewordfound to true.
         Onewordfound = true;
      }
         //Otherwise, we need to display a comma and the word.
      else if (!spelledRight && Onewordfound)
      {
         cout << ", " << wordsToCheck[i];
      }
   }
   //If nothing was found the display the following;
   if (!Onewordfound)
      cout << "File contains no spelling errors" << endl;
   
   //Or move to the new line since we're done with the list of misspelled words.
   else
      cout << endl;
   return;
}

/*****************************************
* GETFILENAME
* Prompt the User for the Filename.
****************************************/
string getFileName()
{
   cin.ignore();
   string filename;
   cout << "What file do you want to check? ";
   getline(cin, filename);
   return filename;
}

/*****************************************
* GET DICTIONARY
* Attempts to find the dictionary file in
* multiple locations. If it's not found in
* either location, Request it from the user.
* Then it reads the dictionary into the
* string vector.
****************************************/
void getDictionary(vector<string> &dictionary)
{
   //First attempt (this location is on my local computer)
   ifstream fin("c:/Users/Chase\ Busacker/Documents/BYUI/Winter\ 2018/CS235/Visual\ Studio\ Files/week12/week12files/dictionary.txt");
   
   //Second attempt (this location is on the Linux Lab
   if (fin.fail())
      fin.open("/home/cs235e/week12/dictionary.txt");
   //Neither one worked. Try again until we get a good dictionary.
   while (fin.fail())
   {
      string dictionaryFile;
      cout << "Dictionary not found at location." << endl;
      cout << "Please put in a new location for the dictionary." << endl;
      getline(cin, dictionaryFile);
      fin.open(dictionaryFile.c_str());
   }

   //read in the dictionary one word at a time.
   string nextWord;
   while (fin >> nextWord)
      dictionary.push_back(nextWord);

   //close the file.
   fin.close();
}

/*********************************************************
* READ DICTIONARY INTO HASH
* The dictionary is originally read into a Vector.
* Read dictionary into hash takes the vector and transforms
* it into a hash.
**********************************************************/
void readDictionaryIntoHash(vector<string> &dictionary, SHash & dictHash)
{
   for (int i = 0; i < dictionary.size(); i++)
   {
      dictHash.insert(dictionary[i]);
   }

   //No longer need the dictionary vector. It's in a hash now.
   //Clear it to save memory space.
   dictionary.clear();
}

