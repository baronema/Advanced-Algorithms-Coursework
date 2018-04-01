/*****************************************************************************
/*****************************************************************************
	CODE FILENAME: Barone-assn2-prog.cpp
	DESCRIPTION:   This program will read two text files and analyze all 
				   integers contained within the files. Integers read from the
				   first file will be stored into doubly linked lists, one for
				   odd, and another for even numbers. The integers in the 
				   second file will be used to search each list, and display
				   whether those numbers were found in the list or not. 
				   Duplicate integers will be ignored, and files containing 
				   data will hold integer values between 1-999 only.
				   Files will contain lists of integers in the following format
				   1 2 3 4 5 6...999
	CLASS/TERM:    CS372_XIN-X40_Advanced Programming and Algorithms
	DESIGNER:	   Mark Barone
	FUNCTIONS	   main - calls functions to complete program tasks
				   CheckFile - Validates filenames input as command line arg
				   			   prompts user for correct name until valid 
				   CreateList - Reads all data from first data file, and calls
				   				necessary functions to store data to lists
				   CheckList - Reads all data from second data file, and calls
				   			   functions to search for integers in the list
				   IsListFull - Determines if space available to allocate
				   				a new node to list
				   InitializeList - Initializes a new list head pointer, and
				   					sets values to null or zero
				   EmptyList - Determines if list is empty
				   NumInList - Searches list to see if integer is already stored
				   OrderedListInsertion - Inserts unique integer into list in
				   						  ascending numeric order
				   ListLength - Returns the length of a list
				   PositionInList - Traverses list in reverse to find position
				   					of node in list
				   DisplayList - Displays number of integers stored in each list
				   				 and displays each integer in the list
				   DestroyList - De-allocates each node in a list
*****************************************************************************/
#include <iostream>				//for I/O 
#include <iomanip>				//for formatting output
#include <fstream>				//for reading from text file
#include <cstddef>				//for definition of null
#include <cstdlib>				//for pause

using namespace std;

//Global Constants
	const string EXT = ".TXT";			//file extension to add if not specified
	const int EXPECTED_NUM_ARGS = 3;	//number of required cmd line arguments

//Global Structure Definitions
struct nodeType{
	int data;
	nodeType* prev;
	nodeType* next;
};

struct listType{
	int length;
	nodeType* top;
};

//declare typedef
typedef nodeType* dllNode;
typedef listType* headNode;

//function prototypes
void CheckFile(int argc, char **argv, string& firstFile, string& secondFile);
void CreateList(headNode& evens, headNode& odds, string fileName);
void CheckList(headNode evens, headNode odds, string fileName);
bool IsListFull();
//ADT function prototypes
headNode InitializeList(headNode list);
bool EmptyList(headNode list);
dllNode NumInList(headNode list, int num);
bool OrderedListInsertion(headNode& list, int num);
int ListLength(headNode list);
int PositionInList(headNode list, int num);
void DisplayList(headNode evens, headNode odds, string fileName);
void DestroyList(headNode& list);

/*****************************************************************************
   FUNCTION: 	Main
   DESCRIPTION: Displays program header, declares two dll lists, calls functions
   				to carry out program tasks.
   OUTPUT:		Return Value:  0 on exit
   CALLS TO: 	CheckFile, InitializeList, CreateList, DisplayList, CheckList
   				DestroyList
****************************************************************************/
int main(int argc, char* argv[])
{
	//variable declarations
	headNode evens,						//pointer to top node in even dll
			 odds;						//pointer to top node in odd dll
	string firstFile,					//first input data file for storing
		   secondFile;					//second input data file for checking
		   
	cout << " Doubly Linked List Program" << endl << endl;
	
	//validate correct filenames input as cmd line arguments, loops until
	//user enters two valid filenames
	CheckFile(argc, argv, firstFile, secondFile);
	
	evens = InitializeList(evens);
	odds = InitializeList(odds);
	
	//read first file and store each unique even and odd number in dll
	CreateList(evens, odds, firstFile);
	
	DisplayList(evens, odds, firstFile);
	
	//read second file and check appropriate list for integer, diplaying results
	CheckList(evens, odds, secondFile);
	
	//de-allocate each list
	DestroyList(evens);
	DestroyList(odds);

 	system("pause");
 	
	return 0;
 }

