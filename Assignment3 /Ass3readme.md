# Assignment 3 README
## Header
Oceane Andreis
June 29 2018
Assignment3.cpp 
CSCI 2270 Section 310


## Description

* My addCity inserts a new city into the linked list after the previousCityName. 
* The name of the new city is in the argument newCityName. 
* My transmitMsg opens the file and transmit the message between all cities in the network word by word.
* A word needs to be received at the beginning of the network after being sent to the end of the network* before sending the next word (coast to coast to coast). 
* Only one city can hold the message at a time; 
* as soon as it is passed to the next city, it needs to be deleted from the sender city. 
* My printNetwork starts at the head of the linked list and print the name of each city in order to the 
* end of the list. 
* My buildNetwork
* Build the initial network from the cities given in this writeup. The cities can be fixed in the 
* function,you do not need to write the function to work with any list of cities. 
* My deleteCity finds the city in the network where city name matches removeCity. Change the next and  
* previous pointers for the surrounding cities and free the memory. 
* My deleteNetwork deletes all cities in the network, starting at the head city. 


##File Description

* I only have my .cpp file. 

## Build descriptions

* [Sublime] & [Terminal]
* I simply use the command g++ -o Assignment3 Assignment3.cpp then press enter
* After that I enter ./Assignment2 messageIn.txt
* (I pass in the text file provided for this assignment)
* Make sure to build the network before adding or deleting or transmitting or printing anything.


## Miscellaneous

* No extra info




