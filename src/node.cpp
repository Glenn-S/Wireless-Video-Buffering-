/**
 * CPSC 441, Assignment 3
 * Glenn Skelton
 * Last modified: November 4, 2018
 *
 * filename: node.cpp
 */

#include <iostream>
#include "node.h"
using namespace std;

/* class: node */

/************************* CONSTRUCTOR/DESTRUCTOR *********************/
node::node() : arrival(0.0),  packetSize(0), departure(0.0), next(NULL) {

}

node::node(double start, int size, double end) {
	this->arrival = start;
	this->packetSize = size;
	this->departure = end;
	this->next = NULL;
}

node::~node() {

}

/**************************** NODE METHODS *****************************/

/**
 * Purpose:
 */
string node::toString() {
	return "start: " + to_string(arrival) +
		   ", packet size: " + to_string(packetSize) +
		   ", departure: " + to_string(departure);
}
