#pragma once
#include <string>
using namespace std;

class Product {
	string title;
	string surname;
	string isbn;
	double wholesalePrice;

public:
	Product(string, string, string, double);
	Product();
	~Product();
	void setDetails(string, string, string, double);
	string getTitle();
	string getSurname();
	string getIsbn();
	double getWholesalePrice();
};