/*************************************************************************
  FUNCTION:	   CheckFile
  DESCRIPTION: Validates filenames input as command line arg
			   prompts user for correct name until valid 
  INPUT:	 
  		Parameter: argc - number of arguments entered
  			 	   argv - array holding c-strings		 						   
  OUTPUT: 	 
  		Parameter: firstFile - valid input data filename
  	               secondFile - valid input data filename		 
**************************************************************************/
void CheckFile(int argc, char **argv, string& firstFile, string& secondFile){
	
	//variable declarations
	ifstream dataFile;					//input file stream to read file
	bool checkArg1 = false,				//true if valid filename
		 checkArg2 = false;				//true if valid filename
	
	//prompt user for correct data files if not given as arguments
	if (argc != EXPECTED_NUM_ARGS){
		cout << " Error: you must enter 2 (and only 2) data files as command " 
			 << "line arguments" << endl << " Enter the data files to open now "
			 << endl << endl << " Data file 1: ";	 
		cin >> firstFile;
		
		cout << endl << " Data file 2: ";
		cin >> secondFile;
		
		cout << endl << endl;
	}
	//check data files entered as arguments
	else{
		firstFile = argv[1];
		secondFile = argv[2];
	}
	//loop until a valid first data file is found
	while(!checkArg1){
		
		dataFile.open(firstFile.c_str());
		
		//if valid file
		if(dataFile){
			checkArg1 = true;
		}
		//add .txt extension and check again
		else{
			dataFile.clear();
			firstFile += EXT;
			
			dataFile.open(firstFile.c_str());
			//valid with extension
			if(dataFile){
				checkArg1 = true;
			}
			//filename not valid
			else{
				dataFile.clear();
				cout << " Error: data file " << firstFile << " doesn't exist,"
					 << endl
					 << " Enter another first filename to check: ";
				cin >> firstFile;
				
				cout << endl << endl;
			}
		}//end else at !dataFile
	}//end loop
	
	dataFile.close();
	dataFile.clear();
	
	//loop until a valid second data file is found
	while(!checkArg2){
		
		dataFile.open(secondFile.c_str());
		
		//if valid file
		if(dataFile){
			checkArg2 = true;
		}
		//add .txt extension and check again
		else{
			dataFile.clear();
			secondFile += EXT;
			
			dataFile.open(secondFile.c_str());
			//valid with extension
			if(dataFile){
				checkArg2 = true;
			}
			//filename not valid
			else{
				dataFile.clear();
				cout << " Error: data file " << secondFile << " doesn't exist,"
					 << endl
					 << " Enter another second filename to check: ";
				cin >> secondFile;
				
				cout << endl << endl;
			}
		}//end else at !dataFile
	}//end loop
	
	dataFile.close();
	dataFile.clear();
	
	return;	
}

