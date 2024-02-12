/* Name: Marlan McInnes-Taylor 
Date: 11/02/2016 
Section: 20 
Assignment: 5 
Due Date: 11/02/2016 
About this project: This program allows a user to create an array of integers, and perform a number of 
                    different functions on ot to the array. This includes inserting a new valus, removing
					a value, reversing the order of the array contents, and sorting the array from least to
					greatest value, amongst others. The number of changes made to the array is tracked throughout the program, 
					and can be displayed. The counter is reset when the Fill function is called.
Assumptions: Assumes correct user input. Assumes index values are used to refer to position in array, as 
             opposed to 'nth term in array' notation.

All work below was performed by Marlan McInnes-Taylor */



#include <iostream>
using namespace std;

/*Given Function prototypes*/
void PrintArray (const int arr[], const int size);
void FillArray(int arr[], const int size);

/*Function Test prototypes*/
void Insert(int arr[], const int size, int newVal, int index); 
void Delete(int arr[], const int size, int index);
void Reverse(int arr[], const int size);
void Sort(int arr[], const int size);
bool Found(const int arr[], const int size, int searchVal);

/*Extra Function prototypes*/
double Average(const int arr[], const int size);
int Sum(const int arr[], const int size);
int FoundIndex(const int arr[], const int size, int searchVal);
int Least(const int arr[], const int size);
int Greatest(const int arr[], const int size);

int main()
{
   const int SIZE = 15;
   int intArray[SIZE], insertVal, searchVal, indexVal, changes;
   char menuSelection = '\0';
   do
   {
	  //Full menu which is displayed on the first run, or when the user selects 'M'
	  if(menuSelection == '\0' || menuSelection == 'M' || menuSelection == 'm')
	  {
		  cout << " \t** Given features **" << endl;
	      cout << "P\tPrint the array contents" << endl;
	      cout << "F\tFill the array (user entry)" << endl << endl;
	      cout << " \t** Function Tests **" << endl;
	      cout << "I\tInsert" << endl;
	      cout << "D\tDelete" << endl;
	      cout << "R\tReverse" << endl;
	      cout << "S\tSort" << endl;
	      cout << "X\tFound" << endl <<endl;
	      cout << "\t** Extra Functions **" << endl;
		  cout << "A\tAverage" << endl;
		  cout << "U\tSum" << endl;
		  cout << "G\tGreatest" << endl;
		  cout << "L\tLeast" << endl;
		  cout << "C\tCount of changes to the array" << endl << endl;
		  cout << "M\tPrint this menu" << endl;
		  cout << "Q\tQuit this program" << endl << endl;
		  cout << "Enter your menu selection: ";

		  cin >> menuSelection;
	  }
	  //Short menu entry prompt which appears as a default after the first run
	  else
	  {
		  cout << endl << "Enter your menu selection: ";
		  cin >> menuSelection;
	  }
	  //Switch handles menu selection
	  switch(menuSelection)
	  {
		 case 'P':
		 case 'p':
			  {
				  PrintArray(intArray, SIZE);
				  break;
			  }
		 case 'F':
		 case 'f':
			  {
				  FillArray(intArray, SIZE);
				  changes = 0;
				  break;
			  }
		 case 'I':
		 case 'i':
			  {
				  //Prompt user to input value to be inserted, and at which index
				  cout << "Enter value to insert: ";
				  cin >> insertVal;
				  cout << "Enter index at which to insert: ";
				  cin >> indexVal;
				  Insert(intArray, SIZE, insertVal, indexVal);
				  PrintArray(intArray, SIZE);
				  changes++;
				  break;
			  }
		 case 'D':
		 case 'd':
			  {
				  //Prompt user to which which index location to perform delete function
				  cout << "Enter index of item to delete: ";
				  cin >> indexVal;
				  Delete(intArray, SIZE, indexVal);
				  PrintArray(intArray, SIZE);
				  changes++;
				  break;
			  }
		 case 'R':
		 case 'r':
			  {
				  Reverse(intArray, SIZE);
				  PrintArray(intArray, SIZE);
				  changes++;
				  break;
			  }
		 case 'S':
		 case 's':
			  {
				  Sort(intArray, SIZE);
				  PrintArray(intArray, SIZE);
				  changes++;
				  break;
			  }
		 case 'X':
		 case 'x':
			  {
				  //Prompt user to enter a value to search for
				  cout << "What value should we search for? --> ";
				  cin >> searchVal;
				  //Assess function return value, and display appropriate output
				  if(Found(intArray, SIZE, searchVal))
				  {
					  cout << "The value " << searchVal << " appears in the list." << endl;
					  cout << "The value is located at index number " << FoundIndex(intArray, SIZE, searchVal) << "." << endl;
				  }

				  else
					  cout << "The value " << searchVal << " does not appear in the list." << endl;
				  break;
			  }
		 case 'A':
		 case 'a':
			  {
				  cout << "The average of all numbers in the array is " << Average(intArray, SIZE) << endl;
				  break;
			  }
		 case 'U':
		 case 'u':
			  {
				  cout << "The sum of all numbers in the array is " << Sum(intArray, SIZE) << endl;
				  break;
			  }
		 case 'C':
		 case 'c':
			  {
				  cout << "There have been " << changes << " changes made to the array since is was filled." << endl;
				  break;
			  }
		 case 'G':
		 case 'g':
			  {
				  cout << "The largest number in the array is: " << Greatest(intArray, SIZE) << endl;
				  break;
			  }
		 case 'L':
		 case 'l':
			  {
				  cout << "The smallest number in the array is: " << Least(intArray, SIZE) << endl;
				  break;
			  }
		 case 'M':
		 case 'm':
			  {
				  cout << endl;
				  break;
			  }
		 case 'Q':
		 case 'q':
			  {
				  PrintArray(intArray, SIZE);
				  break;
			  }
	  }
   }while(menuSelection != 'Q' && menuSelection != 'q');

   
   return 0;
}					


