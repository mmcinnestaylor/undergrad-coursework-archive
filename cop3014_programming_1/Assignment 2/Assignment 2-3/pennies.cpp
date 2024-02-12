/* Name: Marlan McInnes-Taylor
 Date: 9-28-2016
 Section: 20
 Assignment: 20
 Due Date: 9-28-2016
 About this project: This is an earnings calculator. The goal is to prompt the user to input the number of days
					 worked, and output their earning each day, and over the course of the entire time period.
 Assumptions: Assumes correct user input, specifically that the input is a positive or negative number of
		      working days. Additionally it is assumed the first day's earning's will be $.01, although the
			  associated variable can be altered to different values.
 
 All work below was performed by Marlan McInnes-Taylor */


#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    
    //Declare and initialize variables for the number of days worked, the amount earned the
	//first day, amount earned on a subsequent day, and the total earned in a given time period
    int daysWorked;
    double firstEarned = .01, amountEarned = 0, totalEarned = 0;
    
    //Prompt the user to enter the number of days worked. If the number is less than or equal to 0
    //then the user is prompted to enter a value again.
    do
    {
        cout << "Please enter the number of days worked: ";
        cin >> daysWorked;
        
        if (daysWorked <= 0)
        {
            cout << "Invalid number of days.  Try again" << endl;
        }
    }while (daysWorked <= 0);
    
    //Set output parameters
	cout << fixed << showpoint << setprecision(2);
	
	//Display the amount earned each day, assuming earnings double daily
    cout << endl;
	cout << "Day\t\t\t\tAmount Earned" << endl;
    cout << "--------------------------------------------------" << endl;
    
    for (int i = 1; i <= daysWorked; i++)
    {
        //First day's earnings
        if (amountEarned == 0)
        {
            amountEarned = amountEarned + firstEarned;
            cout << i << "\t\t\t\t$ " << amountEarned << endl;
        }
        //Double daily earnings after first day
        else
        {
            amountEarned = (2 * amountEarned);
            cout << i << "\t\t\t\t$ " << amountEarned << endl;
            
        }
		//Maintain a total of the amount earned over a given time period
        totalEarned = totalEarned + amountEarned;
    }
    
    //Display the total earnings 
	cout << endl;
    cout << "Total earnings: $ " << totalEarned << endl;  
    
    return 0;
}
