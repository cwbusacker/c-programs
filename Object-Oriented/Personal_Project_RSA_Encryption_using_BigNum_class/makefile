#Here is where I make the file since I have classes
#included

a.out: bignum.h RSA.o bignum.o
	g++ -o a.out RSA.o bignum.o
	tar -cf RSA.out bignum.h RSA.cpp makefile

RSA.o: bignum.h RSA.cpp
	g++ -c RSA.cpp
 
bignum.o: bignum.h bignum.cpp
	g++ -c bignum.cpp
