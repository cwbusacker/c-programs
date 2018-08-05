###############################################################
# Program:
#     Week 01, Vector
#     Brother Ercanbrack, CS235
# Author:
#     Chase Busacker
# Summary:
#     THis is the vector class and it's implementation
# Time:
#     This took me over 6 hours because I couldn't get testBed
#     to work. I also tried to start from scratch when I didn't
#     have to. 
###############################################################

##############################################################
# The main rule
##############################################################
a.out: vector.h week01.o
	g++ -o a.out week01.o 
	tar -cf week01.tar vector.h week01.cpp makefile

##############################################################
# The individual components
#      week01.o     : the driver program
##############################################################
week01.o: vector.h week01.cpp
	g++ -c week01.cpp
