#include <chrono>
#include <list>
#include <ctime>
#include <ratio>
#include <cstdlib>
#include <fstream>
#include <iomanip>

using namespace std::chrono;

int* bucket_sort(int *A, size_t len);

int main(){
  srand(time(0));
  const int maxVal = 65536;
  int *intArr;
  int SIZE = 0;
  high_resolution_clock::time_point t1, t2;
  duration<double> time_span;
  std::ofstream fout;
  fout.open("bucket_sort.txt");

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
    bucket_sort(intArr, SIZE);
    t2 = high_resolution_clock::now();
    time_span = duration_cast<duration<double>>(t2 - t1);
    fout << std::fixed << std::showpoint << std::setprecision(8) << time_span.count() << ",";

    delete [] intArr;
  }

  fout.close();
  return 0;
}

int* bucket_sort(int *A, size_t len){
  int i;
  std::list<int> bucketArr[7];

  for(i = 1; i <= len; i++)
    bucketArr[A[i]/10000].push_back(A[i]);

  bucketArr[0].sort();
  for(i = 1; i < 7; i++){
    bucketArr[i].sort();
    bucketArr[0].merge(bucketArr[i]);
  }

  for(i = 1; i <= len; i++){
    A[i] = bucketArr[0].front();
    bucketArr[0].pop_front();
  }
  return A;
}
