#include "bitarray.h"

using namespace std;

void Sieve(BitArray& a){
	int n;
	for(int i = 0; i < a.Length(); i++)
		a.Set(i);

	a.Unset(0);
	a.Unset(1);

	for(int i = 2; i < sqrt(a.Length()); i++){
		if(a.Query(i)){
			n = 0;
			for(int j = pow(i, 2); j < a.Length(); j = (pow(i, 2) + n * i)){
				a.Unset(j);
				n++;
			}
		}
	}
}		
