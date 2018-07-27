# Final Project README
## Header
Oceane Andreis
July 22 2018
Part 1 and part 2
CSCI 2270 Section 310


## Description

* void addEdge Used to build the graph
* void addVertex Used to build the graph
* int isAdjacent When the user starts the
program, read in the cities and distances from the text file and build a graph where each city is
a vertex, and the adjacent cities are stored in an adjacency list for each vertex
* void displayEdges This displays the graph(vertices and adj vertices)
* void assignDistricts This uses the Depth First search algorithm
* void shortestPath(Breadth First Search) This uses the Breadth First Search algorithm
* void shortestWeightedPath(Dijkstras) This uses the dijkstras algorithm


##File Description

* This zip file contains FinalPart1.cpp FinalPart1Main.cpp FinalPart2.cpp FinalPart2Main.cpp Graph.h and Graph.hpp(part 2)
* I only have my .cpp files. 

## Build descriptions

* [Sublime] & [Terminal]
* I simply use the command g++ -std=c++11  -o  code FinalPart1.cpp FinalPart1Main.cpp then press enter
* After that I enter ./code zombieCities.txt
* I simply use the command g++ -std=c++11  -o  code FinalPart2.cpp FinalPart2Main.cpp then press enter
* After that I enter ./code zombieCities.txt


## Miscellaneous

* If INT_MAX doesn't work for you, you can just replace it with a large number(used in  shortestWeightedPath)(I heard for some people it works and for some it doesn't)
