###############################################################
# Program:
#     Week 11, Sorts
#     Brother Ercanbrack, CS235
# Author:
#	  Chase Busacker
# Summary:
#     This program will complete a heap merge and merge sort 
#     on files filled with intergers.
# Time:
# Clock in		| Clock out		| Subtotal	| total	| 
# 3/13/18 19:42	| 3/13/18 20:42	| 1:00		| 1:00	|	Read in the files.
# 3/18/18 19:40	| 3/18/18 21:43	| 2:03		| 3:03	|	Merge sort (Done recursively)
# 3/21/18 18:30 | 3/21/18 23:30 | 5:00		| 8:03	|   Heap sort and redid the Merge sort so it will do it more efficiently
###############################################################

##############################################################
# The main rule
##############################################################
a.out: week11.o
	g++ -o a.out week11.o 
	tar -cf week11.tar *.h *.cpp makefile

##############################################################
# The individual components
#      week11.o     : the driver program
##############################################################
week11.o: merge.h heap.h week11.cpp
	g++ -c week11.cpp
##############################################################
# Makes clean 
##############################################################
clean:
	rm a.out *.o *.tar
all : a.out
