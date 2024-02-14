#include <chrono>
#include <ctime>
#include <ratio>
#include <cstdlib>
#include <fstream>
#include <iomanip>

using namespace std::chrono;

void max_heapify(int *A, int i, size_t len);
void build_max_heap(int *A, size_t len);
int* heapsort(int *A, size_t len);

int main(){

  srand(time(0));
  const int maxVal = 65536;
  int *intArr;
  int SIZE = 0;
  high_resolution_clock::time_point t1, t2;
  duration<double> time_span;
  std::ofstream fout;
  fout.open("heapsort.txt");

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
    heapsort(intArr, SIZE);
    t2 = high_resolution_clock::now();
    time_span = duration_cast<duration<double>>(t2 - t1);
    fout << std::fixed << std::showpoint << std::setprecision(8) << time_span.count() << ",";

    delete [] intArr;
  }
  fout.close();
  return 0;
}

void max_heapify(int *A, int i, size_t len){
  int l = 2 * i;
  int r = (2 * i) + 1;
  int largest;

  if(l <= len && A[l] > A[i])
    largest = l;
  else
    largest = i;

  if(r <= len && A[r] > A[largest])
    largest = r;

  if(largest != i){
    int temp = A[largest];
    A[largest] = A[i];
    A[i] = temp;
    max_heapify(A, largest, len);
  }
}
void build_max_heap(int *A, size_t len){
  for(int i = len/2; i >= 1; i--)
    max_heapify(A, i, len);
}
int* heapsort(int *A, size_t len){
  int temp;
  build_max_heap(A, len);
  int heapsize = len;

  for(int i = len; i >= 1; i--){
    temp = A[i];
    A[i] = A[1];
    A[1] = temp;
    heapsize -= 1;
    max_heapify(A, 1, heapsize);
  }
  return A;
}
