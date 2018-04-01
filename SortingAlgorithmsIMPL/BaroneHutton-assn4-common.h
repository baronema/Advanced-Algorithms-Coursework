/*****************************************************************************
	CODE FILENAME: BaroneHutton-assn4-common.h
	DESCRIPTION:   This file contains the global constant, and
				   TYPE definitions for project assignment 4
	CLASS/TERM:    CS372_XIN-X40_Advanced Programming and Algorithms
	DESIGNER:	   Mark Barone and William Hutton
*****************************************************************************/
//GUARD***********************************************************************
#ifndef BARONE_HUTTON_ASSN4_COMMON_H
// Include guard to prevent multiple definitions if the header is included more 
// than once
#define BARONE_HUTTON_ASSN4_COMMON_H
//****************************************************************************

//INCLUDES********************************************************************
#include "barone-assn4-funcs.h"
#include "hutton-assn4-funcs.h"
//****************************************************************************

using namespace std;

//global constant definitions
const int MAX_RAN_NUM = 30000,				//max value of random number
		  MIN_RAN_NUM = 1,					//minimum random number allowed
          LIST_SIZE = 100000,				//size of number array
		  NUM_FUNCS = 4,					//number of sort functions
		  NUM_SORTS = 2,					//number of sorts to test
		  QS_LIMIT = 5,						//threshold to switch to insertion
		  HALF = 2,							//used to calculate middle
		  BUBBLE = 0,						// to set specific   // 
		  INSERTION = 1,					// index values of   //
		  MERGE = 2,						// constant array of //
		  QUICK = 3,						// function pointers //
		  EXIT = 4;							//user selected exit


//Defines a TYPE pointer to a function that takes an int array, int, int as 
//arguments
typedef void (*funcPtr)(int[], int, int);

//Constant array of pointers to integer sort functions
const funcPtr sortFuncPtr[NUM_FUNCS] = {&BubbleSort,
										&InsertionSort,
										&MergeSort,
										&QuickSort};
										  
//Constant string to describe sort choice
const string sortType[NUM_FUNCS] = {"Bubble Sort", "Insertion Sort",
									"Merge Sort", "QuickSort"};
									
#endif /*BARONEHUTTON_ASSN4_COMMON_H*/
