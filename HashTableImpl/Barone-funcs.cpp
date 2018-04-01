/*****************************************************************************
	CODE FILENAME: Barone-assn3-funcs.cpp
	DESCRIPTION:   This file contains the function definitions for the project
				   Barone_Vickrey-assn3
	CLASS/TERM:    CS372_XIN-X40_Advanced Programming and Algorithms
	IMPLEMENTED BY:   Mark Barone
*****************************************************************************/

#include <iostream>				//for I/O
#include <iomanip>				//for formatting output
#include <cstddef>				//for definition of null
#include <cmath>				//for logarithm definition

using namespace std;

#include "Barone_Vickrey-assn3-common.h"
#include "Barone-assn3-funcs.h"
#include "Vickrey-assn3-funcs.h"
//********************************************************************* 
//  FUNCTION: ModHashFunc3 
//  DESCRIPTION: Calls function to initialize array of pointers, then performs
//				 modulo division to determine initial key address value and
//				 separate chaining collision resolution 
//  INPUT: 
//      Parameters: numArray - array of random key values to hash
//					chainHash - a points to array of keyNode pointers 
//					hashSize - size of hash table    
//  OUTPUT:   
//      Parameters: full - true if no memory space to allocate 
//  CALLS TO:  InitChainTable, CreateNode
//	IMPLEMENTED BY:		Mark Barone 
//********************************************************************** 

void ModHashFunc3(arrayPtr numArray, keyNode** chainHash, int hashSize,
					bool& full)
{
	//variable declarations
	int address, 					//address to store key info (key % hashSize)
		key,						//value to hash and store
		idx = 0;					//used to manipulate array index
		
	//points to new node to insert into linked list
	nodePtr newNode;
	
	//while random numbers still to hash and memory to allocate
	while((!full) && (idx < MAX_NUMBERS)){

		//perform mod div hash
		address = numArray[idx] % hashSize;
		//key value to store
		key = numArray[idx];
		//create new node to store at address
		newNode = CreateNode(key, full);
		//insert node if memory was allocated
		if(!full){
			// If the hash address is empty, point array pointer to new node
			if (chainHash[address] == NULL) {
				chainHash[address] = newNode;
			}
			// Else, place newNode as first node in linked list
			else {
				newNode->next = chainHash[address];
				chainHash[address] = newNode;
			}
		}
			
		idx++;		
	}//end while
	
	//prompt user if unable to allocate list nodes for all key values
	if(full){
		cout << " Error: Heap is full, separate chaining method could not"
			 << " be tested" << endl << endl;
	}
	
	return;
}					
//********************************************************************* 
//  FUNCTION: ChainSearchFunc
//  DESCRIPTION: Searches for half of the key values in chain hash table, to
//				 determine number of collisions
//  INPUT: 
//      Parameters: numArray - array of random key values to hash
//					chainHash - points to chain hash table array
//					hashSize - max capacity of hash table   
//  OUTPUT:   
//      Returns: Count - number of elements examined in list
//  CALLS TO:	ChainHashFunc
//	IMPLEMENTED BY:		Mark Barone 
//********************************************************************** 					
int ChainSearchFunc(arrayPtr numArray, keyNode** chainHash, int hashSize)
{
	//variable declaration	
	int address, 				//address to search for key value
		key,					//value to search hash table for
		counter = 0;			//number of items examined while searching 

	//loop to search all even elements 
	for(int x = 0; x < MAX_NUMBERS; x += 2){
		//mod div key to get hash address
		address = numArray[x] % hashSize;
		//key value to search
		key = numArray[x];

		//if key value found in first node increment count, and search next key
		if (chainHash[address]->keyVal == key){
			counter++;
		}
		//call function to traverse list searching for key value
		else {
			counter += ChainHashFunc(address, key, chainHash);
		}	
	}//end loop

	return counter;
}				
					
//********************************************************************* 
//  FUNCTION: ChainHashFunc
//  DESCRIPTION: Traverses linked list searching for node that stores key value 
//  INPUT: 
//      Parameters: address - location in table to search
//					chainHash - points to chain hash table array
//					key - value to search for stored at address   
//  OUTPUT:   
//      Returns: Count - number of nodes searched before key is found
//	IMPLEMENTED BY:		Mark Barone 
//********************************************************************** 					
int ChainHashFunc(int address, int key, keyNode** chainHash){
	
	//variable declarations
	keyNode* temp;					//temp pointer to traverse list
	int count = 0;					//counts number of nodes searched 
	
	//set temp to first node in chain list
	temp = chainHash[address];
	count++;

	//traverse list counting nodes	
	while(temp->keyVal != key){
		temp = temp->next;				//check next node in list
		count++;
	}

	return count;
}					