/*************************************************************************
  FUNCTION:	    CreateList
  DESCRIPTION:  Reads all data from first data file, and calls
				necessary functions to store data to lists
  INPUT:	
  		File:   Reads following list of random integers in range 1-999
   					num
   					Data on each line is formatted as follows
   					int int....int
   		Parameter: evens - even dll to store integers
  				   odds - odd dll to store integers 
  				   fileName - name of data file to read 
  OUTPUT: 	 
  		Parameter: evens - holds unique even integers read from file
  				   odds - holds unique odd integers read from file
  CALLS TO: NumInList, OrderedListInsertion		 
**************************************************************************/
void CreateList(headNode& evens, headNode& odds, string fileName)
{

	//variable declaration
	ifstream readFile;					//for file input
	nodeType* chkNum;					//points to number in list if not unique
	int num,							//value read from file
		cond;							//modulus calc to determine odd/even
	bool full = false;					//true if no memory to allocate
	
	readFile.open(fileName.c_str());
	
	cout << " Reading input" << endl;
	
	//priming read
	readFile >> num;
	
	//loop while more entries in file and space left to allocate
	while((readFile) && (!full)){
		
		//calculate if number is even or odd	
		cond = (num % 2);
		
		//number is even
		if(cond == 0){
			//determine if number is unique
			chkNum = NumInList(evens, num);
			
			//store if unique
			if(chkNum == NULL){
				full = OrderedListInsertion(evens, num);
			}
			//ignore if number already in list
			else{
				cout << setw(7) << num << " is a duplicate and will be ignored"
					 << endl;
			}
		}//end if at even number
		//number is odd
		else{
			//determine if number is unique
			chkNum = NumInList(odds, num);
			//store if unique
			if(chkNum == NULL){
				full = OrderedListInsertion(odds, num);
			}
			//ignore if number already in list
			else{
				cout << setw(7) << num << " is a duplicate and will be ignored"
					 << endl;
			}
		}//end else at odd number
		
		//read next line of file
		readFile >> num;
	}//end loop
	
	readFile.clear();
	readFile.close();
	
	cout << endl;
	
	return;
}

/*************************************************************************
  FUNCTION:	    CheckList
  DESCRIPTION:  Reads all data from second data file, and calls
				functions to search for integers in the list					   
  INPUT:	
  		File:   Reads following list of random integers in range of 1-999
   					num
   					Data on each line is formatted as follows
   					int int...int
   					1 2...999
   		Parameter: evens - even dll to store integers
  				   odds - odd dll to store integers 
  				   fileName - name of data file to read 
  CALLS TO: PositionInList, EmptyList		 
**************************************************************************/
void CheckList(headNode evens, headNode odds, string fileName)
{
	//variable declaration
	ifstream readFile;					//for file input
	int num,							//value read from file
		cond,							//calculates if num is even/odd
		result;							//numeric postion num is found in list
	bool empty;							//true if list is empty
	
	readFile.open(fileName.c_str());
	
	cout << " Search results for input file " << fileName << ":" << endl 
		 << endl;
	
	//priming read
	readFile >> num;
	
	//loop until all values in file are read	 
	while(readFile){
		
		//calculate if number is even/odd
		cond = (num % 2);
		
		//number is even
		if(cond == 0){
			
			//find its position in the list
			result = PositionInList(evens, num);
			
			//number is not stored in the list
			if(result == 0){
				
				//see if list is empty
				empty = EmptyList(evens);
		
				if(empty){
					cout << setw(8) << " " << left << setw(4) << left << num 
						 << " not found - even list empty" << endl;
				}
				else{
					cout << setw(8) << " " << left << setw(4) << num 
					     << " not found in even list" << endl;
				}
			}
			//show position number is found in the list
			else{
				
				cout << setw(8) << " " << left << setw(4) << num << " found " 
					 << result << " numbers" << " down in the even list" 
					 << endl;
			}
		}//end if at even number
		//number is odd
		else{
			
			//find its position in the list
			result = PositionInList(odds, num);
			
			//number is not stored in the list
			if(result == 0){
				
				empty = EmptyList(odds);
				
				if(empty){
					cout << setw(8) << " " << left << setw(4) << num 
						 << " not found - odd list empty" << endl;
				}
				else{
					cout << setw(8) << " " << left << setw(4) << num 
						 << " not found in odd list" << endl;
				}
			}//end if at result
			//show position number is found in the list
			else{
				
				cout << setw(8) << " " << left << setw(4) << num << " found " 
					 << result << " numbers" << " down in the odd list" 
					 << endl;
			}
		}//end else at odd number
		
		readFile >> num;
		
	}//end loop
	
	cout << endl;
	
	return;
}

