/*****************************************************************************
	CODE FILENAME: Barone-assn4-funcs.cpp
	DESCRIPTION:   This file contains the function definitions for the project
				   Barone_Hutton-assn4
	CLASS/TERM:    CS372_XIN-X40_Advanced Programming and Algorithms
	IMPLEMENTED BY:   Mark Barone
*****************************************************************************/
//INCLUDES********************************************************************
#include <iostream>				//for I/O
#include <iomanip>				//for formatting 
#include <ctime>				//for call to clock
//#include <string>				//for string checking

#include "BaroneHutton-assn4-common.h"
#include "Barone-assn4-funcs.h"
//****************************************************************************

using namespace std;

//****************************************************************************
//  FUNCTION: PromptUser 
//  DESCRIPTION: Function allows user to enter two sort selections from a sort
//				 menu, and also gives the option to exit program. Calls another
//				 function to validate choices and convert choice to integer.    
//  OUTPUT:   
//		Returns:	 valid - true to continue, false to exit program
//      Parameters:  sortType1 - sort choice converted to int value used to 
//							     index array of pointers
//					 sortType2 - sort choice converted to int value used to 
//							     index array of pointers
//  CALLS TO: ValidateChoice 
//	IMPLEMENTED BY:		Mark Barone 
//**************************************************************************** 
bool PromptUser(int& sortType1, int& sortType2)
{
	//variable declarations
	bool valid = false;					//true if user enters two valid choices
	string choice;						//for reading user input
	int length;							//for checking length of input

	//loop until user selects two valid menu options
	do{
		cout << " Choose two sorts you wish to compare:" << endl
			 << setw(10) << ' ' << "B = Bubble sort" << endl
			 << setw(10) << ' ' << "I = Insertion sort" << endl
			 << setw(10) << ' ' << "M = Merge sort" << endl
			 << setw(10) << ' ' << "Q = Quick sort" << endl
			 << setw(10) << ' ' << "E = Exit program" << endl << endl
			 << " Enter two letter choices (or EE to exit): ";
		
		cin >> choice;

		cout << endl << endl;

		length = choice.length();

		//check for valid characters if two selections were given
		if (length == NUM_SORTS){
			//set sort type one if valid entry
			sortType1 = ValidateChoice(toupper(choice[0]), valid);
			//set sort type two if valid entry
			if (valid)
				sortType2 = ValidateChoice(toupper(choice[1]), valid);
		}
		else if (length > NUM_SORTS){
			cout << " Error: you entered more than two characters, try again"
				<< endl << endl;
		}
		else{
			cout << " Error: you entered less than two characters, try again"
				<< endl << endl;
		}
		//check if 'E' was entered
		if ((sortType1 == EXIT) || (sortType2 == EXIT)){
			//if one is EXIT, they must both be EXIT
			if (sortType1 != sortType2){
				valid = false;
				cout << " Error: you made one selection to exit, choose 'EE'"
					<< endl << " to exit, or select two sort options!"
					<< endl << endl;
				sortType1 = 0;					//reset sortType for next pass
				sortType2 = 0;					//reset sortType for next pass
			}
		}

	} while (!valid);				//exit loop on valid input

	//return false if user selected to exit
	if ((sortType1 == EXIT) && (sortType2 == EXIT))
		valid = false;

	return valid;
}
//********************************************************************* 
//  FUNCTION: ValidateChoice 
//  DESCRIPTION:  Checks for valid character entry, and returns valid index
//				  needed for function pointer to call sort function.
//  INPUT: 
//      Parameters:	choice - character representing user entry for sort type
//  OUTPUT:
//		Returns:    num - index value to access array of pointer to sort func
//      Parameters: valid - true if valid character entry, false if not valid  
//	IMPLEMENTED BY:		Mark Barone 
//**********************************************************************
int ValidateChoice(char choice, bool& valid){

	//variable declarations
	int num = 0;							//index value to return
	
	//assume entry is valid 
	valid = true;							

	if (choice == 'B'){						//valid choice for bubble sort
		num = BUBBLE;
	}
	else if (choice == 'I'){				//valid choice for insertion sort
		num = INSERTION;
	}
	else if (choice == 'M'){				//valid choice for merge sort
		num = MERGE;
	}
	else if (choice == 'Q'){				//valid choice for quick sort
		num = QUICK;
	}
	else if (choice == 'E'){				//valid choice for exit program
		num = EXIT;
	}
	//user input was not a valid selection
	else{
		valid = false;
		cout << " Error: " << choice << " is not a valid menu choice, try again"
			<< endl << endl;
	}

	return num;
}
//********************************************************************* 
//  FUNCTION: GetValidInteger
//  DESCRIPTION: Prompts user for number of times to perform each sort  
//  OUTPUT:   
//      Returns:    num - user choice for number of times to repeat sort	
//	IMPLEMENTED BY:		Mark Barone 
//********************************************************************** 
int GetValidInteger()
{
	//declare variables
	int num = 0;						//number of times to repeat sort
	bool valid = false;					//true if valid int >= 1

	//loop until a valid positive integer is entered
	while (!valid){

		cout << " Enter the number of times to repeat each sort (1 or more): ";

		cin >> num;

		//no extraction occured, input was not an integer
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');
			valid = false;
			cout << " Error: you did not enter a valid number, try again"
				<< endl << endl;

		}
		// extraction took place, clear out any additional input 
		else{
			cin.ignore(1000, '\n');

			// if characters cleared after integer extraction
			if (cin.gcount() > 1){

				valid = false; 					// input is not valid
				cout << " Error: your number cannot contain trailing characters"
					<< endl << " or a decimal place, try again"
					<< endl << endl;
			}
			else
				valid = true;					//an integer value was entered

			//number must be positive non-zero value
			if (num <= 0){

				valid = false;					// input is not valid
				cout << "Error: your number must be a positive number greater "
					<< "than" << endl << " zero, try again" << endl << endl;
			}
		}//end else
	}//end loop

	return num;
}				

