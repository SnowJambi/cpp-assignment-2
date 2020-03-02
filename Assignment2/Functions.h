#pragma once
#include "Stock.h"
#include <iostream>
using namespace std;

bool getAnswer();
Stock addBook();
void outputCatalogue(Stock catalogue[], int numItems);
double calcRetailPrice(double inWholesalePrice, char inBookFormat);