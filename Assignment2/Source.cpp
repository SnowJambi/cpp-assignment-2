#include "Functions.h"
#include <iostream>
#include <fstream>
#include <vector>
#include "Product.h"
#include "Stock.h"

using namespace std;

void addBook(vector<Stock> catalogue)
{
	string surname;
	string title;
	int stock;
	char format;
	string isbn;
	double price;

	cout << "Please enter the Author's surname: ";
	cin >> surname;

	cout << "Please enter the title: ";
	cin >> title;

	cout << "Please enter the quantity of the product in stock: ";
	cin >> stock;

	cout << "Please enter the book's format from one of the following options -" << endl;
	cout << "a - Audiobook" << endl;
	cout << "e - Ebook" << endl;
	cout << "h - Hardback" << endl;
	cout << "s - Paperback / Softback: ";
	cin >> format;

	cout << "Please enter the isbn: ";
	cin >> isbn;

	cout << "Please enter the wholesale price: ";
	cin >> price;

	catalogue.insert(catalogue.begin(), Stock(title, surname, isbn, price, format, stock));
}