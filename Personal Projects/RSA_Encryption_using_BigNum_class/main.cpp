// Example program
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

// C function for extended Euclidean Algorithm
long int euclidExtended(long int x, long int y)
{
	for (long int b = 1; b < x; b++) {
		for (long int a = 1; a <= b; a++) {
			//cout << "b = "<< b << " Final: " << ((a*x) - (b*y)) << "\n";
			if ((a*x) - (b*y) == 1) { cout << "a = " << a << "\nb = " << b;  return b;}
		}
	}
	return -1;
}

long int modExp(long int base, long int exponent, int modulus)
{
	long int result = 1;
	while (exponent > 0)
	{
		if (exponent % 2 == 1)
			result = (result * base) % modulus;
		exponent = exponent >> 1;
		base = (base * base) % modulus;
	}
	return result;
}

long int RSA(long int message, long int exponent, int publicKey)
{
	long int tempRemain = 1;
	long int tempExp = 1;
	long int mult = 0;
	while (pow(message, tempExp) < publicKey)
	{
		tempExp++;
	}
	long int mod1 = modExp(message, tempExp, publicKey);
	mult = exponent / tempExp;
	long int mod2 = modExp(mod1, mult, publicKey);
	tempRemain = pow(message, (exponent % tempExp));
	return ((mod2 * tempRemain) % publicKey);
}

// Driver Program
int main()
{
	long int O = 6480, e = 31;
	long int finalb = euclidExtended(O, e);
	long int d = (O - finalb);
	//cout << "\nfinal = -" << finalb;
	cout << "\nd = " << d;
	long int finalC = RSA(256, e, 6649);
	cout << "\nEncrypted: " << finalC;
	cout << "\nDecrypted: " << RSA(finalC, d, 6649);
	return 0;
}