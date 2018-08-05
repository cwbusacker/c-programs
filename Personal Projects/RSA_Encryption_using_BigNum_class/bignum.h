/***********************************************************************
* Program:
*    BIG-NUMBER
************************************************************************/

#ifndef BIG_NUM_H
#define BIG_NUM_H

#include <iostream>
#include <list>
#include <iomanip>
#include <cassert>
#include <vector>
using namespace std;


class BigNum
{
private:
  
  //bool negative;
  //bool isnegative();
public:
  list <unsigned int> num;
  BigNum(const BigNum & copy);
  BigNum(list <unsigned int> num){this->num = num;}
  BigNum(long int number);
  BigNum(){num.push_back(0);}
  bool isDivisible(int divisor);
  long int transformIntoLongInt();

  BigNum & operator = (const BigNum & rhs);
 // BigNum & operator = (const int & rhs);
  friend BigNum operator + (const BigNum & lhs, const BigNum & rhs);
  friend ostream & operator << (ostream & out, BigNum & display);
};
BigNum operator * (const BigNum & lhs, const BigNum & rhs);
long int operator % (BigNum & lhs, long int divisor);
#endif
