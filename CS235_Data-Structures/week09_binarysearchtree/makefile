###############################################################
# Program:
#     Week 09, Binary Search Tree
#     Brother Ercanbrack, CS235
# Author:
#     Chase Busacker
# Summary:
#     This program is the implementation of the Binary Search Tree.
#     It includes the BST class and BSTIterator class. 
#     It also uses the BST class and BSTIterator to
#     sort an array of items.
# Time:
# Clock in			| Clock out		| Subtotal	| Total
# 3.9.2018 12:06	|3.9.2018 13:59	|	1:53	| 1:53
# 3.9.2018 15:01	|3.9.2018 16:00	|	0:59	| 2:52
###############################################################

##############################################################
# The main rule
##############################################################
a.out: week09.o
	g++ -o a.out week09.o 
	tar -cf week09.tar *.h *.cpp makefile

##############################################################
# The individual components
#      lesson08.o     : the driver program
##############################################################
week09.o: bnode.h bst.h stack.h week09.cpp sortBinary.h
	g++ -c week09.cpp

