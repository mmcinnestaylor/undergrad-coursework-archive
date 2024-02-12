#include <cstring>
#include "mystring.h"

using namespace std;

ostream& operator<< (ostream& os, const MyString& a){
	os << a.str;
	return os;
}
istream& operator>> (istream& is, MyString& a){
	while(is.peek() == ' ')
		is.ignore();
	delete [] a.str;
	a.cSize = 0;
	a.str = new char[a.mSize];

	while(is){
		if(a.cSize == a.mSize)
			a.Grow();
		if(is.peek() == ' '){
			a.str[a.cSize] = '\0';
			a.cSize++; 
			return is;
		}
		else{
			a.str[a.cSize] = is.get();
			a.cSize++;
		}
	}	
	return is;
}
istream& getline (istream& is, MyString& a, char delim){
	delete [] a.str;
	a.cSize = 0;
	a.str = new char[a.mSize];
	if(is.peek() == '\n')
		is.ignore();
	while(is){
		if(a.cSize == a.mSize)
			a.Grow();
		if(is.peek() == delim){
			is.ignore();
			a.str[a.cSize] = '\0';
			a.cSize++; 
			return is;
		}
		else{
			a.str[a.cSize] = is.get();
			a.cSize++;
		}
	}	
	
}

MyString operator+ (const MyString& a, const MyString& b){
	MyString temp;
	temp.Grow(a.cSize + b.cSize);
	strcpy(temp.str, a.str);
	strcat(temp.str, b.str);
	temp.cSize = strlen(temp.str);
	return temp; 
}
MyString operator- (const MyString& a, const MyString& b){
	char* temp = strstr(a.str, b.str);
	if(temp == 0)
		return a;
	else{
		int offset = strlen(b.str);
		MyString tempobj(a);
		while(temp != 0){
			int i= 0;
			do{
				tempobj.str[(temp - tempobj.str) + i] = 
					tempobj.str[(temp - tempobj.str) + 
						offset +i];
				i++; 
			}while(tempobj.str[(temp - tempobj.str) + 
				offset + i] != '\0');
			tempobj.str[(temp-tempobj.str) + i] = '\0';
			temp = strstr(tempobj.str, b.str);
		}
		tempobj.cSize = strlen(tempobj.str);
		return tempobj;
	}
		
}
void MyString::Grow(int size){
	char* temp = new char[mSize];
	strcpy(temp, str);
	delete [] str;
	
	if(size == 0) 
		mSize += 5;
	else
		mSize += size;
 
	str = new char[mSize];
	strcpy(str, temp);
	delete [] temp;	
}
bool operator< (const MyString& a, const MyString& b){
	if(strcmp(a.str, b.str) < 0) 
		return true;
	else 
		return false;
}
bool operator> (const MyString& a, const MyString& b){
	return b < a;
}
bool operator<=(const MyString& a, const MyString& b){
	return (a < b || a == b);
}
bool operator>=(const MyString& a, const MyString& b){
	return (a > b || a == b);
}
bool operator==(const MyString& a, const MyString& b){
return !(a != b);
}
bool operator!=(const MyString& a, const MyString& b){
	return (a < b || b < a);
}

//public:
MyString::MyString(){
	mSize = 5;
	cSize = 1;
	str = new char[mSize];
	str[0] = '\0';
}				// empty string
MyString::MyString(const char* a){
	mSize = 5;
	cSize = 1;
	str = new char[mSize];
	str[0] = '\0';
	if(strlen(a) > mSize)
		Grow(strlen(a) + 5);
	strcpy(str, a);
	cSize = strlen(str);
	
}		// conversion from c-string
MyString::MyString(int a){
	mSize = 5;
	cSize = 0;
	str = new char[mSize];
	char* temp;
	do{
		if(cSize <  mSize){
			switch(a % 10){
				case 0:{str[cSize] = 48; break;}
				case 1:{str[cSize] = 49; break;}
				case 2:{str[cSize] = 50; break;}
				case 3:{str[cSize] = 51; break;}
				case 4:{str[cSize] = 52; break;}
				case 5:{str[cSize] = 53; break;}
				case 6:{str[cSize] = 54; break;}
				case 7:{str[cSize] = 55; break;}
				case 8:{str[cSize] = 56; break;}
				case 9:{str[cSize] = 57; break;}
			}
			a = a / 10;
			cSize++;
			if((a / 10) == 0 && (a % 10) == 0){
				str[cSize] = '\0';
				cSize++;
			}
		}
		else
			Grow();
	}while(a != 0);

	temp = new char[mSize];
	strcpy(temp, str);
	for(int i = 0; i < strlen(temp); i++)
		str[i] = temp[strlen(temp) - (i + 1)];

	delete [] temp; 
	
}			// conversion from int
MyString::~MyString(){
	delete [] str;
}				// destructor
MyString::MyString(const MyString& a){
	mSize = a.mSize;
	cSize = a.cSize;
	str = new char[mSize];
	strcpy(str, a.str);
}		// copy constructor
MyString& MyString::operator=(const MyString& a){
	delete [] str;
	mSize = a.mSize;
	cSize = a.cSize;
	str = new char[mSize];
	strcpy(str, a.str);
	return *this;
}   // assignment operator

MyString& MyString::operator+=(const MyString& a){
	*this = *this + a;
	return *this;	
}  // concatenation/assignment

// bracket operators to access char positions
char& MyString::operator[] (unsigned int index){
	if(index <=  cSize){
		return str[index];
	}
	else{
		if(index >= mSize)
			Grow(index - mSize);
		for(int i = cSize; i<= index + 1; i++){
			if(i != index + 1)
				str[i] = ' ';
			else
				str[i] = '\0';
		}
		cSize = strlen(str);
		return str[index];
	}
}
const char& MyString::operator[] (unsigned int index) const{
	if(index < mSize)
		return str[index];
	else 
		return str[mSize - 1];
}

// insert s into the string at position "index"
MyString& MyString::insert(unsigned int index, const MyString& s){
	if(s.cSize > (mSize-cSize)) 
		Grow(s.cSize);
	if(index >= cSize){
		strcat(str, s.str);
		cSize = strlen(str);
		return *this;
	}
	else{
		for(int i = cSize; i >= index; i--)
			str[i + s.cSize] = str[i];
		for(int i = 0; i < s.cSize; i++)
			str[index + i] = s.str[i];
		cSize = strlen(str);
		return *this;
	}
}

// find index of the first occurrence of s inside the string
//  return the index, or -1 if not found
int MyString::indexOf(const MyString& s) const{
	char* temp = strstr(str, s.str);
	if(temp == 0)
		return -1;
	else 
		return temp - str;		
}
  
int MyString::getLength() const{
	return cSize;
}		// return string length
const char* MyString::getCString() const{
	return str;
}	// return c-string equiv

MyString MyString::substring(unsigned int start, unsigned int length) const{
	char* temp = new char[length];
	if((start + length) > cSize){
		for(int i = start; i <= cSize; i++)
			temp[i - start] = str[i];
	}
	else{
		for(int i = 0; i <= length; i++){
			if(i != length)
				temp[i] = str[i + start];
			else
				temp[i] = '\0';
		}
	}
	MyString tempobj(temp);
	delete [] temp;
	return tempobj;
	}
MyString MyString::substring(unsigned int start) const{
	char* temp = new char[cSize];
	for(int i = start; i <= cSize; i++)
			temp[i - start] = str[i];

	MyString tempobj(temp);
	delete [] temp;
	return tempobj;
}
