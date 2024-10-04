// Names: Aarohi Patel and Alyssa Barbee
// CS201 Program 14 - Simulation
// Date: 4/27/24

#include "Function.h"

int main()
{
  //seed random number generator
  //DECLARE linked list object and integer to initialize IDs
	srand(time(0));
  Linked masterList;
  int ListID = 100;

  //OPEN output file and check that it's opened
  ofstream outFile;
  outFile.open("output.txt");
  if (!outFile.is_open()){
    cout << "Output file could not be opened. Exiting the program.\n";
    return 1;
  }

  //DECLARE integer to get the number of lines 
  //  and DISPLAY this information
  int lines = getLines();
	outFile << "Here is your data for " << lines << " checkout lines:\n\n";

  //DECLARE vector of queues
	vector<Queue> allQueues;
	//creating the number of checkout lines (queues) the user wants to test
	for (int k = 0; k < lines; ++k){
		Queue tempQueue;
		tempQueue.masterData.queueNumber = k + 1;
		tempQueue.masterData.queueCount = 0;
		tempQueue.masterData.totalIdleTime = 0;
		tempQueue.masterData.totalOverTime = 0;
		tempQueue.masterData.maxQueueLength = 0;
    
		allQueues.push_back(tempQueue);
	}

  for (int i = 0; i < 721; ++i) {
    //variable for how many people come in at a time
    int inAtThisTime = ((rand() % 3) + 1); 
    for (int j = 0; j < inAtThisTime; ++j) {
            masterList.addElement(createCustomer(ListID, i));
            ListID++;
    }
    //check if anyone needs to be moved from the store to the checkout line
    masterList.storeToQueue(i, allQueues);
    //have people leave the checkout line as they leave and add up idle time
    for (int a = 0; a < allQueues.size(); ++a) {
      if (!allQueues[a].queueEmpty())
        allQueues[a].leaveQueue(i);
    }
  }
  
	//take care of any people still in the store after the store closes (for loop is done)
  int time = 721;
  while (!masterList.listIsEmpty()) {	
    masterList.storeToQueue(time, allQueues);
    for (int a = 0; a < allQueues.size(); ++a){
      allQueues[a].leaveQueue(time);
    }
    time++;
  }

  //DISPLY queues to output file
	for (int b = 0; b < allQueues.size(); ++b){
		allQueues[b].printQueue(outFile);
	}
  
  return 0;
}