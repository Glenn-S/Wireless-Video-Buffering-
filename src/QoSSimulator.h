/**
 * CPSC 441, Assignment 3
 * Glenn Skelton
 * Last modified: November 4, 2018
 *
 * filename: QoSSimulator.h
 */

#define STD_BUFFER 100 // buffer size definition for default
#define LINK_IN 100 // link input speed 100 Mbps
#define DEBUG 0 // for debug purposes


#ifndef QOS_SIMULATOR_H
#define QOS_SIMULATOR_H

typedef struct {
	int incoming = 0;
	int delivered = 0;
	int lost = 0;
	float queueDelay = 0.0f;
	int buffer = 0;
	int inputLink = 0;
	int outputLink = 0;
	float avgDelay = 0.0f;
	float loss = 0.0f;
} results;

void networkSimulator(int inputLink,
					  int outputLink,
					  int bufferCapacity,
					  char *filename,
					  results* summary);

void printStatistics(results *summary);

void networkConfig1(char *filename);
void networkConfig2(char *filename);
void networkConfig3(char *filename);
void networkConfig4(char *filename);



#endif
