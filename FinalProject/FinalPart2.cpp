// CSCI 2270 - Data Structures
// Author: Oceane Andreis
// Section: 310
// Final Project Part 2 .cpp
// Instructor: Christopher Godley

/*

* void addEdge  Used to create the graph by adding connections 
* void addVertex Used to create the graph by adding vertex
* void displayEdges Used to print the graph
* void assignDistricts This doesn't print anything. It does a depth-first search (DFS) of
the graph to determine the connected cities in the graph, and assign those cities the 
same district ID. The connected cities are the vertices that are connected, either directly
by an edge, or indirectly through another vertex. 
* void shortestPath(Breadth First Search) This uses BTS to find the shortest 
path(not accounting for the weight)
* void shortestWeightedPath(Dijkstras) This finds the shortest path from one city to another
and it take into account the distance between every city.

*/


#include <iostream>
#include <sstream>
#include <fstream>
#include "Graph.hpp"
#include <stack>
#include <queue>
#include <string>


using namespace std;

Graph::Graph() //constructor
{

}

Graph::~Graph() //deconstructor 
{

}

void Graph::addVertex(string n)
{
	bool found = false;
	

	for(int i = 0; i<vertices.size(); i++)
	{
		
		if(vertices[i].name == n )  //Not add duplicate
		{
			found = true;
			
			break;
		}
		
	}

	vertex v;
	v.name = n;
	v.ID=vertices.size();
	v.districtID = -1;
	vertices.push_back(v);

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
					vertices[x].adj.push_back(av); //add in adj vector
				}
			}
		}
	}
}


void Graph::DFSLabel(std::string startingCity, int distID)
{
	stack<vertex*>vertexholder;
	vertex* current; 
	vertex* ve;

	for(int i=0; i<vertices.size();i++)
		{
			if(vertices[i].name ==startingCity)
			{
				current = &vertices[i];
				
				break;
				
			}
		}

	if(current->visited ==false) //vertice not visited then we want to change district ID
	{
		current->districtID=distID;	
	}
	else
	{
		return;
	}
	//Depth first search taken from the textbook
	vertexholder.push(current);
	while(!vertexholder.empty())
	{
			ve = vertexholder.top();
			vertexholder.pop();
			
			for (int x = 0 ; x < ve->adj.size(); x++)
			{	
				if(!ve->adj[x].v->visited)
				{
					ve->adj[x].v->visited = true;
					
					ve->adj[x].v->districtID=distID;
				
					vertexholder.push(ve->adj[x].v);
				}
			}
	}
}

void Graph::assignDistricts()// Depth First Search
{
	string value;
	int update=1;
	for(int i=0; i<vertices.size();i++)
	{
		if(vertices[i].districtID < 0){
			DFSLabel(vertices[i].name, update); //helps build a list of district with the help of dfslabel 
			update++;
		}
	}

}


vertex* Graph::findVertex(string startingCity) //finds the right vertex
{
	for(int i=0; i<vertices.size();i++)
	{
		if(vertices[i].name ==startingCity )
		{
			return &vertices[i];
		}
		
	}
	return nullptr;
}
        
