#include "Queue.h"

//RETURN true if the queue is empty, false otherwise
bool Queue::queueEmpty() {
    return (front == nullptr);
}

//constructor
Queue::Queue() {
	front = nullptr;
	rear = nullptr;
}

//destructor
Queue::~Queue() {
    while (!queueEmpty()) {
        deQueue();
    }
}

//ADD the queueNodeData item to the end of the queue
void Queue::enQueue(queueNodeData d) {
    //create node
    queueNode* newNode = new queueNode;
    newNode->data = d;
    newNode->nextPtr = nullptr;
    //IF empty - add to empty list
    if (queueEmpty()) {
        front = newNode;
        rear = newNode;
    }
    //ADD to end of list
    else {
      rear->nextPtr = newNode;
      rear = newNode;
    }
    //UPDATE struct members
    this->masterData.peopleHelped++;
    this->masterData.queueCount++;
    this->masterData.totalItems += d.itemCount;
    if (this->masterData.maxQueueLength < this->masterData.queueCount)
      this->masterData.maxQueueLength = this->masterData.queueCount;
}

//REMOVE a queueNodeData item from the front of the queue
queueNodeData Queue::deQueue() {
    queueNodeData tempData;
    this->masterData.queueCount--;
    //IF queue is not empty
    //REMOVE 'headPtr' element
    if (!queueEmpty()) { 
      queueNode* tempNode = front; 
      tempData = front->data;
      front = front->nextPtr;
      //IF queue is now empty - reset tailPtr
      if (queueEmpty()) { 
          rear = nullptr;
      }
      delete tempNode;
      tempNode = nullptr;
    }
  return tempData;
}


//RETURN the contents of the front of the queue (but do not remove)
queueNodeData Queue::peek() {
  queueNodeData tempData;
  if (!queueEmpty()) { 
    tempData = front->data;
  }
  return tempData;
}

//DISPLAY queue
void Queue::printQueue(ofstream& outFile) {
  outFile << "CHECKOUT LINE: \t" << this->masterData.queueNumber << endl;
  outFile << "\t" << left << setw(26) << "Total Customers Helped:" 
          << this->masterData.peopleHelped << endl;
  outFile << "\t" << left << setw(26) << "Total Number of Items:" 
          << this->masterData.totalItems << endl;
  outFile << "\t" << left << setw(26) << "Max Line Length:" 
          << this->masterData.maxQueueLength << endl;
  outFile << "\t" << left << setw(26) << "Total Idle Time:" 
          << this->masterData.totalIdleTime << endl;
  outFile << "\t" << left << setw(26) << "Total Over Time:" 
          << this->masterData.totalOverTime << endl;
  outFile << endl << endl; 
}

//sees who needs to leave the queue and updates the queue
void Queue::leaveQueue(int time) {
 if (this->peek().timeAvailable <= time) {
    this->deQueue();  
    if (this->masterData.queueCount > this->masterData.maxQueueLength)
      this->masterData.maxQueueLength = this->masterData.queueCount;
 }
 if (this->masterData.queueCount == 0)
    this->masterData.totalIdleTime++;
}