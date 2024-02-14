#include <iostream>
#include "knapsack.cpp"

using namespace std;

int main(){
  unsigned long totalWeight = 8;
  int numItems = 4;

  unsigned int values[] = {15, 10, 9, 5};
  unsigned int weights[] = {1, 5, 3, 4};

  cout << "The weight array before.\n";
  for(int i = 0; i < numItems; i++)
    cout << weights[i] << ", ";
  cout << endl;

  knapsack(weights, values, numItems, totalWeight);

  cout << "The value array.\n";
  for(int i = 0; i < numItems; i++)
    cout << values[i] << ", ";
  cout << endl;

  cout << "The weight array after.\n";
  for(int i = 0; i < numItems; i++)
    cout << weights[i] << ", ";
  cout << endl;

  return 0;
}
