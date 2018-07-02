// CSCI 2270 - Data Structures
// Author: Oceane Andreis
// Section: 310
// Assignment 3
// Instructor:  Christopher Godley

#include <iostream>
#include <sstream>
#include <fstream>
#include "CommunicationNetwork.h"

using namespace std;

/*
The goal of my code is to create a user menu where they can choose 6 different option
like build network, print network path, transmit message
coast-to-coast-to-coast, add city, delete city, clear network, and
if they presse any number other than 1,2,3,4,5,6 then the menu quits
while if you press one of the 6 numbers mentionned the program will keep 
running until you quit.
Before transmitting a message or add or delete city or print
network you need to build the network first (Also need to do that before clearing the network)
In my add function I can add anything after any city.
My transmit message goes through the text file and each word is being
sent through the network and then being sent back (reverse) and then
it goes to the next word in the file.
My print network prints the network and it shows the city I added
and It shows when a city has been deleted.
My delete city function deletes any of the city in my network.
Finally delete network just makes my network empty. It deletes every city.
Then you can press 7 or 8 or 9 to exit out the menu.

*/


//constructor
CommunicationNetwork::CommunicationNetwork() 
{
  head = NULL;
}
//deconstructor
CommunicationNetwork::~CommunicationNetwork() 
{
	deleteNetwork();
}

void CommunicationNetwork::addCity(string newCityName, string previousCityName)
/*Insert a new city into the linked list after the previousCityName. The name of the new
city is in the argument newCityName. */

{
	
	City* newCity = new City(newCityName, NULL, NULL, "");
	City* current = head;

	if (current == NULL) 
	{ //if empty
		
		head = newCity;
		head->next=tail;
		return; // end function early
		
	}


	else if (head->next->cityName==previousCityName) 
		// Insert after the head
	{
		head->next= newCity;
		newCity->previous = head;
		
	
	}
	
	else if (previousCityName == "" || tail->cityName == previousCityName) 
	{
        if (tail == NULL) 
        {
            tail = newCity;
            tail->previous = head;
            head->next = tail;
            return;
        } 
        else 
        {
            tail->next = newCity;
            newCity->previous = tail;
            tail = newCity;
            return;
        }
   } 
    else 
    {

		while (current != NULL) 
		{

			if (current->cityName == previousCityName) 
			{//CityName works like key
				if(current->next !=NULL)
				{
				current->next->previous=newCity;
				newCity->next = current->next;
				current->next = newCity;
				newCity->previous=current;
				
				break;
				}
				else//(current->next == NULL) 
				{
				current->next = newCity;
				newCity->previous=current;
				tail = newCity;
				
				break;
				
				}
			
			}
			
			if (current->next == NULL) 
			{
				current->next = newCity;
				newCity->previous=current;
				tail = newCity;
				
				break;
				
			}
			
			current = current->next;
		}

	
	}
}
	


void CommunicationNetwork::transmitMsg(char * filename)
/*Open the file and transmit the message between all cities in the network word by word. A word needs
to be received at the beginning of the network after being sent to the end of the network before
sending the next word (coast to coast to coast). Only one city can hold the message at a time; as soon as
it is passed to the next city, it needs to be deleted from the sender city. */
{
	

	ifstream file; 
    file.open(filename);
    string line;
    City *send  = head;
    if(head == NULL)
    {
    	cout << "Empty list" << endl;
    }
 	while (getline(file, line, ' ')) 
	{
	    while(send!=NULL)
	    {
				cout<<send->cityName << " received " << line << endl;
				send= send->next;

	    }
	    send=tail;
	    send=send->previous; // do this so it doesn't print boston twice because boston is the tail
	    while(send !=NULL)
	    {

			cout<<send->cityName << " received " << line << endl;
			send= send->previous;
	    }
	   send=head;
   
	}
}


void CommunicationNetwork::buildNetwork()
/*Build the initial network from the cities given in this writeup. The cities can be fixed in the function,
you do not need to write the function to work with any list of cities. */

{
	
    City* LA = new City("Los Angeles", NULL, NULL, "");
	City* PH = new City("Phoenix", NULL,NULL, "");
	City* DE = new City("Denver", NULL,NULL, "");
	City* DA = new City("Dallas", NULL,NULL, "");
	City* ST = new City("St. Louis", NULL,NULL, "");
	City* CH = new City("Chicago", NULL,NULL, "");
	City* AT = new City("Atlanta", NULL,NULL, "");
	City* WA = new City("Washington, D.C.", NULL,NULL, "");
	City* NY = new City("New York", NULL,NULL, "");
	City* BO = new City("Boston", NULL,NULL, "");	
	
    head = LA;
	LA->next = PH;
	PH->previous=LA;
	PH->next = DE;
	DE->previous=PH;
	DE->next = DA;
	DA->previous=DE;
	DA->next = ST;
	ST->previous=DA;
	ST->next = CH;
	CH->previous=ST;
	CH->next = AT;
	AT->previous=CH;
	AT->next = WA;
	WA->previous=AT;
	WA->next = NY;
	NY->previous=WA;
	NY->next = BO;
	BO->previous=NY;
	tail = BO;
  
}

void CommunicationNetwork::printNetwork()
/*Start at the head of the linked list and print the name of each city in order to the end of the list. */
{

if(head!=NULL)
{
	cout << "===CURRENT PATH===" << endl;
	City* tmp = head;
	cout<<"NULL <- ";
	while (tmp != NULL) 
		{
			if(tmp->next!=NULL)
			{
				cout << tmp->cityName  << " <-> "; //for all nodes in network
			}

			if(tmp->next==NULL)
			{
				tail=tmp;
			}
			tmp=tmp->next;

		}
	cout << tail->cityName << " -> ";
	cout << "NULL" << endl;
	cout << "==================" << endl;
}
else
{
	cout<<"Network is empty"<<endl;
}

}


void CommunicationNetwork::deleteCity(string removeCity)
/*Find the city in the network where city name matches removeCity. Change the next and previous
pointers for the surrounding cities and free the memory. */
{
	City* tmp;
	if (head->cityName == removeCity) 
	{	
		tmp = head;
		head = head->next;
		tmp->next = NULL;
		// Else it's in the middle
	} 
			else 
			{
				City* left = head;
				City* deleting = left->next;
				while ((deleting->next != NULL) && (deleting->cityName != removeCity)) 
				{
					left = left->next;
					deleting = deleting->next;
				}
				if (deleting->cityName == removeCity) 
				{
					tmp = left->next;
					left->next = deleting->next;
					tmp->next = NULL;
					
				}
			}

}

void CommunicationNetwork::deleteNetwork()
/*Delete all cities in the network, starting at the head city. */
{
	

City *tmp;
	while(head!=NULL)
	{
		tmp= head->next;
		cout << "deleting " << head -> cityName << endl;
		delete head;
		head=tmp;
	}
	if(head!=NULL)
	{
		delete head;
	}
	head=NULL;	
	
}

