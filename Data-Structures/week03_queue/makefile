###############################################################
# Program:
#     Week 03, QUEUE
#     Brother Ercanbrack, CS235
# Author:
#     Chase Busacker
# Summary:
#     This is the Queue feature. Stocks are able to be bought
#     and added to the queue. And then sold and added to a
#     different queue.
# Time:
#     This program took 15 hours to solve. Lots of double free
#     errors to resolve and Segmentation faults. Plus, other
#     issues with the back and frontItem indexes. 
###############################################################

##############################################################
# The main rule
##############################################################
a.out: queue.h week03.o dollars.o stock.o
	g++ -o a.out week03.o dollars.o stock.o
	tar -cf week03.tar *.h *.cpp makefile

dollarsTest: dollars.o dollarsTest.cpp
	g++ -o dollarsTest dollars.o dollarsTest.cpp

##############################################################
# The individual components
#      week03.o       : the driver program
#      dollars.o      : the Dollars class
#      stock.o        : the logic for the stock program
##############################################################
week03.o: queue.h week03.cpp
	g++ -c week03.cpp

dollars.o: dollars.h dollars.cpp
	g++ -c dollars.cpp

stock.o: stock.h stock.cpp queue.h
	g++ -c stock.cpp
