// CSCI 2270 - Data Structures
// Author: Oceane Andreis
// Section: 310
// Assignment 1
// Instructor:  Christopher Godley

/*
    For this assignment,I have a function that matches Item together. For example, 
    it finds a car that's for sale and a car that's wanted and if the price matches for 
    sale or is higher than the pair is a match. When I find a match it removes it from 
    my array, with the help of my deletearrayelement function. Which then just
    leave what hasn't been matched. Additionally, I have a function to turn a string into a boolean. 
    My readfile function calls all the other function. I have two counters in it to keep count of 
    how much item are left or how much remains. I use stringstream and getline to read the file and 
    separate the categories.
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

// made struct
struct Item
{
    string type;
    bool status;
    int price;

};

//This function converts item status to boolean
bool ToBool(string saleStatus){
    if (saleStatus == " wanted"){
        return true;
    }
    return false;
}

//Taken from the book, It shifts the array thus deleting an element
int deleteArrayElement(Item array[], int index, int numElements)
{
    for (int x = index; x<numElements - 2; x++) //less than or equal to
    {
        
          array[x] = array[x+1];
    }
   
     numElements = numElements - 1;
     return 0;
}

// My find match matches similar object with the right status and price required for a match
int findmatch(Item array[], Item secondarray[], Item key, int counter2)
{
    bool whichcase = false;
    int index = -1;//-1 not found
    for(int i = 0; i < 100; i++)
    {
        
        if(array[i].type == key.type && (array[i].status != key.status))  //compare two item and see if they have different status
        {
            
            if(key.status == 0 && key.price <= array[i].price) //if the item is wanted and that its price is lower than the same item for sale
            {
                index = i;
                whichcase = true;
                break;
            } else if(key.status == 1 && key.price >= array[i].price) //if the item is for sale and that its price is bigger than the price for whoever wants it.
            {
                
                index = i;
                break;
            }
        }
    }
    
    //secondarray =item sold array
    if(index!=-1)
    {
            
         secondarray[counter2]=array[index];
         if(whichcase==true) //for sale price is less than the wanted price and the item is for sale is key (item key)
            secondarray[counter2].price = key.price; //the price of the item for sale even if the wanted was higher
         
        
        //if two matches then delete
        //call delete array in here
         
         deleteArrayElement(array, index, 100);
    }

    return index;
   
}

void readfile(string filename, Item array[], Item secondarray[])
{
    ifstream file; 
    file.open(filename);
    string line;
    //do a get line with while
    
    //getline (ss,get one for each  like for type,status,price (seperate with',')
    int counter=0;
    int counter2=0;
  
     while((getline(file, line)) && (counter<100))
        {

            stringstream ss(line);   // string stream let's me split the line I get from the file
            
            
            string tempType;
            string tempStatus;
            string tempPrice;

            getline(ss, tempType, ',');
            getline(ss, tempStatus, ',');
            getline(ss, tempPrice); //no need to add comma since it's at the end


            array[counter].type=tempType; //linked with the struct above
            array[counter].status=ToBool(tempStatus);
            array[counter].price=stoi(tempPrice); //convert string to integer
            

            int index=findmatch(array, secondarray, array[counter],counter2); // Call the index from findmatch
              
            if( index!=-1) //if match then delete the match from the array
            {
                
                deleteArrayElement(array, counter-1, 100);
                counter= counter-1;
                 
                   counter2++;

            }
            counter++;
            
        }

}
//populate the array with Items sold and then an array of items remaining. 
//Use the find match
//Items sold.
//#
//Items remaining in the message board after reading all lines in the file.
//#

int main(int argc, char* argv[]) 
{
    Item itemArray[100]; //struct
    Item secondarray[100];
    int counter=0;
    int counter1=0;

    // Reads file lines and prints out items that were matched
    readfile(argv[1], itemArray, secondarray);
    for(int i = 0; i < 100; i++) 
        {

            if(secondarray[i].type != "") 
            {
                cout<<secondarray[i].type<<" "<<secondarray[i].price<<endl;
                counter=counter+1;
            }

        }
        cout<<counter<<endl;

    // Prints its remaining(no match found)
    for(int i = 0; i < 100; i++) 
    {
        if(itemArray[i].type != "") 
        {
            counter1=counter1+1;
            if(itemArray[i].status == 1) 
            {
                cout<<itemArray[i].type<<", wanted, "<<itemArray[i].price<<endl;
            } 
            else 
            {
                cout<<itemArray[i].type<<", for sale, "<<itemArray[i].price<<endl;
            }
        }
    }
    
    cout<<counter1<<endl;
}