#include <iostream>
using namespace std;

class Time
{
friend Time operator+(const Time&, const Time&);
friend Time operator-(const Time&, const Time&);
friend Time operator*(const Time&, int);
friend ostream& operator<<(ostream& os, const Time&);
friend istream& operator>>(istream& is, Time&); 
friend bool operator<(const Time&, const Time&);
friend bool operator>(const Time&, const Time&);
friend bool operator>=(const Time&, const Time&);
friend bool operator<=(const Time&, const Time&);
friend bool operator==(const Time&, const Time&);
friend bool operator!=(const Time&, const Time&);


public:
	Time();
	Time(int s);
	Time(int d, int h, int m, int s);
	Time& operator++(); 
	Time operator++(int); 
	Time& operator--();
	Time operator--(int);
	
private:
	void Conversion(int&, int&, int&, int&);
	void Borrow();
	int days, hours, minutes, seconds;
};
