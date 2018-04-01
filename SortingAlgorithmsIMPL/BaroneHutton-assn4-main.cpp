/*****************************************************************************
	CODE FILENAME: Barone_Hutton-assn4-main.cpp
	DESCRIPTION:   File contains main function for assignment 4 
	CLASS/TERM:    CS372_XIN-X40_Advanced Programming and Algorithms
	DESIGNER:	   Mark Barone and William Hutton
*****************************************************************************/
//INCLUDES*******************************************************************
#include <iostream>			//for I/O
#include <iomanip>			//for formatting 
#include <cstdlib>			//standard library

#include "BaroneHutton-assn4-common.h"
#include "Barone-assn4-funcs.h"
#include "Hutton-assn4-funcs.h"
//****************************************************************************

using namespace std;


//********************************************************************* 
//  FUNCTION: 	 main
//  DESCRIPTION: Loops until user chooses to exit, calls functions to
//				 sort random int arrays using sorting algorithms entered by
//				 user. 
//  OUTPUT:   
//      Returns: 0 on exit
//  CALLS TO:  PromptUser, GetValidInteger, AllocArrays, PerformSorts, CalcAvgs, 
//			   DisplayResults, DeAllocArrays
//	IMPLEMENTED BY:		Mark Barone
//********************************************************************** 
int main()

{
	//variable declarations
	int sortType1 = 0,				//user first sort choice
		sortType2 = 0,				//user second sort choice
		sortPasses;					//user choice of # times to repeat each sort
	float avgOne,					//calculated average for first sort choice
		  avgTwo;					//calculated average for second sort choice
	bool cont = false;				//true if user chooses to exit
	//pointer declarations
	int *results1 = NULL,			//used to point to results array one
		*results2 = NULL;			//used to point to results array two

	//continue to perform user selected sorts until user selects exit or
	//sort is invalid
	do{
		//have user select sort options to test, or 'EE' to exit
		cont = PromptUser(sortType1, sortType2);

		//continue if valid sort choices are entered
		if (cont){
			//have user select number of times to repeat each sort
			sortPasses = GetValidInteger();

			//allocate results array for first sort choice, size of sortPasses
			cont = AllocArrays(results1, sortPasses);

			if (cont){
				//allocate results array for second sort choice
				cont = AllocArrays(results2, sortPasses);
			}
			if (cont){
				//perform sorts and store sort times into sort results array
				cont = PerformSorts(results1, results2, sortType1, sortType2,
					sortPasses);
			}

			//continue if sorts are validated and sorted in ascending order 
			if (cont){
				//calculate average sort time in clock ticks for each sort performed
				avgOne = CalcAvgs(results1, sortPasses);
				avgTwo = CalcAvgs(results2, sortPasses);

				//display final results for the two tested sort methods
				DisplayResults(avgOne, avgTwo, sortType1, sortType2);

			}

			//de-allocate the dynamic arrays
			DeallocArrays(results1, results2);
		}

	}while(cont);

	system("pause");
	  return 0;
}
