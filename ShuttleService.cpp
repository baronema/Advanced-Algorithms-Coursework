/*****************************************************************************
	CODE FILENAME: Barone-assn1-prog.cpp
	DESCRIPTION:   Program manages shuttle services for XYZ Company. User will
				   input two data files as command line arguments, and these
				   files will be read in order to manage vehicles parked
				   in parking lot, and groups of employees as they are
				   either loaded into the vehicle or waiting in line. 
	CLASS/TERM:    CS372_XIN-X40_Advanced Programming and Algorithms
	DESIGNER:	   Mark Barone
	FUNCTIONS	   main - calls functions to complete program tasks
				   CheckFile - Validates filenames input as command line arg
				   CreateEmptyStack - Creates stack head nodes
				   CreateEmptyQueue - Creates queue head node
				   ReadData - Reads data from input files, call functions to
				   			  perform tasks
				   IsEmptyStack - Determines if stack is empty
				   IsFullStack - Determines if memory available for new node
				   IsEmptyQueue - Determines if queue is empty
				   IsFullQueue - Determines if memory available for new node
				   GetStackCount - Returns number of nodes in stack
				   PushStack - Adds new node to stack if memory available
				   PopStack - Removes node from stack, returns node value
				   Enqueue - Adds new node to queue
				   DeQueue - Removes node from queue, returns queue value
				   DisplayStatus - Shows number of vehicles parked and/or
				   				   employees waiting
				   SaveFile - Saves stack data to output file
				   DestroyQueue - Deallocates queue nodes, returns employees 
				   		          still waiting
				    
*****************************************************************************/
#include <iostream>				//for I/O 
#include <iomanip>				//for formatting output
#include <fstream>				//for reading from text file
#include <cctype>				//for character checking
#include <string>				//for string checking
#include <cstddef>				//for definition of null
#include <cstdlib>				//for pause

using namespace std;

//Global Structure Definitions
struct stackRec{
	char vehType;
	string license;
	int capacity;
	stackRec* next;	
};
struct vehStack{
	int count;
	stackRec* next;
};

struct queueRec{
	int waiting;
	queueRec* next;
};
struct empQueue{
	queueRec* front;
	queueRec* back;
};

//declare typedef
typedef stackRec* vehNode;
typedef vehStack* vehType;
typedef queueRec* empNode;
typedef empQueue* waitList;

//Prototypes
bool CheckFile(int argc, char **argv, string& vehFile, string& chkRtnFile);
vehType CreateEmptyStack(vehType vehicle, bool& full);
waitList CreateEmptyQueue(waitList empWaiting, bool& full);
void ReadData(string fileType,vehType& car,vehType& van,
			   waitList& empWaiting, bool& full);
int GetStackCount(vehType vehicle);
void DisplayStatus (int carCount,int vanCount,int empCount);
void SaveFile(vehType& vehicle, int count);
bool IsEmptyStack(vehType vehicle);
bool IsFullStack();
bool IsEmptyQueue(waitList empWaiting);
bool IsFullQueue();
vehType PushStack(vehType vehicle, char type, string lic, int cap, bool& full);
vehType PopStack(vehType vehicle, char& type, string& lic, int& cap);
waitList EnQueue(waitList list, int numWait, bool& full);
waitList DeQueue(waitList list, int& numWait);
int DestroyQueue(waitList& list);

