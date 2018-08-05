#include <iostream>
#include <stdlib.h> //Need this for rand()
#include <ctime>
#include <string>
#include <list>

using namespace std;
 
void buildPolybiusSquare(char square[][5], string key)
{
   string alphabet = "abcdefghi*klmnopqrstuvwxyz";
   string polybius = "";  
   for(int i = 0; i < key.size(); i++)
   {
      if(key[i] != 'j')
      {

         key[i] = tolower(key[i]);
      }
      else
      {
         continue;
      }

      if( key[i] == alphabet[(int)key[i] - 97])
      {
         polybius += key[i];
         alphabet[(int)key[i] - 97] = '*';
       
      }
                                   
   }
   polybius += alphabet;
   int i = 0;
   for(int r = 0; r < 5; r++)
      for(int c = 0; c < 5; c++)
      {
         
         square[c][r] = polybius[i];
         i++;
         while(polybius[i] == '*')
         i++;
      }   
}


void displayPolybiusSquare(char alphabet[][5])
{
 for(int r = 0; r < 5; r++)
   {
      for(int c = 0; c < 5; c++)
      {
         cout << " " << alphabet[c][r] << " "; 
      }
      cout << endl;
   }
}
void find(char alphabet[][5], char findme, int & x, int & y)
{
 for(int r = 0; r < 5; r++)
   {
      for(int c = 0; c < 5; c++)
      {
        if (alphabet[c][r] == findme)
        {
          x = c;
          y = r;
          return;
        }
        
      }
   }
}
string encryptanddisplay(string plain, char alphabet[][5], int key)
{

   string crypted = "";
   int newx, newy, x, y;
   list<int> xs;
   list<int> ys;
   list<int> spaces;
   for(int i = 0; i < plain.size(); i++)
   {
     if(plain[i] == ' ')
     {
     spaces.push_back(i);
     }
     else
     {
     if(plain[i] == 'j')
       plain[i] = 'i';
     find(alphabet, plain[i],x,y);
     xs.push_back(x);
     ys.push_back(y);
     }
   }
  
  
   int counter = 0;
   int counterspace = 0;
   int front = 0;
   list <int> tempxs = xs;
   list <int> tempys = ys;
   list <int> * temp3;
   list <int> * temp2 = &tempys;
   list <int> * temp = &tempxs;
   while(!tempxs.empty() || !tempys.empty())
   {
      //Check Spaces add it if we've reached one.
      if(counterspace == spaces.front())
      {
         crypted += " ";
         spaces.pop_front();
         counterspace++;
      }
      
            
      if((counter % key == 0 && !temp2->empty() && counter != 0) || temp->empty())
      {

         temp3 = temp;
         temp = temp2;
         temp2 = temp3;
      }
      newx = temp->front();
      temp->pop_front();
      counter++;
      
      
      if(counter % key == 0 && !temp2->empty() || temp->empty())
      {

         temp3 = temp;
         temp = temp2;
         temp2 = temp3;
      }
      newy = temp->front();
      temp->pop_front();
      counter++;
      

      crypted += alphabet[newx][newy];
      counterspace++;
   }

   cout << "Your encrypted text: ";
   cout << crypted << endl;

   return crypted;
}
string promptPlainText()
{
   string plain;
   cout << "What message would you like to encrypt using the Bifid Cipher? ";
   getline(cin, plain);
   for(int i = 0; i < plain.size(); i++)
      plain[i] = tolower(plain[i]);
   return plain;
}
void decryptanddisplay(string crypted, char alphabet[][5], int key)
{
   
   list<int> coords;
   list<int> spaces;
   list<int> xs;
   list<int> ys;
   int val1;
   int val2;
   int space = 0;
   int keyit;
   for(int i = 0; i < crypted.size(); i++)
   {
      if(crypted[i] == ' ')
      {
         spaces.push_back(i);
         space++;
      }
      else
      {
      find(alphabet, crypted[i], val1, val2);
      coords.push_back(val1);
      coords.push_back(val2);
      }
   }
   
   cerr << "\nXs: ";
   
   list<int> temp = coords;
   int size;
   while(temp.size() >= 2*key)
   {
      
      for(int j = 0; j < key && !temp.empty(); j++)
      {
        cerr << temp.front() << " ";
         xs.push_back(temp.front());
         temp.pop_front();
      }
      for(int j = 0; j < key && !temp.empty(); j++)
      {
         
         cerr << " POPPING" << temp.front() << " ";
         temp.pop_front();
      }
     
      size = temp.size();
   }

   if(!temp.empty())
      for(int j = 0; j < size/2; j++)
      {
         
             cerr << "Remain" << temp.front() << " ";
         xs.push_back(temp.front());
         temp.pop_front();
      }
   temp = coords;
//   cerr << "\nYs: ";
   while(temp.size() >= 2*key)
   {
      for(int j = 0; j < key && !temp.empty(); j++)
      {
         //       cerr << " POPPING" << temp.front()<< " ";
         temp.pop_front();
      }
      for(int j = 0; j < key && !temp.empty(); j++)
      {
         // cerr << temp.front() << " ";
         ys.push_back(temp.front());
         temp.pop_front();
      }
   }
   size = temp.size();
   if(!temp.empty())
   {
      for(int j = 0; j <= size/2; j++)
      {
         //cerr << "POPPINGbRem" << temp.front() << " ";
         temp.pop_front();
      }
      while(!temp.empty())
      {
         //cerr << "Remain" << temp.front() << " ";
         ys.push_back(temp.front());
         temp.pop_front();             
      }
   }
   
   int spacecounter = 0;
   size = xs.size();
   cout << "Your decrypted message is: ";
   for(int i = 0; i < size; i++)
   {
      //cout << "i = " << i << endl;
          
      if(!spaces.empty() && spacecounter == spaces.front())
            {
         cout << " ";
         spaces.pop_front();
         i--;
      }
      else
      {  //cerr << "{ " << xs.front() << " " << ys.front() << " }"<< endl;
          cout << alphabet[xs.front()][ys.front()];
         xs.pop_front();
         ys.pop_front();
      }
      spacecounter++;
   }
   cout << endl;
}


int main()
{
   int key;
   char alphabet[5][5];
   string keyword;
   cout << "What keyword do you want to use? ";
   cin >> keyword;
   cin.ignore();
   buildPolybiusSquare(alphabet, keyword);
   cout << "Your randomized Polybius square:\n";
   displayPolybiusSquare(alphabet);
   string plain = promptPlainText();
   cout << "What is the desired key size(int)? " ; cin >> key;
   string crypted = encryptanddisplay(plain, alphabet, key);
   decryptanddisplay(crypted, alphabet, key);
  return 0;
 
}
