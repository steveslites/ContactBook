#include <iostream>
#include <fstream>


// Specification file for ContactBook class


using namespace std;

const int MAX_BOOK_SIZE = 99;

struct Contact
{
	string firstName;
	string lastName;
	string homePhone;
	string mobilePhone;
	string email;
};


class ContactBook
{
private:
	Contact contact[MAX_BOOK_SIZE];
	int numContacts;

public:
	string const ID = "ID";
	string const FIRST_NAME = "FIRST NAME";
	string const LAST_NAME = "LAST NAME";
	string const HOME_PHONE = "HOME PHONE";
	string const MOBILE_PHONE = "MOBILE PHONE";
	string const EMAIL = "EMAIL";

	ContactBook();

	void displayNamesOfAllContacts(ostream& /*out*/) const;
	void displayAllContactsDetails(ostream& out) const;
	void viewContactOption();
	void displayContactInfo(int /*editID*/, bool /*options*/) const;
	void addNewContact();
	void removeContact();
	void editContact();
	void exportContactBook() const;
	void saveToFile() const;

	int validOption(int /*id*/, int /*numOptions*/, string /*question*/);
	int findName(string /*lastName*/, string /*firstName*/);
	string addStringField(string /*question*/, bool = false /*askYN*/, string = ""/*questionYN*/);
	int findInsertPos(string /*newLastName*/, string /*newFirstName*/);
	bool confirmNewName(int /*nameIndex*/, string /*newLastName*/, string /*newFirstName*/);
	char validYOrN(char answerYN, string questionYN);
	bool askYNQuestion(string question);
	void clearScreen() const;
	void shiftArrayUp(int const /*shiftArrayUp*/);
};
