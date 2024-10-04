#pragma once
#include "Function.h"
#include "Queue.h"

using namespace std;

struct listType {
	int cartId; //unique id assigned for each cart
	int itemCount; //amount of items the customer will get (randomly generated)
	int enterQTime; //current 'time' + shopping time
};

struct Node {
	listType data;
	Node* nextPtr;
};

class Linked {
private:
	Node* headPtr;
	Node* tailPtr;
public:
	Linked(); //constructor
	~Linked(); //destructor
  //ADD cart info to list
	void addElement(listType d); 
  //RETURN the contents of the front of the list (but do not remove)
	listType peek();
  //REMOVE a node item from the front of the list
	void delElement(int cartId); 
  //DISPLAY list
	void printList();
  //RETURN true if the list is empty, false otherwise
	bool listIsEmpty();
  //number of carts currently in the list
	static int listCount;
  //moves people from the list to the queue if their time in the store is over
	void storeToQueue(int time, vector<Queue> &allQueues); 
};