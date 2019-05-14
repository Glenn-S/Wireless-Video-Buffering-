# CPSC 441, Assignment 3
# Glenn Skelton
#
# makefile


CC = g++
FLAGS = -Wall -g -std=c++0x
SRC = QoSSimulator.cpp list.cpp node.cpp
OBJ = $(SRC:.cpp=.o)
HDR = $(SRC:.cpp=.h)
MAIN = simulator


all: $(MAIN)

simulator: $(OBJ)
	$(CC) $(FLAGS) $(addprefix artifacts/,$(OBJ)) -o $(MAIN)
	
QoSSimulator.o: $(addprefix src/,QoSSimulator.cpp $(HDR))
	$(CC) $(FLAGS) src/QoSSimulator.cpp -c
	mv $@ ./artifacts

list.o: $(addprefix src/,list.cpp list.h node.h)
	$(CC) $(FLAGS) src/list.cpp -c
	mv $@ ./artifacts

node.o: $(addprefix src/,node.cpp node.h)
	$(CC) $(FLAGS) src/node.cpp -c
	mv $@ ./artifacts

clean:
	$(RM) $(addprefix artifacts/,$(OBJ)) $(MAIN)

.PHONY: 
	clean all