void Graph::shortestPath(string startingCity, string endingCity)//  Breadth First Search
{
// If the cities are in
// the same district, run a breadth-first search (BFS) that returns the number of edges to
// traverse along the shortest path, and the names of the vertices along the path.
//if disctrict not built or not district equivalent

	for(int i=0; i<vertices.size(); i++)
	{
		vertices[i].parent =NULL;
		vertices[i].visited=false;
	}

	queue<vertex*>q;
	vertex* start = findVertex(startingCity);
	vertex* end = findVertex(endingCity);

//Other way to find the vertices, without using findvertex
/*	

	for(int i=0; i<vertices.size();i++)
	{
		if(vertices[i].name ==startingCity )
		{
			start = &vertices[i];
		}
		else if(vertices[i].name ==endingCity)
		{
			end= &vertices[i];
		}
	}
*/

	if(start == NULL|| end==NULL)
	{
		cout<<"One or more cities doesn't exist"<<endl;
		return;
	}
	if(start->districtID<0 ||  end->districtID<0)
	{
		cout<< "Please identify the districts before checking distances" << endl;
		return;
	}
	if(start->districtID!=end->districtID)
	{
		cout<< "No safe path between cities" << endl;
		return;
	}
	
	//traverse
	start->unweightedDistance=-1;
	start->visited = true;
	start->parent=NULL;
	q.push(start);
	vertex* curv ;
	int minDistance=0;
	while(!q.empty()) //while queue not empty
	{
		curv = q.front();
		q.pop();
		
		for(int i=0;i<curv->adj.size();i++)
		{
			if(curv->adj[i].v->visited == false)
			{	
				//line 8 book
				curv->adj[i].v->unweightedDistance = curv->unweightedDistance+1;
				curv->adj[i].v->parent = curv;
				curv->adj[i].v->unweightedDistance++;
				
				curv->adj[i].v->visited = true;
				q.push(curv->adj[i].v);
			}
		}
	}
	stack<string>reverse_path;
	vertex* curv2 ;
	curv2=end;

	while(curv2 !=NULL)
	{
		reverse_path.push(curv2->name);
		
		start->unweightedDistance++;
		
		curv2 = curv2->parent;	

	}
	
	cout<<start->unweightedDistance<<",";
	bool comma=true;
	while(!reverse_path.empty())
	{		
		if(comma)
		{
			comma=false;
		}
		else
		{
			cout<<",";

		}
		cout<<reverse_path.top();
		reverse_path.pop();
	
	}
	cout<<endl;
}

      
void Graph::shortestWeightedPath(string startingCity, string endingCity) //Djik
{
// If the cities are in the same district, run Dijkstra’s algorithm 
// to find the shortest distance between the two cities. 

	vertex* start = findVertex(startingCity);
	vertex* end = findVertex(endingCity);
	for (int i = 0; i < vertices.size(); ++i) 
	{
		vertices[i].weightedDistance = 0;
		vertices[i].visited = false;
		vertices[i].parent = NULL;
	}

	if(start == NULL|| end==NULL)
	{
		cout<<"One or more cities doesn't exist"<<endl;
		return;
	}
	if(start->districtID<0 ||  end->districtID<0)
	{
		cout<< "Please identify the districts before checking distances" << endl;
		return;
	}
	if(start->districtID!= end->districtID)
	{
		cout<< "No safe path between cities" << endl;
		return;
	}
	//Data structure textbook 
	start->visited = true;
	start->weightedDistance = 0;
	vector<vertex*> solved; //list of solved vertices
	vertex* s;
	vertex* parent2;
	vertex* solvedV;
	int dist;
	int minDistance=0;
	solved.push_back(start);
	while (!end->visited)
	{
		minDistance = INT_MAX;
		solvedV = NULL;
		for (int x = 0 ;x<solved.size(); x++)
		{
			s = solved[x];
			for (int y = 0; y < s->adj.size();y++)
			{
				if(!s->adj[y].v->visited)
				{
					dist = s->weightedDistance + s->adj[y].weight;

					if(dist < minDistance)
					{
						solvedV = s->adj[y].v;
						minDistance = dist;
						parent2 = s;
						
					}
				}
			}
		}
		solvedV->weightedDistance = minDistance;
		solvedV->parent = parent2;
		solvedV->visited = true;
		solved.push_back(solvedV);
	}
	//Go backward, used part of BFS

	vector<vertex*>reverse_path;
	vertex* curv2 = end;

	while(curv2->parent !=NULL)
	{
		reverse_path.push_back(curv2);
		curv2 = curv2->parent;		
	}
	
	cout<<end->weightedDistance;
	reverse_path.push_back(curv2);
	
	for(int i = reverse_path.size()-1; i>=0; i--)
	{
		cout<<","<<reverse_path[i]->name;
	}
	
	cout<<endl;

}


void Graph::displayEdges() // this displays the graph and once the user
//presses assign district then this function will print the districts.
{

	for(int i = 0; i < vertices.size(); i++)
	{
		cout<< vertices[i].districtID <<" "<<vertices[i].name<<"-->";
		for(int j = 0; j<vertices[i].adj.size(); j++)
		{
		//for each adjacent vertex:
			cout<<vertices[i].adj[j].v->name;

			 if (j != vertices[i].adj.size()-1)
				{
					cout<<"***";
				}
		}
		cout<<endl;
	}
}

