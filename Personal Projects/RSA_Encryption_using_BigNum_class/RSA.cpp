/***********************************************************************

************************************************************************/

#include <iostream>
#include <stdlib.h> //Need this for rand()
#include <ctime>
#include <string>
#include <cmath>
#include "bignum.h"
using namespace std;

//forward declarations.
unsigned long int modme(long int base, long int exponent, long int modulus);


long int bigMod(long int base, long int exponent, long int modulus)
{
long int tempRemain = 1;
long int tempExp = 1;
long int mult = 1;
while(pow(base, tempExp) < modulus)
{
tempExp++;
}
long int mod1 = modme(base, tempExp, modulus);
mult = exponent /tempExp;
long int mod2 = modme(mod1, mult, modulus);
tempRemain = pow(base, (exponent % tempExp));
return(mod2 * tempRemain) % modulus;
}
unsigned long int modme(long int base, long int exponent, long int modulus)
{

  long int result = 1;
  //cerr << endl << base << " ^ " << exponent << " % " << modulus << " = ";
  while(exponent > 0)
  {
  //cerr << result << endl;
  if(exponent % 2 == 1)
    result = (result * base) % modulus;
    //cerr << "result = (result * base) % modulus = " << result << 
   //  " " << base << endl;
  exponent = exponent >> 1;
  base = (base * base) % modulus;
  }
 //cerr << result << endl;
  return result;
}
long int findPrivateKey(int totient, int publickey)
{

  long int privatekey;
  for(int i = 1; i < totient; i++)
  {
  if(i % 5000 == 0)
  {
 
  if(i == 35000){ cout << " Almost " << flush;}
  else if(i == 40000) {cout << "there " << flush;}
  else{cout << " ." << flush;}
  }
  for(int j = 1; j <= i; j++)
    {
      if(j*totient - i*publickey == 1 )
      {
      cout << endl;
      return totient - i;
      }
    }
  }
  cout << "\nERROR: PUBLIC KEY NOT FOUND\n" << flush;
  return 0;
}  
bool isPrime(BigNum number)
{
//An array of the first 100 primes(no 2 or 5 since they can be calculated faster by checking the ones place.
   long int first100primes[] = 
      {  3,  7,  11,  13,  17,  19,  23,  29,  31,  37,  41,
         43,  47,  53,  59,  61,  67,  71,  73,  79,  83,  89,  97, 101,
         103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167,
         173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239,
         241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313,
         317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397,
         401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467,
         479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569,
         571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643,
         647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733,
         739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823,
         827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911,
         919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997} ;
   int ones = number.num.back();
   if(ones%2 == 0 || ones%5 == 0)
   {
      return false;
   }
   else
   {
      for(int i = 0; i < 168; i++)
      {
         if(number.isDivisible(first100primes[i]))
            return false;
      }
   }
   return true;
}
/*********************************************************************
 * The function main tells the program where to begin execution.
 * After main the program is told to display "Hello World" and
 * then end the program.
 ***********************************************************************/
BigNum generateLargeRandomPrime(int size)
{

   BigNum attempt = rand();
   for(int i = 0; i < rand() % 3 + size; i++)
   {
      attempt.num.push_back(rand() % 1000);
   }
   if(isPrime(attempt))
      return attempt;
   else
      attempt = generateLargeRandomPrime(size);   
}

BigNum computeTotient(BigNum & p, BigNum & q)
{
   BigNum newp = p;
   BigNum newq = q;
   BigNum e;
   newp.num.back() = (p.num.back() - 1);
   newq.num.back() = (q.num.back() - 1);
   e = newp * newq;
   return e;
}

BigNum createPublicKey(BigNum & totient)
{
   BigNum attempt = rand() % 1000;
   for(int i = 0; i < 3; i++)
   {
      attempt.num.push_back(rand() % 1000);
   }
   if(isPrime(attempt) && attempt.num.size() < totient.num.size())
      return attempt;
   else
      attempt = createPublicKey(totient); 
}
void mainints()
{
     cout << endl <<"--------------------------------------------------------------\n";
cout << endl << "Please note that p and q will be a random prime less than 100.\n";
int primes[] ={  31,  37,  41,
         43,  47,  53,  59,  61,  67,  71,  73,  79,  83,  89,  97, 101,
         103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167,
         173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239,
         241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313,
         317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397,
         401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467,
         479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569,
         571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643,
         647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733,
         739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823,
         827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911,
         919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997} ;
         
         
int p = primes[rand() % 158];
int q = primes[rand() % 158];
long int n = p * q;
int e;
int O = (p -1) * (q - 1);
do
{
e = primes[rand() % 158];
}
while(e > O);
  cout << "Please wait, finding the private key";
int d = findPrivateKey(O, e);

cout << "Here are your RSA numbers:\n";
cout << endl << "p = " << p << endl << endl;
cout << "q = " << q << endl << endl;
cout << "n = " << n << endl << endl;
cout << "O = " << O << endl << endl;
cout << "e = " << e << endl << endl;
cout << "d = " << d << endl << endl;
  string m;
  cout << "What message would you like to encrypt? ";
  cin.ignore();
  getline(cin, m);
  vector<long int> c;
  long int temp;
  cout << endl << "Your encrypted message is: ";
  for(int i = 0; i < m.size(); i++)
  {
  temp = bigMod((long int) m[i], e, n);
  c.push_back(temp);
  cout << c[i] << " ";
  }
  cout << endl;
  string newm = "";
  for(int i = 0; i < c.size(); i++)
  {
    //cerr << "integer value " << modme(c[i],e,n) << endl;
    newm += (char)(bigMod(c[i], d, n));
  }
  cout << "Decrypted: " << newm << endl;
  cout << endl << "---------------------------------------------------------------\n";
}

