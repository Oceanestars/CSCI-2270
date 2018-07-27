// CSCI 2270 - Data Structures
// Author: Oceane Andreis
// Section: 310
// Final Project Part 1.cpp
// Instructor: Christopher Godley

/*

* void addEdge  Used to create the graph by adding connections 
* void addVertex Used to create the graph by adding vertex
* void displayEdges Used to print the graph
* int isAdjacent Used to print whether there is a connection between the vertices
 When the user starts the program, it reads in the cities and distances from the text
  file and build a graph where each city is
a vertex, and the adjacent cities are stored 
in an adjacency list for each vertex. M

*/


#include <iostream>
#include <sstream>
#include <fstream>
#include "Graph.h"


using namespace std;

void Graph::addVertex(string n)
{
	bool found = false;

	for(int i = 0; i<vertices.size(); i++) 
	{
		
		if(vertices[i].name == n )  //check if it's already in our vector
		{
			found = true;
			break;
		}
	}

	vertex v;
	v.name = n;
	vertices.push_back(v); // Add into our vector
	
}

void Graph::addEdge(string v1, string v2, int weight)
{
	for(int x = 0; x < vertices.size(); x++)
	{
		if(vertices[x].name == v1) //found v1
		{
			for(int y = 0; y < vertices.size(); y++)
			{
				if(vertices[y].name == v2 && x != y) //found v2
				{
					
					adjVertex av;
					av.v = &vertices[y];
					av.weight = weight;
					vertices[x].adj.push_back(av);
					
				}
			}
		}
	}
}

int Graph::isAdjacent(string v1,string v2)
{

	if (v1==v2) //if the two cities entered are the same cities
	{
		return true;
	}
	else
	{
		for(int i = 0; i<vertices.size(); i++)
		{
			if(v1 == vertices[i].name) //find the name in the vertices
			{
				for(int j = 0; j<vertices[i].adj.size(); j++) //grab the adj city
				{
					if(v2 == vertices[i].adj[j].v->name) //if the second city inputed is the city adj then v1 and v2 areconnected
					{
						return true;
					}
				}
			}
		}
		return false;
	}
}

void Graph::displayEdges() //display graphs
{

	for(int i = 0; i < vertices.size(); i++)
	{
		cout<<vertices[i].name<<"-->";
		for(int j = 0; j<vertices[i].adj.size(); j++)
		{//for each adjacent vertex:
			
			cout<<vertices[i].adj[j].v->name;

			 if (j != vertices[i].adj.size()-1)
				{
					cout<<"***";
				}
		}
		cout<<endl;
	}
}