/*****************************************************************************
   FUNCTION: 	Main
   DESCRIPTION: Displays program header, calls functions to carry out tasks
   OUTPUT:		Return Value:  0 on exit			
   CALLS TO: 	CheckFile, CreateEmptyStack, CreateEmptyQueue, GetStackCount,
   				DisplayStatus, ReadData, SaveFile, DestroyQueue
****************************************************************************/
int main(int argc, char* argv[])
{
	//variable declarations
	vehType car,					//top of automobile stack
			van;					//top of van stack
	waitList empWaiting;			//top of waiting queue
	bool full = false,				//true if heap is full
		 valid = false;				//true if input files not valid
	string vehFile,					//stores valid first input file 
		   chkRtnFile;				//stores valid second input file
	int carCount = 0,				//number of autobiles in parking
		vanCount = 0,				//number of vans in parking
		empCount = 0;				//number of employees left waiting
	
	cout << " XYZ Company Employee Shuttle Program" << endl << endl;
	
	//validate input data files passed in as arguments
	valid = CheckFile(argc, argv, vehFile, chkRtnFile);
	//continue if files are valid
	if (valid){
		car = CreateEmptyStack(car, full);
		
		if(!full)
			van = CreateEmptyStack(van, full);
		if(!full)	
			empWaiting = CreateEmptyQueue(empWaiting, full);
		if(!full)
			ReadData(vehFile, car, van, empWaiting, full);	
	}
	//if files are valid and memory left to allocate
	if ((valid) && (!full)){
		carCount = GetStackCount(car);
		vanCount = GetStackCount(van);
		DisplayStatus (carCount, vanCount, empCount);
		
		ReadData(chkRtnFile, car, van, empWaiting, full);
	}
	//if files are valid and memory left to allocate
	if ((valid) && (!full)){
		carCount = GetStackCount(car);
		vanCount = GetStackCount(van);
		
		//save only if vehicles left in parking
		if(carCount > 0)
			SaveFile(car, carCount);
		if(vanCount > 0)
			SaveFile(van, vanCount);
		//deallocate queue and return total employees still waiting
		empCount = DestroyQueue(empWaiting);
		
		DisplayStatus (carCount, vanCount, empCount);
	}
	
	
	cout << endl << endl;

	system("pause");
	return 0;
 }
