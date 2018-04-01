
/*****************************************************************************
	CODE FILENAME: Vickrey-assn3-funcs.cpp
	DESCRIPTION:   This file contains the function definitions for the project
				   assignment 3
	CLASS/TERM:    CS372_XIN-X40_Advanced Programming and Algorithms
	IMPLEMENTED BY:   Ed Vickrey
*****************************************************************************/

using namespace std;

#include <iostream>				//for I/O
#include <iomanip>				//for formatting output
#include <cstddef>				//for definition of null
#include <cstdlib>				//for pause
#include <ctime>				//for random num gen
#include "Barone_Vickrey-assn3-common.h"
#include "Barone-assn3-funcs.h"
#include "Vickrey-assn3-funcs.h"


///********************************************************************* 
//  FUNCTION: GenerateNumberArray
//  DESCRIPTION: Generates random numbers between 1 - MAX_RANDOM_NUMBER
//				 and calls function to verify no duplicate numbers are 
//				 stored in array     
//  OUTPUT:   
//      Parameters: numArray - array of random key values to hash 
//  CALLS TO:  VerifyNumbersInArray
//	IMPLEMENTED BY:		Ed Vickrey 
//********************************************************************** 
void GenerateNumberArray (arrayPtr& numArray)
{
	int number;			// variable holding the random number generated
	bool found = false;		// Is number duplicate or not	
	
	srand(time(NULL));	// Pseudo-random number generator
	 
	// Loop to load the array with unordered random numbers
	for (int i = 0; i < MAX_NUMBERS; i++) {
		
		// Returns a pseudo-random number between 1 and MAX_RANDOM_NUMBER
		number = rand() % MAX_RANDOM_NUMBER + 1;
		
		// Function call to verify the number generated is not alreay in
		//	the array; returns boolean, true if number is unique
		found = VerifyNumbersInArray (numArray, number);
		
		// If number is unique, add it to the array
		if(found){
			numArray[i] = number;
		}
		// Else, subtract the iteration to aquire the proper amount of numbers
		else{
			i--;
		}
	}	// end for loop
}	// end GenerateNumberArray function

//********************************************************************* 
//  FUNCTION: VerifyNumbersInArray
//  DESCRIPTION: Verifies random number array stores unique numbers
//  INPUT: 
//      Parameters: numArray - array of random numbers
//					num - number to verify   
//  OUTPUT:   
//      Returns: found - true if number is not unique
//	IMPLEMENTED BY:		Ed Vickrey 
//********************************************************************** 
bool VerifyNumbersInArray (arrayPtr numArray, int num)
{
	bool found = false;		// Returns true if number is unique
	int i = 0;
	
	// Loops through the array to look for duplicate number
	do{
		if (numArray[i] == num)
			found = false;
		//return true stating number is unique
		else
			found = true;
			
		i++;
	}while(found && numArray[i] !=0);
	
	return found;	// Return boolean value
}	// end VerifyNumbersInArray function

//********************************************************************* 
//  FUNCTION: GetHashSize
//  DESCRIPTION: Prompts user for hash table size and calculates load 
//				 factor  
//  OUTPUT:   
//      Parameter: hashSize - size of hash table, value MIN_HASH_SIZE 
//							  or greater
//				   loadFactor - ratio of table capacity used
//	IMPLEMENTED BY:		Ed Vickrey 
//**********************************************************************
void GetHashSize (int& hashSize, float& loadFactor)
{
	
	cout << "Enter the size of the hash table (minimum 6700):  ";
	cin >> hashSize;

	// Loop until valid number is entered
	while(hashSize < MIN_HASH_SIZE){	
		
		cout << "  Error: You must enter at least (6700) minimum size: ";
		cin >> hashSize;	
	}	// end while loop
	
	cout << endl << endl;
	
	// Load Factor calculation for use in other functions
	loadFactor = static_cast<float>(MAX_NUMBERS) / hashSize; 

}	// end GetHashSize function

