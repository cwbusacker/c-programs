###############################################################
# Program:
#     Week 08, Binary Tree
#     Brother Ercanbrack, CS235
# Author:
#     Chase Busacker
# Summary:
#     This is the Huffman and bNode assignment. The bNode's
#     represent the Binary nodes on a Binary Tree. The Huffman
#     takes a set of letters from a file (along with their
#     freqencies) and put them in a tree that has the easiest
#     access to the most frequent.
# Time:
#	Clock in		|	Clock out		| SubTotal	| Total	|
# 2/28/2018 11:40	| 2/28/2018 12:45	|	1:05	| 1:05	| //Implemented Binary Node Constructors and AddLeft/Right Member Functions
# 3/1/2018	12:03	| 3/1/2018	12:43	|	0:40	| 1:45	| //DeleteBinaryTree Function and the Insertion Operator
# 3/2/2018	18:00	| 3/2/2018	22:00	|	4:00	| 5:45	| //Implemented the HuffmanTree class and figured out how to sort the pairs
# 3/3/2018	08:00	| 3/3/2018	11:30	|	3:30	| 9:15	| //Finished making the Huffman Tree and displaying the char directories.
###############################################################

##############################################################
# The main rule
##############################################################
a.out: week08.o huffman.o 
	g++ -o a.out week08.o huffman.o -g
	tar -cf week08.tar *.h *.cpp makefile

##############################################################
# The individual components
#      week08.o     : the driver program
#      huffman.o      : the logic for the huffman code program
##############################################################
week08.o: bnode.h huffman.h week08.cpp
	g++ -c week08.cpp -g

huffman.o: bnode.h huffman.h huffmanTree.h huffman.cpp
	g++ -c huffman.cpp -g



