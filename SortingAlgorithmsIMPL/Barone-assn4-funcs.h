/*****************************************************************************
	CODE FILENAME: Barone-assn4-funcs.h
	DESCRIPTION:   This file contains the function prototypes for 
				   Barone-assn4-funcs.cpp
	CLASS/TERM:    CS372_XIN-X40_Advanced Programming and Algorithms
	FUNCTIONS:	   PromptUser - Allows user to choose two sorts, or exit program
				   ValidateChoice - Checks for valid char entry
				   GetValidInteger - returns valid integer value 1 or more
				   AllocArrays - Prompts user for 'X' number of times to repeat
				                 sorts, then allocates two arrays to hold 'X' 
								 # of results
				   PerformSorts - Loops 'X' times, calling functions to generate
				   				  arrays and perform user choosen sorts
				   InsertionSort - Sorts array using insertion sort method
				   MergeSort - Sorts array using merge sort method
	IMPLEMENTED BY:   Mark Barone
*****************************************************************************/
//GUARD***********************************************************************
#ifndef BARONE_ASSN4_FUNCS_H
// Include guard to prevent multiple definitions if the header is included 
// more than once
#define BARONE_ASSN4_FUNCS_H
//****************************************************************************

//INCLUDES********************************************************************
#include "BaroneHutton-assn4-common.h"
//****************************************************************************

using namespace std;

//PROTOTYPES******************************************************************

// Sort Functions
void InsertionSort(int numberArray[], int lower, int upper);
void MergeSort(int numberArray[], int lower, int upper);
void Merge(int numberArray[], int lower, int middle, int upper);

// Helper Functions
bool PromptUser(int& sortType1, int& sortType2);
int ValidateChoice(char choice, bool& valid);
int GetValidInteger();
bool AllocArrays(int* &array, int sortPasses);
bool PerformSorts(int* results1, int* results2, int sortType1, int sortType2,
				  int sortPasses);

#endif /*BARONE_ASSN4_FUNCS_H*/
