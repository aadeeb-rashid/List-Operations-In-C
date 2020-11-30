// CSE240 Fall 2020 HW 7 & 8
// Aadeeb Rashid
// Write the compiler used: Visual studio 

// READ BEFORE YOU START:
// You are given a partially completed program that creates a linked list of employee information.
// The global linked list 'list' is a list of employees with each node being struct 'employeeList'.
// 'employeeList' consists of struct 'employee' which has: employee name, room number, and a linked list of 'supervisors'.
// The linked list of supervisors has each node containing simply the name of the supervisor.
// HW7 ignores the 'supervisors' linked list since there is no operation/manipulation to be done on 'supervisors' list in HW7.
// HW8 has operations/manipulations to be done with 'supervisors' list like add a supervisor, display last added supervisor.

// To begin, you should trace through the given code and understand how it works.
// Please read the instructions above each required function and follow the directions carefully.
// If you modify any of the given code, the return types, or the parameters, you risk getting compile error.
// You are not allowed to modify main ().
// You can use string library functions.

// ***** WRITE COMMENTS FOR IMPORANT STEPS OF YOUR CODE. *****
// ***** GIVE MEANINGFUL NAMES TO VARIABLES. *****
// ***** Before implementing any function, see how it is called in executeAction() *****


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable: 4996) // for Visual Studio

#define MAX_NAME 30

// global linked list 'list' contains the list of employees
struct employeeList {
	struct employee* employee;
	struct employeeList* next;
} *list = NULL;				// currently empty list

// structure "employee" contains the employee's name, room number and linked list of supervisors
struct employee {
	char name[MAX_NAME];
	unsigned int roomNumber;
	struct supervisor* supervisors;		// linked list 'supervisors' contains names of supervisors
};

//  structure 'supervisor' contains supervisor's name 
struct supervisor {
	char name[MAX_NAME];
	struct supervisor* next;
};

// forward declaration of functions (already implmented)
void flushStdIn();
void executeAction(char);

// functions that need implementation:
// HW 7
void addEmployee(char* employeeNameInput, unsigned int roomNumInput); // 20 points
void displayEmployeeList(struct employeeList* tempList);	      // 15 points
struct employee* searchEmployee(char* employeeNameInput);	      // 15 points
//HW 8
void addSupervisor(char* employeeNameInput, char* supervisorNameInput);	// 15 points
void displayEmployeeSupervisorList(struct employeeList* tempList);	// 15 points
void removeEmployee(char* employeeNameInput);			        // 20 points

int main()
{
	char selection = 'a';		// initialized to a dummy value
	do
	{
		printf("\nCSE240 HW 7,8\n");
		printf("Please enter your selection:\n");
		printf("HW7:\n");
		printf("\t a: add a new employee to the list\n");
		printf("\t d: display employee list (no supervisors)\n");
		printf("\t b: search for an employee on the list\n");
		printf("\t q: quit\n");
		printf("HW8:\n");
		printf("\t c: add a supervisor of a employee\n");
		printf("\t l: display employees who report to a specific supervisor\n");
		printf("\t r: remove an employee\n");
		printf("\t q: quit\n");

		selection = getchar();
		flushStdIn();
		executeAction(selection);
	} while (selection != 'q');

	return 0;
}

// flush out leftover '\n' characters
void flushStdIn()
{
	char c;
	do c = getchar();
	while (c != '\n' && c != EOF);
}

