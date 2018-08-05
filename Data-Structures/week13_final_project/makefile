###############################################################
# Program:
#     Week 13, Geneaology
#     Brother Ercanbrack, CS235
# Author:
#     Chase Busacker
# Summary:
#     Reads a GEDFile from the LDS Church. Finds all individuals
#     in the GEDFile and sorts them by name and birthday.
#     Then puts the individuals in a tree by generation
#     and displays the generations in order.
# Time:
#       This took approximately 10 hours.
##############################################################

##############################################################
# The main rule
##############################################################
a.out: list.h bnode.h week13.o
	g++ -o a.out week13.o
	tar -cf week13.tar *.h *.cpp makefile

##############################################################
# The individual components
#      week13.o       : the driver program
#      <anything else?>
##############################################################
week13.o: list.h bnode.h week13.cpp
	g++ -c week13.cpp