//********************************************************************* 
//  FUNCTION: InitOpenTable
//  DESCRIPTION: Initializes dynamic array of integers
//  INPUT: 
//      Parameters: hashSize - size of hash table to initialize
//  OUTPUT:   
//      Returns: full - true if no memory to allocate
//		Parameter:	hash - points to initialized array
//	IMPLEMENTED BY:		Mark Barone 
//********************************************************************** 
bool InitOpenTable(arrayPtr& hash, int hashSize){
	
	//variable declaration
	bool full = false;					//true if no space to allocate
	
	//allocate an array of integers size of hash table
	hash = new (nothrow) int[hashSize];
	//check that array was allocated
	if(hash == NULL){
		full = true;
		cout << " Heap Error: cannot allocate array, program will exit " 
			 << endl;
	}
	//initialize all values to zero if array is allocated	
	if(!full){
		for (int i = 0; i < hashSize; i++)
			hash[i] = 0;
	}
		
	return full;
}

//********************************************************************* 
//  FUNCTION: InitChainTable
//  DESCRIPTION: Initializes dynamic array of pointers to type keyNode 
//  INPUT: 
//      Parameters: hashSize - size of hash table to initialize
//  OUTPUT:   
//      Returns: full - true if no memory to allocate
//		Parameter:	chainHash - pointer to initialized array
//	IMPLEMENTED BY:		Mark Barone 
//**********************************************************************
keyNode** InitChainTable(keyNode** chainHash, int hashSize, bool& full){	
	
	//allocate an array of keyNode pointers to size of hash table
	chainHash = new keyNode*[hashSize];
	
	//check that array was allocated
	if(chainHash == NULL){
		full = true;
		
		cout << " Heap Error: cannot allocate array, program will exit " 
			 << endl;
	}

	//initialize all pointers to NULL if space available	
	if(!full){
		for (int i = 0; i < hashSize; i++)

			chainHash[i] = NULL;
	}
		
	return chainHash;
}
//********************************************************************* 
//  FUNCTION: CreateNode
//  DESCRIPTION: Allocates memory for a new keyNode, initializes if space avail
//  INPUT: 
//      Parameters: key - value to store in node  
//  OUTPUT:   
//      Returns: newNode - points to address of new keyNode
//		Parameter:	full - true if no memory available
//	IMPLEMENTED BY:		Mark Barone 
//********************************************************************** 
nodePtr CreateNode(int key, bool& full){
	
	//variable declaration
	nodePtr newNode;					//temp pointer to new node
	
	//allocate space for new keyNode
	newNode = new (nothrow) keyNode;
	
	//verify node was allocated
	if(newNode == NULL){
		full = true;
	}
	//initialize new node and store key
	else{
		newNode->keyVal = key;			//store key value
		newNode->next = NULL;			//set pointer to NULL
	}
	
	return newNode;
}

//********************************************************************* 
//  FUNCTION: CalcKnuth
//  DESCRIPTION: Calculates Knuths average time analysis for linear probing, 
//				 double hashing, and separate chaining methods
//  INPUT: 
//      Parameters: loadFactor - ratio of current table storage to capacity   
//  OUTPUT:   
//		Parameter:	linExp - expected # of examined items for linear probe  
//					dblExp - expected # of examined items for double hashing
//					chnExp - expected # of examined items for chain hashing
//	IMPLEMENTED BY:		Mark Barone 
//********************************************************************** 
void CalcKnuth(float loadFactor, float& linExp, float& dblExp, float& chnExp){
	
	linExp = (((1 / (1 - loadFactor)) + 1) * .5);
	
	dblExp = ((-log(1 - loadFactor)) / loadFactor);
	
	chnExp = (1 + (loadFactor / 2));
	
	return;
}

//********************************************************************* 
//  FUNCTION: CalcAvgs
//  DESCRIPTION: Calculates average # of elements examined for linear probing, 
//				 double hashing, and separate chaining methods
//  INPUT: 
//      Parameters: hashSize - max capacity of hash table
//					linearItems - # of items examined in linear search
//					doubleItems - # of items examined in double search
//					chainItems - # of items examined in chain search   
//  OUTPUT:   
//		Parameter:	linAvg - avg # of elements examined per linear probe  
//					dblAvg - avg # of elements examined per double hash
//					chnAvg - avg # of elements examined per chained hash
//	IMPLEMENTED BY:		Mark Barone 
//********************************************************************** 
void CalcAvgs(float& linAvg, float& dblAvg, float& chnAvg, int hashSize,
				int linearItems, int doubleItems, int chainItems)
{
	
	linAvg = static_cast<float>(linearItems) / SEARCH_SIZE;
	
	dblAvg = static_cast<float>(doubleItems) / SEARCH_SIZE;
	
	chnAvg = static_cast<float>(chainItems) / SEARCH_SIZE;
	
	return;
}