/*************************************************************************
  FUNCTION:	 CheckFile
  DESCRIPTION: Validates filenames input as command line arg
  INPUT:	 Parameter: argc - number of arguments entered
  			 			argv - array holding c-strings		 						   
  OUTPUT: 	 Parameter: vehFile - valid input data filename
  	                    chkRtnFile - valid input data filename
  			 Returns: valid - true if filenames are valid		 
**************************************************************************/
bool CheckFile(int argc, char **argv, string& vehFile, string& chkRtnFile){
	
	//Local constant declaration
	const string EXT = ".TXT";			//file extension to add if not specified
	const int EXPECTED_NUM_ARGS = 3;	//number of required cmd line arguments
	
	//variable declarations
	ifstream dataFile;					//input file stream to read file
	string firstFile,					//test first argument 
		   secondFile;					//test second argument
	bool checkArg1 = false,				//true if valid filename
		 checkArg2 = false,				//true if valid filename
		 valid = false;					//true if both filenames are valid
	
	//exit program if two parameters were not entered
	if (argc != EXPECTED_NUM_ARGS){
		cout << " Error: you must enter 2 (and only 2) data files as a command " 
			 << "line argument" << endl << " you will have to exit the program "
			 << "and run again" << endl << endl;
	}
	//check files
	else{
		firstFile = argv[1];
		secondFile = argv[2];
		
		dataFile.open(firstFile.c_str());
		
		//if valid file
		if(dataFile){
			checkArg1 = true;
			dataFile.close();
			dataFile.clear();
		}
		//add extension
		else{
			dataFile.clear();
			firstFile += EXT;
			
			dataFile.open(firstFile.c_str());
			//valid with extension
			if(dataFile){
				checkArg1 = true;
				dataFile.close();
				dataFile.clear();
			}
			//filename not valid
			else{
				cout << " Error: data file " << firstFile << " doesn't exist,"
					 << endl
					 << " you must exit and run program again with valid files"
					 << endl << endl;
				dataFile.clear();
			}
		}
		
		dataFile.open(secondFile.c_str());
		//if valid file
		if(dataFile){
			checkArg2 = true;
			dataFile.close();
			dataFile.clear();
		}
		//add extension
		else{
			dataFile.clear();
			secondFile += EXT;
			
			dataFile.open(secondFile.c_str());
			//valid with extension
			if(dataFile){
				checkArg2 = true;
				dataFile.close();
				dataFile.clear();
			}
			//filename not valid
			else{
				cout << " Error: data file " << secondFile << " doesn't "
					 << "exist," << endl << " you must exit and run program " 
					 << "again " << "with valid files" << endl << endl;
				dataFile.clear();
			}
		}
	}
	//return valid only if both files are valid
	if((checkArg1) && (checkArg2)){
		valid = true;
		vehFile = firstFile;
		chkRtnFile = secondFile;
	}
	
	return valid;
	
	
}
/*************************************************************************
  FUNCTION:	 CreateEmptyStack
  DESCRIPTION: Creates stack head node
  INPUT:	 Parameter: vehicle - pointer to top node in stack						   
  OUTPUT: 	 Parameter: full - true if no memory left to allocate
  			 Returns: vehicle - pointer to top node in stack if changed	
  CALLS TO: IsFullStack		 
**************************************************************************/
vehType CreateEmptyStack(vehType vehicle, bool& full){
		
		vehType newRec;			//new node
		//check that there is room to allocate
		full = IsFullStack();
		//if there is room
		if(!full){

			newRec = new (nothrow) vehStack;
			newRec->count = 0;
			newRec->next = NULL;
		
			vehicle = newRec;
		}
		
		return vehicle;
	
}
/*************************************************************************
  FUNCTION:	 CreateEmptyQueue
  DESCRIPTION: Creates queue head node
  INPUT:	 Parameter: empWaiting - pointer to top node in queue						   
  OUTPUT: 	 Parameter: full - true if no memory left to allocate
  			 Returns: empWaiting - pointer to top node in queue if changed
  CALLS TO: IsFullStack		 
**************************************************************************/
waitList CreateEmptyQueue(waitList empWaiting, bool& full){
		
		waitList newRec;			//new node
		//check that there is room to allocate
		full = IsFullStack();
		//if there is room
		if(!full){
		
			newRec = new (nothrow) empQueue;
		
			newRec->front = NULL;
			newRec->back = NULL;
		
			empWaiting = newRec;
		}
		
		return empWaiting;
	
}
/*************************************************************************
  FUNCTION:	 ReadData
  DESCRIPTION: Reads data from input files, call functions to perform tasks					   
  INPUT:	File:   Reads following vehicle info from each line of selected file
   					type, license, qty
   					Data on each line is formatted depending on filetype
   					char, string, int
   					A AAA123 4
					   or
					char, int
					C 10
					   or
					char, char, string, int
					R A AAA123 4 
  			Parameter: fileType - filename to open
  						car - pointer to top node of stack 
  				        van - pointer to top node of stack 
						empWaiting - pointer to top node of queue
  OUTPUT: 	 Parameter: car - pointer to top node of stack if changed
  				        van - pointer to top node of stack if changed
						empWaiting - pointer to top node of queue if changed
						full - true if no memory to allocate
  CALLS TO: IsEmptyStack, IsEmptyQueue, IsFullStack, IsFullQueue, PushStack
  			PopStack, EnQueue, DeQueue		 
**************************************************************************/
void ReadData(string fileType,vehType& car,vehType& van,
			  waitList& empWaiting, bool& full)
{
	//constant declaration
	const int CAR_MAX = 4;				//determines which vehicle to use
	//variable declaration
	ifstream readFile;					//for file input
	
	char action,						//determines action to take
		 type;							//vehicle type
	string	license;					//vehicle license plate
	int qty,							//max occupancy of vehicle
		emp;							//number of employees in group
	bool sEmpty = false,				//true if vehicles in parking
		 cEmpty = false,				//true if automobiles in parking
		 vEmpty = false,				//true if vans in parking
		 qEmpty = false;				//true if no employees waiting
	
	readFile.open(fileType.c_str());
	
	readFile >> action;
	//loop while file data exists and memory to allocate
	while((readFile) && (!full)){
		//if 1st file is an automobile to enter	
		if(action == 'A'){
			readFile >> license;
			readFile >> qty;
			
			cout << " Placing " << license << " into automobile area"
				 << endl << endl;
			car = PushStack(car, action, license, qty, full);
		}
		//if 1st file is a van to enter
		else if(action == 'V'){
			readFile >> license;
			readFile >> qty;
			
			cout << " Placing " << license << " into van area"
				 << endl << endl;
			van = PushStack(van, action, license, qty, full);	
		}
		//if second file is a group of employees to move
		else if(action == 'C'){
			readFile >> emp;
			//check if vehicles left to assign
			vEmpty = IsEmptyStack(van);
			cEmpty = IsEmptyStack(car);
			//check if not vehicles in lot
			if((vEmpty) && (cEmpty))
					sEmpty = true;
			//if no vehicles left in parking	
			if(sEmpty){
				cout << " For " << emp << " employees in group, no vehicles"
					 << " are available:" << endl << endl;
				cout << ' ' << emp << " employees waiting for a vehicle."
					 << endl << endl;
				//assign group of employees to waitlist		 
				empWaiting = EnQueue(empWaiting, emp, full);
				emp = 0;
			}
			else{
				cout << " For " << emp << " employees in group, vehicles "
					 << "checked out are:" << endl;
			}
			//loop until all vehicles assigned or lot is empty
			while((emp > 0) && (!sEmpty)){
				//if more than 4 employees try to fill vans first
				if(emp > CAR_MAX){
					if(!vEmpty){
						van = PopStack(van, type, license, qty);
						cout << "  Van " << license << " holds " << qty
							 << " passengers." << endl;
						emp = (emp - qty);
					}
					else if(!cEmpty){
						car = PopStack(car, type, license, qty);
						cout << "  Automobile " << license << " holds " << qty
							 << " passengers." << endl;
						emp = (emp - qty);
					}
				}
				//if less than 5 employees try to fill cars first
				else if(emp <= CAR_MAX){
					if(!cEmpty){
						car = PopStack(car, type, license, qty);
						cout << "  Automobile " << license << " holds " << qty
							 << " passengers." << endl;
						emp = (emp - qty);
					}
					else if(!vEmpty){
						van = PopStack(van, type, license, qty);
						cout << "  Van " << license << " holds " << qty
							 << " passengers." << endl;
						emp = (emp - qty);
					}
				}
				//check how many vehicles are left in lot
				cEmpty = IsEmptyStack(car);
				vEmpty = IsEmptyStack(van);
				if((vEmpty) && (cEmpty))
					sEmpty = true;
			}
			
			cout << endl;
			//if employees left waiting with no vehicles place in waitlist
			if(emp > 0){
				cout << "  " << emp << " employees waiting for a vehicle."
					 << endl << endl;
					 
				empWaiting = EnQueue(empWaiting, emp, full);
				emp = 0;
			}
		}
		//if returning a vehicle
		else if(action == 'R'){
			readFile >> type;
			readFile >> license;
			readFile >> qty;
			//prompt for vehicle type returning to lot
			if(type == 'A'){
				cout << " Returning " << license << " to automobile area"
					 << endl << endl;	
			}
			else if(type == 'V'){
				cout << " Returning " << license << " to van area"
					 << endl << endl;	
			}
			//check if employees in waitlist
			qEmpty = IsEmptyQueue(empWaiting);
			//return vehicle if no employees
			if(qEmpty){
				if(type == 'A'){
		
					car = PushStack(car, type, license, qty, full);
				}
				else if(type == 'V'){
		
					van = PushStack(van, type, license, qty, full);
				}
				
			}
			//assign group waiting to returned vehicle
			else{
				empWaiting = DeQueue(empWaiting, emp);

				cout << " For " << emp << " employees waiting, vehicles "
				     << "checked out are:" << endl;
				     
				if(type == 'A')
					cout << "  Automobile ";
				else if (type == 'V')
					cout << "  Van ";
					
				cout << license <<	" holds " << qty << " passengers" 
					 << endl << endl;
				//calc if too many employees in group	 
				emp = emp - qty;
				//return employees to waitlist if too many
				if(emp > 0){
					cout << " " << emp << " employees still waiting for a "
						 << "vehicle." << endl << endl;
						 
					EnQueue(empWaiting, emp, full);
				}
				
				emp = 0;
			}
		}
		//ignore remaining data on line and prime next line
		readFile.ignore(1000, '\n');
		readFile.clear();
		readFile >> action;
	}
	
	return;	   		   	
}
/*************************************************************************
  FUNCTION:	 GetStackCount
  DESCRIPTION: Returns number of nodes in stack
  INPUT:	 Parameter: vehicle - pointer to top node in stack						   
  OUTPUT: 	 Parameter: numVeh - number of vehicles in stack		 
**************************************************************************/
int GetStackCount(vehType vehicle){
	//stores number of vehicles in stack
	int numVeh;
	numVeh = vehicle->count;
	
	return numVeh;
}
/*************************************************************************
  FUNCTION:	 DisplayStatus
  DESCRIPTION: Shows number of vehicles parked and/or employees waiting						   
  INPUT: 	 Parameter: carCount - number of autos in parking
  					    vanCount - number of vans in parking
						empCount - number of employees waiting		 
**************************************************************************/
void DisplayStatus (int carCount,int vanCount,int empCount){
	
	cout << " Parking lot status:" << endl
		 << setw(8) << carCount << " automobiles available" << endl
		 << setw(8) << vanCount << " vans available" << endl;
		 
	if(empCount > 0){
		cout << setw(8) << empCount << " employees waiting" << endl;
	}
	
	cout << endl;
	
	return;
}
/*************************************************************************
  FUNCTION:	 SaveFile
  DESCRIPTION: Saves stack data to output file
  INPUT:	 Parameter: count - number of vehicles in parking						   
  OUTPUT: 	 Parameter: vehicle - deallocated head node
  CALLS TO: PopStack		 
**************************************************************************/
void SaveFile(vehType& vehicle, int count){
	//constant declaration
	const string FILE = "LotStatus.txt";		//file to save data to
	//variable declaration
	ofstream saveFile;				//for writing to file
	char type;						//vehicle type
	string lic;						//license plate
	int qty;						//maximum occupancy
	
	//open save file and append data to end of file
	saveFile.open(FILE.c_str(), ios::out | ios::app);
	
	saveFile << count << endl;

	while(vehicle->count != 0){
		
		vehicle = PopStack(vehicle, type, lic, qty);
		
		saveFile << type << ' ' << lic << ' ' << qty << endl;
	}
	saveFile.close();
	
	delete vehicle;

	return;
}
/*************************************************************************
  FUNCTION:	 IsEmptyStack
  DESCRIPTION: Determines if stack is empty
  INPUT:	 Parameter: vehicle - pointer to first node in queue					   
  OUTPUT: 	 Returns: empty - true if queue is empty
**************************************************************************/
bool IsEmptyStack(vehType vehicle){
	//variable declarations
	bool empty = false;				//true if stack is empty
	int num;						//hold number of vehicles in stack
	
	num = vehicle->count;
	
	if(num == 0)
		empty = true;
		
	return empty;
}
/*************************************************************************
  FUNCTION:	 IsFullStack
  DESCRIPTION: Determines if memory available for new node						   
  OUTPUT: 	 Returns: full - true if no memory available	 
**************************************************************************/
bool IsFullStack(){
	//variable declaration
	vehNode newNode;				//node to test
	bool full = false;				//true if no memory to allocate
	
	newNode = new (nothrow) stackRec;
	
	
	//if heap is full
	if (newNode == NULL){
		cout << " Heap Error -- out of heap memory!" << endl
			 << " Cannot allocate space, program will exit" << endl << endl;
		full = true;
	}
	
	delete newNode;
	
	return full;
}
/*************************************************************************
  FUNCTION:	 IsEmptyQueue
  DESCRIPTION: Determines if queue is empty
  INPUT:	 Parameter: empWaiting - pointer to first node in queue					   
  OUTPUT: 	 Returns: empty - true if queue is empty
**************************************************************************/
bool IsEmptyQueue(waitList empWaiting){
	//variable declaration
	bool empty = false;				//true if queue is empty
	queueRec* test;					//node to test
	
	test = empWaiting->front;
	
	if(test == NULL)
		empty = true;
		
	return empty;
}
/*************************************************************************
  FUNCTION:	 IsFullQueue
  DESCRIPTION: Determines if memory available for new node						   
  OUTPUT: 	 Returns: full - true if no memory available	 
**************************************************************************/
bool IsFullQueue(){
	//variable declaration
	empNode newNode;				//new node to test
	bool full = false;				//true if no memory to allocate
	
	newNode = new (nothrow) queueRec;
	
	//if heap is full
	if (newNode == NULL){
		cout << " Heap Error -- out of heap memory!" << endl
			 << " Cannot allocate space, program will exit" << endl << endl;
		full = true;
	}
	
	delete newNode;
	
	return full;
}
/*************************************************************************
  FUNCTION:	 PushStack
  DESCRIPTION: Adds new node to stack if memory available
  INPUT:	Parameter: vehicle - points to top of stack
  					   type - type of vehicle to store
					   lic - licence number to store
					   cap - capacity of vehicle to store				   
  OUTPUT: 	Parameter: full - true if no memory to allocate
  			Returns: vehicle - pointer to new top of list
  CALLS TO: IsFullStack	
**************************************************************************/
vehType PushStack(vehType vehicle, char type, string lic, int cap, bool& full){
	//variable declaration
	vehNode newNode;					//node to add
	//verify memory is not full
	full = IsFullStack();
	//if room to allocate add new node
	if(!full){
	
		newNode = new (nothrow) stackRec;
	
		newNode->vehType = type;
		newNode->license = lic;
		newNode->capacity = cap;
		newNode->next = vehicle->next;
		vehicle->next = newNode;
		vehicle->count++;
	}
	
	return vehicle;
	
	
}
/*************************************************************************
  FUNCTION:	 PopStack
  DESCRIPTION: Removes node from stack, returns node value
  INPUT:	Parameter: vehicle - points to top of stack						   
  OUTPUT: 	Parameter: type - vehicle type stored
  					   lic - license number stored
					   cap - capacity of vehicle stored 
  			Returns: vehicle - pointer to new top of stack	 
**************************************************************************/
vehType PopStack(vehType vehicle, char& type, string& lic, int& cap){
	//variable declaration
	vehNode popNode;				//node to remove
	
	popNode = vehicle->next;
	type = popNode->vehType;
	lic = popNode->license;
	cap = popNode->capacity;
	vehicle->count--;
	vehicle->next = popNode->next;
	
	delete popNode;
	
	return vehicle;
}
/*************************************************************************
  FUNCTION:	 EnQueue
  DESCRIPTION: Adds new node to queue
  INPUT:	Parameter: list - points to top node in queue
  					   numWait - number waiting in group to add to queue				   
  OUTPUT: 	Parameter: full - true if no memory to allocate
  			Returns: list - pointer to new top of queue
  CALLS TO: IsFullStack	
**************************************************************************/
waitList EnQueue(waitList list, int numWait, bool& full){
	//variable declaration
	empNode newNode;				//node to add
	//verify memory to allocate
	full = IsFullQueue();
	//add node if memory is left
	if(!full){
	
		newNode = new (nothrow) queueRec;
	
		newNode->waiting = numWait;
		newNode->next = NULL;
		
		if(list->front == NULL){
			list->front = newNode;
			list->back = newNode;
		}
		else{
			list->back->next = newNode;
			list->back = newNode;
		}
	}
	
	return list;
	
}
/*************************************************************************
  FUNCTION:	 DeQueue
  DESCRIPTION: Removes node from queue, returns queue value						   
  OUTPUT: 	Parameter: numWait - employees waiting in group 
  			Returns: list - pointer to new list top		 
**************************************************************************/
waitList DeQueue(waitList list, int& numWait){
	//variable declaration
	empNode delNode;				//node to delete
	
	numWait = list->front->waiting;
	delNode = list->front;
	list->front = list->front->next;
	
	delete delNode;
	
	return list;
}
/*************************************************************************
  FUNCTION:	 DestroyQueue
  DESCRIPTION: Deallocates queue nodes, returns employees still waiting						   
  OUTPUT: 	Parameter: list - deleted head node 
  			Returns: count - total employees still waiting
  CALLS TO: IsEmptyQueue		 
**************************************************************************/
int DestroyQueue(waitList& list){
	//variable declaration
	int count,					//total employees waiting in line
		num;					//number of employees in group in line
	bool empty;					//true if no employees waiting
	
	do{
	
		empty = IsEmptyQueue(list);
		
		if(!empty){
			list = DeQueue(list, num);
			count += num;
		}
	
	
	}while(!empty);
	
	delete list;
	
	return count;
	
}