void mainlongs()
{
//declare the variables that we want to keep the whole time.
   long int n = -1;
   long int p;
   long int q;
   while(n < 0)
   {
   BigNum b = generateLargeRandomPrime(0);
   p = b.transformIntoLongInt();
   b = generateLargeRandomPrime(0);
   q = b.transformIntoLongInt();
   n = p * q;
   }
   BigNum b;
   long int O = (p - 1)*(q - 1);
   b = O;
   long int e = createPublicKey(b).transformIntoLongInt();
   cout << endl <<"---------------------------------------------------------------\n" ;
   cout << "Here are your RSA numbers:\n";
cout << endl << "p = " << p << endl << endl;
cout << "q = " << q << endl << endl;
cout << "n = " << n << endl << endl;
cout << "O = " << O << endl << endl;
cout << "e = " << e << endl << endl; 

  string m;
  cout << "What message would you like to encrypt? ";
  cin.ignore();
  getline(cin, m);
  string c = "";
  cout << endl << "Your encrypted message is: ";
  for(int i = 0; i < m.size(); i++)
  {
  cout << bigMod(m[i], e, n) << " ";
  }
  cout << "\n\nDECRYPTING NOT AVAILABLE AT THIS TIME.\n";
  cout << endl << "---------------------------------------------------------------\n";
}
void mainBNs()
{
//declare the variables that we want to keep the whole time.
   BigNum n;
   BigNum e;
   BigNum O;
   {
      int size = 0;
      cout << endl <<"---------------------------------------------------------------\n" 
         << "\nNOTE: The number of digits will be approximate.\n";
     cout << "MAX: 10, MIN: 9\n";
      cout << "How many digits would you like your p and q (large random primes) to have? " ;
      cin >> size;
      if(size > 999)
         size = 999;
      if (size < 3)
         size = 3;
      size = size / 3;

//Generate 2 Large Random 
      BigNum p = generateLargeRandomPrime(size);
      BigNum q = generateLargeRandomPrime(size);
      cout  << endl << "p = " << p << endl << endl;
      cout << "q = " << q << endl <<endl;
      n = p * q;
      cout << "n = " << n << endl << endl;
      O = computeTotient(p, q);
   } //FORCE THINGS OUT OF SCOPE TO SAVE MEMORY! Only need e, n and the totient.
   
   cout << "O = " << O << endl << endl;
   //BigNum Modulus = totient % 1000000000000000;
                              
   e = createPublicKey(O); 
   cout << "e = " << e << endl << endl;
   /*
   string m;
  cout << "What message would you like to encrypt? ";
  cin.ignore();
  getline(cin, m);
  string c = "";
  BigNum mNum;
  long int mNumLongInt;
  for(int i = 0; i < m.size(); i++)
  {
  mNum = (long int)m[i];
  //mNum = ((mNum^e) % n);
  mNumLongInt = mNum.transformIntoLongInt();
  //cerr <<  "Transform me " << mNumLongInt;
  }*/
cout << "ENCRYPTING AND DECRYPTING NOT AVAILABLE AT THIS TIME.\n";
cout << endl << "---------------------------------------------------------------\n"  ; 
  
}
void maintriv()
{
cout << endl <<"---------------------------------------------------------------\n";
int p = 5;
int q = 11;
int n = p * q;
int O = (p-1)*(q-1);
int e = 7;
int d = findPrivateKey(O, e);
 
 cout << "Here are your RSA numbers:\n";
cout << endl << "p = " << p << endl << endl;
cout << "q = " << q << endl << endl;
cout << "n = " << n << endl << endl;
cout << "O = " << O << endl << endl;
cout << "e = " << e << endl << endl;
cout << "d = " << d << endl << endl;
cin.ignore();
bool valid;
  int temp;
  string m;
   vector<int> c;
  do
  {
  cout << "What message would you like to encrypt? ";
  getline(cin, m);
 
 
  cout << endl << "Your message converted to digits is: ";
  for(int i = 0; i < m.size(); i++)
  {
  if(isalpha(m[i]))
  {
  valid = true;
  m[i] = tolower(m[i]);
  cout << m[i] - 92 << " ";
  }
  else
  {
  cout << "\nPlease try again with no spaces and no symbols.\n";
  valid = false;
  break;
  }
  }
  }
  while(!valid);
  
  cout << endl << endl << "Your message encrypted is: ";
  for(int i = 0; i < m.size(); i++)
  {
  temp = modme((int)m[i] - 92, e, n);
  c.push_back(temp);
  cout << c[i] << " ";
  }
  cout << endl;
  string newm = "";
  for(int i = 0; i < c.size(); i++)
  {
    newm += (char)(modme(c[i], d, n) + 92);
  }
  cout << "\nDecrypted: " << newm << endl;
  cout << endl << "---------------------------------------------------------------\n";
}


int main()
{
 //setup the random system seed.
  srand(time(NULL));
  char choice;
  do
  {
  
  cout << "What data type would you like to use for RSA Encryption?\n";
  cout << "Enter small integers(i), trivial example(e), BigNums(b), long ints(l), or quit(q):";
  cin >> choice;
  if(choice == 'i')
    mainints();
  else if(choice == 'b')
    mainBNs();
  else if(choice == 'l')
    mainlongs();
  else if (choice == 'e')
    maintriv();
  else if(choice != 'q')
    cout << "Invalid Command. Please Try again.\n";
  else
    cout << "Thanks for encrypting!\n";
  cout << endl;
  }
   while(choice != 'q');
   return 0;
}

      
