###############################################################
# Program:
#     Week 04, DEQUE
#     Brother Ercanbrack, CS235
# Author:
#     Chase Busacker
# Summary:
#     The deque is the double-ended queue. Now serving will
#     use the deque in order to give students with "emergencies"
#     to go after the person that is currently being served.
# Time:
#     This program took about 4 hours to complete.
###############################################################

##############################################################
# The main rule
##############################################################
a.out: deque.h week04.o nowServing.o
	g++ -o a.out week04.o nowServing.o
	tar -cf week04.tar *.h *.cpp makefile

##############################################################
# The individual components
#      week04.o       : the driver program
#      nowServing.o   : the logic for the now serving program
##############################################################
week04.o: deque.h week04.cpp
	g++ -c week04.cpp

nowServing.o: nowServing.h nowServing.cpp deque.h
	g++ -c nowServing.cpp
