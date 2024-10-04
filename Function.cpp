#include "Function.h"

// PRE: Accepts a string
// POST: returns true if all numeric (orspaces), false otherwise
bool isDigits(string str) {
  return (str.find_first_not_of("-0123456789 ") == string::npos);
}

//GET number of checkout lines for the grocery store
int getLines() {
  try {
    string lines;
    cout << "Please enter the number of checkout lines: ";
    cin >> lines;
    while ((!isDigits(lines)) || (stoi(lines) <= 0) || (stoi(lines) >= 11)) {
      cout << "Please enter a valid value: ";
      cin >> lines;
    }
    return stoi(lines);
  } 
  catch (invalid_argument &) {
    cout << "Previous number has an invalid stoi argument error\n\n";
    return 1;
  } 
  catch (...) {
    cout << "There was an unexpected error.\n";
    return 1;
  }
}

//CREATE customers and ADD them to the store
listType createCustomer(int id, int currTime) {
  listType tempType;
  int random = ((rand() % 99) + 1);
  if (random <= 100 && random >= 90)
    tempType.itemCount = ((rand() % 30) + 31);
  else if (random >= 70)
    tempType.itemCount = ((rand() % 10) + 21);
  else if (random >= 40)
    tempType.itemCount = ((rand() % 10) + 11);
  else if (random >= 0)
    tempType.itemCount = (rand() % 11);

  tempType.cartId = id;

  int timeInSec = 0;
  for (int i = 0; i < tempType.itemCount; ++i) {
    timeInSec += ((rand() % 31) + 30);
  }
  //make sure to truncate the time and then add it to the listType time
  tempType.enterQTime = (currTime + (timeInSec / 60));
  return tempType;
}