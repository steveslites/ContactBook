#include "ContactBook.h"
#include <iomanip>
#include <string>

// Implementation file for Contact Book class

ContactBook::ContactBook()
{
	ifstream fin("contacts.dat");

	if (!fin.is_open())
	{
		cout << "INPUT FILE DID NOT OPEN PROPERLY!";
		system("pause");
		exit(-1);
	}

	int ctr;
	int insertPos;
	string newFirstName;
	string newLastName;
	numContacts = 0;

 	for (ctr = 0; ctr < MAX_BOOK_SIZE; ctr++)
	{
		getline(fin, newFirstName);

		if (fin.eof())
		{
			break;
		}
		numContacts = ctr;
		getline(fin, newLastName);

			insertPos = findInsertPos(newLastName, newFirstName);

			if (insertPos < numContacts)
			{
				shiftArrayUp(insertPos);
			}

		contact[insertPos].firstName = newFirstName;
		contact[insertPos].lastName = newLastName;
		getline(fin, contact[insertPos].homePhone);
		getline(fin, contact[insertPos].mobilePhone);
		getline(fin, contact[insertPos].email);

	}

	fin.close();
};



/// <summary>
/// Outputs list of all contacts names with ID's
/// </summary>
/// <param name="out"></param>
void ContactBook::displayNamesOfAllContacts(ostream& out) const
{
	clearScreen();

	out << "****************************************" << endl;

	// output headers
	out << left << setw(5) << ID
		<< setw(20) << FIRST_NAME
		<< setw(20) << LAST_NAME
		<< endl;

	out << "----------------------------------------" << endl;

	// output names to console
	for (int index = 0; index < numContacts; index++)
	{
		string firstName = contact[index].firstName;
		string lastName = contact[index].lastName;

		out << left << setw(5) << index + 1
			<< setw(20) << firstName
			<< setw(20) << lastName
			<< endl;
	}

	out << "****************************************" << endl << endl;
}



/// <summary>
/// Output all contact details to console or file
/// </summary>
/// <param name="out"></param>
void ContactBook::displayAllContactsDetails(ostream& out) const
{
	clearScreen();

	out << fixed;

	out << "****************************************************************************************************" << endl;

	// output headers
	out << left << setw(5) << ID
		<< setw(20) << FIRST_NAME
		<< setw(20) << LAST_NAME
		<< setw(17) << HOME_PHONE
		<< setw(17) << MOBILE_PHONE
		<< setw(30) << EMAIL
		<< endl;

	out << "----------------------------------------------------------------------------------------------------" << endl;

	// output contact info
	for (int index = 0; index < numContacts; index++)
	{
		string firstName = contact[index].firstName;
		string lastName = contact[index].lastName;
		string homePhone = (contact[index].homePhone != "-1") ? contact[index].homePhone : "";
		string mobilePhone = (contact[index].mobilePhone != "-1") ? contact[index].mobilePhone : "";
		string email = (contact[index].email != "-1") ? contact[index].email : "";

		out << left << setw(5) << index + 1 // Modify index so it shows ID's
					<< setw(20) << firstName
					<< setw(20) << lastName
					<< setw(17) << homePhone
					<< setw(17) << mobilePhone
					<< setw(30) << email
					<< endl;
	}

	out << "****************************************************************************************************" << endl << endl;
}



/// <summary>
/// View Contact Options
/// </summary>
void ContactBook::viewContactOption()
{
	int option;
	string question;
	int namePos;
	int id;

	clearScreen();

	cout << "VIEW SINGLE CONTACT" << endl << endl;

	//output contact options
	cout << "1 - SELECT FROM LIST" << endl;
	cout << "2 - SEARCH BY NAME" << endl;
	cout << "3 - EXIT" << endl;
	cout << endl;

	// user input for option selection
	question = "Please select an option: ";
	cout << question;
	cin >> option;

	// validate option
	option = validOption(option, 3, question);

	// Contact Options
	if (option == 1) //1 - SELECT FROM LIST
	{
		displayNamesOfAllContacts(cout);

		question = "Enter contact ID to view: ";
		cout << question;
		cin >> id;

		// validate id
		id = validOption(id, numContacts, question) - 1; // Modify id so it shows index

		// output contact info
		displayContactInfo(id, false);
	}
	else if (option == 2) // 2 - SEARCH BY NAME
	{
		string firstName, lastName;

		cin.ignore(80, '\n');

		// user input for name to search for
		cout << "Enter first name: ";
		getline(cin, firstName);

		cout << "Enter last name: ";
		getline(cin, lastName);

		// validate id
		id = findName(lastName, firstName);

		if (id == numContacts) // If name not found
		{
			cout << endl << "NAME NOT FOUND!" << endl << endl;
		}
		else
		{
			// output contact info
			displayContactInfo(id, false);
		}
	}
	else if (option == 3)
	{
		clearScreen();
	}
}



