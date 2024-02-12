/* Name: Marlan McInnes-Taylor 
Date: 10/7/2016 
Section: 20 
Assignment: 3 
Due Date: 10/7/2016 
About this project: This program is meant be an integer digit calculator. It accepts 
					a user entered integer, and returns the sum of all digits in that 
					integer.
Assumptions: Assumes correct user input, assumes inputted integer fits into an int variable 

All work below was performed by Marlan McInnes-Taylor */

#include <iostream>
#include <cmath>

using namespace std;

//Prototype for AddNumbers function
int AddNumbers(int);

int main()
{
	//Declare varibles for user input and quit value
	int enteredInteger, quitValue = 0;

	//Loop to prompt user to enter an inter to be summed, or enter the quit value
	do
	{
		cout << "Please enter an integer (" << quitValue << " to quit): ";
		cin >> enteredInteger;
		//Test to assess whether or not quit value entered. If quit value is not entered, interger is sent to AddNumbers
		//function to be summed, and the result is dispayed here.
		if (enteredInteger != quitValue)
			cout << endl << "The sum of the digits " << enteredInteger << " is " 
				 << AddNumbers(enteredInteger) << endl << endl;
	}while(enteredInteger != quitValue);
	
	cout << endl << "Goodbye" << endl;

	return 0;
}

//Function to sum digits of a user provided integer
int AddNumbers(int givenInteger)
{
    //Declare and initialize variable to hold sum of digits
	int numSum = 0;
    
	//Takes the absolute value of the variable givenInteger to remove possible negative user input
	givenInteger = abs(givenInteger);
	
    //Loop to sum digits of user provided integer
	while (givenInteger > 0)
    {
        //Mod operator returns value of rightmost digit, and value is stored 
		//in numSum.
		numSum = numSum + (givenInteger % 10);
        //Integer division removes rightmost digit, allowing for next loop pass
		//to grab next digit value.
		givenInteger = (givenInteger / 10);
    }
	//Sum of digits is returned to main function
	return numSum;
}