// Ask for details from user for the given selection and perform that action
// Read the function case by case
void executeAction(char c)
{
	char employeeNameInput[MAX_NAME], supervisorNameInput[MAX_NAME];
	unsigned int roomNumInput;
	struct employee* searchResult = NULL;

	switch (c)
	{
	case 'a':	// add employee
				// input employee details from user
		printf("\nPlease enter employee's name: ");
		fgets(employeeNameInput, sizeof(employeeNameInput), stdin);
		employeeNameInput[strlen(employeeNameInput) - 1] = '\0';	// discard the trailing '\n' char
		printf("Please enter room number: ");
		scanf("%d", &roomNumInput);
		flushStdIn();

		if (searchEmployee(employeeNameInput) == NULL)	// un-comment this line after implementing searchEmployee()					
		//if (1)									// comment out this line after implementing searchEmployee()
		{
			addEmployee(employeeNameInput, roomNumInput);
			printf("\nEmployee successfully added to the list!\n");
		}
		else
			printf("\nThat employee is already on the list!\n");
		break;

	case 'd':		// display the list
		displayEmployeeList(list);
		break;

	case 'b':		// search for an employee on the list
		printf("\nPlease enter employee's name: ");
		fgets(employeeNameInput, sizeof(employeeNameInput), stdin);
		employeeNameInput[strlen(employeeNameInput) - 1] = '\0';	// discard the trailing '\n' char

		if (searchEmployee(employeeNameInput) == NULL)	// un-comment this line after implementing searchEmployee()					
		//if (0)									// comment out this line after implementing searchEmployee()
			printf("\nEmployee name does not exist or the list is empty! \n\n");
		else
		{
			printf("\nEmployee name exists on the list! \n\n");
		}
		break;

	case 'r':		// remove employee
		printf("\nPlease enter employee's name: ");
		fgets(employeeNameInput, sizeof(employeeNameInput), stdin);
		employeeNameInput[strlen(employeeNameInput) - 1] = '\0';	// discard the trailing '\n' char

		if (searchEmployee(employeeNameInput) == NULL)	// un-comment this line after implementing searchEmployee()					
		//if (0)									// comment out this line after implementing searchEmployee()
			printf("\nEmployee name does not exist or the list is empty! \n\n");
		else
		{
			removeEmployee(employeeNameInput);
			printf("\nEmployee successfully removed from the list! \n\n");
		}
		break;

	case 'c':		// add supervisor
		printf("\nPlease enter employee's name: ");
		fgets(employeeNameInput, sizeof(employeeNameInput), stdin);
		employeeNameInput[strlen(employeeNameInput) - 1] = '\0';	// discard the trailing '\n' char

		if (searchEmployee(employeeNameInput) == NULL)	// un-comment this line after implementing searchEmployee()					
		//if (0)										// comment out this line after implementing searchEmployee()
			printf("\nEmployee name does not exist or the list is empty! \n\n");
		else
		{
			printf("\nPlease enter supervisor's name: ");
			fgets(supervisorNameInput, sizeof(supervisorNameInput), stdin);
			supervisorNameInput[strlen(supervisorNameInput) - 1] = '\0';	// discard the trailing '\n' char

			addSupervisor(employeeNameInput, supervisorNameInput);
			printf("\nSupervisor added! \n\n");
		}
		break;

	case 'l':		// list supervisor's employees
		displayEmployeeSupervisorList(list);
		break;

	case 'q':		// quit
		break;

	default: printf("%c is invalid input!\n", c);
	}
}

// HW7 Q1: addEmployee (20 points)
// This function is used to insert a new employee in the linked list. 
// You must insert the new employee to the head of linked list 'list'.
// You need NOT check if the employee already exists in the list because that is taken care by searchEmployee() called in executeAction(). Look at how this function is used in executeAction().
// Don't bother to check how to implement searchEmployee() while implementing this function. Simply assume that employee does not exist in the list while implementing this function.
// NOTE: The function needs to add the employee to the head of the list.
// NOTE: This function does not add supervisors to the employee info. There is another function addSupervisor() in HW8 for that.
// Hint: In this question, no supervisors means NULL supervisors.

void addEmployee(char* employeeNameInput, unsigned int roomNumInput)
{
	 // create new employee
    struct employee* new_emp = (struct employee*)malloc(sizeof(struct employee)); // allocate memory 
    strcpy(new_emp->name, employeeNameInput); 			// copy name
    new_emp->roomNumber = roomNumInput; 				// copy room number
	new_emp->supervisors = NULL;
    
	// add to the list
	struct employeeList* node = (struct employeeList*)malloc(sizeof(struct employeeList)); // allocate new memory for node in the list
    node->employee = new_emp; // copy pointer
	node->next = NULL;
    
	if(list != NULL) // if list is not empty
	{
		node->next = list; // add before the old head
	}
    list = node; // create the new head
}

// HW7 Q2: displayEmployeeList (15 points)
// This function displays the employee details (struct elements) of each employee.
// Parse through the linked list 'list' and print the employee details ( name and room number) one after the other. See expected output screenshots in homework question file.
// You should not display supervisor names (because they are not added in HW7).
// You MUST use recursion in the function to get full points. Notice that 'list' is passed to the function argument. Use recursion to keep calling this function till end of list.

void displayEmployeeList(struct employeeList* tempList)
{
	if(tempList == NULL) //check if list is empty or if it's at the end of the list, base case
	{
		return;
	}
	printf("\nEmployee Name: %s\nRoom Number: %d\n", tempList->employee->name, tempList->employee->roomNumber); //display information
	displayEmployeeList(tempList->next); //recursively call the method until it reaches the base case. 
}

// HW7 Q3: searchEmployee (15 points)
// This function searches the 'list' to check if the given employee exists in the list. Search by employee name.
// If it exists then return that 'employee' node of the list. Notice the return type of this function.
// If the employee does not exist in the list, then return NULL.
// NOTE: After implementing this fucntion, go to executeAction() to comment and un-comment the lines mentioned there which use searchEmployee()
//       in case 'a', case 'r', case 'l' (total 3 places)
struct employee* searchEmployee(char* employeeNameInput)
{

	struct employeeList* tempList = list;			// work on a copy of 'list'
	while (tempList != NULL)                        //loop through list 
	{
		if(strcmp(tempList->employee->name,employeeNameInput) == 0) //compare name with list names
		{
			return tempList->employee;
		}
		tempList = tempList->next;                                 //iterate through list
	}
	return NULL;                                                  //return NULL id it's not found
	
}



