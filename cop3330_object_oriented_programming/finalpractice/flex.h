#include <iostream>
#include <cstring>
using namespace std;


class Flex
{
	friend ostream& operator <<(ostream&, const Flex&);
public:	
	Flex();
	Flex(char*);
	~Flex();
	void cat(Flex&);
private:
	char* arr;
	int max;
	int current;
};

Flex::Flex(){
	int max = 5;
	arr = new char[max];
	strcpy(arr, " ");
}
Flex::Flex(char* a){
	max = strlen(a);
	arr = new char[max];
	strcpy(arr, a);
}
Flex::~Flex(){
	delete [] arr;
}
void Flex::cat(Flex& a){
	max = max + a.max; 
	char* temp = arr;
	arr = new char[max];
	strcpy(arr, temp);
	strcat(arr, a.arr);
	delete [] temp;
}
ostream& operator <<(ostream& os, const Flex& a){
	os << '*' << a.arr << '*';
	return os;
}	
