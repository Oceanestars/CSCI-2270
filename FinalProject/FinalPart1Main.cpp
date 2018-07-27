// CSCI 2270 - Data Structures
// Author: Oceane Andreis
// Section: 310
// Final Project main Part 1
// Instructor:Christopher Godley


/*

This main is meant to test my functions for part 1.
* void addEdge 
* void addVertex
* void displayEdges
* int isAdjacent

*/

#include <iostream>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <ctype.h>
#include "Graph.h"
#include <string>


using namespace std;

int main(int argc, char* argv[])
{

	Graph g;
	string firstcity;
	string secondcity;
	vector<string>citynum;


	ifstream fp;
	fp.open(argv[1]);
	string line;
	
	getline(fp, line);//first line
	
	stringstream sp (line); //first line is just city names
	
	string name;
	getline(sp, name, ',');

	while(getline(sp, name, ','))
	{
		citynum.push_back(name);
		g.addVertex(name); //this need to be in a vector
			
 	}

	string edge;
	int cityone=0;
	while(getline(fp,line)) // go through each line, excluding first line
	{
		stringstream sp2(line); //take second line of 
		getline(sp2, edge, ','); //skip the city name
		
		int citytwo=0;
		while(getline(sp2, edge, ',')) // get all the numbers(go through numbers after cityname)
		 { 
		 	int weight = stoi(edge);
		 		
			if(weight!=0 && weight!=-1)
			{
				g.addEdge(citynum[cityone],citynum[citytwo], weight);
				

			}
			citytwo++; //vertical
		}
		cityone++; //horizontal
		
	}



int userinput;
while(userinput!=3)
{
//Display menu

cout << "======Main Menu======" << endl;
cout << "1. Print vertices" << endl;
cout << "2. Vertex adjacent" << endl;
cout << "3. Quit" << endl;
cin>>userinput;

switch(userinput)
{


	case 1:
	// //1. Print vertices
	g.displayEdges();
	

	break;

	case 2:
	//2. Vertex adjacent
	cout << "Enter first city:" << endl;
	getline(cin>>ws,firstcity);

	cout << "Enter second city:" << endl;
	getline(cin>>ws,secondcity);
	
	if(g.isAdjacent(firstcity,secondcity)==true) // Cities are adjacent:
	{
		cout << "True" << endl;
	}
	else // //Cities are not adjacent:
	{
		cout << "False" << endl;
	}

	break;

	case 3:
	//3. Quit
	cout << "Goodbye!" << endl;



	default:
	exit(0);
	break;

	}
	}

return 0;
}







