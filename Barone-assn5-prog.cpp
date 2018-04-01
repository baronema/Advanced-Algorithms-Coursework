/*****************************************************************************
	CODE FILENAME: Barone-assn.cpp
	DESCRIPTION:   Program reads integer data from a text file in order to 
				   store unique integers into a binary tree. User has the 
				   option to show, add, delete, and search for and display
				   subtree values. Program loops until user selects exit.
	CLASS/TERM:    CS372_XIN-X40_Advanced Programming and Algorithms
	DESIGNER:	   Mark Barone
	FUNCTIONS	   main - calls functions to complete program tasks
				   ReadData - Opens selected text file and stores values in tree
				   UserMenu - Loops calling functions to carry out tasks
				   GetInteger - Reads and verifies integer input between 0-10000
				   CreateTree - Allocates and initializes pointer to tree struct
				   IsEmpty - Determines if binary tree is empty, or has values
				   CreateNode - Allocates a new node and initializes it to null
				   InsertNode - Inserts new node into correct location
				   FindNode - Searches for a specific value in binary tree
				   DeleteNode - Deletes a specific node from binary tree
				   InOrderDisplay - Displays values using in-order recursion
				   FreeNodes - Deletes nodes using post-order recursion
				   DestroyTree - De-allocates BST dynamic memory

*****************************************************************************/
#include <iostream>				//for I/O
#include <iomanip>				//for formatting output
#include <fstream>				//for reading from text file
#include <cctype>				//for character manipulation
#include <string>				//for string manipulation
#include <cstdlib>				//standard library

using namespace std;

//constant declaration
const string EXT = ".TXT";			//file extension to add for text file

//BST structure definitions
struct treeNode{
	int value;
	treeNode* left;
	treeNode* right;
};

struct headNode{
	int count;
	treeNode* root;
};

//Function Prototypes
void ReadData(headNode* &treeTop);
void UserMenu(headNode* &treeTop);
int GetInteger();

//ADT Functions
headNode* CreateTree();
bool IsEmpty(headNode* treeTop);
void CreateNode(treeNode* &newNode, int key);
void InsertNode(headNode* &treeTop, treeNode* newNode);
void FindNode(treeNode* &current, bool& found, int key);
void DeleteNode(headNode* &treeTop, treeNode* delNode);
void InOrderDisplay(treeNode* root, int& count);
void FreeNodes(treeNode* treeTop);
void DestroyTree(headNode* &treeTop);

//****************************************************************************
//   FUNCTION: 	Main
//   DESCRIPTION: Displays program title, calls functions to carry out tasks
//   OUTPUT:		Return Value:  0 on exit
//   CALLS TO: 	CreateTree, ReadData, UserMenu, DestroyTree
//****************************************************************************
int main()
{
	headNode* treeTop = NULL;
	
	cout << " Binary Search Tree Program" << endl << endl;
	
	treeTop = CreateTree();
	
	ReadData(treeTop);
	
	UserMenu(treeTop);
	
	DestroyTree(treeTop);
	
 system("pause");
	  return 0;
 }
//****************************************************************************
//  FUNCTION: ReadData 
//  DESCRIPTION: Opens selected text file and stores values in tree   
//  INPUT:
//	    File:	Reads following list of random integers in range 1-9999
//   					num
//   					Data on each line is formatted as follows
//   					int int....int
//	OUTPUT:   
//      Parameters:  treeTop - pointer to first node in BST
//  CALLS TO: FindNode, CreateNode, InsertNode 
//****************************************************************************
void ReadData(headNode* &treeTop){
	
	ifstream dataFile;					//input file stream to read file
	string fileName;					//user choice for file name
	bool valid = false,					//true if file is valid
		 found = false;					//true if value found in tree
	int num;							//value read from file
	
	treeNode* newNode = NULL;			//points to new node to insert
	treeNode* node = NULL;				//points to found node
	
	cout << " Enter a filename to open: ";
	
	cin >> fileName;
	
	cout << endl << endl;
	
	//loop until user enters valid file name 
	while(!valid){
		
		dataFile.open(fileName.c_str());
		
		if(dataFile){
			valid = true;						//found valid file
		}
		else{
			dataFile.clear();
			fileName += EXT;					//search with file extention
			
			dataFile.open(fileName.c_str());

			if(dataFile){
				valid = true;					//found valid file
			}
			else{
				dataFile.clear();
				cout << " Error: data file " << fileName << " doesn't exist,"
					 << endl
					 << " Enter another filename to check: ";
				cin >> fileName;
				
				cout << endl << endl;
			}
		}//end else 
	}//end loop
	
	//priming read
	dataFile >> num;
	 
	while(dataFile){
		
		node = treeTop->root;					//pointer to start search with
		//try to find the number read from file
		FindNode(node, found, num);
		
		if(found){
			cout << " Warning: " << num << " already found in tree and will be"
				 << " ignored" << endl << endl;
		}
		else{
			
			CreateNode(newNode, num);
			
			if(newNode != NULL)
				InsertNode(treeTop, newNode);
			else{
				cout << " Error: Remaining data file ignored due to "
					 << "insufficient heap memory" << endl << endl;
			}
		}
		
		//check for next number in file 
		dataFile >> num;
		
	}
	
	dataFile.close();
	dataFile.clear();
}

