
#include "bignum.h"

BigNum::BigNum(const BigNum & copy)
{
*this = copy;
}
BigNum & BigNum::operator = (const BigNum & rhs)
{
  list<unsigned int> temp = rhs.num;
  num.clear();
  //list<unsigned int> ::iterator it = rhs.num.begin();
  while(!temp.empty())
  {
    num.push_back(temp.front());
    temp.pop_front();
  }
  return *this;
 
}

BigNum::BigNum(long int number)
{
long int copynum = number;
long int insert;
  num.clear();
  int mod = 1000;
  while(copynum != 0)
  {
    insert = copynum % mod;
    num.push_front(insert);
    copynum = copynum - insert;
    copynum = copynum/mod;    
  }
}

bool BigNum::isDivisible(int divisor)
{
  list<unsigned int> temp = num;
  int dividingpart = 0;
  while(!temp.empty())
  {
  dividingpart += temp.front();
  temp.pop_front();
    if(dividingpart > divisor)
    {
    dividingpart = dividingpart % divisor;
    }
    dividingpart *= 1000;
  }
  if(dividingpart == 0)
  { 
  
    return true;
  }
  else
  {
 
    return false;
    }
  
}


BigNum operator + (const BigNum & lhs, const BigNum & rhs)
{
list<unsigned int > left = lhs.num;
list<unsigned int > right = rhs.num;
   BigNum sum;
   sum.num.clear();
  bool addone = false;
  while(!(left.empty()) || !(right.empty()))
         {
           if(right.empty())
           right.push_back(0);
           if(left.empty())
           left.push_back(0);
            if (left.back() + right.back() + addone >= 1000) //if the number in this set is more than one thousand
               {

               sum.num.push_front(left.back() + right.back()- 1000 + addone); //we have to carry the one. (addone is set later)
               }
            else
            {

            sum.num.push_front( left.back() + right.back() + addone); //otherwise just add up all the numbers.
            }
            if (left.back() + right.back() + addone >= 1000)
               addone = true; //adding one next time!
            else
               addone = false; //no need to carry the one.
            left.pop_back();
            right.pop_back();
         }
  return sum;
}


ostream & operator << (ostream & out, BigNum & display)
{

  list<unsigned int>::iterator it = display.num.begin();
  list<unsigned int>::iterator it2 = display.num.begin();
  it2++;
   if (display.num.end() ==  it2 && it == display.num.begin())
      {
       
         out << *it; //If the number is less than 3 digits, just display it.
         it++;
      }
   
   for (it; it != display.num.end(); it++, it2++)
   {
  
      //assert(*it < 1000);
      
      if (it == display.num.begin())
      {
         out << *it << ","; //if it's the first in the list, we don't want 0 fillers
      }
      else if (it2 != display.num.end())
      {
         out << setw(3) << setfill('0') << *it << ","; //0 fillers for numbers in the middle
      }
      else
      {
        
         out << setw(3) << setfill('0') << *it; //last number to display.
      }
      
   }
   return out;
}

BigNum operator * (const BigNum & lhs, const BigNum & rhs) 
{
   vector<BigNum> summation;
   list<unsigned int> temp1 = lhs.num;
   list<unsigned int> temp2 = rhs.num;
   BigNum temp3;
   temp3.num.pop_back();
   BigNum returnme; 
   int temp1back;
   int temppro;
   int carry = 0;
   int multiplier = 0;
   while(!temp1.empty())
   {
      temp1back = temp1.back();
      multiplier += 1;
       for(int m = 1; m < multiplier; m++)
         {
            temp3.num.push_front(0);
        }
      while(!temp2.empty())
      {
        
         
         temppro = temp1back*temp2.back() + carry;

         if(temppro > 1000)
            carry = temppro/1000;
         else
            carry = 0;
 
         temp3.num.push_front(temppro % 1000);
         temp2.pop_back();
      }
      if(carry)
      {

         temp3.num.push_front(carry);
         carry = 0;
      }
      
      summation.push_back(temp3);
      temp3.num.clear();
      temp1.pop_back();
      temp2 = rhs.num;

   }
   
   for(int i = 0; i < summation.size(); i++)
   {

   returnme = summation[i] + returnme;
   }     
   
   return returnme;
}
long int operator % (BigNum & lhs, long int divisor)
{

  list<unsigned int> temp = lhs.num;
  long int dividingpart = 0;
  while(!temp.empty())
  {
  dividingpart += temp.front();
  temp.pop_front();
    if(dividingpart > divisor)
    {
    dividingpart = dividingpart % divisor;
    }
    if(!temp.empty())
      dividingpart *= 1000;
  }
  return dividingpart;
}
long int BigNum::transformIntoLongInt()
{
long int returnme = 0;
   if(num.size() > 10)
      throw "ERROR: Number must be less than 30 digits to transform into a long int.";
      else
      {
         int multiplier = 1;
         list <unsigned int> temp = num;
         while(!temp.empty())
         {
            returnme += temp.back() * multiplier;
            temp.pop_back();
            multiplier *= 1000;
         }
      }
   return returnme;
}
