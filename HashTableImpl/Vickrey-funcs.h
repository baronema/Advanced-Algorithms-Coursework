/******************************************************************************************
    FILE NAME:	Vickrey-assn3-funcs.h
	DESCRIPTION:   This file contains the function prototypes for the project
				   assignment 3
	CLASS/TERM:    CS372_XIN-X40_Advanced Programming and Algorithms
    
    FUNCTIONS: GenerateNumberArray -
			   VerifyNumbersInArray -
			   GetHashSize -
		   	   ModHashFunc1 -
			   ModHashFunc2 -
		  	   LinearProbeFunc -
			   DoubleHashFunc -
			   LinearSearchFunc -
			   DoubleSearchFunc -
			   
	IMPLEMENTED BY:   Ed Vickrey			   
*****************************************************************************************/

void GenerateNumberArray (arrayPtr& numArray);
bool VerifyNumbersInArray (arrayPtr numArray, int num);
void GetHashSize (int& hashSize, float& loadFactor);
void ModHashFunc1 (arrayPtr numArray, arrayPtr& linearHash, int hashSize,
					bool& full);
void ModHashFunc2 (arrayPtr numArray, arrayPtr& doubleHash, int hashSize,
					bool& full);
int LinearProbeFunc (int address, int hashSize);
int DoubleHashFunc (int address, int hashSize, int key);
int LinearSearchFunc (arrayPtr numArray, arrayPtr linearHash, int hashSize);
int DoubleSearchFunc (arrayPtr numArray, arrayPtr doubleHash, int hashSize);