/*Function Tests*/

//Insert function
void Insert(int arr[], const int size, int newVal, int index)
{
	int tempStore;
	//Insert process will only take place if the inputted index is within bounds
	if(index < size)
		//Starts loop at user inputted index
		for (int i = index; i < size; i++)
		{
			//Store original value, insert new value
			tempStore = arr[i];
			arr[i] = newVal;
			newVal = tempStore;
		}
}
//Delete Function
void Delete(int arr[], const int size, int index)
{    
	//Delete process will only take place if the inputted index is within bounds
	if(index < size)
		for (int i = index; i < size; i++)
		{
			//If loop has reached last index location, 0 is automatically assigned
			if(i == (size -1))
				arr[i] = 0;
			//Shift array contents to the left
			else
			{
				arr[i] = arr[i + 1];
			}
		}
}
//Reverse Function
void Reverse(int arr[], const int size)
{
	int tempVal;

	for(int i = 0; i < (size/2); i++)
	{
		//Temp store then swap values throughout the array
		tempVal = arr[i];
		arr[i] = arr[size-(i + 1)];
		arr[size-(i + 1)] = tempVal;
	}
}
//Sort function
void Sort(int arr[], const int size) 
{
	int swap;
	int tempVal;
	do
	{
		//Counter to monitor swap process is set to zero, controlling loop exit
		swap = 0;
		for (int i = 0; i < (size- 1); i++)
		{
			//Adjacent indices are compared and a swap is performed, if appropriate
			if(arr[i] > arr[i + 1])
			{
				tempVal = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = tempVal;
				swap++;
			}
		}
	}while(swap != 0);
}
//Found function
bool Found(const int arr[], const int size, int searchVal)
{
	//Default return value is set
	bool result = false;
	for(int i = 0; i < size; i++)
	{
		if (arr[i] == searchVal)
		{
			//Return value is set to true only if a match is located
			result = true;
			break;
		}
	}

	return result;
}

/*Extra Functions*/

//Average function
double Average(const int arr[], const int size)
{
	int arraySum = 0;
	//Array values are summed
	for(int i = 0; i < size; i++)
		arraySum = arraySum + arr[i];
	//Returns the average of all array values
	return ((arraySum * 1.0)/size);
}
//Sum function
int Sum(const int arr[], const int size)
{
	int arraySum = 0;
	//contents of array are summed
	for(int i = 0; i < size; i++)
		arraySum = arraySum + arr[i];
	//returns sum of all array contents
	return arraySum;
}
//FoundIndex function 
int FoundIndex(const int arr[], const int size, int searchVal)
{
	int i;

	for(i = 0; i < size; i++)
	{
		if (arr[i] == searchVal)
		{
			break;
		}
	}
	//returns the index location of the matched search value
	return i;
}
//Least function
int Least(const int arr[], const int size)
{
	//Default value is set to index 0 value
	int leastVal = arr[0];
	//Checks all array contents for the smallest number
	for(int i = 0; i < size; i++)
	{
		if(leastVal > arr[i])
			leastVal = arr[i];
	}
	//returns smallest number in array
	return leastVal;
}
//Grestest function
int Greatest(const int arr[], const int size)
{
	//Default value is set to index 0 value
	int greatestVal = arr[0];
	//Checks all array contents for the largest number
	for(int i = 0; i < size; i++)
	{
		if(greatestVal < arr[i])
			greatestVal = arr[i];
	}
	//returns largest number in array
	return greatestVal;
}



/* Definitions of PrintArray and FillArray below DO NOT CHANGE THESE!*/

//PrintArray Function
//This function prints the contents of any interger array of any size seperated by commas
void PrintArray(const int arr[], const int size)
{
   cout << "\nThe array:\n { ";
   for (int i = 0; i < size-1; i++)	// for loop, prints each item (not last due to comma handling)
      cout << arr[i] << ", ";

   cout << arr[size-1] << " }\n";	// prints last item , no comma
}

//FillArray Function 
//Allows the user to enter data into any integer array of any size.
void FillArray(int arr[], const int size)
{
   cout << "Please enter " << size 
	<< " integers to load into the array\n> ";

   for (int i = 0; i < size; i++)
	cin >> arr[i];		
}














