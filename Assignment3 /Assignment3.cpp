// CSCI 2270 - Data Structures
// Author: Oceane Andreis
// Section: 310
// Assignment 3 main
// Instructor:  Christopher Godley

#include <iostream>
#include <sstream>
#include <fstream>
#include "CommunicationNetwork.h"

/*
My main check all my function, displays the menu, ask for the user input, and it uses switch and cases to make it look cleaner and easier instead of a bunch 
of if statement
*/

using namespace std;

int main(int argc, char* argv[])
{

int userinput;
string Name;
string Name2;
string cityNewName;
string cityPreviousName;
City *receiver;
string removeCity;
CommunicationNetwork Internet;
while(userinput!=7)
{
//Print menu
cout << "======Main Menu======" << endl;
cout << "1. Build Network" << endl;
cout << "2. Print Network Path" << endl;
cout << "3. Transmit Message Coast-To-Coast-To-Coast" << endl;
cout << "4. Add City" << endl;
cout << "5. Delete City" << endl;
cout << "6. Clear Network" << endl;
cout << "7. Quit" << endl;
cout << "Please enter a number: " << endl;

cin>>userinput;

switch(userinput)
{
	
	case 1:

	//Build Network
	Internet.buildNetwork();
	break;

	case 2:

	//Print path :
	Internet.printNetwork();
	break;

	
	case 3:

	//Transmit Message:
	Internet.transmitMsg(argv[1]);
	break;

	
	case 4:

	//Adding a new city:	
	cout << "Enter a city name: " << endl;
	getline(cin>>ws,cityNewName);
	cout << "Enter a previous city name: " << endl;	
	getline(cin>>ws,cityPreviousName);
	Internet.addCity(cityNewName, cityPreviousName);
	break;
	

	case 5:

	//Delete city:
	cout<<"Enter a city name to delete: " << endl;
	getline(cin>>ws,removeCity);
	Internet.deleteCity(removeCity);
	break;

	case 6:

	//Clear network:
	Internet.deleteNetwork();
	break;

default:
	cout << "Goodbye!" << endl;
	exit (0);

}

}
return 0;
}