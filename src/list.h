/**
 * CPSC 441, Assignment 3
 * Glenn Skelton
 * Last modified: November 4, 2018
 *
 * filename: list.h
 */

#include <iostream>
#include "node.h"

#ifndef LIST_H
#define LIST_H

/**
 * Purpose: structure for storing linked list.
 */
class list {
public:
	list();
	virtual ~list();

	int length();
	void print();
	double checkDeparture();
	void add(double arrival, int packetSize, double departure);
	void remove();
	void destroy();

private:
	int size; // size of the current queue
	node *head; // pointer to the first node
};


#endif
