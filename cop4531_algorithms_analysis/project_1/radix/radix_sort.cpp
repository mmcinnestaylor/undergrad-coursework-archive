#include <chrono>
#include <ctime>
#include <ratio>
#include <cstdlib>
#include <fstream>
#include <cmath>
#include <iomanip>

using namespace std::chrono;

int* radix_sort(int *A, size_t len);
void mod_merge_sort(int *A, size_t p, size_t r, int divisor);
void mod_merge(int* A, int p, int q, int r, int divisor);

int main(){
  srand(time(0));
  const int maxVal = 65536;
  int *intArr;
  int SIZE = 0;
  high_resolution_clock::time_point t1, t2;
  duration<double> time_span;
  std::ofstream fout;
  fout.open("radix_sort.txt");

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
    radix_sort(intArr, SIZE);
    t2 = high_resolution_clock::now();
    time_span = duration_cast<duration<double>>(t2 - t1);
    fout << std::fixed << std::showpoint << std::setprecision(8) << time_span.count() << ",";

    delete [] intArr;
  }
  fout.close();
  return 0;
}

int* radix_sort(int *A, size_t len){
  for(int i = 0; i < 5; i++){
    int divisor = static_cast<int>(1 * pow(10, i));
    mod_merge_sort(A, 1, len, divisor);
  }
}
void mod_merge(int* A, int p, int q, int r, int divisor){
  int i, j, k;
  int n1 = q - p + 1;
  int n2 = r - q;
  int leftEnd = q;

  int *L = new int[n1 + 2];
  int *R = new int[n2 + 2];

  for(i = 1; i <= n1; i++)
    L[i] = A[p + i - 1];
  for(j = 1; j <= n2; j++)
    R[j] = A[q + j];

  L[n1 + 1] = 2147483647;
  R[n2 + 1] = 2147483647;

  i = j = 1;
  k = p;

  while(p <= leftEnd && q <= r){
    if(((L[i] / divisor) % 10) <= ((R[j] / divisor) % 10)){
      if(L[i] == 2147483647)
        break;
      else{
        A[k++] = L[i++];
        p++;
      }
    }
    else{
      if(R[j] == 2147483647)
        break;
      else{
        A[k++] = R[j++];
        q++;
      }
    }
  }
  while(p <= leftEnd){
    if(L[i] == 2147483647)
      break;
    else{
      A[k++] = L[i++];
      p++;
    }
  }
  while(q <= r){
    if(R[j] == 2147483647)
      break;
    else{
      A[k++] = R[j++];
      q++;
    }
  }

  delete [] L;
  delete [] R;
}
void mod_merge_sort(int *A, size_t p, size_t r, int divisor){
  if(p < r){
      int q = (p + r) / 2;
      mod_merge_sort(A, p, q, divisor);
      mod_merge_sort(A, q + 1, r, divisor);
      mod_merge(A, p, q, r, divisor);
  }
}
