#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

struct queueNodeData {
	int timeAvailable = 0; //clock time when current customer is dequeued
	int itemCount = 0; //the number of items for current customer
};

struct queueNode {
	queueNodeData data; 
	queueNode* nextPtr;
};

struct queueData {
	int queueNumber = 0; //the number of queue that it is (x/5 queues that the user requested)
	int queueCount = 0; //current queue length (set to 0 initially)
	int totalIdleTime = 0; //if queueCount == 0; this is incremented
	int totalOverTime = 0; //increment if current time > 720 & there are people in line
	int maxQueueLength = 0; //if current queueCount>maxQueueLength, reset
	int currItems = 0; //update as customers are added/removed from queue
	int totalItems = 0; //running count of items purchased
	int peopleHelped = 0; //running count of the amount of people helped
};


class Queue {
private:
	queueNode* front;
	queueNode* rear;
	
public:
	Queue(); //constructor
	~Queue(); //destructor
  //ADD the queueNodeData item to the end of the queue
	void enQueue(queueNodeData d); 
  //REMOVE a queueNodeData item from the front of the queue
	queueNodeData deQueue(); 
  //RETURN the contents of the front of the queue (but do not remove)
	queueNodeData peek();
  //RETURN true if the queue is empty, false otherwise
	bool queueEmpty();
  //DISPLAY queue
	void printQueue(ofstream& outFile);
  //master data of the queue/the main stats that will be printed to the output file
	queueData masterData;
  //sees who needs to leave the queue
	void leaveQueue(int time); 
};