/// <summary>
/// Display all info for a contact
/// </summary>
/// <param name="editID"></param>
/// <param name="options"></param>
void ContactBook::displayContactInfo(int editID, bool options) const
{
	Contact currentContact = contact[editID];

	clearScreen();

	string firstName = currentContact.firstName;
	string lastName = currentContact.lastName;
	string homePhone = (currentContact.homePhone != "-1") ? currentContact.homePhone : "";
	string mobilePhone = (currentContact.mobilePhone != "-1") ? currentContact.mobilePhone : "";
	string email = (currentContact.email != "-1") ? currentContact.email : "";

	cout << "****************************************" << endl;

	// output contact information
	if (options)
	{
		cout << "1 - ";
	}
	cout << FIRST_NAME << ": " << firstName << endl;
	if (options)
	{
		cout << "2 - ";
	}
	cout << LAST_NAME << ": " << lastName << endl;
	if (options)
	{
		cout << "3 - ";
	}
	cout << HOME_PHONE << ": " << homePhone << endl;
	if (options)
	{
		cout << "4 - ";
	}
	cout << MOBILE_PHONE << ": " << mobilePhone << endl;
	if (options)
	{
		cout << "5 - ";
	}
	cout << EMAIL << ": " << email << endl;
	if (options)
	{
		cout << "6 - EXIT" << endl;
	}

	cout << "****************************************" << endl;
	cout << endl;
}



/// <summary>
/// Create and insert a new contact in alphabetical order
/// </summary>
void ContactBook::addNewContact()
{
	clearScreen();

	string newFirstName;
	string newLastName;
	string newHomePhone;
	string newMobilePhone;
	string newEmail;

	string question;
	string questionYN;

	bool newName;
	int insertPos;

	cin.ignore(80, '\n');

	//Get user input for new contact info
	//First Name
	question = "What is the contacts first name? ";
	newFirstName = addStringField(question);

	//Lsst Name
	question = "What is " + newFirstName + "'s last name? ";
	newLastName = addStringField(question);

	// Find position to insert to
	insertPos = findInsertPos(newLastName, newFirstName);

	// Check if the name already exists
	newName = confirmNewName(insertPos, newLastName, newFirstName);

	if (newName)
	{
		// Get contact details
		// Home Phone
		questionYN = "Does " + newFirstName + " have a home phone number?(Y or N) ";
		question = "What is " + newFirstName + "'s home phone number? ";
		newHomePhone = addStringField(question, true, questionYN);

		// Mobile Phone
		questionYN = "Does " + newFirstName + " have a mobile phone number?(Y or N) ";
		question = "What is " + newFirstName + "'s mobile phone number? ";
		newMobilePhone = addStringField(question, true, questionYN);

		// Email
		questionYN = "Does " + newFirstName + " have an e-mail address?(Y or N) ";
		question = "What is " + newFirstName + "'s e-mail address? ";
		newEmail = addStringField(question, true, questionYN);

		shiftArrayUp(insertPos);


		// Shift array to allow for insertion
		//for (int index = numContacts; index >= insertPos; index--)
		//{
		//	contact[index + 1] = contact[index];
		//}

		// Insert new contact into array
		contact[insertPos].firstName = newFirstName;
		contact[insertPos].lastName = newLastName;
		contact[insertPos].homePhone = newHomePhone;
		contact[insertPos].mobilePhone = newMobilePhone;
		contact[insertPos].email = newEmail;

		// Increase number of contacts
		numContacts++;
	}
	else
	{
		cout << endl << endl;
		cout << "NAME ALREADY EXISTS." << endl;
		cout << "CAN'T HAVE DUPLICATES OF THE SAME NAME." << endl << endl;
	}
}




