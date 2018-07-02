# Assignment 2 README
## Header
Oceane Andreis
June 22 2018
Assignment2.cpp 
CSCI 2270 Section 310


## Description

* My code reads in a file that has the book Hunger game. I have functions like :
* My getstopword reads stop word list from file and store into an array
* My isStopWord checks to see if it is a stop word
* My getTotalNumberNonStopWords computes the total # of words saved in the words array(including repeated words)
* My arraySort sorts an array of wordItems, decreasing by their count fields 
* My printTopN prints the top N high frequency words.(Like the 10 most common words)
* My search checks in the array(unique) if the word we are at is already in the array.
* My doubleArray just doubles the size of my array
* In my main I return the nth most common words, then how many times my array has been doubled, then 
* how many Unique non-common words, and how many Total non-common words.


##File Description

* I only have my .cpp file. 

## Build descriptions

* [Sublime] & [Terminal]
* I simply use the command g++ -o Assignment2 Assignment2.cpp then press enter
* After that I enter ./Assignment2 10 HungerGame_edit.txt ignorewords.txt
* (I pass in the text file provided for this assignment)


## Miscellaneous

* No extra info




