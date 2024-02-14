#include <chrono>
#include <ctime>
#include <ratio>
#include <cstdlib>
#include <fstream>
#include <iomanip>

using namespace std::chrono;

int* counting_sort(int *A, size_t len);
int max(int const *A, size_t len);

int main(){
  srand(time(0));
  const int maxVal = 65536;
  int *intArr;
  int *sortedArr;
  int SIZE = 0;
  high_resolution_clock::time_point t1, t2;
  duration<double> time_span;
  std::ofstream fout;
  fout.open("counting_sort.txt");

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
    sortedArr = counting_sort(intArr, SIZE);
    t2 = high_resolution_clock::now();
    time_span = duration_cast<duration<double>>(t2 - t1);
    fout << std::fixed << std::showpoint << std::setprecision(8) << time_span.count() << ",";

    delete [] sortedArr;
    delete [] intArr;
  }

  fout.close();
  return 0;
}

int* counting_sort(int *A, size_t len){
  int i, j;
  int SIZE = max(A, len);
  int *B = new int[len+1];
  int *C = new int[SIZE+1];

  for(i = 0; i <= SIZE; i++)
    C[i] = 0;
  for(j = 1; j <= len; j++)
    C[A[j]] += 1;
  for(i = 1; i <= SIZE; i++)
    C[i] = C[i] + C[i - 1];
  for(j = len; j >= 1; j--){
    B[C[A[j]]] = A[j];
    C[A[j]] -= 1;
  }
  delete [] C;
  return B;
}
int max(int const *A, size_t len){
  int max = 0;
  for(int i = 1; i <= len; i++){
    if(max < A[i])
      max = A[i];
  }
  return max;
}
