#pragma once
#include "Product.h"
using namespace std;

class Stock :
	public Product
{
public:
	Stock(string, string, string, double, char, int);
	Stock();
	~Stock();
	double retailPrice;
	char bookFormat;
	int stockLevel;
	void print();
};

