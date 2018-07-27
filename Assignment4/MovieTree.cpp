// CSCI 2270 - Data Structures
// Author: Oceane Andreis
// Section: 310
// Assignment 4
// Instructor:  Christopher Godley


/*
This assignment wanted me to find a movie, Rent a movie, Print the inventory
, Delete a movie, Count the movies, and to Quit. So I needed a function add all the 
movies from the text files into a Binary Search Tree and then each node would have its 
own Linked List. The Linked List will alsor be sortes(alphabetically). When the user runs 
the program a menu with options will appear. When they choose find a movie, they have to enter
the movie and then it'll output all the information about the movie(ranking, year, quantity, and title).
If choosing rent, the user needs to enter a title and then the movie's quantity will decrease. When the quantity
reaches zero then it deletes

*/

#include <iostream>
#include <sstream>
#include <fstream>
#include "MovieTree.hpp"


using namespace std;

//constructor
MovieTree::MovieTree() 
{
  root = NULL;
  //DeleteAll(root);
}
//deconstructor
MovieTree::~MovieTree() 
{
	DeleteAll(root);
	root =NULL;
	//DeleteAll(root);
}
/*

When the user selects this option from the menu, your program should display all movie titles and the
quantity available in sorted order by title. Refer to the lecture notes as well as the text book on in-order
tree traversal, and linked list traversals, for more information.

*/

void MovieTree::printMovieInventory()
{

 printMovieInventory(root);

}


/*
When the user selects this option, your program should traverse the tree and singly linked lists and
count the total movie nodes in the tree and print the count.

*/


int MovieTree::countMovieNodes()
{
int count=0;

countMovieNodes(root, &count);

return count;
}


/*

When the user selects this option, they should be prompted for the title of the movie to delete. Your
code should then search the tree for the first letter of that movie, and then search the singly linked list
for the title. If the title is found, delete it from the singly linked list. If it was the only title for that letter
in the BST, you also need to delete the node in the BST and re-assign the parent and child pointers to
bypass the deleted node, and free the memory assigned to the node. If the movie is not found in the
search process, print “Movie not found” and do not attempt to delete. A movie node should also be
deleted when its quantity goes to 0.

*/

void MovieTree::deleteMovieNode(std::string title)
{
  	MovieNodeBST* tmp = searchBST(root,title); //Search the tree, find the correct node
  	//MovieNodeBST* parentBST=tmpll->parent;
  	
  	 if(tmp==NULL) //couldn't find the node
  	{
  		cout<< "Movie not found."<<endl;
  		//return;
  	}
  	else//
  	{

  		MovieNodeLL* tmpll= searchLL(tmp->head, title); //Search the Linked List and find the movie
  		MovieNodeBST* parentBST=tmp->parent;
  		if(tmpll==NULL)//couldn't find in the linked list
  		{
        	cout << "Movie not found." << endl;
        	//return;
    	}
    	else
    	{
    		MovieNodeLL *temp = tmp->head;
    	
	    	if(temp==tmpll) //If the head of the linked list is the title then we want to delete the head which tmpll
	    	{
	    		if(!tmpll->next)
	    		{
		    		delete tmpll;
		   			tmp->head=nullptr;
		   		}
		   		else
		   		{
		   			 tmp->head=tmp->head->next;
		     		//(Book Algorithm)
		      		delete tmpll; //Delete node at the head if there is a node after

		   		}
		      
		  	}
		  	else //Delete middle of Linked List 
		  	{ 
			    while(temp->next->title!=title) 
			    {
	      			temp=temp->next; //traverse
	      		}
	      		temp->next=tmpll->next;// same logic as above but instead of deleting the head we are deleting in the middle or tail
	     		 delete tmpll;
	     	}
	
			if (tmp->head==NULL)// If linked list is empty then we want to empty the node
     		{
     			//Case 1: Deleting a Leaf
		       if (tmp->leftChild == tmp->rightChild) 
		       { 
						if (tmp->parent==NULL)
							{
								delete root;
								root = nullptr;
							}
							else if (tmp->letter > tmp->parent->letter)
							{
								//Leaf Node on the right
								tmp->parent->rightChild = nullptr;
								delete tmp;
							}
							else if (tmp->letter < tmp->parent->letter)
								{
									//Leaf node on the left
									tmp->parent->leftChild = nullptr;
									delete tmp;
								}
				}

				//Case 2: Deleting a node with 1 children
				else if (!parentBST)
                    {
                        //Deleting the root, but the root has only one child

                        if (!tmp->rightChild)
                        {
                            //Left Child only
                            root = tmp->leftChild;
                            root->parent = nullptr;
                            delete tmp;
                        }
                        else
                        {
                            //Right Child only
                            root = tmp->rightChild;
                            root->parent = nullptr;
                            delete tmp;
                        }
                    }

				else if (tmp->leftChild == NULL && tmp->rightChild!=NULL)
				{		
						
						//Node is a right child  and has a left child
						if(tmp->parent->leftChild==tmp)
						{
							tmp->parent->rightChild = tmp->leftChild;
                            parentBST->rightChild->parent = parentBST;
                            delete tmp;
							
						}
						//Node is a right child  and has a right child
						else
						{
							tmp->parent->rightChild = tmp->rightChild;
                            parentBST->rightChild->parent = parentBST;
                            delete tmp;
							
						}
				}

				else if (tmp->leftChild != NULL && tmp->rightChild==NULL)
				{

						//Node is a left child  and has a left child
						if(tmp->parent->leftChild==tmp)
						{
							 tmp->parent->leftChild = tmp->leftChild;
                            parentBST->leftChild->parent = parentBST;
                            delete tmp;
							
						}
						//Node is a left child  and has right child
						else
						{
							tmp->parent->leftChild = tmp->rightChild;
                            parentBST->leftChild->parent = parentBST;
                            delete tmp;
							
						}
				}

				// case 3: Deleting a node with 2 children
				else 
				{
					MovieNodeBST *min = treeMinimum(tmp->rightChild);
					min->leftChild= tmp->leftChild;
					tmp->leftChild->parent=min;

					if(tmp->parent == NULL) //Deleting the root
					{
						root=tmp->rightChild;
						root->parent=nullptr;
					}
					else
					{
						if (tmp->letter > tmp->parent->letter) 
							{
								tmp->parent->rightChild = tmp->rightChild;
								parentBST->rightChild->parent=parentBST;
							} 
							else 
							{
								tmp->parent->leftChild = tmp->rightChild;
								parentBST->leftChild->parent=parentBST;
							}

					}


				}


		    }// end of deleting node

    	}

	}
}


