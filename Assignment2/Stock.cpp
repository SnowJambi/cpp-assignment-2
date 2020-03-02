#include "Stock.h"
#include "Functions.h"
using namespace std;

Stock::Stock(string inTitle, string inSurname, string inIsbn, double inWholesalePrice, char inBookFormat, int inStockLevel) :Product(inTitle, inSurname, inIsbn, inWholesalePrice)
{
	retailPrice = calcRetailPrice(inWholesalePrice, inBookFormat);
	bookFormat = inBookFormat;
	stockLevel = inStockLevel;
}

Stock::Stock()
{
	bookFormat = NULL;
	retailPrice = NULL;
	stockLevel = NULL;
}

Stock::~Stock()
{

}

// Useful for debugging
void Stock::print()
{
	cout << getTitle() << " " 
		 << getSurname() << " " 
		 << getIsbn() << " " 
		 << getWholesalePrice() << " " 
		 << bookFormat << " " 
		 << stockLevel << " " 
		 << retailPrice << endl;
}