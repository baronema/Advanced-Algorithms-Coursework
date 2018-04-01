/*****************************************************************************
	CODE FILENAME: Barone_Vickrey-assn3-main.cpp
	DESCRIPTION:   This program tests three different hashing collision methods
				   linear probing, double hashing, and separate chaining.
				   It then displays average results of each test compared
				   to the Knuth prediction for the method. 
	CLASS/TERM:    CS372_XIN-X40_Advanced Programming and Algorithms
	DESIGNER:	   Mark Barone and Ed Vickrey
*****************************************************************************/
#include <iostream>				//for I/O
#include <iomanip>				//for formatting output
#include <cstddef>				//for definition of null
#include <cstdlib>				//for pause
#include <ctime>				//for date/time manipulation
#include <cmath>				//for logarithm definition

using namespace std;

#include "Barone_Vickrey-assn3-common.h"
#include "Barone-assn3-funcs.h"
#include "Vickrey-assn3-funcs.h"

//********************************************************************* 
//  FUNCTION: 	main
//  DESCRIPTION: Calls required functions to execute tasks, verifies dynamic
//				 memory is allocated and exits if space is not available     
//  OUTPUT:   
//      Returns: 0 on exit
//  CALLS TO:  GenerateNumberArray, GetHashSize, ModHashFunc1, LinearSearchFunc
//			   ModHashFunc2, DoubleSearchFunc, InitChainTable, ModHashFunc3,
//			   ChainSearchFunc, CalcAvgs, CalcKnuth, DisplayResults,
//			   DeleteTables
//	IMPLEMENTED BY:		Mark Barone
//********************************************************************** 
int main()
{
	//variable declarations
	arrayPtr linearHash,			//pointer to linear hash table
		 	 doubleHash,			//pointer to double hash table
		 	 numArray;				//pointer to random number array
	keyNode** chainHash;			//pointer to array of type keyNode pointers
	int hashSize,					//size of hash table
		linearItems = 0,			//number of items examined for linear search
		doubleItems = 0,			//num of items examined for double search
		chainItems = 0,				//num of items examined for chain search
		array[MAX_NUMBERS];			//array of random numbers
	float linExp = 0,				//knuth calculation for linear
		  dblExp = 0,				//knuth calculation for double
		  chnExp = 0,				//knuth calculation for chain
		  linAvg = 0,				//avg # of items examined per linear search
		  dblAvg = 0,				//avg # of items examined per double search
		  chnAvg = 0,				//avg # of items examined per chain search
	      loadFactor;				//num of keys in table / size of table
	bool full = false;				//true if no memory space to allocate
	
	//point numArray to random number array
	numArray = array;
						
	//assign 5000 random numbers and store in array	
	GenerateNumberArray(numArray);
	
	//prompt user for hash table size
	GetHashSize(hashSize, loadFactor);
	
	//perform hash with modulo division, resolving collisions with linear 
	//probing method
	ModHashFunc1(numArray, linearHash, hashSize, full);
	
	//continue if linear array was allocated, exit if space not available
	if(!full){
		//search for half of the key values using linear probe method
		linearItems = LinearSearchFunc(numArray, linearHash, hashSize);

		//perform hash with modulo division, resolving collisions with double
		//hash method
		ModHashFunc2(numArray, doubleHash, hashSize, full);
		
		//de-allocate linear array before exit if space not available for double
		if(full)
			delete [] linearHash;
	}
	
	//continue if space for double array was allocated, exit if not
	if(!full){
		//search for half of the key values using double hash method
		doubleItems = DoubleSearchFunc(numArray, doubleHash, hashSize);	
		
		//allocate memory for an array of pointers 
		chainHash = InitChainTable(chainHash, hashSize, full);
		
		//de-allocate linear and double before exit if space not available 
		//for chain array
		if(full){
			delete [] linearHash;
			delete [] doubleHash;
		}	
	}
		
	//continue if array of pointers was allocated, exit if not
	if(!full){
		//perform hash with modulo division, resolving collisions with 
		//separate chaining method
		ModHashFunc3(numArray, chainHash, hashSize, full);
		
		//perform search if all key values have been hashed
		if(!full){
			//search for half of the key values using chained hashing method				
			chainItems = ChainSearchFunc(numArray, chainHash, hashSize);
		}
		
		//calculate average number of items examined per search method
		CalcAvgs(linAvg, dblAvg, chnAvg, hashSize, linearItems, doubleItems, 
					chainItems);
		
		//calculate Knuth expected # of items examined per search method			
		CalcKnuth(loadFactor, linExp, dblExp, chnExp);
		
		//display results to user
		DisplayResults(loadFactor, hashSize, linExp, dblExp, chnExp, linAvg, 
						dblAvg, chnAvg, linearItems, doubleItems, chainItems);
						
		//de-allocate all list nodes and dynamic arrays
		DeleteTables(linearHash, doubleHash, chainHash, hashSize);				
	}

 system("pause");
	  return 0;
 }

