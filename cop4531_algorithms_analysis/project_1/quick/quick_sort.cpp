#include <chrono>
#include <ctime>
#include <ratio>
#include <cstdlib>
#include <fstream>
#include <iomanip>

using namespace std::chrono;

int* quicksort(int *A, size_t p, size_t r);
int partition(int *A, int p, int r);

int main(){
  srand(time(0));
  const int maxVal = 65536;
  int *intArr;
  int SIZE = 0;
  high_resolution_clock::time_point t1, t2;
  duration<double> time_span;
  std::ofstream fout;
  fout.open("quicksort.txt");

  for(int i = 1; i <= 11; i++){
    if(i == 1)
      SIZE = 10;
    else if(i % 2 == 0)
      SIZE = SIZE * 5;
    else
      SIZE = SIZE * 2;

    intArr = new int[SIZE+1];
    for(int j = 1; j <= SIZE; j++)
      intArr[j] = (rand() % maxVal) + 1;

    t1 = high_resolution_clock::now();
    quicksort(intArr, 1, SIZE);
    t2 = high_resolution_clock::now();
    time_span = duration_cast<duration<double>>(t2 - t1);
    fout << std::fixed << std::showpoint << std::setprecision(8) << time_span.count() << ",";

    delete [] intArr;
  }

  fout.close();
  return 0;
}

int* quicksort(int *A, size_t p, size_t r){
  if (p < r){
      int q = partition(A, p, r);
      quicksort(A, p, q - 1);
      quicksort(A, q + 1, r);
  }
  return A;
}
int partition(int *A, int p, int r){
  int temp;
  int x = A[r];
  int i = p - 1;
  for(int j = p; j <= r - 1; j++){
    if(A[j] <= x){
      i++;
      temp = A[i];
      A[i]= A[j];
      A[j] = temp;
    }
  }
  temp = A[i + 1];
  A[i + 1] = A[r];
  A[r] = temp;
  return i + 1;
}
