###############################################################
# Program:
#     Week 07, LIST
#     Brother Ercanbrack, CS235
# Author:
#     Chase Busacker
# Summary:
#     This is the list implementation as well as a Fibonacci function
#     I did it two ways. First way (found in another file) was to
#     save every Fibonacci and display the whole thing at the end
#     Second way was to generate each number individually and display
#     it after each calculation.
# Time:
#	Clock in		|	Clock out		| SubTotal	| Total	|
# 2/19/2018 19:05	|	2/19/2018 19:40	|	0:35	| 0:35	|
# 2/21/2018 11:30	|	2/21/2018 12:30	|	1:35	| 1:35	|
# 2/22/2018 19:44	|	2/22/2018 22:07	|	2:23	| 3:58	|
# 2/23/2018 11:42	|	2/23/2018 13:48 |	2:06	| 6:04	|
# 2/23/2018 13:45	|	2/23/2018 14:50 |	1:05	| 7:09	|
# 2/23/2018 16:05	|	2/23/2018 16:53	|	0:48	| 7:57	| //all of the above: building list.
# 2/24/2018 22:30	|	2/25/2018 04:01 |	5:31	| 13:28 | //finished fibonacci
# 2/25/2018 13:30	|	2/25/2018 14:07 |	0:37	| 14:04 | //broke fibonacci into functions
# 2/26/2018 08:10	|	2/26/2018 08:30	|	0:20	| 14:24 | //repaired some fibonacci logic flaws
# 2/26/2018 12:15	|	2/26/2018 19:00 |   6:45	| 21:09 | //Started to rewrite the fibonacci function
# 2/26/2018 21:00	|   2/26/2018 22:02 |	0:32	| 22:11	| //I was stroring everything in memory.
##############################################################

##############################################################
# The main rule
##############################################################
a.out: list.h week07.o fibonacci.o
	g++ -o a.out week07.o fibonacci.o
	tar -cf week07.tar *.h *.cpp makefile

##############################################################
# The individual components
#      week07.o       : the driver program
#      fibonacci.o    : the logic for the fibonacci-generating function
#      <anything else?>
##############################################################
week07.o: list.h week07.cpp
	g++ -c week07.cpp

fibonacci.o: fibonacci.h fibonacci.cpp list.h
	g++ -c fibonacci.cpp

