/* Name: Marlan McInnes-Taylor
 Date: 9-28-2016
 Section: 20
 Assignment: 2
 Due Date: 9-28-2016
 About this project: This project is designed to be a days of the month calculator. It is meant to accept month
					 and year input, and the output the number of days in the given month of the given year.
					 This program does account for leap years.
 Assumptions: Assumes correct user input, specifically that the year inputted is valid.
 
 All work below was performed by Marlan McInnes-Taylor */


#include <iostream>

using namespace std;

int main()
{
    //Declare variables for the month and year user input, and number of days output
    int month, year, daysDisplayed;
    
    //Prompt user for month and year input
    cout << "Enter a month (1-12): ";
    cin >> month;
    
    cout << "Enter a year: ";
    cin >> year;
    
    cout << endl;
    
    //Check user's month input to see if it is valid. If it in't, the program aborts.
    if (month < 1 || month > 12)
    {
        cout << "Invalid Month entered. Aborting Program." << endl;
    }
    
    //Determine if the user's input correlates to a 30 or 31 day month, and output the answer.
    else if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month ==10 || month ==12)
    {
        daysDisplayed = 31;
		cout << "Number of days: " << daysDisplayed <<endl;
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        daysDisplayed = 30;
		cout << "Number of days: " << daysDisplayed << endl;
    }
    
    //If the user selects February, a calculation is used to determine whether or not the user's year input
    //is a leap year, the appropriate number is then displayed.
    else if (month == 2)
    {
        if (year % 100 == 0 && year % 400 == 0)
        {
            daysDisplayed = 29;
			cout << "Number of days: " << daysDisplayed << endl;
        }
        else if (year % 100 > 0 && year % 400 > 0 && year % 4 == 0)
        {
            daysDisplayed = 29;
			cout << "Number of days: " << daysDisplayed << endl;
        }
        else if (year % 100 == 0 && year % 400 > 0)
        {
            daysDisplayed = 28;
			cout << "Number of days: " << daysDisplayed << endl;
        }
        else
        {
            daysDisplayed = 28;
			cout << "Number of days: " << daysDisplayed << endl;
        }
            
    }
    
    return 0;
}
