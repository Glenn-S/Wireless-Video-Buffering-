/**
 * CPSC 441, Assignment 3
 * Glenn Skelton
 * Last modified: November 4, 2018
 *
 * filename: list.cpp
 */

#include <iostream>
#include <stdlib.h>
#include "list.h"
#include "node.h"

using namespace std;

/* class: list */

/************************* CONSTRUCTOR/DESTRUCTOR *********************/
list::list() {
	head = NULL;
	size = 0;
}

list::~list() {
	// destroy all elements within the list
	this->destroy();
	return;
}


/**************************** LIST METHODS *****************************/

/**
 * Purpose: To retrieve the current length of the list.
 */
int list::length() {
	return size;
}

/**
 * Purpose: To print out the current list.
 */
void list::print() {
	int count = 0;
	for (node *p = head; p != NULL; p = p->next) {
		count++;
		cout << p->toString() << endl;
	}
	cout << count << endl;
}

/**
 * Purpose: To retrieve the current departure time of the first element
 * in the list.
 */
double list::checkDeparture() {
	if (head == NULL) return 0.0;
	else return head->departure;
}


/**
 * Purpose: To add a new packet to the end of the list.
 * Side effects: The node added is allocated memory.
 */
void list::add(double arrival, int packetSize, double departure) {
	node *newNode = new node(arrival, packetSize, departure);

	if (newNode == NULL) { // error check for memory allocation
		fprintf(stderr, "Error allocating new node\n");
		exit(EXIT_FAILURE);
	}

	if (head == NULL) { // if list is empty
		head = newNode;
		size++;
	}
	else { // if list is not empty
		for (node *p = head; p != NULL; p = p->next) {
			if (p->next == NULL) {
				p->next = newNode;
				size++;
				break;
			}
		}
	}

	return;
}

/**
 * Purpose: To remove the head of the list.
 * Side effect: memory is freed for the removed node.
 */
void list::remove() {
	if ((head == NULL) && (size == 0)) return; // if list is empty
	else { // if list is not empty
		node *temp = head;
		head = head->next; // remove the head of the list
		delete temp;
		size--;
	}
	return;
}

/**
 * Purpose: To remove all nodes from the list.
 * Side effect: memory for each node is freed.
 */
void list::destroy() {
	while (head != NULL) {
		this->remove();
	}
	return;
}






// no need for other add/remove methods for this particular project
