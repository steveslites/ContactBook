#include "SourceFunctions.h"

// Implementation file for SourceFunctions

using namespace std;

/// <summary>
/// Output main options
/// </summary>
void displayOptions()
{
	cout << "PLEASE SELECT FROM ONE OF THE FOLLOW OPTIONS:" << endl;
	cout << "1 - DISPLAY NAME LIST OF ALL CONTACTS" << endl;
	cout << "2 - DISPLAY ALL CONTACTS" << endl;
	cout << "3 - VIEW SINGLE CONTACT" << endl;
	cout << "4 - ADD A NEW CONTACT" << endl;
	cout << "5 - REMOVE A CONTACT" << endl;
	cout << "6 - EDIT CONTACT" << endl;
	cout << "7 - SAVE TO FILE" << endl;
	cout << "8 - EXPORT CONTACT BOOK TO FILE" << endl;
	cout << "9 - EXIT PROGRAM" << endl;
	cout << endl;
	cout << "What option would you like? ";
}



/// <summary>
/// Validate option
/// </summary>
/// <param name="option"></param>
/// <param name="numOptions"></param>
/// <returns>valid option</returns>
int validateOption(int option, const int numOptions)
{


	while (option < 1 || option > numOptions || cin.fail())
	{
		cin.clear();
		cin.ignore(80, '\n');
		cout << "INVALID OPTION." << endl;
		cout << "What option would you like? ";
		cin >> option;
	}
	return option;
}