/*************************************************************************
  FUNCTION:	   IsListFull
  DESCRIPTION: Determines if space available to allocate a new node to list						   
  OUTPUT: 	 
  		Returns: full - true if heap is full, false if space available 		 
**************************************************************************/
bool IsListFull(){
    //variable declaration
	dllNode newNode;				//node to test
	bool full = false;				//true if no memory to allocate
	
	//allocate memory
	newNode = new (nothrow) nodeType;
	
	//if heap is full
	if (newNode == NULL){
		cout << " Heap Error -- out of heap memory!" << endl
			 << " Cannot allocate space, no further entries will be stored" 
			 << endl << endl;
			 
		full = true;
	}
	
	delete newNode;
	
	return full;
}

/*************************************************************************
  FUNCTION:	   InitialzeList
  DESCRIPTION: Initializes a new list head pointer, and sets values to 
  			   null or zero
  INPUT:	 
		Parameter: list - head node of list						   
  OUTPUT: 	 
  		Returns: list - head node initialized to empty
  CALLS TO: IsListFull
**************************************************************************/
headNode InitializeList(headNode list){
	
	//variable declaration
	headNode newRec;			//new list node
	bool full;
	
	//check that there is room to allocate
	full = IsListFull();
	
	//if there is room initialize list
	if(!full){

		newRec = new (nothrow) listType;
		newRec->length = 0;
		newRec->top = NULL;
		
		list = newRec;
	}
		
	return list;
}

/*************************************************************************
  FUNCTION:	   EmptyList
  DESCRIPTION: Determines if list is empty
  INPUT:	 
		Parameter: list - list to check						   
  OUTPUT: 	 
  		Returns: empty - true if list is empty, false if list contains nodes		 
**************************************************************************/
bool EmptyList(headNode list){
	
	//variable declarations
	int test = 0;						//holds number of nodes stored in list
	bool empty = false;					//true if length is 0
	
	//get node count stored in list head node
	test = list->length;
	
	if(test == 0)
		empty = true;
		
	return empty;
}

/*************************************************************************
  FUNCTION:	   NumInList
  DESCRIPTION: Searches list to see if integer is already stored
  INPUT:	 
		Parameter: list - head node of list
				   num - integer value to search in list						   
  OUTPUT: 	 
  		Returns: temp - pointer to value in list, null if value not found
**************************************************************************/
dllNode NumInList(headNode list, int num){
	
	//variable declaration
	nodeType* temp;						//pointer to traverse list
	bool found = false;					//true if number is found
	
	//start at first node
	temp = list->top;
	
	//loop until number is found or end of list
	while ((temp != NULL) && (!found)){
		//value is found
		if(temp->data == num)
			found = true;
		//search next node	
		else
			temp = temp->next;
	}
	
	return temp;
}	
/*************************************************************************
  FUNCTION:	   OrderedListInsertion
  DESCRIPTION: Inserts unique integer into list in ascending numeric order
  INPUT:	 
  		Parameter: list - dll to store value
		  		   num - value to store						   
  OUTPUT: 	 
  		Parameter: list - dll list with new value inserted in ascending order
  		Returns: full - true if no memory to allocate, false if num inserted
  CALLS TO: IsListFull		 
**************************************************************************/
bool OrderedListInsertion(headNode& list, int num){
	
	//variable declaration
	nodeType* current;					//points to current node in search
	nodeType* location;					//new node inserted after this location
	dllNode newNode;					//new node to insert
	bool full = false,					//true if no memory to allocate
		 found = false;					//true when postion to insert is found
	
	//determine if memory space is available
	full = IsListFull();
	
	//insert if space is available
	if(!full){
		
		//allocate memory for new node
		newNode = new (nothrow) nodeType;
		
		newNode->data = num;
		newNode->prev = NULL;
		newNode->next = NULL;
		
		//if list is empty insert new node first
		if(list->top == NULL){
			list->top = newNode;
			list->length++;
		}
		//there are nodes in the list
		else{
			//begin search at top of list
			current = list->top;
			
			//search until location to insert is found
			while((current != NULL) && (!found)){	
				
				if(current->data < num){
					location = current;
					current = current->next;
				}
				else{
					found = true;
				}
			}//end loop
		
			//value to insert is smaller than first node
			if(current == list->top){
				newNode->next = current;
				current->prev = newNode;
				list->top = newNode;
				list->length++;
			}
			//is not the first node in list
			else{
				//value to insert is in middle of list
				if(current != NULL){
					newNode->next = current;
					newNode->prev = location;
					location->next = newNode;
					current->prev = newNode;
					list->length++;
				}
				//value to insert is last node in list
				else{
					location->next = newNode;
					newNode->prev = location;
					list->length++;
				}
			}//end else at not first node
		}//end else at there are nodes in list
	}//end if at !full
	
	return full;
}

