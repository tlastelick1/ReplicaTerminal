###########################################################
#
# Makefile for gnuIslandShell
#
###########################################################
default: gnuIslandShell 

gnuIslandShell: gnuIslandShell.o
	g++ gnuIslandShell.o -std=c++11 -o gnuIslandShell
gnuIslandShell.o: gnuIslandShell.cpp
	g++ -std=c++11 gnuIslandShell.cpp  -c 
clean: 
	rm gnuIslandShell.o
	