/*


When the user starts the program they will pass it the name of the text file that contains all movie
information. Each line in the file shows the IMDB ranking, title, year released, and quantity in stock. Your
program needs to handle that command line argument, open the file, and read all movie data in the file.
From this data, build the BST ordered by the first letter in the movie title. For each of the nodes in the
BST, there should be a sorted singly linked list of the actual movie data. Note: the nodes should be added
to the BST and Linked Lists in the order they are read in. The name of the file that contains the movie
data is Assignment4Movies.txt.


*/

void MovieTree::addMovieNode(int ranking, string title, int releaseYear, int quantity)
{
    MovieNodeLL* movie = new MovieNodeLL(ranking, title, releaseYear, quantity);
    MovieNodeBST * ParentTitle;
    MovieNodeBST * anothertmp;
    char firstletter =title[0];
    //
    if(root == NULL)//Add the root
    {
        root = new MovieNodeBST(title[0]);
        root->head = movie;
        return;
    }
   anothertmp = root;

    while(anothertmp != NULL)
        {
            if (anothertmp->letter == firstletter)//found correct BST node
            {
                break;
            }

            ParentTitle = anothertmp;

            if (firstletter > anothertmp->letter)
            {
                anothertmp = anothertmp->rightChild;
            }
            else if (firstletter < anothertmp->letter)
            {
                anothertmp = anothertmp->leftChild;
            }
        }
   
    if(anothertmp == NULL)// Add new node(Movie Bst node) (letter node)
    {
        if(ParentTitle->letter<firstletter)
        {
            MovieNodeBST* newNode = new MovieNodeBST(firstletter);
            ParentTitle->rightChild = newNode;
            newNode->parent = ParentTitle;
            anothertmp = newNode;
            newNode->head = movie;

        }
        else if(ParentTitle->letter>firstletter)
        {
            MovieNodeBST* newNode = new MovieNodeBST(firstletter);
            ParentTitle->leftChild = newNode;
            newNode->parent = ParentTitle;
            anothertmp = newNode;
            newNode->head = movie;
        }
    }
    else if (anothertmp != NULL)// Add to anothertmp linked list
    {


    		if(anothertmp->head==NULL) //Add the head;
    			{
		    		anothertmp->head=movie;
		    		return;
    			}


    		if(anothertmp->head->title > movie->title)
    		{
    			movie->next=anothertmp->head;
    			anothertmp->head=movie;
    			
    		}
    		else
    		{
				MovieNodeLL *addtolist=anothertmp->head;
		    		
	    		while((addtolist->next) && (addtolist->next->title < movie->title))
	    		{
	    			
	    			addtolist=addtolist->next;
	    		}
	    		movie->next = addtolist->next;
	    		addtolist->next=movie;

	    	}
    }  
   
}

/*

When the user selects this option from the menu, they should be prompted for the name of the movie.
Your program should then search the tree and singly linked lists and display all information for that
movie. If the movie is not found, your program should display, “Movie not found.”

*/

