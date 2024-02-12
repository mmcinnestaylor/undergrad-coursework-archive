/* Name: Marlan McInnes-Taylor 
Date: 9/19/2016 
Section: 20 
Assignment: #1 
Due Date: 9/19/2016 
About this project: This project's aim is to create a simple calculator to compute the number of cans of paint
					required to paint a room. The program prompts the user to input the dimensions of a wall in a 
					square room, along with the dimensions of a window in the same room. The program will then 
					display a calculation of how many cans of paint would be required to paint the room.		
Assumptions: Assumes correct user input, that the amount of area a paint can covers is fixed  

All work below was performed by Marlan McInnes-Taylor */

#include <iostream> 
#include <iomanip>
using namespace std;

int main()
{
    /*Create variables to store the area a paint can covers, room and window dimensions, 
	calculations performed to determine room area, and number of cans required to paint room*/ 
	const int canCoverage = 240;
    double wallHeight, wallWidth, windowHeight, windowWidth, totalArea, paintableArea, totalCans;
    
    cout << "Welcome to Paint Calculator 2016!!" << endl << endl;
   
    //Obtain wall and window dimensions from user, and store each value in their respective variables
    cout << "Please enter all values in feet: " << endl;
    
    cout << "How wide is each wall in the room? ";
    cin >> wallWidth;
    
    cout << "and how high is each wall in the room? ";
    cin >> wallHeight;
	   
    cout << "How wide is the window? ";
    cin >> windowWidth;
    
    cout << "and what is the window's height? ";
    cin >> windowHeight;
	cout << endl;
    
    
    //Calculate total wall area, paintable wall area, and number of cans required to paint walls
    totalArea = 4 * (wallHeight * wallWidth);
    
    paintableArea = totalArea - (windowHeight * windowWidth);
    
    totalCans = paintableArea / canCoverage;
    
    
    //Display room and window dimensions inputed by user
	cout << "A room where each wall is\n";
    cout << "\t" << wallWidth << "\' wide and\n";
    cout << "\t" << wallHeight << "\' tall and\n";
    cout << "\tcontaining a window that is\n";
    cout << "\t" << windowWidth << "\' wide and\n";
    cout << "\t" << windowHeight << "\' tall,\n";

	//Display how much area needs to be painted, and how many cans are required
    cout << "has " << fixed << showpoint << setprecision(1) << paintableArea << " square feet of paintable wall\n";
    cout << "and would require " << fixed << showpoint << setprecision(2) << totalCans << " cans of paint\n";
    cout << "(assuming that each can will cover 240 square feet of wall)." << endl << endl;

    cout << "Thanks for using Paint Calculator 2016. Goodbye!!" << endl;
    
    return 0;
    
}