//********************************************************************* 
//  FUNCTION: AllocArrays
//  DESCRIPTION: Allocates an array of specified size to store elapsed times 
//  OUTPUT:   
//      Returns:    success - true if memory allocated, false for program exit
//		Parameters: array - points to allocated integer array
//  CALLS TO:	
//	IMPLEMENTED BY:		Mark Barone 
//********************************************************************** 					
bool AllocArrays(int* &array, int sortPasses)
{
	//variable declaration
	bool success = true;				//true if allocation successful
	
	//allocate an array of integers of size specified
	array = new (nothrow) int[sortPasses];

	//if array not allocated
	if(array == NULL){
		success = false;
		cout << " Heap Error: cannot allocate array, program will exit " 
			 << endl;
	}
	//initialize allocated array	
	else{
		for (int i = 0; i < sortPasses; i++)
			array[i] = 0;
	}
		
	return success;
}				
					
//********************************************************************* 
//  FUNCTION:	PerformSorts
//  DESCRIPTION: Loops calling functions to carry out choosen sort methods on
//				 random arrays of integers. Continues testing array sorts until
//				 number of tests is complete, or sorted array is not in correct
//				 order.
//  INPUT: 
//      Parameters:  sortType1 - # representing the method to use for 1st sort
//					 sortType2 - # representing the method to use for 2nd sort
//					 sortPasses - number of times to repeat sorts 
//  OUTPUT:   
//      Returns: 	valid - true if array is valid, false to exit program
//		Parameters: results1 - pointer to array holding elapsed times for 
//							   for each pass using sortType 1
//					results2 - pointer to array holding elapsed times for 
//							   for each pass using sortType 2
//	IMPLEMENTED BY:		Mark Barone 
//********************************************************************** 					
bool PerformSorts(int* results1, int* results2, int sortType1, int sortType2,
				  int sortPasses)
{
	//variable declarations
	int arrayOne[LIST_SIZE],			//array for first sort method
		arrayTwo[LIST_SIZE],			//array for second sort method
		lower = 0, 						//first index in array
		upper = LIST_SIZE - 1,			//last index in array
		startTime,						//time when sort started
		endTime,						//time when sort finished
		elapsedTime,					//total time in clock ticks for sort
		pass = 0;						//counts number of times sort repeated
	funcPtr sortPtrOne,					//calls first sort function
			sortPtrTwo;					//calls second sort function
	bool valid = false;					//true if sort is valid

			
	//initialize pointers to correct sort functions for test
	sortPtrOne = sortFuncPtr[sortType1];
	sortPtrTwo = sortFuncPtr[sortType2];
	
	//loop until all sorts are completed, or sort is not in correct order 	
	do{	
		//generate two identical random arrays, one for each sort
		GenRandArrays(arrayOne, arrayTwo);
		
		cout << endl << " Starting sort #" << (pass + 1) << "..." << endl;
		
		//begin sort type one
		startTime = clock();						//record start time
			sortPtrOne(arrayOne, lower, upper);
		endTime = clock();							//record end time
		
		//calculate total time of sort
		elapsedTime = endTime - startTime;
		
		//store results in array
		results1[pass] = elapsedTime;
		
		//display sort results for first sort type
		cout << setw(10) << ' ' << sortType[sortType1] << " time " 
			 << elapsedTime << "..." << endl;	
		
		//begin sort type two	 
		startTime = clock();						//record start time
			sortPtrTwo(arrayTwo, lower, upper);
		endTime = clock();							//record end time
		
		//calculate total time of sort
		elapsedTime = endTime - startTime;
		
		//store results in array
		results2[pass] = elapsedTime;
		
		//display sort results for second sort type
		cout << setw(10) << ' ' << sortType[sortType2] << " time "
			<< elapsedTime << "..." << endl;
			 
		//validate sorts are in ascending order
		valid = ValidateSort(arrayOne);
		
		//validate the second sort if first sort is valid
		if (valid){
			valid = ValidateSort(arrayTwo);
		}

		if (valid)
			cout << setw(10) << ' ' << "Sorts validated" << endl << endl;
		else
			cout << " Error: sort is not valid, program will exit" << endl;
			
		//increment pass counter for next test
		pass++;
		
	//exit loop if all passes complete or sorted array is not in correct order	
	}while((pass < sortPasses) && (valid));
		
	return valid;	
}					

