#include "Linked.h"
#include "Queue.h"

//RETURN true if the list is empty (headPtr = nullptr?), false otherwise
bool Linked::listIsEmpty() {
	return (headPtr == nullptr);
}

//constructor
Linked::Linked() {
	headPtr = nullptr;
	tailPtr = nullptr;
}

//destructor
Linked::~Linked() {
	if (this->listIsEmpty()) 
		return;
	else {
		Node* tempPtr = headPtr;
		while (headPtr != nullptr) {
			headPtr = headPtr->nextPtr;
			delete tempPtr;
			tempPtr = headPtr;
		}
		tailPtr = nullptr;
		tempPtr = nullptr;
	}
}


//ADD cart information to the list
void Linked::addElement(listType d) {
	Node* tempPtr = new Node;
	tempPtr->data = d;
	tempPtr->nextPtr = nullptr;
  //IF list is empty, UPDATE head and tail
	if (headPtr == nullptr) {
		headPtr = tempPtr;
		tailPtr = tempPtr;
	}
  //checks if new node goes before head
	else if (tempPtr->data.cartId < headPtr->data.cartId) {
		tempPtr->nextPtr = headPtr;
		headPtr = tempPtr;
	}
  //UPDATE POINTERS
	else {
		Node* holdPtr = headPtr;
		while (holdPtr->nextPtr != nullptr && 
           holdPtr->nextPtr->data.cartId 
           < tempPtr->data.cartId) {
			holdPtr = holdPtr->nextPtr;
		}
		tempPtr->nextPtr = holdPtr->nextPtr;
		holdPtr->nextPtr = tempPtr;
		if (tailPtr == holdPtr) {
			tailPtr = tempPtr;
		}
	}
}

//RETURN the contents of the front of the list (but do not remove)
listType Linked::peek() {
	listType tempData = {};
	if (!listIsEmpty()) {
		tempData = headPtr->data;
	}
	return tempData;
}

//REMOVE a node item from the list that matches the cart id
void Linked::delElement(int cartId) {
	Node* tempPtr = headPtr;
	Node* prevPtr = nullptr;
	while (tempPtr != nullptr && tempPtr->data.cartId != cartId) {
		prevPtr = tempPtr;
		tempPtr = tempPtr->nextPtr;
	}
  //cart with the given ID not found
	if (tempPtr == nullptr) {
		return;
	}
  //deleting the head node
	if (prevPtr == nullptr) {
		headPtr = headPtr->nextPtr;
		delete tempPtr;
		if (headPtr == nullptr) {
			tailPtr = nullptr;
		}
	}
	else {
		prevPtr->nextPtr = tempPtr->nextPtr;
		if (tempPtr == tailPtr) {
			tailPtr = prevPtr;
		}
		delete tempPtr;
	}
}

//DISPLAY list
void Linked::printList() {
	Node* tempPtr = headPtr;
	int totalItems = 0;
	while (tempPtr != nullptr) {
		totalItems += tempPtr->data.itemCount;
		tempPtr = tempPtr->nextPtr;
  }
}

//moves people from the list to the queue if their time in the store is over
//sends people from the store to the queue with the smallest queue count
void Linked::storeToQueue(int time, vector<Queue>& allQueues){
	int smallest = allQueues[0].masterData.totalItems;
	int queueNum = allQueues[0].masterData.queueNumber;
	for (int i = 0; i < allQueues.size(); ++i){
		if (allQueues[i].masterData.totalItems <= smallest){
			smallest = allQueues[i].masterData.totalItems;
			queueNum = allQueues[i].masterData.queueNumber;
		}
	}
	
	Node* tempPtr = headPtr;
	while (tempPtr != nullptr) {
		if (tempPtr->data.enterQTime <= time){
			//ADD to queue
			queueNodeData tempNodeData;
			tempNodeData.timeAvailable = (time + ((9 * tempPtr->data.itemCount) / 60));
			tempNodeData.itemCount = tempPtr->data.itemCount;
			for (int j = 0; j < allQueues.size(); ++j){
				if (allQueues[j].masterData.queueNumber == queueNum){
					allQueues[j].enQueue(tempNodeData);
          if (time > 720)
            allQueues[j].masterData.totalOverTime++;
					break;
				}
			}
			delElement(tempPtr->data.cartId);
			//REMOVE from list/store
		}
		tempPtr = tempPtr->nextPtr;
	}
} 