//********************************************************************* 
//  FUNCTION: DisplayResults
//  DESCRIPTION: Displays results of hashing tests
//  INPUT: 
//      Parameters: loadFactor - ratio of table capacity used
//				    hashSize - max capacity of table
//					linExp - expected linear probe result
//					dblExp - expected double hash result
//					chnExp - expected chain hash result
//					linAvg - actual linear probe result
//					dblAvg - actual double hash result
//					chnAvg - actual chain hash result
//					linearItems - total elements examined in linear search
//					doubleItems - total elements examined in double search
//					chainItems - total elements examined in chain search
//	IMPLEMENTED BY:		Mark Barone 
//********************************************************************** 
void DisplayResults(float loadFactor, int hashSize, float linExp, float dblExp,
				     float chnExp, float linAvg, float dblAvg, float chnAvg,
					  int linearItems, int doubleItems, int chainItems)
{
	
	cout << fixed << setprecision(3);
	
	//display header
	cout << setw(8) << ' ' << MAX_NUMBERS << " items loaded into a "
		 << hashSize << " element hash table" << endl << setw(7) << ' '
		 << " Load Factor = " << loadFactor << endl << endl << setw(7) << ' '
		 << " Results of searching for 2500 items:" << endl << endl;
	
	//display linear probing test results	 
	cout << setw(14) << ' ' << " Linear Probing" << endl << setw(17) << ' '
		 << linearItems << " items examined (avg = " << linAvg
		 << " items examined per search)" << endl << setw(17) << ' '
		 << "  vs Knuth predicted avg = " << linExp << " items examined per "
		 << " search" << endl << endl; 	
	
	//display double hashing test results	 
	cout << setw(14) << ' ' << " Double Hashing" << endl << setw(17) << ' '
		 << doubleItems << " items examined (avg = " << dblAvg
		 << " items examined per search)" << endl << setw(17) << ' '
		 << "  vs Knuth predicted avg = " << dblExp << " items examined per "
		 << " search" << endl << endl; 
	
	//display chained hashing results if enough space to allocate while hashing
	if(chainItems > 0){
	cout << setw(14) << ' ' << " Chained Hashing" << endl << setw(17) << ' '
		 << chainItems << " items examined (avg = " << chnAvg
		 << " items examined per search)" << endl << setw(17) << ' '
		 << "  vs Knuth predicted avg = " << chnExp << " items examined per "
		 << " search" << endl << endl; 
	}
	//could not perform chained hashing test
	else
		cout << setw(14) <<  ' ' << " Separate chaining method not tested" 
			 << endl;
			 
	return;
}

//********************************************************************* 
//  FUNCTION: DeleteTables
//  DESCRIPTION: De-allocates dynamic arrays and linked lists
//  INPUT: 
//      Parameters: linearHash - pointer to linear array
//					doubleHash - pointer to double array
//					chainHash - pointer to chain array  
//  OUTPUT:   
//		Parameter:	linearHash - points to NULL
//					doubleHash - points to NULL
//					chainHash - points to NULL
//	IMPLEMENTED BY:		Mark Barone 
//********************************************************************** 
void DeleteTables(arrayPtr& linearHash, arrayPtr& doubleHash, 
					keyNode** &chainHash, int hashSize)
{
	//variable declaration
	keyNode* temp;						//temp node pointer to traverse list
	
	//de-allocate dynamic linear array
	delete [] linearHash;		
	//de-allocate dynamic double array		
	delete [] doubleHash;
	
	//loop to traverse array of pointers
	for(int x = 0; x < hashSize; x++){
		//loop to traverse list to delete all nodes
		while(chainHash[x] != NULL){
			temp = chainHash[x];			//point temp to first node
			chainHash[x] = temp->next;		//point list to next node
			delete temp;					//delete first node
		}//end loop at list
		
	}//end loop at array

	//de-allocate array of pointers
	delete [] chainHash;
	
	//set pointers to NULL
	linearHash = NULL;
	doubleHash = NULL;
	chainHash = NULL;
	
	return;
}
