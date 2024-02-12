#include <iostream>
#include <fstream>
using namespace std;

#include "bitarray.h"
#include "sieve.h"

int main()
{
/*
	BitArray a(16);
	cout << a << endl;
	a.Set(9);
	cout << a << endl;
	a.Set(1); a.Set(3); a.Set(5); a.Set(7);
	//a.Unset(9);
	BitArray b = a;
	cout << b << endl;
	if(b == a) cout << "true A" << endl;
	if(b != a) cout << "true B" << endl;
	b.Unset(1);
	if(b == a) cout << "true C" << endl;
	if(b != a) cout << "true D" << endl;
	//b = b;
	cout << b << endl;
	a.Flip(3);
	cout << a << endl;
*/
   unsigned int i, max, counter = 0;

   cout << "\nEnter a positive integer for the maximum value: ";
   cin >> max;

   BitArray ba(max);

   Sieve(ba);                    // find the primes (marking the bits)

   cout << "The bit array looks like this: \n"
        << ba
        << '\n';  

   cout << "\nPrimes less than " << max << ':' << '\n';
   for (i = 0; i < max; i++)
   {    
       if (ba.Query(i))
       {
	    counter++;
            cout << i;
            if (counter % 8 == 0)
            {
                cout << '\n';
                counter = 0;
            }
            else
                cout << '\t';
       }
   }


   cout << "\nGoodbye!\n";

  return 0;
}

