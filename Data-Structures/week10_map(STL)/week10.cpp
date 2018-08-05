/***********************************************************************
* Module:
*    Week 10, Map(wordCount)
*    Brother Ercanbrack, CS 235
* Author:
*    Chase Busacker
* Summary:
*    This program will count the words in a .txt file using map.
************************************************************************/
#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

string getFilename();
map<string, double> readFilename(string filename, double & numFinds);
string handlePunctuation(string nextWord);
multimap<double, string> sort(map<string, double> words);
void display(multimap<double, string> wordsSorted, double numFinds);


/*****************************************************
* MAIN
* main driver for the program.
****************************************************/
int main()
{
   //Declare the variables we will be using.
   map <string, double > words;              //For the first time the file is read in.
   double numFinds = 0;                      //to count the words we read.
   multimap<double, string> wordsSorted;     //To sort the words by frequency. 

   //go get the filename.
   string fileName = getFilename();

   //if the user quits, end the program.
   
   //read the fileinto words.
   words = readFilename(fileName, numFinds);

   //if the file is empty or the file was not received, end the program.
   if (words.empty())
   {
      return 0;
   }
   //sort words by freqency.
   wordsSorted = sort(words);

   //display the words and frequencies.
 
   display(wordsSorted, numFinds);
   return 0;
}

/*****************************************************
* DISPLAY
* Display the contents of the multimap in order.
****************************************************/
void display(multimap <double, string> sorted, double numFinds)
{
   cout << "Number of words processed: " << numFinds << endl;  //display the number of words processed.
   multimap <double, string> ::reverse_iterator it3;
   int i = 0;

   //Only display 100 most used frequency words unless there are less that 100.
   //if (numFinds > 100)
   //{
      cout << "100 most common words found and their frequencies:" << endl;
      for (it3 = sorted.rbegin(); it3 != sorted.rend() && i < 100; it3++)
      {
         cout << setw(23) << it3->second << " - " << it3->first << endl;
         i++;
      }
      // }

/*   //Display the number of words that exist.
   else
   {
      cout << numFinds << " most common words found and their frequencies:" << endl;
      for (it3 = sorted.rbegin(); it3 != sorted.rend() && i < numFinds; it3++)
      {
         cout << setw(23) << it3->second << " - " << it3->first << endl;
         i++;
      }
 }
*/}

/*****************************************************
* GETFILENAME
* Request the filename fro the user.
****************************************************/
string getFilename()
{
   string filename;
   cout << "Enter filename: ";
   getline(cin, filename);
   return filename;
}

/*****************************************************
* READFILENAME
* read the contents of the file into the first map.
****************************************************/
map<string, double> readFilename(string filename, double & numFinds)
{
   ifstream fin(filename.c_str());
   string nextWord;
   map <string, double > words;
   while (fin.fail())
   {
      cout << "Error - File Failed to Open. Please Try Again." << endl;
      cout << "Enter 'quit' to exit" << endl;
      filename = getFilename();
      fin.open(filename.c_str());
      if (filename == "quit")
         return words;
   }
   cout << endl;
   while (fin >> nextWord)
   {
      numFinds++;
      nextWord = handlePunctuation(nextWord);
      if (words.find(nextWord) == words.end())
      {
         words.insert(pair <string, double>(nextWord, 1));

      }
      else
      {
         map <string, double> ::iterator it1 = words.find(nextWord);
         it1->second += 1;
      }
   }

   fin.close();

   return words;
}

/*****************************************************
* HANDLEPUNCTUATION
* remove unnecessary punctuation(everything but hyphens)
****************************************************/
string handlePunctuation(string nextWord)
{
   for (int i = 0; i != nextWord.size(); i++)
   {
      nextWord[i] = tolower(nextWord[i]);
      if (ispunct(nextWord[i]) && nextWord[i] != '-')
      {
         nextWord.erase(i, 1);
         i--;
      }
   }
   return nextWord;
}

/*****************************************************
* SORT
* convert the words that were read in into a multimap
* that is sorted by frequency.
****************************************************/
multimap<double, string> sort(map<string, double> words)
{
   multimap <double, string> sortedWords;
   map <string, double>::reverse_iterator it;
   for (it = words.rbegin(); it != words.rend(); it++)
      sortedWords.insert(pair< double, string>(it->second, it->first));
   return sortedWords;
}
