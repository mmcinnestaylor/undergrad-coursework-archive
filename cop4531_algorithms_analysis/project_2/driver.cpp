#include <fstream>
#include <random>
#include <iostream>
#include <iomanip>
//#include "linear.cpp"
#include "quadratic.cpp"
//#include "double.cpp"
//#include "part1.cpp"
using namespace std;

int main(){
  double loadFactor;
  double dSIZE = SIZE;
  int theArray[SIZE];
  init(theArray);

  ofstream fout;
  fout.open("quadtest.txt");
  random_device rd;  //Will be used to obtain a seed for the random number engine
  mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
  uniform_int_distribution<> dis(-2147483647, 2147483646);
  cout << "About to insert\n";
  int temp;
  for(int i = 0; i < (SIZE/2); i++){
    temp = dis(gen);
    insert(theArray, temp);
    //insert(theArray, i);
    if(failFlag) cout << "Failed to insert\n";
  }



  /*for(int i = 0; i < 15; i++){
    if(search(theArray, i)) cout << i << " is present\n";
  }*/

  for(int i = SIZE/2; i < SIZE; i++){
    loadFactor = i/dSIZE;
    insert(theArray, dis(gen));
    if(failFlag) cout << "Part 2 failed to insert\n";
    fout << fixed << showpoint << setprecision(8) << loadFactor << "," << probes
        << "," << 1/(1-loadFactor) << "\n";
  }

  for(int i = 0; i < SIZE; i++){
    if(theArray[i] == nullVal) cout << "Found NULL before delete\n";
  }
  if(search(theArray, temp)) cout << "Found temp in theArray\n";
  remove(theArray, temp);
  for(int i = 0; i < SIZE; i++){
    if(theArray[i] == nullVal) cout << "Found NULL after delete\n";
  }

  /*for(int i = 0; i < SIZE; i++){
    if(theArray[i] == -2147483648) cout << "NULL value is present\n";
  }*/
  //if(search(theArray, -2147483648)) cout << "NULL value is present\n";

  return 0;
}