void MovieTree::findMovie(string title)
{
	
	MovieNodeBST* movie = searchBST(root,title);
    
	if (movie == NULL) //check if it's BST
	{
		cout << "Movie not found." << endl;
		
		return;
	}
	
	MovieNodeLL * moviefind = searchLL(movie->head, title);
	if(moviefind==NULL)//check if it's in linked list
	{
		cout << "Movie not found." << endl;	
	}
	
	if(moviefind!=NULL)
    {
    cout << "Movie Info:" << endl;
	cout << "===========" << endl;
	cout << "Ranking:" << moviefind->ranking << endl;
	cout << "Title:" << moviefind->title << endl;
	cout << "Year:" << moviefind->year << endl;
	cout << "Quantity:" << moviefind->quantity << endl;
    }

}

/*

When the user selects this option from the menu, they should be prompted for the name of the movie.
If the movie is found in your data structure, your program should update the Quantity in stock property
of the movie and display the new information about the movie.
If the movie is not found, your program should display, “Movie not found.” When the quantity reaches
0, the movie should be deleted from the singly linked list. If that was the only node in the singly linked
list, the node should also be deleted from the BST for that letter.

*/
void MovieTree::rentMovie(string title)
{
	//rent same as findmovie but you want to decrease the quantity

	MovieNodeBST* movie = searchBST(root,title);
    
	if (movie == NULL) 
	{
		cout << "Movie not found." << endl;
		return;
	}
	MovieNodeLL * moviefind = searchLL(movie->head, title);
	  if(moviefind==NULL)
    {
    	cout<<"Movie Not Found."<<endl;
    	return;
    }
	
	if(moviefind!=NULL && moviefind->quantity!=0)
    {
   	moviefind->quantity--;
   	cout << "Movie has been rented." << endl; 
    cout << "Movie Info:" << endl;
	cout << "===========" << endl;
	cout << "Ranking:" << moviefind->ranking << endl;
	cout << "Title:" << moviefind->title << endl;
	cout << "Year:" << moviefind->year << endl;
	cout << "Quantity:" << moviefind->quantity << endl;
    }
    if(moviefind->quantity == 0)
    {
    	
    	deleteMovieNode(moviefind->title);

    }

}

//Private function seperations


void MovieTree::DeleteAll(MovieNodeBST * node) //use this for the post-order traversal deletion of the tree

{
	if(node==NULL)
	{
		return;
	}
	//Go left;
	DeleteAll(node->leftChild);
	//Go right;
	DeleteAll(node->rightChild);
	//Delete Linked List
	MovieNodeLL *tmp=node->head;
	MovieNodeLL *tmp_next=node->head;
	//Lecture code
	while(tmp!= NULL) //this while loop deletes the nodes in the linked list
	{

		cout<<"Deleting: "<<tmp->title<<endl;
		tmp_next=tmp->next;
		deleteMovieNode(tmp->title);
		tmp=tmp_next;
	}
}


void MovieTree::printMovieInventory(MovieNodeBST * node)
{	
	if (node!= NULL) 
	{	
		printMovieInventory(node->leftChild);
		MovieNodeLL *node1 = node->head;
	
		while(node1 !=NULL)
		{
			cout << "Movie: " << node1->title << " " << node1->quantity << endl;
			node1=node1->next;
		}
		
		printMovieInventory(node->rightChild);
	}
}

void MovieTree::countMovieNodes(MovieNodeBST *node, int *c)
{
	
	if(node->leftChild!=NULL)
	{
		countMovieNodes(node->leftChild, c);
	}

	MovieNodeLL* tmp= node->head;
	while(tmp !=NULL)
	{
		(*c)+=1;
		tmp=tmp->next;
	}

	if(node->rightChild!=NULL)
	{
		countMovieNodes(node->rightChild,c);
	}
}


 MovieNodeBST*MovieTree::searchBST(MovieNodeBST *n, string value)
 {
 	char letter=value[0];
 	bool found=false;
 	n=root;
	if (n == NULL) 
	{ 
		cout<<"Print1:"<<endl;
		return NULL;	
	}
	
	if (n->letter == value[0] ) 
	{	
		return n;
	} 
	
	MovieNodeBST *tmp=n;
	while(!found && tmp!=NULL)
	{
		if(letter<tmp->letter)
		{
			
			tmp=tmp->leftChild;
		}
		else if (letter >tmp->letter)
		{
			
			tmp=tmp->rightChild;
		}
		else if(letter == tmp->letter)
		{
			
			found=true;
		}
	}
 return tmp;	
}

 MovieNodeLL*MovieTree::searchLL(MovieNodeLL* head, string movietitle) //use this to return a pointer to a node in a linked list, given a MOVIE TITLE and the head of the linked list
 {
			MovieNodeLL* tmp = head;

			while (tmp != NULL) 
			{
				if (tmp->title == movietitle) 
				{	
					return tmp;
				} 
				else 
				{
					tmp = tmp->next; //Traverse the list until you find the title
				}
			}
			return nullptr;		
 }
 MovieNodeBST*MovieTree::treeMinimum(MovieNodeBST *node) //use this to find the left most leaf node of the BST, you'll need this in the delete function
 {
 	if (node->leftChild != NULL ) 
 		{ // go left!
			return treeMinimum(node->leftChild);
		}
		return node;
 }
