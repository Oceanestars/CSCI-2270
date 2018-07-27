// CSCI 2270 - Data Structures
// Author: Oceane Andreis
// Section: 310
// Final Project main Part 2
// Instructor: Christopher Godley

/*

This main let's me implement my functions
* void addEdge 
* void addVertex
* void displayEdges
* void assignDistricts
* void shortestPath(Breadth First Search)
* void shortestWeightedPath(Dijkstras)
I use part of part 1 to build my graph (addEdge and addVertex)
I use a switch case so then depending on the input It will
implement the function.

*/

#include <iostream>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <ctype.h>
#include "Graph.hpp"
#include <string>


using namespace std;

int main(int argc, char* argv[])
{

Graph g;
string firstcity;
string secondcity;
string startingCity;
string endingCity;
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
				citytwo++; //vertical1
			}
			cityone++; //horizontal		
	}

int userinput;
while(userinput!=5)
{
//Display menu

cout << "======Main Menu======" << endl;
cout << "1. Print vertices" << endl;
cout << "2. Find districts" << endl;
cout << "3. Find shortest path" << endl;
cout << "4. Find shortest weighted path" << endl;
cout << "5. Quit" << endl;
cin>>userinput;

	switch(userinput)
	{


		case 1:
		// //1. Print vertices
		g.displayEdges();

		break;

		case 2:
		//Assign district
		g.assignDistricts();

		break;

		case 3:
		// Bts
		cout << "Enter a starting city:" << endl;
		getline(cin>>ws,startingCity);
		cout << "Enter an ending city:" << endl;
		getline(cin>>ws,endingCity);
		g.shortestPath(startingCity, endingCity);

		break;

		case 4:
		//find weighted path, Djikastra 
		cout << "Enter a starting city:" << endl;
		getline(cin>>ws,startingCity);
		cout << "Enter an ending city:" << endl;
		getline(cin>>ws,endingCity);
		g.shortestWeightedPath(startingCity,endingCity);


		break;

		case 5:
		//5. Quit
		cout << "Goodbye!" << endl;

		default:
		exit(0);
		break;

		}
	}

return 0;
}

