// CSCI 2270 - Data Structures
// Author: Oceane Andreis
// Section: 310
// Assignment 4 main
// Instructor:  Christopher Godley

#include <iostream>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <ctype.h>
#include "MovieTree.hpp"


using namespace std;

int main(int argc, char* argv[])
{


MovieTree BStree;
string title;
int userinput;

	ifstream file; 
    file.open(argv[1]);
    string line;
    string word;
    string field[4];
    int count=0;
    if(!file.is_open())
    {
    	cout<<"file not open";
    }
   
 	while (getline(file, line))
 	{

 		stringstream ss(line);
 		while(getline(ss,word,','))
 		{
 			field[count]=word;
 			count=(count+1)%4;
 		}
 		int ranking= stoi(field[0]);
 		string title = field[1];
 		int releaseYear = stoi(field[2]);
 		int quantity= stoi(field[3]);
 		
 		BStree.addMovieNode(ranking, title, releaseYear, quantity);
 	}
/*
 Insert all the movies in the tree.
When the user starts the program they will pass it the name of the text file that contains all movie
information. Each line in the file shows the IMDB ranking, title, year released, and quantity in stock. Your
program needs to handle that command line argument, open the file, and read all movie data in the file.
From this data, build the BST ordered by the first letter in the movie title. For each of the nodes in the
BST, there should be a sorted singly linked list of the actual movie data. Note: the nodes should be added
to the BST and Linked Lists in the order they are read in. The name of the file that contains the movie
data is Assignment4Movies.txt.
*/

while(userinput!=6)
{
//Display menu
cout << "======Main Menu======" << endl;
cout << "1. Find a movie" << endl;
cout << "2. Rent a movie" << endl;
cout << "3. Print the inventory" << endl;
cout << "4. Delete a movie" << endl;
cout << "5. Count the movies" << endl;
cout << "6. Quit" << endl;
//cout <<"Please enter a number: "<<endl;
cin>>userinput;

switch(userinput)
{
	
	case 1:

	//Find a movie
	cout << "Enter title:" << endl;
	getline(cin>>ws,title);
	BStree.findMovie(title);
	break;

	case 2:
	//Rent a movie
	cout << "Enter title:" << endl;
	getline(cin>>ws,title);
	BStree.rentMovie(title);
	break;
	
	case 3:

	//Print the inventory
	//For all movies in tree
	BStree.printMovieInventory();
	break;

	case 4:
	//Delete movie
	cout << "Enter title:" << endl;
	getline(cin>>ws,title);
	BStree.deleteMovieNode(title);
	break;

	case 5:

	//Count movies in the tree
	cout<<"Tree contains: "<<BStree.countMovieNodes()<<" movies." << endl;
	break;

	case 6:

	//Delete all nodes in the tree
	cout << "Goodbye!" << endl;
	//exit (0);

	break;

	default:
		break;
	
}
}

return 0;
}