//****************************************************************************
//  FUNCTION: UserMenu 
//  DESCRIPTION: Loops calling functions to carry out tasks   
//  INPUT:
//	    Parameter: treeTop - pointer to BST
//	OUTPUT:   
//      Parameter: treeTop - points to new node if top node changed
//  CALLS TO: IsEmpty, FindNode, CreateNode, InsertNode, InOrderDisplay,
//			  GetInteger, DeleteNode 
//****************************************************************************
void UserMenu(headNode* &treeTop){
	
	char userEntry = ' ';			//used to navigate menu options
	bool exit = false,				//true if user selects exit
		 found = false,				//true if value found in tree
		 empty = false;				//true if tree is empty
	int num,						//value to search, store, or delete
		count = 0;					//for output formatting
	
	treeNode* newNode = NULL;		//points to new node to insert
	treeNode* node = NULL;			//points to found node
	
	do{

		cout << " Tree Count = " << treeTop->count << endl << endl;
		count = 0;				//output format set to 0 before each recursion
		
		cout << " User Menu: Choose from the following" << endl
			 << setw(10) << ' ' << "S - Show all integers in tree" << endl
			 << setw(10) << ' ' << "A - Add an integer to tree" << endl
			 << setw(10) << ' ' << "D - Delete an integer from tree" << endl
			 << setw(10) << ' ' << "F - Find an integer and display subtree" 
			 << endl
			 << setw(10) << ' ' << "E = Exit program" << endl << endl
			 << " Enter letter choice: ";
			 
		cin >> userEntry;
		
		cin.ignore(1000, '\n');
		
		cout << endl << endl;
		
		//try to find values starting at top node		
		node = treeTop->root;
		
		//check user entry is a single character
		if (cin.gcount() > 1){
			
			cout << " You entered more than 1 character"
			     << endl << endl;
			userEntry = ' ';
		}
	
		userEntry = toupper(userEntry);
	
		if (userEntry == 'S'){
			//check that list has values to display
			empty = IsEmpty(treeTop);
			
			if(empty)
				cout << " Binary search tree is empty" << endl << endl;
			else{
				cout << " Values stored in the entire binary search tree are:"
					 << endl;
				InOrderDisplay(node, count);
				cout << endl << endl;
			}
		}
				
		else if (userEntry == 'A'){
			
			cout << " Enter value to add: ";
			
			num = GetInteger();
			//check to see if value is stored in tree
			FindNode(node, found, num);
			
			if(found){
				cout << " Error: Integer already in tree, cannot add value"
					 << endl << endl;
			}
			//store new value if it is unique
			else{
				CreateNode(newNode, num);
				if(newNode != NULL){
					InsertNode(treeTop, newNode);
				}
				else{
					cout << " Error: No heap space available, cannot add"
						 << endl << endl;
				}
			}
		}
		else if (userEntry == 'D'){
			
			cout << " Enter value to delete: ";
			
			num = GetInteger();
			//make sure value is in tree before deleting
			FindNode(node, found, num);
			
			if(found){
				DeleteNode(treeTop, node);
			}
			else{
				cout << " Integer was not found in the list" << endl << endl;
			}
		}
		else if (userEntry == 'F'){
			
			cout << " Enter value to find: ";
			
			num = GetInteger();
			//check that value is found before displaying sub-tree
			FindNode(node, found, num);
			
			if(found){
				cout << " Values stored in subtree with root " 
					 << num << " are:" << endl << endl;
					 
				InOrderDisplay(node, count);
				
				cout << endl << endl;
			}
			else{
				cout << " Integer was not found in the list" << endl << endl;
			}
		}	
		else if (userEntry == 'E'){
			exit = true;
		}
		else{
			cout << " Entry not valid: Must enter 'S', 'A', 'D', 'F', or 'E':"
				 << endl << endl;
		}
		
	}while (!exit);
}