/// <summary>
/// Remove a contact from the array
/// </summary>
void ContactBook::removeContact()
{
	char another;

	do {
		clearScreen();

		int id;
		string question;
		string questionYN;
		char removeYN;

		displayNamesOfAllContacts(cout);

		// user input for which contact to remove
		question = "Enter contact ID to remove: ";
		cout << question;
		cin >> id;
		// validate id
		id = validOption(id, numContacts, question) - 1; // Modify id to index with -1

		// get user to confirm they want to remove the contact
		questionYN = "ARE YOU SURE YOU WANT TO REMOVE " + contact[id].firstName + " " + contact[id].lastName + "? (Y or N) ";
		cout << questionYN;
		cin >> removeYN;
		removeYN = toupper(removeYN);
		// validate answer
		removeYN = validYOrN(removeYN, questionYN);

		// remove contact
		if (removeYN == 'Y')
		{
			// Check that the contact isn't the last in the list
			if (id != numContacts - 1)
			{
				for (int index = id; index < numContacts; index++)
				{
					contact[index] = contact[index + 1];
				}
			}
			// decrease number of contacts
			numContacts--;

			cout << "CONTACT REMOVED!" << endl;

			displayNamesOfAllContacts(cout);
		}

		// Ask user if they want to remove another contact
		questionYN = "Remove another contact? (Y or N) ";
		cout << questionYN;
		cin >> another;
		another = toupper(another);
		//validate answer
		another = validYOrN(another, questionYN);

	} while (another == 'Y');

	clearScreen();
}



/// <summary>
/// Edit an existing contact
/// </summary>
void ContactBook::editContact()
{
	clearScreen();

	int editID;
	int lineID;
	string question;

	cout << "EDIT CONTACT" << endl;

	displayNamesOfAllContacts(cout);

	// user input for ID selection to edit
	question = "Enter contact ID to edit: ";
	cout << question;
	cin >> editID;
	// validate option
	editID = validOption(editID, numContacts, question) - 1;// Modify ID so it is the index

	do {
		displayContactInfo(editID, true);

		// user input for which field to edit
		question = "Enter line number for field you want to edit: ";
		cout << question;
		cin >> lineID;
		// validate option
		lineID = validOption(lineID, 6, question);
		cin.ignore(80, '\n');


		if (lineID == 1) // 1 - FIRST NAME
		{
			question = "What is the contacts updated first name? ";
			contact[editID].firstName = addStringField(question);
		}
		else if (lineID == 2) // 2 - LAST NAME
		{
			question = "What is " + contact[editID].firstName + "'s updated last name? ";
			contact[editID].lastName = addStringField(question);
		}
		else if (lineID == 3) // 3 - HOME PHONE
		{
			question = "What is " + contact[editID].firstName + "'s updated home phone? ";
			contact[editID].homePhone = addStringField(question);
		}
		else if (lineID == 4) // 4 - MOBILE PHONE
		{
			question = "What is " + contact[editID].firstName + "'s updated mobile phone? ";
			contact[editID].mobilePhone = addStringField(question);
		}
		else if (lineID == 5) // 5 - EMAIL
		{
			question = "What is " + contact[editID].firstName + "'s updated email? ";
			contact[editID].email = addStringField(question);
		}
	} while (lineID != 6); // 6 - EXIT

	clearScreen();
}



/// <summary>
/// Output all contact book details to report file
/// </summary>
void ContactBook::exportContactBook() const
{
	// Open output file
	ofstream fout("contactBook.rpt");
	if (!fout.is_open())
	{
		cout << "OUTPUT FILE DID NOT OPEN PROPERLY!";
		system("pause");
		exit(-3);
	}

	displayAllContactsDetails(fout);

	// Close output file
	fout.close();

	cout << "FILE EXPORTED!" << endl << endl;
}



/// <summary>
/// Output array data to file
/// </summary>
void ContactBook::saveToFile() const
{
	// Open output file
	ofstream fout("contacts.dat");
	if (!fout.is_open())
	{
		cout << "OUTPUT FILE DID NOT OPEN PROPERLY!";
		system("pause");
		exit(-2);
	}

	// loop through array outputting data
	for (int index = 0; index < numContacts; index++)
	{
		fout << contact[index].firstName << endl;
		fout << contact[index].lastName << endl;
		fout << contact[index].homePhone << endl;
		fout << contact[index].mobilePhone << endl;
		fout << contact[index].email << endl;
	}

	// close output file
	fout.close();

	clearScreen();

	cout << "FILE SAVED!" << endl << endl;
}



/// <summary>
/// Validate option is within bounds
/// </summary>
/// <param name="option"></param>
/// <param name="numOptions"></param>
/// <param name="question"></param>
/// <returns>valid option</returns>
int ContactBook::validOption(int option, int numOptions, string question)
{
	while (option < 1 || option > numOptions || cin.fail())
	{
		cin.clear();
		cin.ignore(80, '\n');

		cout << "INVALID INPUT." << endl;
		cout << question;
		cin >> option;
	}
	return option;
}



