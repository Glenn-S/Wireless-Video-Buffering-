/**
 * CPSC 441, Assignment 3
 * Glenn Skelton
 * Last modified: November 4, 2018
 *
 * filename: node.h
 */

#include <iostream>
using namespace std;

#ifndef NODE_H
#define NODE_H

/**
 * Purpose: structure for storing contents of a linked list node.
 */
class node {
public:

	node();
	node(double arrival, int packetSize, double departure);
	virtual ~node();

	string toString();

	double arrival;
	int packetSize;
	double departure;
	node *next;

private:
};


#endif
