/*****************************************************************************
	CODE FILENAME: Barone_Vickrey-assn3-common.h
	DESCRIPTION:   This file contains the global constant, structure, and
				   typedef definitions for the project assignment 3
	CLASS/TERM:    CS372_XIN-X40_Advanced Programming and Algorithms
	DESIGNER:	   Mark Barone and Edward Vickrey
*****************************************************************************/

//global constant definitions
const int MAX_RANDOM_NUMBER = 30000;			//max value of random number
const int MAX_NUMBERS = 5000;					//size of random num array
const int MIN_HASH_SIZE = 6700;					//minimum hash table size
const int SEARCH_SIZE = 2500;					//number of search queries

//structure definition
struct keyNode{
	int keyVal;
	keyNode* next;
};

//typedef definitions
typedef keyNode* nodePtr;						//node pointer to type keyNode
typedef int* arrayPtr;							//array pointer to type integer