//********************************************************************* 
//  FUNCTION: CreateTree
//  DESCRIPTION: Allocates and initializes pointer to tree struct  
//  OUTPUT:   
//      Returns: top - initialized head node pointer	
//********************************************************************** 
headNode* CreateTree(){
	
	headNode* top = new headNode;
	
	top->count = 0;
	top->root = NULL;
	
	return top;	
}

//********************************************************************* 
//  FUNCTION: IsEmpty
//  DESCRIPTION: Determines if binary tree is empty, or has values
//	INPUT:
//		Parameter: treeTop - pointer to BST
//  OUTPUT:   
//      Returns: empty - true if tree is empty, false if not	
//********************************************************************** 
bool IsEmpty(headNode* treeTop){
	
	bool empty = false;				//true if no nodes stored in tree

	if(treeTop->count == 0)
		empty = true;

	return empty;
}

//********************************************************************* 
//  FUNCTION: CreateNode
//  DESCRIPTION: Allocates a new node and initializes it to null 
//	INPUT:
//		Parameter:  key - value to store in new node 
//  OUTPUT:   
//      Parameter:  newNode - pointer to new node	
//********************************************************************** 
void CreateNode(treeNode* &newNode, int key){
	
	//allocate a new node
	newNode = new (nothrow) treeNode;
	
	if(newNode != NULL){
		newNode->value = key;
		newNode->left = NULL;
		newNode->right = NULL;
	}
}

//********************************************************************* 
//  FUNCTION: InsertNode
//  DESCRIPTION: Inserts new node into correct location
//	INPUT:
//		Parameter:  treeTop - pointer to top of BST
//					newNode - node to insert into tree
//  OUTPUT:   
//      Parameter:  treeTop - points to new tree top if changed	
//**********************************************************************
void InsertNode(headNode* &treeTop, treeNode* newNode){
	
	treeNode* checkNode = treeTop->root;	//traverses tree to find insert pt 
	bool inserted = false;					//true when node is inserted
	int key = newNode->value;				//value to compare 
	
	//first node to insert in the tree
	if(checkNode == NULL){
		treeTop->root = newNode;
		treeTop->count++;
		inserted = true;
	}
	
	while(!inserted){
		//walk left side of tree
		if(key < checkNode->value){
			//insert node into lowest value
			if(checkNode->left == NULL){
				
				checkNode->left = newNode;
				treeTop->count++;
				inserted = true;
			}
			//walk lower values
			else
				checkNode = checkNode->left;
		}
		//walk right side of tree
		else if (key > checkNode->value){
			//insert node into highest value
			if(checkNode->right == NULL){
				
				checkNode->right = newNode;
				treeTop->count++;
				inserted = true;
			}
			//walk higher values
			else
				checkNode = checkNode->right;
		}
	}
}

//********************************************************************* 
//  FUNCTION: FindNode
//  DESCRIPTION: Searches recursively for a specific value in binary tree
//	INPUT:
//		Parameters: current - points to first node in tree
//					key - value to find in tree
//  OUTPUT:   
//      Parameters: current - pointer to node containing value if found
//					found - true if value is found, false if not
//	CALLS TO:	FindNode	
//**********************************************************************
void FindNode(treeNode* &current, bool& found, int key){
	
	found = false;
	
	if(current == NULL)
		return;
	//search left sublist
	else if(key < current->value){
		//continue to search if more nodes in left sublist
		if(current->left != NULL){
			current = current->left;
			FindNode(current, found, key);
		}
	}
	//search right sublist
	else if (key > current->value){
		//continue to search if more nodes in right sublist
		if(current->right != NULL){
			current = current->right;
			FindNode(current, found, key);
		}
	}
	//value is found if current value is equal to key value
	else
		found = true;
		
}

