--------------------------------------------------------------------------------
CPSC 441, Assignment 3
Glenn Skelton

--------------------------------------------------------------------------------

This program was developed in a Linux based environment on a Linux Mint operating
system using a g++ compiler.

Contents:

artifacts
	-this is empty unless "make all" is called in which case it is filled
	 with the object code.
src
	list.cpp
	list.h
	node.cpp
	node.h
	QoSSimulator.cpp
	QoSSimulator.h
tests
	soccer.txt
	test.txt
	test1.txt
	test2.txt
Report.txt
Raw Results.txt
Final Results.txt
Assignment 3 Results.pdf (this contains the graphs created)
Makefile


---------------------------------------------------------------------------------
COMPILE/RUN:

If make is enabled on your system type:
	>>make all
	>>./simulator <filename>
	
To remove dependencies after type:
	>>make clean
	
Additionally, each object file can be compiled independently by calling:
	>>make node.o
	>>make list.o
	>>make QoSSimulator.o
	>>make simulator
	
If make is not enabled please type the following:
	>>g++ -std=c++0x -Wall -g src/node.cpp -c
	>>g++ -std=c++0x -Wall -g src/list.cpp -c
	>>g++ -std=c++0x -Wall -g src/QoSSimulator.cpp -c
	>>g++ -std=c++0x -Wall -g *.o -o simulator
	>>./simulator <filename>
	
--------------------------------------------------------------------------------
	
	
	
	