//********************************************************************* 
//  FUNCTION: ModHashFunc1 
//  DESCRIPTION: Calls function to initialize array of integers, then performs
//				 modulo division hashing with linear probe collision 
//				 resolution 
//  INPUT: 
//      Parameters: numArray - array of random key values to hash
//					linearHash - a pointer to type integer 
//					hashSize - max capacity of hash table    
//  OUTPUT:   
//      Parameters: linearHash - points to linear hash table array
//					full - true if no memory space to allocate 
//  CALLS TO:  InitOpenTable, LinearProbeFunc
//	IMPLEMENTED BY:		Ed Vickrey 
//********************************************************************** 
void ModHashFunc1 (arrayPtr numArray, arrayPtr& linearHash, int hashSize,
					bool& full)
{
	int address; 		// Variable to hold the address of the hashed value
	
	// Function call to initialize all linear hash array elements to 0
	full = InitOpenTable(linearHash, hashSize);	

	// If memory is available
	if (!full) {
		// Loop to Mod-hash the numbers in the number array
		for (int i = 0; i < MAX_NUMBERS; i++) {
		
			// Mod-hash calculation
			address = numArray[i] % hashSize;
		
			// If the address in the linear hash array is empty,
			if (linearHash[address] == 0) {
				// load the number from the number array into the linear hash array
				linearHash[address] = numArray[i];
			}	// end if	
			// Else, call the function to probe for the next open array element
			else{
				
				// Loop until empty position is found
				while (linearHash[address] != 0) {
					// Function call to advance to next array element
					address = LinearProbeFunc (address, hashSize);
				}	// end while loop
				
				// Load array number into hash array
				linearHash[address] = numArray[i];
			}	// end else
		}	// end if
	}	// end for loop
}	// end ModHashFunc1 function
					
//********************************************************************* 
//  FUNCTION: ModHashFunc2 
//  DESCRIPTION: Calls function to initialize array of integers, then performs
//				 modulo division hashing with double hashing collision 
//				 resolution 
//  INPUT: 
//      Parameters: numArray - array of random key values to hash
//					doubleHash - a pointer to type integer 
//					hashSize - max capacity of hash table    
//  OUTPUT:   
//      Parameters: doubleHash - points to double hash table array
//					full - true if no memory space to allocate 
//  CALLS TO:  InitOpenTable, DoubleHashFunc
//	IMPLEMENTED BY:		Ed Vickrey 
//********************************************************************** 
void ModHashFunc2 (arrayPtr numArray, arrayPtr& doubleHash, int hashSize,
				   bool& full)
{
	int address = 0, 	// Holds the address of the hashed value 
		key;			// Holds the number from the number array
	
	// Function call to initialize all double hash array elements to 0
	full = InitOpenTable(doubleHash, hashSize);	
	
	// If memory is available
	if (!full) {
		
		// Loop to Mod-hash the numbers in the number array
		for (int i = 0; i < MAX_NUMBERS; i++) {

			// Mod-hash calculation
			address = numArray[i] % hashSize;
				
			// If the address in the hash array is empty,	
			if (doubleHash[address] == 0) {
				// load the number from the number array into the double 
				//hash array
				doubleHash[address] = numArray[i];
			}	// end if
			// Else, call the function to double hash the next open array 
			//element
			else {
				// Assign number from array to key variable
				key = numArray[i];
			
				// Loop until empty position is found
				while(doubleHash[address] != 0){
					// Function call to double hash for new open double hash 
					//	array element
					address = DoubleHashFunc (address, hashSize, key);
				}	// end while loop
				// Load array number into hash array
				doubleHash[address] = numArray[i];
			}	// end else
		}	// end for loop
	}	// end if
}	// end ModHashFunc2 function

//********************************************************************* 
//  FUNCTION: LinearProbeFunc 
//  DESCRIPTION: Handles linear probe collision resolution 
//  INPUT: 
//      Parameters: address - address collision took place
//					hashSize - max capacity of hash table    
//  OUTPUT:   
//      Parameters: address - rehashed address to try 
//	IMPLEMENTED BY:		Ed Vickrey 
//**********************************************************************
int LinearProbeFunc (int address, int hashSize)
{
	address++;			// Advance to the next linear hash array element
		
	// If at the end of the array size, start back at the first element
	if (address >= hashSize) 
		address = 0;	// set address to 0, indicating first element
		
	return address;		// Return the address of the next array element
}	// end LinearProbeFunc function	