// HW8 Q1: addSupervisor (15 points)
// This function adds supervisor's name to a employee node.
// Parse the list to locate the employee and add the supervisor to that employee's 'supervisors' linked list. No need to check if the employee name exists on the list. That is done in executeAction().
// If the 'supervisors' list is empty, then add the supervisor. If the employee has existing supervisors, then you may add the new supervisor to the head or the tail of the 'supervisors' list.
// You can assume that the same supervisor name does not exist. So no need to check for existing supervisor names, like we do when we add new employee.
// NOTE: Make note of whether you add the supervisor to the head or tail of 'supervisors' list. You will need that info when you implement lastSupervisor()
//       (Sample solution has supervisor added to the tail of 'supervisors' list. You are free to add new supervisor to head or tail of 'supervisors' list.)

void addSupervisor(char* employeeNameInput, char* supervisorNameInput)
{

	struct employeeList* tempList = list;		// work on a copy of 'list'
	
	struct employee* new_emp = searchEmployee(employeeNameInput);                          //find employee to add supervisor to 
	struct supervisor* new_sup = (struct supervisor*)malloc(sizeof(struct supervisor));    //create instance of said supervisor
	strcpy(new_sup->name, supervisorNameInput);											   //assign supervisor's name 
	new_sup->next = new_emp->supervisors;                                                  //add supervisor to the list of supervisors 
	new_emp->supervisors = new_sup; 													   //assign supervisor to employee	
}

// HW8 Q2: displayEmployeeSupervisorList (15 points)
// This function prompts the user to enter a supervisor name. This function then searches for employees with this supervisor.
// Parse through the linked list passed as parameter and print the matching employee details ( name and room number) one after the other. See expected output screenshots in homework question file.
// HINT: Use inputs gathered in executeAction() as a model for getting the supervisor name input.
// NOTE: You may re-use some HW7 Q2 displayEmployeeList(list) code here.
void displayEmployeeSupervisorList(struct employeeList* tempList)
{
	// YOUR CODE HERE
	char supervisorNameInput[MAX_NAME];                            //store input
	printf("\nPlease enter supervisor's name: ");
	fgets(supervisorNameInput, sizeof(supervisorNameInput), stdin);
	supervisorNameInput[strlen(supervisorNameInput) - 1] = '\0';	// discard the trailing '\n' char
	int found = 0;                                                  //variable for keeping track of how many people have the supervisor
	while (tempList != NULL)                        				//loop through list 
	{
		int count = 0;                                                                //for keeping track of how many times the loop has taken place
		struct employee* tempEmp = (struct employee*)malloc(sizeof(struct employee));  //for storing an employee, so we can reset it later
		while(tempList->employee->supervisors != NULL) 									//loop through supervisors for each employee
		{
			if(count == 0)                                                           //copy all information from one node to a "backup" node
			{
				tempEmp->supervisors = tempList->employee->supervisors;

			}
			if(strcmp(tempList->employee->supervisors->name, supervisorNameInput) == 0)
			{
				printf("\nEmployee Name: %s\nRoom Number: %d\n", tempList->employee->name, tempList->employee->roomNumber); //display information
				found++;						//update value
			}
			tempList->employee->supervisors = tempList->employee->supervisors->next;  //iterate through supervisors (we are changing them so we have to restore a "backup" later)
			count++;                            //update value
			if(tempList->employee->supervisors == NULL)
			{
				count = -1;                                                          //use this as an indicator that this employee has been fully checked. 
			}	
		}
		if(count == -1)                                                                                        //restore node to the "backup" after checking it 
		{                                       
			tempList->employee->supervisors = tempEmp->supervisors;
		}
		tempList = tempList->next;                                						 //iterate through list
	}
	if(found <= 0)
	{
		printf("\nNo Employees with that Supervisor");
	}
	



}

// HW8 Q3: removeEmployee (20 points)
// This function removes an employee from the list.
// Parse the list to locate the employee and delete that 'employee' node.
// You need not check if the employee exists because that is done in executeAction()
//removeEmployee() is supposed to remove employee details like name and room number.
// The function will remove supervisors of the employee too.
// When the employee is located in the 'list', after removing the employee name and room number, parse the 'supervisors' list of that employee
// and remove the supervisors.

void removeEmployee(char* employeeNameInput)
{
	if(list->next == NULL)
	{
		list = NULL;
		return;
	}

	struct employeeList* tempList = list;	// work on a copy of 'list'
	struct employee* new_emp = searchEmployee(employeeNameInput);    //find employee to remove
	while (tempList != NULL)                        				//loop through list 
	{
		if((strcmp(new_emp->name,tempList->next->employee->name)== 0) && (new_emp->roomNumber == tempList->next->employee->roomNumber)) //check if the next employee is the one we want to remove
		{
			while(tempList->employee->supervisors != NULL) 									//loop through supervisors for each employee
			{
				free(tempList->employee->supervisors);                                    //free supervisors 
				tempList->employee->supervisors = tempList->employee->supervisors->next;  //iterate through supervisors 

			}
			tempList->next = tempList->next->next;
			free(new_emp);
		}
		tempList = tempList->next;
	}
}
