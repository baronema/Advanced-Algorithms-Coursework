
// -----------------------------------------------------------------------------
// FILENAME:	Hutton-assn4-funcs.cpp
// DESCRIPTION:	Implementation of bubble sort and quicksort functions; random
//				list generator; and helper functions. 
// CLASS/TERM:	CS372/2015 Fall 8W1
// DESIGNER:	William Hutton
// FUNCTIONS:	BubbleSort, QuickSort, GenRandArrays, CalcAvgs, DisplayResults,
//				DeallocArrays
// -----------------------------------------------------------------------------


// INCLUDES --------------------------------------------------------------------

// I/O Stream for command line input and output streams including formatting
#include <iostream>
#include <iomanip>

// Include stdlib, time, and cmath for srand(), time(), and ln()
#include <stdlib.h>
#include <time.h>
#include <cmath>

// Other headers
#include <string>

// Include Assignment 4 headers
#include "BaroneHutton-assn4-common.h"
#include "Hutton-assn4-funcs.h"

using namespace std;


// FUNCTIONS -------------------------------------------------------------------

#pragma region Primary Functions
// -----------------------------------------------------------------------------
// FUNCTION:	BubbleSort
// IMPLEMENTER:	William Hutton
// DESCRIPTION:	Sort the interval [lower, upper) using the bubble sort algorithm
// INPUT
//   Parameters:	numberArray[] - Pointer to the array containing the unsorted list
//					lower - The lower bound (inclusive) for the portion of the list to sort
//					upper - The upper bound (exclusive) for the portion of the list to sort
// OUTPUT
//	 Return Val:	None
//   Parameters:	numberArray[] - Pointer to the array sorted for the interval [lower, upper)
// CALLS TO:	None
// -----------------------------------------------------------------------------

void BubbleSort(int numberArray[], int lower, int upper)
{
	bool isSorted;						// Flag to track when list is sorted
	int swapTemp;						// Temporary storage for swapping elements

	// Repeat until the list is fully sorted (using algorithm from course content)
	do
	{
		// Presume that list is sorted
		isSorted = true;

		// Iterate through the list through the end of the unsorted portion tracked by upper
		for (int compareIndex = 0; compareIndex < upper; compareIndex++)
		{
			// Determine if the current element and the next element are out of order
			if (numberArray[compareIndex] > numberArray[compareIndex + 1])
			{
				// Swap current element with the next element and indicate list is still unsorted
				isSorted = false;
				swapTemp = numberArray[compareIndex];
				numberArray[compareIndex] = numberArray[compareIndex + 1];
				numberArray[compareIndex + 1] = swapTemp;
			}
		}

		// Lower the upper bound as the list is sorted
		upper--;
	}
	// Determine if list is fully sorted
	while (!isSorted);
}

// -----------------------------------------------------------------------------
// FUNCTION:	QuickSort
// IMPLEMENTER:	William Hutton
// DESCRIPTION:	Sort the interval [lower, upper) using the quick sort algorithm
// INPUT
//   Parameters:	numberArray[] - Pointer to the array containing the unsorted list
//					lower - The lower bound (inclusive) for the portion of the list to sort
//					upper - The upper bound (exclusive) for the portion of the list to sort
// OUTPUT
//	 Return Val:	None
//   Parameters:	numberArray[] - Pointer to the array sorted for the interval [lower, upper)
// CALLS TO:	QuickSort
// -----------------------------------------------------------------------------

void QuickSort(int numberArray[], int lower, int upper)
{
	int temp;
	int pivot;
	int left;
	int right;
	int partitionSize = (upper - lower) + 1;
	int middle = partitionSize / HALF + lower;

	if (partitionSize > 1)
	{
		// Determine if list is small enough for insertion sort
		if (partitionSize <= QS_LIMIT)
			InsertionSort(numberArray, lower, upper);
		else
		{
			// Sort lower, middle, and upper elements and move median to lower to implement median of 3
			// Begin by swapping the middle and upper if necessary using temp as temporary storage
			if (numberArray[middle] > numberArray[upper])
			{
				temp = numberArray[upper];
				numberArray[upper] = numberArray[middle];
				numberArray[middle] = temp;
			}
			// Next, swap lower and upper if necessary using pivot as temporary storage		
			if (numberArray[lower] > numberArray[upper])
			{
				temp = numberArray[upper];
				numberArray[upper] = numberArray[lower];
				numberArray[lower] = temp;
			}
			// Finally, swap lower and middle if necessary using pivot as temporary storage
			if (numberArray[lower] < numberArray[middle])
			{
				temp = numberArray[middle];
				numberArray[middle] = numberArray[lower];
				numberArray[lower] = temp;
			}

			// Partition the array
			left = lower + 1;
			right = upper;
			pivot = numberArray[lower];

			while (left <= right)
			{
				while ((left <= upper) && (numberArray[left] <= pivot))
					left++;
				while ((right >= left) && (numberArray[right] >= pivot))
					right--;
				// Swap left and right if they haven't crossed
				if (left < right)
				{
					temp = numberArray[left];
					numberArray[left] = numberArray[right];
					numberArray[right] = temp;
				}
			}

			// Move pivot to correct position
			numberArray[lower] = numberArray[right];
			numberArray[right] = pivot;

			// Sort the sub-array to each side of the pivot
			QuickSort(numberArray, lower, right - 1);
			QuickSort(numberArray, right + 1, upper);
		}
	}
}
#pragma endregion


