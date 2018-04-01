// -----------------------------------------------------------------------------
// FILENAME:	Hutton-assn4-funcs.h
// DESCRIPTION:	Header file for the bubble sort and quicksort functions; random
//				list generator; and helper functions.
// CLASS/TERM:	CS372/2015 Fall 8W1
// DESIGNER:	William Hutton
// FUNCTIONS:	BubbleSort, QuickSort, GenRandArrays, CalcAvgs, DisplayResults,
//				DeallocArrays, ValidateSort
// -----------------------------------------------------------------------------

#ifndef HUTTON_ASSN4_FUNCS_H
// Include guard to prevent multiple definitions if the header is included more than once
#define HUTTON_ASSN4_FUNCS_H

// INCLUDES--------------------------------------------------------------------

// Include Assignment 4 common header for data structure and constant definitions
#include "BaroneHutton-assn4-common.h"

// PROTOTYPES ------------------------------------------------------------------

#pragma region Function Prototypes
// Sort functions
void BubbleSort(int numberArray[], int lower, int upper);
void BubbleSort2(int numberArray[], int lower, int upper); 
void QuickSort(int numberArray[], int lower, int upper);

// Helper functions
void GenRandArrays(int arrayOne[], int arrayTwo[]);
float CalcAvgs(int* results, int sortPasses);
void DisplayResults(float avgOne, float avgTwo, int sortType1, int sortType2);
void DeallocArrays(int* &sortResultsOne, int* &sortResultsTwo);
bool ValidateSort(int sortedArray[]);
#pragma endregion

#endif
