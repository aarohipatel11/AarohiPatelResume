#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <string>
#include "Linked.h"
#include "Queue.h"
using namespace std;

bool isDigits(string str);
//PRE: Accepts a string
//POST: returns true if all numeric (orspaces), false otherwise

int getLines();
//Pre: Nothing
//Post: will return a valid number of checkout lines, taken from the user

struct listType createCustomer(int id, int currTime);
//Pre: the current cart count and the current time
//Post: Returns a customer with their  card id, the amount of things that they will buy, and the amount of time it will take for them to buy it. 