//********************************************************************* 
//  FUNCTION:	InsertionSort
//  DESCRIPTION: Sorts random array of integers using insertion sort algorithm
//  INPUT: 
//      Parameters: numberArray[] - pointer to array containing unsorted list
//				    lower - lower bound of list to sort
//					upper - upper bound of list to sort
//  OUTPUT:   
//		Parameter:	numberArray[] - pointer to the sorted array
//	IMPLEMENTED BY:		Mark Barone 
//********************************************************************** 
void InsertionSort(int numberArray[], int lower, int upper){
	
	//variable declarations
	int remainTopIdx = lower + 1,	//top index in remaining unsorted list			
		currentIdx,					//index of item compared to insertValue
		insertValue;				//value of item to insert into sorted list
		
	
	//loop while top index is less than or equal to last array element	
	while(remainTopIdx <= upper){
		
		//set top index as value to insert
		insertValue = numberArray[remainTopIdx];
		
		//current cell to compare insert value
		currentIdx = remainTopIdx - 1;
		
		//enter loop while lower bound not exceeded & compare value is greater 
		//than insert value 
		while((currentIdx >= 0) && (insertValue < numberArray[currentIdx])){
			
			//move value at current index down
			numberArray[currentIdx + 1] = numberArray[currentIdx];
			currentIdx--;			//compare next lowest element
		}
		
		//sorted position found, insert value
		numberArray[currentIdx + 1] = insertValue;
		remainTopIdx++;				//increment top index of unsorted list
	}
	
	return;
}

//********************************************************************* 
//  FUNCTION: 	MergeSort
//  DESCRIPTION: Sorts random array of integers using the merge sort algorithm
//  INPUT: 
//      Parameters: numberArray[] - array to sort
//					lower - lower bound of array to sort
//					upper - upper bound of array to sort
//  OUTPUT:   
//		Parameter:	numberArray[] - array sorted in ascending order 
//	CALLS TO:	MergeSort, Merge
//	IMPLEMENTED BY:		Mark Barone 
//**********************************************************************
void MergeSort(int numberArray[], int lower, int upper){	
	//variable declaration
	int middle;						//determines sub-list upper/lower bound
	
	//base case reached
	if(lower >= upper){
	
		return;
	}
	//calculate middle index of list
	middle = ((lower + upper) / HALF);
	//recursive call to sort left sub-list	
	MergeSort(numberArray, lower, middle);
	//recursive call to sort right sub-list
	MergeSort(numberArray, middle + 1, upper);
	//merge ordered sub-lists into one ordered list 
	Merge(numberArray, lower, middle, upper);
}
//********************************************************************* 
//  FUNCTION: 	Merge
//  DESCRIPTION: Takes two ordered lists and combines them into a single ordered
//				 list
//  INPUT: 
//      Parameters: numberArray[] - sorted list to be split
//					lower - lower bound of array to sort
//					middle - middle index of array to sort
//					upper - upper bound of array to sort
//  OUTPUT:   
//		Parameter:	numberArray[] - merged list
//	IMPLEMENTED BY:		Mark Barone 
//**********************************************************************
void Merge(int numberArray[], int lower, int middle, int upper){
	
	//variable declarations
	int leftIdx = lower,			//walks through elements in left sub list
		rightIdx = middle + 1,		//walks through elements in right sub list
		tempPos = lower;			//index to place elements in merged list
		
	//declare static temp array to prevent multiple declarations
	static int temp[LIST_SIZE];				//holds values being merged
	
	//copy contents of sub array into temp array
	for(int i = lower; i <= upper; i++){
		temp[i] = numberArray[i];
	}

	//loop while there are elements left to compare in both sub-lists
	while((leftIdx <= middle) && (rightIdx <= upper)){
		//next lowest value to merge is in left sub-list
		if(temp[leftIdx] <= temp[rightIdx]){
			//merge value from left sub-list
			numberArray[tempPos] = temp[leftIdx];
			leftIdx++;					//set index to check next element
		}
		//next lowest value to merge is in right sub-list
		else{
			//merge value from right sub-list
			numberArray[tempPos] = temp[rightIdx];
			rightIdx++;					//set index to check next element
		}
		
		tempPos++;						//set index for next merge
	}
	
	//additional elements in left sub-list
	while(leftIdx <= middle){
		//merge value
		numberArray[tempPos] = temp[leftIdx];
		tempPos++;						//set index for next merge
		leftIdx++;						//set index to check next element
	}
	
	//additional elements in right sub-list
	while(rightIdx <= upper){
		//merge value
		numberArray[tempPos] = temp[rightIdx];
		tempPos++;						//set index for next merge
		rightIdx++;						//set index to check next element
	}
}



