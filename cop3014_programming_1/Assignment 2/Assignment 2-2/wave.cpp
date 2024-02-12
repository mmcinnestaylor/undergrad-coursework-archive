/* Name: Marlan McInnes-Taylor
 Date: 9-28-2016
 Section: 20
 Assignment: 2
 Due Date: 9-28-2016
 About this project: This program is intended to be a simple calculator which determines the amount of time
				     a sound wave takes to travel a given distance in a given medium. The goal is to accept 
					 input from the user for the type of travel medium, and travel distance, and output the time
					 it takes the wave to travel the given distance.
 Assumptions: Assumes correct user input, assumes sound wave travel speeds in given mediums will not change.
 
 All work below was performed by Marlan McInnes-Taylor */


#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    //Declare variables for the selection of wave travel medium and travel distance
    char waveMedium;
    double waveDistance;
    
    //Declare and initialize variables for the speeds of waves in different mediums
    const double speedAir = 1100, speedWater = 4900, speedSteel = 16400;
    
    //Program menu and prompt to select travel medium
    cout << "Welcome to Sound Wave Calculator" << endl << endl;
    cout << "Select the medium the sound wave will travel through." << endl;
    cout << "\tA\tAir" << endl;
    cout << "\tW\tWater" << endl;
    cout << "\tS\tSteel" << endl <<endl;
    cout << "> ";
    cin >> waveMedium;
    
	//Set output parameters
	cout << fixed << showpoint << setprecision(4); 

	//Check to see if medium selection is valid. If not, the program terminates.
	if (waveMedium != 'A' && waveMedium != 'a' && waveMedium != 'W' && waveMedium != 'w' && waveMedium != 'S' && waveMedium != 's')
	{
		cout << "Illegal entry. Aborting program." << endl;
	}
    
	else
	{
		//Prompt to input travel distance
		cout << "How far will the sound wave travel (in feet)? ";
		cin >> waveDistance;
		
		 //Test to ensure travel distance is not a negative number
		if (waveDistance < 0)
		{
        cout << "Distance cannot be negative.  Aborting program." << endl;
        
		}
    
		//If travel distance is positive, then a calculation is performed to determine wave travel time
	    //in a given medium
		else
		{
			switch (waveMedium)
			{
				//Travel time calculation if the medium is Air
				case 'a':
				case 'A':
				{
					cout << "The sound wave will travel " << (waveDistance / speedAir) << " seconds" << endl;
					break;
				}
				//Travel time calculation if the medium is Water
				case 'w':
				case 'W':
				{
					cout << "The sound wave will travel " << (waveDistance / speedWater) << " seconds" << endl;
					break;
				}
				//Travel time calculation if the medium is Air
				case 's':
				case 'S':
				{
					cout << "The sound wave will travel " << (waveDistance / speedSteel) << " seconds" << endl;
					break;
				}
			}
		}
	}
   
    cout << "Goodbye" << endl;
    
    return 0;
}