// HELPER FUNCTIONS ------------------------------------------------------------

#pragma region Helper Functions
// -----------------------------------------------------------------------------
// FUNCTION:	GenRandArrays
// IMPLEMENTER:	William Hutton
// DESCRIPTION:	Generate a random list of LIST_SIZE integers in range MIN_RAN_NUM - MAX_RAN_NUM
//				and store the same list in both arrays which are previously allocated
// INPUT
//   Parameters:	array1[] - Pointer to first array to store random list
//					array2[] - Pointer to second array to store random list
// OUTPUT
//	 Return Val:	None
// CALLS TO:	None
// -----------------------------------------------------------------------------

void GenRandArrays(int array1[], int array2[])
{
	static bool needRandomSeed = true;

	// Seed rand() with current time
	if (needRandomSeed)
	{
		srand(static_cast<int>(time(NULL)));
		needRandomSeed = false;
	}
	// Generate random numbers and add to the integer list array
	for (int i = 0; i < LIST_SIZE; i++)
		array1[i] = array2[i] = static_cast<int> (rand() / (RAND_MAX + 1.0) * MAX_RAN_NUM + MIN_RAN_NUM);	
}

// -----------------------------------------------------------------------------
// FUNCTION:	CalcAvgs
// IMPLEMENTER:	William Hutton
// DESCRIPTION:	Calculate the average elapsed time in clock ticks for the specified results array
// INPUT
//   Parameters:	results - The results array to calulate average of
//					sortPasses - The number of passes the sort was executed
// OUTPUT
//	 Return Val:	The average elapsed time in clock ticks
// CALLS TO:	None
// -----------------------------------------------------------------------------


float CalcAvgs(int results[], int sortPasses)
{
	double sumElapsedTime = 0.00;

	// Sum all the elapsed times
	for (int i = 0; i < sortPasses; i++)
		sumElapsedTime += results[i];

	// Calculate and return the average
	return static_cast<float>(sumElapsedTime / sortPasses);
}

// -----------------------------------------------------------------------------
// FUNCTION:	DisplayResults
// IMPLEMENTER:	William Hutton
// DESCRIPTION:	Displays the average results of each sort performed
// INPUT
//   Parameters:	avg1 - Average elapsed time in clock ticks for first sort
//					avg2 - Average elapsed time in clock ticks for second sort
//					sortType1 - Number representing the selected method for the first sort
//					sortType2 - Number representing the selected method for the second sort
// OUTPUT
//	 Return Val:	None
// CALLS TO:	None
// -----------------------------------------------------------------------------

void DisplayResults(float avgOne, float avgTwo, int sortType1, int sortType2)
{
	// Display the header
	cout << "SORTING RESULTS" << endl;
	cout << setfill('-') << setw(15) << "-" << setfill(' ') << fixed << setprecision(1) << endl;
	// Display the results
	cout << setw(20) << sortType[sortType1] << setw(12) << avgOne << " clock ticks on average" << endl;
	cout << setw(20) << sortType[sortType2] << setw(12) << avgTwo << " clock ticks on average" << endl;
	cout << endl;
}

// -----------------------------------------------------------------------------
// FUNCTION:	DeallocArrays
// IMPLEMENTER:	William Hutton
// DESCRIPTION:	Deallocate the sort results arrays
// INPUT
//   Parameters:	sortResultsOne[] - Pointer to first array to destroy
//					SortResultsTwo[] - Pointer to second array to destroy
// OUTPUT
//	 Return Val:	None
//   Parameters:	sortResultsOne[] - Null pointer after array deallocated
//					SortResultsTwo[] - Null pointer after array deallocated
// CALLS TO:	None
// -----------------------------------------------------------------------------

void DeallocArrays(int* &sortResultsOne, int* &sortResultsTwo)
{
	// Delete the arrays
	delete[] sortResultsOne;
	delete[] sortResultsTwo;

	// Set pointers to NULL
	sortResultsOne = NULL;
	sortResultsTwo = NULL;
}

//------------------------------------------------------------------------------
//  FUNCTION:	 ValidateSort
//	IMPLEMENTER: William Hutton
//  DESCRIPTION: 	Compares values in array to validate array is in ascending 
//					order
//  INPUT: 
//      Parameters:  sortedArray[] - sorted array to validate 
//  OUTPUT:   
//		Return Val:  True if sort is valid, false for program exit
//------------------------------------------------------------------------------ 
bool ValidateSort(int sortedArray[])
{
	bool sorted = true;					// Flag to track if list is sorted

	// Start at the top of the list
	for (int i = LIST_SIZE - 1; i && sorted; i--)
		sorted = (sortedArray[i - 1] <= sortedArray[i]);

	return sorted;
}

#pragma endregion
