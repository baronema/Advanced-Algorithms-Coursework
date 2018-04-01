/*****************************************************************************
	CODE FILENAME: Barone-assn3-funcs.h
	DESCRIPTION:   This file contains the function prototypes for 
				   Barone-assn3-funcs.cpp
	CLASS/TERM:    CS372_XIN-X40_Advanced Programming and Algorithms
	FUNCTIONS:	   ModHashFunc3 - Performs separate chaining hash
				   ChainSearchFun - Searches chained hashing table 
				   InitOpenTable - Initializes dynamic array of integers
				   InitChainTable - Initializes dynamic array of keyNode ptr's
				   CreateNode - Allocates memory for new list node
				   CalcKnuth - Calculates Knuth predictions for hash tables
				   CalcAvgs - Calculates avg items examined per hash test
				   DisplayResults - Displays test results for review
				   DeleteTable - De-allocates linked lists and dynamic arrays
	IMPLEMENTED BY:   Mark Barone
*****************************************************************************/
void ModHashFunc3(arrayPtr numArray, keyNode** chainHash, int hashSize,
					bool& full);
int ChainSearchFunc(arrayPtr numArray, keyNode** chainHash, int hashSize);
int ChainHashFunc(int address, int key, keyNode** chainHash);
bool InitOpenTable(arrayPtr& hash, int hashSize);
keyNode** InitChainTable(keyNode** chainHash, int hashSize, bool& full);
nodePtr CreateNode(int key, bool& full);
void CalcKnuth(float loadFactor, float& linExp, float& dblExp, float& chnExp);
void CalcAvgs(float& linAvg, float& dblAvg, float& chnAvg, int hashSize,
				int linearItems, int doubleItems, int chainItems);
void DisplayResults(float loadFactor, int hashSize, float linExp, float dblExp,
				     float chnExp, float linAvg, float dblAvg, float chnAvg,
					  int linearItems, int doubleItems, int chainItems);				     
void DeleteTables(arrayPtr& linearHash, arrayPtr& doubleHash, 
					keyNode** &chainHash, int hashSize);
