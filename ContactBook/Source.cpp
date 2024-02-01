#include "ContactBook.h"
#include "SourceFunctions.h"
#include <cassert>

// Contact Book
// Allows user to view, create, modify or remove contact from list
// Loads contact list from file
// Can save to file
// Can output contact book to a user friendly report

int main()
{
	ContactBook* book = new ContactBook();
	assert(book);

	int option;
	int const numMainOptions = 9;
	bool keepRunning = true;

	cout << "WELCOME TO YOUR CONTACT BOOK!" << endl << endl;

	do
	{
		displayOptions();

		// User input for main options
		cin >> option;
		option = validateOption(option, numMainOptions);

		cout << endl;

		// Main Options
		if (option == 1) // 1 - DISPLAY NAME LIST OF ALL CONTACTS
		{
			book->displayNamesOfAllContacts(cout);
		}
		else if (option == 2) // 2 - DISPLAY ALL CONTACTS
		{
			book->displayAllContactsDetails(cout);
		}
		else if (option == 3) // 3 - VIEW SINGLE CONTACT
		{
			book->viewContactOption();
		}
		else if (option == 4) // 4 - ADD A NEW CONTACT
		{
			book->addNewContact();
		}
		else if (option == 5) // 5 - REMOVE A CONTACT
		{
			book->removeContact();
		}
		else if (option == 6) // 6 - EDIT CONTACT
		{
			book->editContact();
		}
		else if (option == 7) // 7 - SAVE TO FILE
		{
			book->saveToFile();
		}
		else if (option == 8) // 8 - EXPORT CONTACT BOOK TO FILE
		{
			book->exportContactBook();
		}
		else if (option == 9) // 9 - EXIT PROGRAM
		{
			string question;
			question = "ARE YOU SURE YOU WANT TO EXIT?(Y or N) ";

			if (book->askYNQuestion(question))
			{
				keepRunning = false;
			}
			else
			{
				book->clearScreen();
			}
		}
	} while (keepRunning);

	cout << endl;
	system("pause");
}