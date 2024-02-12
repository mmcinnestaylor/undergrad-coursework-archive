/////////////////////////////////////////////////////////
// Bob Myers
//
// sample.cpp -- sample test program starter for Date class
/////////////////////////////////////////////////////////

#include <iostream>
#include "date.h"

using namespace std;

int main()
{
   Date d1;		// should default to 1/1/2000
   Date d2(4,10,-1992);  // should init to 4/10/1992

   // display dates to the screen
   cout << "\nDate d1 is: ";
   d1.Show();
   cout << "\nDate d2 is: ";
   d2.Show();
	cout << endl;

	cout << "input test" << endl;
   d1.Input();			// Allow user to enter a date for d1
   cout << "\nDate d1 is: ";
   d1.Show();
	cout << endl;

	cout << "formetting tests" << endl;
	cout << " formet L" << endl;
	d1.SetFormat('l');
	d1.Show();
	cout << endl;

	cout << "format t" << endl;
	d1.SetFormat('t');
	d1.Show();
	cout << endl;
	
	cout << "format J" << endl;
	d1.SetFormat('j');
	d1.Show();
	cout << endl;

	cout << "reset to D" << endl;
	d1.SetFormat('d');
	d1.Show();
	cout << endl;

	cout << "compare test";

  // d1.SetFormat('L');		// change format of d1 to "Long" format
  // cout << "\nDate d1 is: ";
  // d1.Show();			// print d1 -- should show now in long format
   	cout << "equal" << endl;
	d1.Set(1, 1, 2000);
	d2.Set(1, 1, 2000);
	cout << d1.Compare(d2) << endl;

	cout << "d1 earlier" << endl;
	d2.Set(1, 1, 2001);
	cout << d1.Compare(d2) << endl;

	d2.Set(1, 1, 1999);
	cout << "d1 later" << endl;
	cout << d1.Compare(d2) << endl;


	
	//cout << "Input" << endl;
	//d1.Input();
	//d1.SetFormat('J');
	//d1.Show();

	cout << "increment test"<< endl;
	//d1.Increment(10);
	//d1.Show();
	//cout << endl;
	//d1.Increment(100);
	//d1.Show();
	//cout << endl;
	d1.Set(3, 13, 2033);
	d1.Increment(1000000);
	d1.Show();	
   // and so on.  Add your own tests to fully test the class'
   //   functionality.
}
