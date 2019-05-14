/**
 * CPSC 441, Assignment 3
 * Glenn Skelton
 * Last modified: November 4, 2018
 *
 * filename: QoSSimulator.cpp
 */

#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "QoSSimulator.h"
#include "list.h"
#include "node.h"

using namespace std;


/**
 * Purpose: To run a network simulation using various configuration models.
 */
int main(int argc, char *argv[]) {
	char *filename;

	if (argc != 2) {
		fprintf(stderr, "./QoSSimulator <filename>\n");
	}
	filename = argv[1];
#if DEBUG
	cout << filename << endl;
#endif

	cout << "Start Simulation" << endl;

	// simulation 1 (generate a graph of the values)
	networkConfig1(filename);
	// simulation 2
	networkConfig2(filename);
	// simulation 3
	networkConfig3(filename);
	// simulation 4
	networkConfig4(filename);


	cout << "Simulation Complete" << endl;
	return 0;
}



/***************************** Network configurations *****************************/

/**
 * Purpose: To test the network configuration using a buffer size of
 * my choice.
 */
void networkConfig1(char *filename) {
	cout << "\n******************************** SIMULATION CASE 1 ******************************" << endl;
	results summary = {};

	// for testing buffer sizes
#if DEBUG
	int testVals[8] = {10, 50, 100, 200, 400, 600, 800, 1000};
	for (unsigned int i = 0; i < sizeof(testVals)/sizeof(testVals[0]); i++) {
		networkSimulator(LINK_IN, 11, testVals[i], filename, &summary);
		printStatistics(&summary);
	}
#endif

	// decided value after analyzing
	networkSimulator(LINK_IN, 11, 200, filename, &summary);
	printStatistics(&summary);
}

/**
 * Purpose: To test the network configuration using a smaller out link bandwidth of
 * 6 Mbps.
 */
void networkConfig2(char *filename) {
	cout << "\n******************************** SIMULATION CASE 2 ******************************" << endl;
	results summary = {};

	networkSimulator(LINK_IN, 6, STD_BUFFER, filename, &summary);
	printStatistics(&summary);
}

/**
 * Purpose: To test the network configuration using a smaller out link bandwidth of
 * 54 Mbps.
 */
void networkConfig3(char *filename) {
	cout << "\n******************************** SIMULATION CASE 3 ******************************" << endl;
	results summary = {};

	networkSimulator(LINK_IN, 54, STD_BUFFER, filename, &summary);
	printStatistics(&summary);
}

/**
 * Purpose: To test the network configuration using a smaller out link bandwidth of
 * 30 Mbps.
 */
void networkConfig4(char *filename) {
	cout << "\n******************************** SIMULATION CASE 4 ******************************" << endl;
	results summary = {};

	networkSimulator(LINK_IN, 30, STD_BUFFER, filename, &summary);
	printStatistics(&summary);
}



/************************* Network Simulation helpers methods ***********************/

/**
 * Purpose: To simulate network traffic for a specified input and output
 * link rate and router access point buffer capacity.
 */
void networkSimulator(int inputLink,
					  int outputLink,
					  int bufferCapacity,
					  char *filename,
					  results *summary) {
	FILE *fp;
	double curTime = 0.0f;
	double arrivalTime = 0.0f, departTime = 0.0f;
	int packetSize, ttlPackets = 0;
	double transDelay = 0.0f, queuingDelay = 0.0f, ttlDelay = 0.0f, delay = 0.0f;
	double prevDeparture = 0.0;
	int pktsLost = 0; // current buffered packets
	int bitRate = outputLink*1000000; // convert mbps to bits per second
	list queue; // buffer queue

	// open the file for input
	if ((fp = fopen(filename, "r")) == NULL) {
		fprintf(stderr, "Error opening file for reading\n");
		exit(EXIT_FAILURE);
	}

	// network packet loop
	while (!feof(fp)) {
		fscanf(fp, "%lf %d\n", &arrivalTime, &packetSize);
		ttlPackets++;
		curTime = arrivalTime;
		transDelay = (double)(packetSize*8)/bitRate; // get the transmission delay

		// check the queue to see if there are any packets that have left
		while ((queue.checkDeparture() < curTime) && (queue.length() > 0)) {
			queue.remove(); // packet has left the queue completely
		}
#if DEBUG
		queue.print();
#endif

		// add to the queue checks
		if (queue.length() == bufferCapacity) {
			pktsLost++; // lost packet
			continue; // go on unless there is other stuff to do
		}
		else if (queue.length() == 0) {
			queuingDelay = 0.0f;
			departTime = curTime + queuingDelay + transDelay;
			delay = departTime - arrivalTime; // calculate the packet delay here as well?
			prevDeparture = departTime;
			queue.add(arrivalTime, packetSize, departTime);
		}
		else if ((queue.length() > 0) && (queue.length() < bufferCapacity)) {
			departTime = prevDeparture + transDelay;
			delay = departTime - arrivalTime; // calculate the packet delay
			prevDeparture = departTime;
			queue.add(arrivalTime, packetSize, departTime);
		}
		else {
			fprintf(stderr, "Error in the queue\n");
			exit(EXIT_FAILURE);
		}
		ttlDelay += delay;
	}
	fclose(fp);

	// if no more packets, make sure to get the rest out of the queue if there are any
	while (queue.length() != 0) {
		queue.remove(); // move out the rest of the packets
	}

	float avgDelay = (float)ttlDelay/(ttlPackets-pktsLost); // calculate average queue delay
	float loss = ((float)pktsLost/ttlPackets) * 100; // calculate packet loss percentage

	summary->incoming = ttlPackets;
	summary->delivered = ttlPackets-pktsLost;
	summary->lost = pktsLost;
	summary->queueDelay = ttlDelay;
	summary->buffer = bufferCapacity;
	summary->inputLink = inputLink;
	summary->outputLink = outputLink;
	summary->avgDelay = avgDelay;
	summary->loss = loss;

	queue.destroy(); // make sure all memory has been destroyed if anything left
}


/**
 * Purpose: To print out the network statistics gathered from the network
 * simulation.
 */
void printStatistics(results *summary) {
	printf("\n---------------------------------------------------------------------------------\n" \
		   "|Buffer: %d pkts\tInput Link: %d Mbps\tOutput Link: %d Mbps\t        |\n" \
		   "---------------------------------------------------------------------------------\n" \
		   "|    incoming   |   delivered   |  packets lost |  packet loss  | avg delay     |\n" \
		   "---------------------------------------------------------------------------------\n" \
		   "|%12d   |%12d   |%12d   |%12.2f%%  |%9.6fs     |\n" \
		   "---------------------------------------------------------------------------------\n\n",
		   summary->buffer,
		   summary->inputLink,
		   summary->outputLink,
		   summary->incoming,
		   summary->delivered,
		   summary->lost,
		   summary->loss,
		   summary->avgDelay);
}