/*************************************************************************
  FUNCTION:	   ListLength
  DESCRIPTION: Returns the length of a list
  INPUT:	 
  		Parameter: list - head node of dll 						   
  OUTPUT: 	 
  		Returns: test - value of list length		 
**************************************************************************/
int ListLength(headNode list){
	
	//variable declaration
	int test;					//number of nodes in list
	
	test = list->length;
	
	return test;
}

/*************************************************************************
  FUNCTION:	   PositionInList
  DESCRIPTION: Traverses list in reverse to find position of node in list
  INPUT:	 
  		Parameter: list - dll to traverse
		  		   num - value stored at node position to find						   
  OUTPUT: 	 
  		Returns: nodePos - counter to display sequential position in list
  CALLS TO: NumInList
**************************************************************************/
int PositionInList(headNode list, int num){
	
	//variable declaration
	nodeType* position;					//pointer to node that stores num
	int nodePos;						//counts sequential position in list
	
	//determine if value is located in list, return pointer to node if found
	position = NumInList(list, num);
	
	//value is not stored in list
	if(position == NULL)
		nodePos = 0;
	else{
		//loop until front of list
		while(position != NULL){
			
			nodePos++;
			position = position->prev;
			
		}
	}
	
	return nodePos;
}

/*************************************************************************
  FUNCTION:	   DisplayList
  DESCRIPTION: Displays number of integers stored in each list and displays 
  			   each integer in the list
  INPUT:	 Parameter: evens - dll list of even numbers
  					    odds - dll list of odd numbers
						fileName - name of file integers are read from						   
  CALLS TO: ListLength		 
**************************************************************************/
void DisplayList(headNode evens, headNode odds, string fileName){
	
	//variable declaration
	nodeType* position;						//traverses the list
	int num,								//length of the list
		x = 0;								//counts number of values on line
	
	cout << " Lists created using input file " << fileName << endl << endl;
	
	num = ListLength(odds);
	
	cout << setw(5) << num << " integers inserted into Odd List:" << endl
		 << setw(11);
	
	//start at top of list	 
	position = odds->top;
	
	//loop until all odd values displayed
	while(position != NULL){
		
		cout << position->data << setw(5);
		x++;
		
		position = position->next;
		
		//newline if ten numbers are displayed
		if(x == 10){
			cout << endl << setw(11);
			x = 0;	
		}
	}//end loop
	
	cout << endl << endl;
	x = 0;
	
	num = ListLength(evens);
	
	cout << setw(5) << num << " integers inserted into Even List:" << endl
		 << setw(11);
	
	//start at top of list	 
	position = evens->top;
	
	//loop until all even values displayed
	while(position != NULL){
		
		cout << position->data << setw(5);
		x++;
		
		position = position->next;
		
		//newline if ten numbers are displayed
		if(x == 10){
			cout << endl << setw(11);
			x = 0;	
		}
	}//end loop
	
	cout << endl << endl;
	return;
}
/*************************************************************************
  FUNCTION:	   DestroyList
  DESCRIPTION: De-allocates each node in a list
  INPUT:	 
  		Parameter: list - dll to delete						   
  OUTPUT: 	 
  		Parameter: list - deleted dll		 
**************************************************************************/
void DestroyList(headNode& list){
	
	//variable declaration
	nodeType* deleteNode;					//points to node to de-allocate
	
	//loop until all nodes in list are de-allocated
	while(list->top != NULL){
		
		deleteNode = list->top;
		list->top = deleteNode->next;
		delete deleteNode;
	}
	
	//de-allocate list head node
	delete list;
	
	return;
}
