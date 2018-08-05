###############################################################
# Program:
#     Week 06, NODE
#     Brother Ercanbrack, CS235
# Author:
#     Chase Busacker
# Summary:
#     Node class with some non-member "list" implementations.
#     I was able to finish this assignment earlier this week
#     because I was a lot more on top of all homework.
# Time Clock:
# Clock-in			|	Clock-out		|	Time	|	TOTAL	|
# 2.12.18 10:30		|	2.12.18 10:50	|	0:20	|	0:20	|
# 2.12.18 14:51		|	2.12.18 15:57	|	0:06	|	0:26	|
# 2.14.18 13:29		|	2.14.18 14:30	|	1:01	|	1:27	|
# 2.14.18 17:44		|	2.14.18 20:50	|	2:17	|	3:44	|
# 2.15.18 10:12		|	2.15.18 12:48	|	2:36	|	6:20	|
# 2.15.18 1:50		|	2.15.18 3:05	|	1:15	|	7:35	|
###############################################################

##############################################################
# The main rule
##############################################################
a.out: node.h week06.o 
	g++ -o a.out week06.o  -g
	tar -cf week06.tar *.h *.cpp makefile

##############################################################
# The individual components
#      week06.o      : the driver program
#      <anything else?>
##############################################################
week06.o: node.h week06.cpp sortInsertion.h
	g++ -c week06.cpp -g
