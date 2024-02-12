#include <iostream>
#include "time.h"
 
using namespace std;

Time::Time()
{
	days = hours = minutes = seconds = 0;
}

Time::Time(int s)
{
	*this = Time(0, 0, 0, s);
}

Time::Time(int d, int h, int m, int s)
{
	if (d < 0 || h < 0 || m < 0 || s < 0)
		*this = Time();
	else
	{
		Conversion(d, h, m, s);
		days = d;
		hours = h;
		minutes = m;
		seconds = s;
	}
} 

void Time::Conversion(int& d, int& h, int& m, int& s)
{
	do
	{
		if((s % 60) >= 60 || (s / 60) >= 1)
		{
			s = s - 60;
			m++;
		}
	}while((s % 60) >= 60 || (s / 60) >= 1);
	do
	{
		if((m % 60) >= 60 || (m / 60) >= 1)
		{
			m = m - 60;
			h++;
		}
	}while((m % 60) >= 60 || (m / 60) >= 1);
	do
	{
		if((h % 24) >= 24 || (h / 24) >= 1)
		{
			h = h - 24;
			d++;
		}
	}while((h % 24) >= 24 || (h / 24) >= 1);
}

void Time::Borrow()
{
	if(seconds < 0 && minutes > 0)
	{
		seconds = seconds + 60;
		minutes--;
	}
	else if(seconds < 0 && hours > 0)
	{
		seconds = seconds + 60;
		minutes = minutes + 59;
		hours--;
	}
	else if(seconds< 0 && days > 0) 
	{
		seconds = seconds + 60;
		minutes = minutes + 59;
		hours = hours + 23;
		days--;
	}
	
	if(minutes < 0 && hours > 0)
	{
		minutes = minutes + 60;
		hours--;
	}
	else if(minutes < 0 && days > 0)
	{
		minutes = minutes + 60;
		hours = hours + 23;
		days--;
	}
	
	if(hours < 0 && days > 0)
	{
	hours = hours + 24;
	days--;
	}
	
	if(seconds < 0 || minutes < 0 || hours < 0 || days < 0)
		*this = Time();
}	

bool operator<(const Time& t1, const Time& t2)
{
	if(t1.days < t2.days) return true;
	else if(t1.days > t2.days) return false;
	else
	{
		if(t1.hours < t2.hours) return true;
		else if(t1.hours > t2.hours) return false;
		else
		{
			if(t1.minutes < t2.minutes) return true;
			else if(t1.minutes > t2.minutes) return false;
			else
			{
				if(t1.seconds < t2.seconds) return true;
				else return false;
			}
		}
	}
} 

bool operator>(const Time& t1, const Time& t2)
{
	return t2 < t1;
}

bool operator!=(const Time& t1, const Time& t2)
{
	return t1 < t2 || t2 < t1;
}

bool operator==(const Time& t1, const Time& t2)
{
	return !(t1 != t2);
}

bool operator>=(const Time& t1, const Time& t2)
{
	return t1 > t2 || t1 == t2;
}

bool operator<=(const Time& t1, const Time& t2)
{
	return t1 < t2 || t1 == t2;
}
		
Time operator+(const Time& t1, const Time& t2)
{
	return  Time(t1.days + t2.days, t1.hours + t2.hours, 
                     t1.minutes + t2.minutes, t1.seconds + t2.seconds);
}

Time operator-(const Time& t1, const Time& t2)
{
	Time temp;
	if(t1 <= t2) return Time();
	
	temp.seconds = t1.seconds - t2.seconds;
	temp.minutes = t1.minutes - t2.minutes;
	temp.hours = t1.hours - t2.hours;
	temp.days = t1.days - t2.days;

	temp.Borrow();
	return temp;
}	

Time operator*(const Time& t1, int multi)
{
	return  Time(t1.days * multi, t1.hours * multi, t1.minutes * multi, t1.seconds * multi);
}
ostream& operator<<(ostream& os, const Time& t1)
{
	os << t1.days << "~";
	if(t1.hours < 10)
		os << "0" << t1.hours << ":";
	else
		os << t1.hours << ":";
	if (t1.minutes < 10)
		 os << "0" << t1.minutes << ":";
	else
		os << t1.minutes << ":";
	if(t1.seconds < 10)
		os << "0" << t1.seconds;
	else 
		os << t1.seconds;
	
	return os;
}

istream& operator>>(istream& is, Time& t1)
{
	char ch;
	int tempDays, tempHours, tempMinutes, tempSeconds;
	is >>  tempDays >> ch >> tempHours >> ch >> tempMinutes >> ch >> tempSeconds;
	t1 = Time(tempDays, tempHours, tempMinutes, tempSeconds);
	return is;
}


Time& Time:: operator++()
{
	seconds++;
	*this = Time(days, hours, minutes, seconds);
	return *this;
}

Time Time::operator++(int x)
{
	Time temp = *this;
	*this = Time(days, hours, minutes, seconds + 1);
	return temp;
}

Time& Time::operator--()
{
	Time temp;
	seconds--;
	temp = *this;
	temp.Borrow();
	*this = temp; 
	return *this;
}

Time Time::operator--(int x)
{
	Time temp = *this;
	Time temp2;
	seconds--;
	temp2 = *this;
	temp2.Borrow();
	*this = temp2;
	return temp;
}
