#include "bitarray.h"
using namespace std;

ostream& operator<<(ostream& os, const BitArray& a){
	os << '(';
	for(int i = 0; i < a.Length(); i++)
		os << a.Query(i);
	os << ')';
	return os;
}
bool operator==(const BitArray& a, const BitArray& b){
	if(a.arraySize != b.arraySize)
		return false;
	else{
		for(int i = 0; i < a.Length(); i++)
				if(a.Query(i) != b.Query(i))
					return false;
		return true;
	}	
}
bool operator!=(const BitArray& a, const BitArray& b){
	return !(a == b);
}
BitArray::BitArray(unsigned int n){
	arraySize = ceil((n*1.0)/typeSize);
	barray = new unsigned char[arraySize];
	for(int i = 0; i < arraySize; i++)
		barray[i] = 0;
}
BitArray::BitArray(const BitArray& a){
	arraySize = a.arraySize;
	barray = new unsigned char[arraySize];
	for(int i = 0; i < arraySize; i++)
		barray[i] = a.barray[i];
}
BitArray::~BitArray(){
	delete [] barray;
}
BitArray& BitArray::operator=(const BitArray& a){
	if(this != &a){
		delete [] barray;
		arraySize = a.arraySize;
		barray = new unsigned char[arraySize];
		for(int i = 0; i < arraySize; i++)
			barray[i] = a.barray[i];
		return *this;
	}
	else
		return *this;
}
unsigned int BitArray::Length() const{
	return arraySize * typeSize;
}
void BitArray::Set(unsigned int index){
	barray[index/typeSize] = barray[index/typeSize] | (1 << (index % typeSize));
}
void BitArray::Unset(unsigned int index){
	barray[index/typeSize] = barray[index/typeSize] & ~(1 << (index % typeSize));
}
void BitArray::Flip(unsigned int index){
	barray[index/typeSize] = barray[index/typeSize] ^ (1 << (index % typeSize));
}
bool BitArray::Query(unsigned int index) const{
	if(barray[index/typeSize] & (1 << (index % typeSize)))
		return 1;
	else 
		return 0;
}
