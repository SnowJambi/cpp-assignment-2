// Author: Lachlan Jadezak CIT 207385
// Version: 15/11/2019

#include <iostream>
#include <fstream>
#include "Product.h"
#include "Stock.h"
#include "Functions.h"
using namespace std;

int main()
{
	// Open products file, ensure it is present
	ifstream inProducts("products.txt");
	if (!inProducts) {
	cout << "ERROR: Cannot find file products.txt, exiting program." << endl;
	return -1;
	}

	// Initialise variables to pass data from products.txt
	string surname;
	string title;
	int stock;
	char format;
	string isbn;
	double price;

	int numItems = 0; // Keep track of array size

	// Get number of products listed in products.txt
	while (inProducts >> surname >> title >> stock >> format >> isbn >> price)
	{
		numItems++;
	}

	// Reset stream and seek to beginning of file
	inProducts.clear();
	inProducts.seekg(0, ios::beg);

	// Create array with size of number of items in products.txt
	Stock* cataloguePtr = new Stock[numItems];
	Stock* c;
	c = cataloguePtr;

	// Fill dynamic array
	while (inProducts >> surname >> title >> stock >> format >> isbn >> price)
	{
		*c = Stock(title, surname, isbn, price, format, stock);
		c++;
	}

	inProducts.close();

	cout << "Would you like to enter a new book? (Y/N): ";

	/* If yes, expand size of array by one and add new book to beginning of array.

	   This seems quite inefficient :( Storing the objects in an oversized array
	   and tracking the location of the first and last elements with empty array
	   space in front of and behind those could allow objects to be inserted at
	   the beginning or end without having to traverse the array and copy each
	   element to a new one. I'm sure there's some inbuilt types for this (deque
	   maybe?) though the criteria requires the inserted element at index 0 hence
	   this method. Or just never insert at the front. Just some thoughts from
	   my learning about arrays.*/

	if (getAnswer())
	{
		numItems++;
		Stock* temp = new Stock[numItems];
		for (int i = 0; i < numItems-1; i++)
		{
			temp[i+1] = cataloguePtr[i];
		}

		delete[] cataloguePtr; // Destroy unused array

		cataloguePtr = temp;

		*cataloguePtr = addBook(); // Set index 0 to the new book input by user
	}

	cout << "Would you like to delete a book? (Y/N): ";

	/* If yes, search for ISBN of book and remove it if present in the array

	   Note that the last element does not get deleted, but reducing the
	   numItems tracker will ensure it does not get read. Creating another
	   array just to downsize it and remove the extra element would just
	   be inefficient.*/
	if (getAnswer())
	{
		string tempIsbn;
		cout << "Please enter the ISBN of the book you would like to remove: ";
		cin >> tempIsbn;
		bool isbnFound = false;
		for (int i = 0; i < numItems; i++)
		{
			if (cataloguePtr[i].getIsbn() == tempIsbn)
			{
				numItems--;
				isbnFound = true;

				/* Shift all books one spot left in the array from the index
				   after the deleted book onwards */
				for (int j = i; j < numItems; j++)
				{
					cataloguePtr[j] = cataloguePtr[j + 1];
				}
			}
		}
		if (!isbnFound)
		{
			cout << "ISBN not found!" << endl;
		}
	}

	// Output current inventory to report.txt
	outputCatalogue(cataloguePtr, numItems);

	cout << "Would you like to view the order report? (Y/N): ";

	// If yes, display order report
	if (getAnswer())
	{
		string orderTitle;
		int orderAmount;

		// Check if orders.txt was able to be opened
		ifstream inOrder("orders.txt");
		if (!inOrder) {
			cout << "ERROR: Cannot find file orders.txt, exiting program." << endl;
			return -1;
		}

		cout << string(114, '=') << endl;
		cout << string(51, ' ') << "Order Report" << string(51, ' ') << endl;
		cout << string(114, '=') << endl;

		bool bookFound = false;

		// Read through orders.txt, attempt to match titles to inventory
		while (inOrder >> orderTitle >> orderAmount)
		{
			for (int i = 0; i < numItems; i++)
			{
				bookFound = false;
				if (cataloguePtr[i].getTitle() == orderTitle)
				{
					bookFound = true;
					if (cataloguePtr[i].stockLevel >= orderAmount)
					{
						cout << cataloguePtr[i].getTitle()
							 << " is available at Biblioden and there is enough stock to fulfil your order with " 
							 << cataloguePtr[i].stockLevel << " stock remaining." << endl;
					}
					else
					{
						cout << cataloguePtr[i].getTitle() 
							 << " is available at Biblioden but there is not enough stock to fulfil your order with only " 
							 << cataloguePtr[i].stockLevel << " stock remaining." << endl;
					}
					break;
				}
			}
			if (!bookFound)
			{
				cout << orderTitle << " is not available at Biblioden" << endl;
			}

		}
		inOrder.close();
	}
	return 0;
}