//********************************************************************* 
//  FUNCTION: DoubleHashFunc 
//  DESCRIPTION: Handles double hash collision resolution 
//  INPUT: 
//      Parameters: address - address collision took place
//					hashSize - max capacity of hash table 
//					key - key value to double hash   
//  OUTPUT:   
//      Parameters: address2 - rehashed address to try 
//	IMPLEMENTED BY:		Ed Vickrey 
//**********************************************************************
int DoubleHashFunc (int address, int hashSize, int key)
{
	int address2 = 0;		// Holds double hashed address
	
	// Double hash calculation to load variable,
	address2 = (key % (hashSize - 2)) + 1;
	//  then add old address,1800
	address2 += address;	
	//	then hash the new address
	address2 = address2 % hashSize;
	
	// If at the end of the array size, start back at the first element
	if (address2 >= hashSize) 
		address2 = 0;		// set address to 0, indicating first element

		return address2;	// Return new double hashed address
}	// end DoubleHashFunc function

//********************************************************************* 
//  FUNCTION: LinearSearchFunc 
//  DESCRIPTION: Performs search of linear hash table to determine the amount
//				 of collisions that occur when searching half of the elements
//				 in the table
//  INPUT: 
//      Parameters: numArray - array of random key values to hash
//					linearHash - points to linear hash table 
//					hashSize - max capacity of hash table    
//  OUTPUT:   
//      Returns: counter - actual number of elements examined on 2500 searches 
//  CALLS TO:  LinearProbeFunc
//	IMPLEMENTED BY:		Ed Vickrey 
//********************************************************************** 
int LinearSearchFunc (arrayPtr numArray, arrayPtr linearHash, int hashSize)
{
	int counter = 0,	// Holds total number of elements searched
		address = 0;	// Holds the address of the hashed value
			
	// Loop through the every other number in the number array
	for (int x = 0; x < MAX_NUMBERS; x += 2) {
			
		// Mod-hash calculation
		address = numArray[x] % hashSize;
	
		// If the number being searched for is found in the hashed address,
		if (linearHash[address] == numArray[x]) {
			// 	increment counter
			counter++;
		}	// end if
		// Else, call the linear hash function 
		else {
			// Increment counter
			counter++;
			
			// Loop until the number is found
			while (linearHash[address] != numArray[x]) {
				// Function call to advance to next array element
				address = LinearProbeFunc (address, hashSize);
				// Increment counter each element searched
				counter++;
			}	// end while loop
		}	// end else
	}	// end for loop

	return counter;		// Return the total number of elements searched
}	// end LinearSearchFunc function	

//********************************************************************* 
//  FUNCTION: DoubleSearchFunc 
//  DESCRIPTION: Performs search of double hash table to determine the amount
//				 of collisions that occur when searching half of the elements
//				 in the table
//  INPUT: 
//      Parameters: numArray - array of random key values to hash
//					doubleHash - points to linear hash table 
//					hashSize - max capacity of hash table    
//  OUTPUT:   
//      Returns: counter - actual number of elements examined on 2500 searches 
//  CALLS TO:  DoubleHashFunc
//	IMPLEMENTED BY:		Ed Vickrey 
//********************************************************************** 			
int DoubleSearchFunc (arrayPtr numArray, arrayPtr doubleHash, int hashSize)
{
	int counter = 0,	// Holds total number of elements searched
		address,		// Holds the address of the hashed value
		key;			// Holds the number in the number array
			
	// Loop through the every other number in the number array
	for (int x = 0; x < MAX_NUMBERS; x += 2) {
			
		// Store the number from the number array
		key = numArray[x];
		// Mod-hash calculation
		address = numArray[x] % hashSize;
		
		// If the number being searched for is found in the hashed address,
		if (doubleHash[address] == numArray[x]) {
			// Increment counter
			counter++;
		}	// end if
		// Else, call function to double hash
		else {
			// Increment counter
			counter++;
			
			// Loop until number is found
			while (doubleHash[address] != numArray[x]) {
				// Function call to double hash for new address
				address = DoubleHashFunc (address, hashSize, key);
				// Increment counter each element searched
				counter++;
			}	// end while loop
		
		}	// end else
	}	// end for loop
	
	return counter;		// Return the total number of elements searched
}	// end DoubleSearchFunc function

