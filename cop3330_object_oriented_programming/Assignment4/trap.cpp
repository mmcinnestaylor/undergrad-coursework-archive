#include <iostream>
#include "grid.h"

using namespace std;

int main()
{
	int rows, columns;

	cout << "Please input the number of rows for your grid (maximum 40): ";
	cin >> rows;
	cout << "Please input the number of columns for your grid (maximum 40): ";
	cin >> columns;
	cout << endl;

	Grid trap(rows, columns);
 
	trap.Display();
	while(!trap.FrontIsClear()) trap.TurnLeft();
	while(trap.Move(1));

	
	while(trap.GetRow() != 0 && trap.GetCol() != 0 
	       && trap.GetRow() != (trap.GetNumRows() - 1) 
               && trap.GetCol() != (trap.GetNumCols() - 1))
	{
		while(!trap.FrontIsClear())
		{
			trap.TurnLeft();
		}
		
		while(trap.FrontIsClear() && !trap.RightIsClear())
		{
			trap.Move(1);
		}
		
		if(trap.RightIsClear())
		{
			for(int i = 0; i < 3; i++) trap.TurnLeft();
			trap.Move(1);
			break;
		}
				
	}
	
	cout << endl << "You Escaped!" << endl;
	cout << "Your final position is row: " << trap.GetRow() 
             << " & column: " << trap.GetCol() << endl;
	trap.Display();	
return 0;
}