//********************************************************************* 
//  FUNCTION: DeleteNode
//  DESCRIPTION: Deletes a specific node from binary tree 
//	INPUT:
//		Parameters: treeTop - pointer to top node in BST
//					delNode - node to delete from BST
//  OUTPUT:   
//      Parameter:  treeTop - points to new top node if changed	
//**********************************************************************
void DeleteNode(headNode* &treeTop, treeNode* delNode){
	
	treeNode* temp = NULL;					//temp pointer to delete node
	treeNode* parent = treeTop->root;		//ptr to parent node
	treeNode* current = treeTop->root;		//ptr to traverse tree
	bool found = false;						//true when parent node found
	
	
	while(!found){
		//delete node is first node in tree
		if(current->value == delNode->value)
			found = true;
		//walk list to find parent node
		else{
			parent = current;
			
			if(current->value > delNode->value)
				current = current->left;
			else
				current = current->right;
		}
	}
	//if delete node is a leaf
	if(current->left == NULL && current->right == NULL){
		//if only one node in tree
		if(current == parent){
			treeTop->root = NULL;
		}
		//parent pointer has no left children after delete
		else if(parent->left == current){
			parent->left = NULL;
		}
		//parent pointer has no right children after delete
		else{
			parent->right = NULL;
		}
		
		delete current;
		treeTop->count--;
	}
	//node to delete has no left subtree
	else if(current->left == NULL){
		//node to delete is current tree root
		if(current == parent){
			treeTop->root = current->right;
		}
		//re-link left parent subtree
		else if(parent->left == current){
			parent->left = current->right;
		}
		//re-link right parent subtree
		else{
			parent->right = current->right;
		}
		
		delete current;
		treeTop->count--;
	}
	//node to delete has no right subtree
	else if(current->right == NULL){
		//node to delete is current tree root
		if(current == parent){
			treeTop->root = current->left;
		}
		//re-link left parent subtree
		else if(parent->left == current){
			parent->left = current->left;
		}
		//re-link right parent subtree
		else{
			parent->right = current->left;
		}
		
		delete current;
		treeTop->count--;
	}
	//node to delete has two children
	else{
		//set temp to reroute parent pointer to new child
		temp = current->right;
		
		//new child is a leaf, set parent pointer to leaf
		if(temp->left == NULL && temp->right == NULL){
			
			current->value = temp->value;
			delete temp;
			treeTop->count--;
			
			current->right = NULL;
		}
		//continue to walk lower sublist
		else if(temp->left != NULL){
			//continue walking until end of left sublist
			while(temp->left != NULL){
				parent = temp;
				temp = temp->left;
			}
			//reroute lowest left sublist to current, then delete rerouted node
			current->value = temp->value;
			delete temp;
			treeTop->count--;
			
			parent->left = NULL;
		}
		//reroute next highest value since no lower values exist
		else{
			current->value = temp->value;
			current->right = temp->right;
			delete temp;
			treeTop->count--;
		}
	}
	
	cout << endl;
}

//********************************************************************* 
//  FUNCTION: InOrderDisplay
//  DESCRIPTION: Displays values with in-order recursion 
//  INPUT:   
//      Parameter: root - first node to begin in-order recursion from
//	CALLS TO: InOrderDisplay	
//**********************************************************************
void InOrderDisplay(treeNode* root, int& count){
	
	if(root == NULL){
		return;
	}

	InOrderDisplay(root->left, count);
	
	//display values
	cout << setw(5) << root->value;
	count++;
	
	if(count == 10){
		cout << endl;
		count = 0;
	}
	
	InOrderDisplay(root->right, count);
}

//********************************************************************* 
//  FUNCTION: FreeNodes
//  DESCRIPTION: Deletes nodes using post-order recursion 
//  INPUT:   
//      Parameter:  root - points to first node in BST	
//	CALLS TO: FreeNodes
//**********************************************************************
void FreeNodes(treeNode* root){
	
	if(root == NULL)
		return;
	
	FreeNodes(root->left);
	FreeNodes(root->right);
	delete root;
}

//********************************************************************* 
//  FUNCTION: DestroyTree
//  DESCRIPTION: De-allocates BST dynamic memory
//	INPUT:
//		Parameter: treeTop - pointer to top of BST
//  OUTPUT:   
//      Parameter: treeTop - de-allocated BST pointing to NULL	
//**********************************************************************
void DestroyTree(headNode* &treeTop){
	//de-allocated each node in the tree
	FreeNodes(treeTop->root);
	
	treeTop->count = 0;
	treeTop->root = NULL;
	//de-allocate the BST pointer
	delete treeTop;
}

//********************************************************************* 
//  FUNCTION: GetInteger
//  DESCRIPTION: Reads and verifies integer input between 0-10000
//  OUTPUT:   
//      Returns:    num - user choice for number of times to repeat sort	
//**********************************************************************
int GetInteger(){
	
	int num = 0;						//entry to validate
	bool valid = false;					//true if valid integer entry

	//loop until a valid positive integer is entered
	while (!valid){

		cin >> num;
		cout << endl;

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
			//number must be positive non-zero value
			else if (num <= 0 || num > 9999){

				valid = false;					// input is not valid
				cout << "Error: your number must be between 0 and 10000,"
					 << " try again" << endl << endl;
			}
			else
				valid = true;					//an integer value was entered
		}//end else
	}//end loop

	cout << endl;
	
	return num;
}