/// <summary>
/// search for name in list
/// </summary>
/// <param name="lastName"></param>
/// <param name="firstName"></param>
/// <returns>position of name</returns>
int ContactBook::findName(string lastName, string firstName)
{
	int pos;

	for (pos = 0; pos < numContacts; pos++)
	{
		if (contact[pos].lastName == lastName && contact[pos].firstName == firstName)
		{
			break;
		}
	}
	return pos;
}



/// <summary>
/// Validate and add a new string field to the contact book
/// </summary>
/// <param name="question"></param>
/// <param name="askYN"></param>
/// <param name="questionYN"></param>
/// <returns>valid input from user</returns>
string ContactBook::addStringField(string question, bool askYN, string questionYN)
{
	string field;
	bool answerYN;

	// If a yes or no question needs to be asked
	if (askYN)
	{
		answerYN = askYNQuestion(questionYN);
	}

	// If user knows field
	if (!askYN || answerYN)
	{
		cout << question;
		getline(cin, field);

		// Validate user input for field
		while (field == "")
		{
			cout << "INVALID INPUT." << endl;
			cout << question;
			getline(cin, field);
		}
	}
	else
	{
		// If user doesn't know field
		field = "-1";
	}
	return field;
}



/// <summary>
/// Find insert position
/// </summary>
/// <param name="newLastName"></param>
/// <param name="newFirstName"></param>
/// <returns>insert position</returns>
int ContactBook::findInsertPos(string newLastName, string newFirstName)
{
	int posLastName;
	int pos;
	bool end = false;


	if (numContacts == 0 || newLastName < contact[0].lastName) /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	{
		pos = 0;
	}
	else
	{
		// loop through array for last name
		for (posLastName = 0; posLastName < numContacts; posLastName++)
		{
			// Search for last name
			if (contact[posLastName].lastName >= newLastName)
			{
				// Check if last name doesn't exist
				if (contact[posLastName].lastName != newLastName)
				{
					pos = posLastName;
					break;
				}
				else
				{
					// loop through array for first name
					for (pos = posLastName; pos < numContacts; pos++)
					{
						// Search for first name
						if (contact[pos].firstName >= newFirstName || contact[pos].lastName != contact[posLastName].lastName)
						{
							end = true;
							break;
						}
					}
				}

			}
			else
			{
				// If new last name is less than all contact names
				pos = numContacts;
			}

			if (end)
			{
				break;
			}
		}
	}
	return pos;
}



/// <summary>
/// Confirm if it is a name name or if alreaedy exists
/// </summary>
/// <param name="firstName"></param>
/// <param name="lastName"></param>
/// <returns>bool</returns>
bool ContactBook::confirmNewName(int nameIndex, string newLastName, string newFirstName)
{
	bool newName = true;

	// Check if new name matches insertion point name
	if (newLastName == contact[nameIndex].lastName && newFirstName == contact[nameIndex].firstName)
	{
		newName = false;
	}
	return newName;
}



/// <summary>
/// Validate yes or no input (Y or N)
/// </summary>
/// <param name="answerYN"></param>
/// <param name="questionYN"></param>
/// <returns>Y or N</returns>
char ContactBook::validYOrN(char answerYN, string questionYN)
{
	while (answerYN != 'Y' && answerYN != 'N')
	{
		cout << "INVALID INPUT. Must be Y or N." << endl;
		cout << questionYN;
		cin >> answerYN;
		answerYN = toupper(answerYN);
		cin.ignore(80, '\n');
	}
	return answerYN;
}



/// <summary>
/// Ask Yes or No question (Y or N)
/// </summary>
/// <param name="question"></param>
/// <returns>bool</returns>
bool ContactBook::askYNQuestion(string question)
{
	char answerYN;

	cout << question;
	cin >> answerYN;
	answerYN = toupper(answerYN);
	cin.ignore(80, '\n');

	return validYOrN(answerYN, question) == 'Y';
}



/// <summary>
/// Clear console screen
/// </summary>
void ContactBook::clearScreen() const
{
	cout << flush;
	system("CLS");
}


/// <summary>
/// Shift array values up to allow for insertion
/// </summary>
/// <param name="insertPos"></param>
void ContactBook::shiftArrayUp(int const insertPos)
{
	for (int index = numContacts; index >= insertPos; index--)
	{
		contact[index + 1] = contact[index];
	}
}