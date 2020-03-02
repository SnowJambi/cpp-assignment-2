#include "Product.h"
using namespace std;

Product::Product(string inTitle, string inSurname, string inIsbn, double inWholesalePrice)
{
	title = inTitle;
	surname = inSurname;
	isbn = inIsbn;
	wholesalePrice = inWholesalePrice;
}

Product::Product()
{
	wholesalePrice = NULL;
}

void Product::setDetails(string inTitle, string inSurname, string inIsbn, double inWholesalePrice)
{
	title = inTitle;
	surname = inSurname;
	isbn = inIsbn;
	wholesalePrice = inWholesalePrice;
}

string Product::getTitle()
{
	return title;
}

string Product::getSurname()
{
	return surname;
}

string Product::getIsbn()
{
	return isbn;
}

double Product::getWholesalePrice()
{
	return wholesalePrice;
}

Product::~Product()
{

}