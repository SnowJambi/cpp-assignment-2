#include "Functions.h"
#include <fstream>
#include <iomanip>

using namespace std;

// Determine whether a user inputs y or n, returns true for y
bool getAnswer()
{
	string answer;
	while (true)
	{
		getline(cin, answer);

		/* Using a string for the variable answer ensures inputs such as 'ty' or
		   'nb' will not be accidentally accepted like they would be with char,
		   by allowing us to check that only one character was input. I'm sure
		   there's a better way to do this but this is what I came up with.*/

		answer[0] = tolower(answer[0]);

		if (answer == "y")
		{
			return true;
		}
		else if (answer == "n")
		{
			return false;
		}
		else
		{
			cout << "Please enter either Y or N: ";
		}
	}
}

/* Ask the user to input each detail for the book they wish to add.
   Performs some checks in an attempt to ensure the input is valid,
   but there is of course still many ways to break some of them.*/
Stock addBook()
{
	string surname;
	string title;
	int stock;
	string format;
	string isbn;
	double price;

	cout << "Please enter the Author's surname: ";
	getline(cin, surname);

	cout << "Please enter the title: ";
	getline(cin, title);

	cout << "Please enter the quantity of the product in stock: ";
	while (true)
	{
		cin >> stock;

		/* Fail state is set to true if anything other than an integer is entered.
		   Reads up to the first whitespace so techincally "12 qwerty" could be entered 
		   and still succeed as only 12 will be read, so room for improvement. */
		if (cin.fail())
		{
			cout << "Please enter an integer: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			break;
		}
	}

	cout << "Please enter the book's format from one of the following options -" << endl;
	cout << "a - Audiobook" << endl;
	cout << "e - Ebook" << endl;
	cout << "h - Hardback" << endl;
	cout << "s - Paperback / Softback: ";

	char formatChar;

	// Check that only one character was entered, that also matches the options
	while (true)
	{
		cin >> format;
		format[0] = tolower(format[0]);
		if (format != "a" && format != "e" && format != "h" && format != "s")
		{
			cout << "Please enter one of the given options: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else
		{
			formatChar = format[0];
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			break;
		}
	}

	cout << "Please enter the isbn: ";
	cin >> isbn;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	cout << "Please enter the wholesale price: ";
	while (true)
	{
		cin >> price;
		if (cin.fail())
		{
			cout << "Please enter a valid price: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			break;
		}
	}

	return Stock(title, surname, isbn, price, formatChar, stock);
}

// Format and write current stock to report.txt
void outputCatalogue(Stock catalogue[], int numItems)
{
	remove("report.txt");
	ofstream outputFile("report.txt");
	if (!outputFile) {
		cout << "ERROR: Cannot open file outputFile.txt" << endl;
		return;
	}

	// Round doubles to 2 decimal places
	outputFile << fixed << setprecision(2);

	outputFile << string(114, '-') << endl;
	outputFile << string(46, ' ') << "==  Biblioden Books ==" << string(46, ' ') << endl;
	outputFile << string(114, '-') << endl;
	outputFile << string(114, '-') << endl;
	outputFile << "Audiobook:" << endl;
	outputFile << string(114, '-') << endl;

	outputFile << "ISBN" << string(16, ' ') 
		       << "Title" << string(40, ' ') 
		       << "Author" << string(7, ' ') 
		       << "Retail price" << string(6, ' ') 
		       << "Stock Level" << endl;

	outputFile << string(114, '-') << endl;
	for (int i=0; i<numItems;i++)
	{
		if (catalogue[i].bookFormat == 'a')
		{
			outputFile << left << setw(20) << catalogue[i].getIsbn() 
				       << setw(45) << catalogue[i].getTitle() 
				       << setw(13) << catalogue[i].getSurname() << "$" 
				       << setw(17) << catalogue[i].retailPrice 
				       << setw(11) << catalogue[i].stockLevel << endl;
		}
	}
	outputFile << string(114, '-') << endl;
	outputFile << "eBook:" << endl;
	outputFile << string(114, '-') << endl;

	outputFile << "ISBN" << string(16, ' ')
			   << "Title" << string(40, ' ')
			   << "Author" << string(7, ' ')
			   << "Retail price" << string(6, ' ')
			   << "Stock Level" << endl;

	outputFile << string(114, '-') << endl;
	for (int i = 0; i < numItems; i++)
	{
		if (catalogue[i].bookFormat == 'e')
		{
			outputFile << left << setw(20) << catalogue[i].getIsbn() 
				       << setw(45) << catalogue[i].getTitle() 
				       << setw(13) << catalogue[i].getSurname() << "$" 
				       << setw(17) << catalogue[i].retailPrice 
				       << setw(11) << catalogue[i].stockLevel << endl;
		}
	}
	outputFile << string(114, '-') << endl;
	outputFile << "Hardcover:" << endl;
	outputFile << string(114, '-') << endl;

	outputFile << "ISBN" << string(16, ' ')
		       << "Title" << string(40, ' ')
		       << "Author" << string(7, ' ')
		       << "Retail price" << string(6, ' ')
		       << "Stock Level" << endl;

	outputFile << string(114, '-') << endl;
	for (int i = 0; i < numItems; i++)
	{
		if (catalogue[i].bookFormat == 'h')
		{
			outputFile << left << setw(20) << catalogue[i].getIsbn() 
				       << setw(45) << catalogue[i].getTitle() 
				       << setw(13) << catalogue[i].getSurname() << "$" 
				       << setw(17) << catalogue[i].retailPrice 
				       << setw(11) << catalogue[i].stockLevel << endl;
		}
	}
	outputFile << string(114, '-') << endl;
	outputFile << "Softcover:" << endl;
	outputFile << string(114, '-') << endl;

	outputFile << "ISBN" << string(16, ' ')
		       << "Title" << string(40, ' ')
		       << "Author" << string(7, ' ')
		       << "Retail price" << string(6, ' ')
		       << "Stock Level" << endl;

	outputFile << string(114, '-') << endl;
	for (int i = 0; i < numItems; i++)
	{
		if (catalogue[i].bookFormat == 's')
		{
			outputFile << left << setw(20) << catalogue[i].getIsbn() 
				       << setw(45) << catalogue[i].getTitle() 
				       << setw(13) << catalogue[i].getSurname() << "$" 
				       << setw(17) << catalogue[i].retailPrice 
				       << setw(11) << catalogue[i].stockLevel << endl;
		}
	}
	outputFile.close();
}

// Caluclate retail price depending on the books format
double calcRetailPrice(double inWholesalePrice, char inBookFormat)
{
	switch (inBookFormat) {
		inBookFormat = tolower(inBookFormat);
	case 'a':
		return inWholesalePrice * 1.43;
	case 'e':
		return inWholesalePrice * 1.03;
	case 'h':
		return inWholesalePrice * 1.45;
	case 's':
		return inWholesalePrice * 1.27;
	}
	cout << "ERROR: Invalid book format." << endl;
	return -1;
}