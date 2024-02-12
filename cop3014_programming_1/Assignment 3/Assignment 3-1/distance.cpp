/* Name: Marlan McInnes-Taylor 
Date: 10/7/2016 
Section: 20 
Assignment: 3 
Due Date: 10/7/2016 
About this project: This program is meant to act as a distance converter and calculator. It accepts user input
					in the form of two distances in meters, centimeters, and millimeters. It then outputs the 
					two distances in millimeters only, and the difference of the two distances, also in 
					millimeters.
Assumptions: Assumes correct user input 

All work below was performed by Marlan McInnes-Taylor */

#include <iostream>
#include <cmath>

using namespace std;

//Function prototype for NumMillimeters function
int NumMillimeters(int, int, int);

int main()
{
    //Declare variables for each set of user enteries, along with variables for the totals of each distance
	//and the difference of the two distances
	int firstMeters, firstCentimeters, firstMillimeters, firstTotal, secondMeters, secondCentimeters, 
		secondMillimeters,  secondTotal, distanceDifference;
    
    //Prompt user to input values for the first distance
    cout << "Input first distance..." << endl;
    cout << "Meters: ";
    cin >> firstMeters;
    cout << "Centimeters: ";
    cin >> firstCentimeters;
    cout << "Millimeters: ";
    cin >> firstMillimeters;
    
	//Send first set of values to NumMillimeters function, and assign returned value to firstTotal
    firstTotal = NumMillimeters(firstMeters, firstCentimeters, firstMillimeters);
    
    //Prompt user to input values for the second distance
	cout << endl << "Input second distance..." << endl;
    cout << "Meters: ";
    cin >> secondMeters;
    cout << "Centimeters: ";
    cin >> secondCentimeters;
    cout << "Millimeters: ";
    cin >> secondMillimeters;
    
	//Send second set of values to NumMillimeters function, and assign returned value to secondTotal
    secondTotal = NumMillimeters(secondMeters, secondCentimeters, secondMillimeters);
    
	
	
	//Calculate the difference of the two distances, and return the absolute value of the result
	distanceDifference =  abs((firstTotal - secondTotal));

    //Output the converted distances, and the difference of the two distances
	cout << endl << "The first distance is " << firstTotal << " mm."  << endl;
    cout << "The second distance is " << secondTotal << " mm." << endl;
    cout << "The difference is " << distanceDifference << " mm." << endl;
   
    return 0;
}

//Function to accept distances entered in meters, centimeters, and millimeters be  returned as a 
//single value in millimeters 
int NumMillimeters (int meters, int centimeters, int millimeters)
{ 
    //Declare variables to store the converted meter and centimeter distances
	int convertedMeters, convertedCentimeters;
    
    //Convert meters and centimeters to millimeters
	convertedMeters = meters * 1000;
    convertedCentimeters = centimeters * 10;
    
    //Return the inputted values as a single millimeter distance
	return convertedMeters + convertedCentimeters + millimeters;
}
