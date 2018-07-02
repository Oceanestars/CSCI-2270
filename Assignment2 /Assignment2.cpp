// CSCI 2270 - Data Structures
// Author: Oceane Andreis
// Section: 310
// Assignment 2
// Instructor:  Christopher Godley



/*
In this assignment I have to count the most common words and exclude the ignoreword file 
from the common words. Since hunger game file has a ton of word I have to
 double the array,double the size as words are read in from the 
file and the array fills up with new words. I also have to store the unique words found in the file in
a dynamically allocated array and print the top 10 most common  word and then
count how many time they reappear(counting duplicate is important. Count how many unique words they are(unique word that are not common)
and the count the amount of total non-common word so it's ok if they reappear.
My getstopword reads stop word list from file and store into an array
My isStopWord checks to see if it is a stop word
My getTotalNumberNonStopWords computes the total # of words saved in the words array(including repeated words)
My arraySort sorts an array of wordItems, decreasing by their count fields 
My printTopN prints the top N high frequency words.(Like the 10 most common words)
My search checks in the array(unique) if the word we are at is already in the array.
My doubleArray just doubles the size of my array
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


using namespace std;


struct wordItem 
{
	string word;
	int count;
};


void getStopWords(char *ignoreWordFileName, string ignoreWords[])
//Purpose: read stop word list from file and store into an array
//Parameter:- filename(the file storing ignore words)
//Parameter:- store ignore words from the file(pass by reference) * return-none
//the number of words is fixed to 50
{

	ifstream file; 
    file.open(ignoreWordFileName);
 
    string line;
    int index = 0;


     while(getline(file, line))
        {
            stringstream ss(line);   // string stream let's me split the line I get from the file
            string word;

            while (ss>>word) 
            {
                ignoreWords[index] = word;
                index++;

            }
    
        }
        file.close();
        return;
}

bool isStopWord(string word, string ignoreWords[]) 
//checks to see if it is a stop word
//Parameter:- a word(which you want to check if it is a stop word)
//Parameter;- the array of strings storing ignore/stop words- return true
//if words is a stop word, or false(otherwise)
{
    for (int i = 0; i <50 ; i++) 
    {
        if (word == ignoreWords[i]) 
        {
            return true;
        }
  	    
    }
    return false;
}

int getTotalNumberNonStopWords(wordItem* list, int length)
//Compute the total # of words saved in the words array(including repeated words)
//Parameter:-List- an array of wordItems containing non-stopwords
//Parameter:length- the length of the words array
//return-the total number of words in the array(including repeated words multiple times)
{
  int sum = 0;
  for(int i = 0; i < length; ++i){
    sum += list[i].count;
  }
  return sum;
}

void arraySort(wordItem list[], int length)
//Sort an array of wordItems, decreasing by their count fields 
//Parameter:-an array of wordItems to be sorted
//Parameter: length-the length of the words array
{
    for(int i = 1; i<length; i++)
    {
        for(int j=0; j<length-1;j++)
        {
          if(list[j].count<list[j+1].count)
          {
              wordItem temp;
              temp = list[j];
              list[j] = list[j+1];   
              list[j+1] = temp;             
          }
        }
    }
    //return length;
}

void printTopN(wordItem wordItemList[], int topN)
//To print the top N high frequency words
//Parameter: wordItemList- a pointer that points to a sorted array of 
//wordItems 
//Parameter: topN - the number of top frequency words to print
//return none
{
for (int i = 0; i < topN; i++) 
	{
		cout << wordItemList[i].count << " - " << wordItemList[i].word << endl;
	}	
}


bool search(wordItem *unique, string z, int count)
//This is an additional helper function to check if the word(z) 
// is in the unique array
{
  bool ismatch=false;
  int y=0;
  while(!ismatch &&  y<count)
  {
    if(unique[y].word == z) //(unique[y].word == z)// if already in our array/dict
    {
      unique[y].count++;
      ismatch=true;
    }
    y++;
  }
  return ismatch;
}


void doubleArray(struct wordItem* &track, int counter, int high)
//This function just doubles the array when it reaches its max and
// then we allocate some memory on the heap(new). We store the words in the 
//new array and free the old array. 
{
wordItem *nouveauunique = new wordItem[high];


    for(int i=0; i<counter; i++)
       {
          nouveauunique[i]=track[i];               
       }
        
        delete [] track;
        track=nouveauunique;                                    
}



int main(int argc, char* argv[])

{
int count=100;
int head=0; //count unique words
string line;
string word;
int index = 0; //count non stop words
int doublecountarray=0;
int top=atoi(argv[1]);

wordItem *unique=new wordItem[100];
string ignoreWords[50];


getStopWords(argv[3], ignoreWords);

	ifstream file; 
	file.open(argv[2]); //gethungergame
 
  
     while(getline(file, line))
        {

            stringstream ss(line);   // string stream let's me split the line I get from the file            
          
            while (ss>>word) 
            {
              //cout<<"PART word:"<<word<<endl;
               bool checkignore =isStopWord(word, ignoreWords) ; //check if the word is an ignore word
               bool found = search(unique, word, head);
              
               
                if(checkignore ==false && found==false) //found checks if the word is unique or not
                {
                  //if it's false then the word is unique

                  index++;
                    
                      if(count>head)
                      {
	                       unique[head].count+= 1;
	                       unique[head].word=word;
                        
                      }
                      else
                      {
                      	//Start of the doubling array
	                      count = count*2;
	                     
	                      doublecountarray+=1;
	                      doubleArray(unique, head, count);
	                      unique[head].count+= 1;
	                      unique[head].word=word;

                      }

                      head+=1;
                }
                    //If the word is not unique, we want to increase the counter.
                else if ((found==false) && search(unique, word, count)==true)
                {
                  index++;
                  for(int i=0 ; i<head ; i++)
                  {
                    if(line == unique[i].word)
                    {
                      unique[i].count=unique[i].count+1;
                    }
                  }
                }
            }
                    
        }   
arraySort(unique, head); //sort the array before you print 
printTopN(unique, top );
file.close();      

cout<<"#"<<endl;

cout<< "Array doubled: "<< doublecountarray<<endl;

cout<<"#"<<endl;

cout<<"Unique non-common words: "<<head<<endl; 

cout<<"#"<<endl;

cout << "Total non-common words: "<< getTotalNumberNonStopWords( unique, count)<<endl;
}
