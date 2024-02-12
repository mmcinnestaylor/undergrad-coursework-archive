#include <iostream>
#include <iomanip>
#include <string>
#include "date.h"

using namespace std;

Date::Date(int m, int d, int y)
{
	if(Set(m, d, y));
	else(Set(1, 1, 2000));
	format = 'D';
} 

bool Date::Leap() const
{
	if((year % 100 == 0 && year % 400 == 0) || (year % 100 > 0 && year % 400 > 0  && year % 4 == 0))
		return true;
	else 
		return false;
}

int Date::Julian() const
{
	int totalDays = 0;
	if(Leap())
	{
		int leapDays[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
		for(int i = 0; i < month - 1; i++)
			totalDays = totalDays + leapDays[i];
	}
	else
	{
		int stdDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
		for(int i = 0; i < month - 1; i++)
			totalDays = totalDays + stdDays[i];
	}
	totalDays = totalDays + day;
	
	return totalDays;
} 	
	 	
void Date::Input()
{
	int m, d, y;
	char toss;
	
	cout << "Please enter a date." << endl;
	do
	{
		cin >> m >>toss >> d >> toss >> y;
		if(!Set(m, d, y))
		{
			cout << "Invalid date. Please enter a valid date MM/DD/YYYY." << endl;
		}
	}while(!Set(m, d, y));
	
}

void Date::Show() const
{
	string monthNames[] = {"Jan", "Feb", "Mar", "Apr", "May", "June", "July", 
                               "Aug", "Sept", "Oct", "Nov", "Dec"}; 
	switch(format)
	{
		case 'd':
		case 'D':
		{
			cout << month << '/' << day << '/' << year;
			break;
		}
		case 't':
		case 'T':
		{
			char oldfill = cout.fill();
			int oldwidth = cout.width();
			ios_base::fmtflags oldflags = cout.flags();
			cout.fill('0');
			cout.setf(ios::right);
			cout <<  setw(2) << month << '/' << setw(2) << day << '/' << (year % 100);
			cout.fill(oldfill);
			cout.width(oldwidth); 
			cout.flags(oldflags);
			break;
		}
		case 'l':
		case 'L':
		{
			cout << monthNames[month - 1] << " " << day << ", " << year;
			break;
		}
		case 'j':
		case 'J':
		{
			cout << (year % 100) << "-" << Julian();

			break;
		}
	}	 
}
		
	 
bool Date::Set(int m, int d, int y)
{
	switch(m)
	{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
		{
			if((d >=1 && d <= 31) && y >= 0)
			{
				month = m;
				day = d;
				year = y;
				return true;
			}
			else
				return false;
		}
		case 4:
		case 6:
		case 9:
		case 11:
		{
			if((d >= 1 && d <= 30) && y >= 0)
			{
				month = m;
				day = d;
				year = y;
				return true;
			}
			else 
				return false;
		case 2:
		{
			if(Leap())
			{
				if((d >= 1 && d <= 29) && y >= 0)
				{
					month = m;
					day = d;
					year = y;
					return true;
				}
				else
					return false;
			}
			else
			{
				if((d>= 1 && d <= 28) && y >= 0)
				{
					month = m;
					day = d;
					year = y;
					return true;
				}
				else
					return false;
			}
		}
		default: 
			return false;
		}
	}
}

int Date::GetMonth() const
{
	return month;
}

int Date::GetDay() const
{
	return day;
}

int Date::GetYear() const
{
	return year;
}

bool Date::SetFormat(char f)
{
	switch(f)
	{
		case 'd':
		case 'D':
		{
			format = f;
			return true;
		}
		case 't':
		case 'T':
		{
			format = f;
			return true;
		}
		case 'l':
		case 'L':
		{
			format = f;
			return true;
		}
		case 'j':
		case 'J':
		{
			format = f;
			return true;
		}
		default:
			return false;
	}
}

void Date::Increment(int numDays)
{
	int leapDays[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int stdDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	
	for(int i = numDays; i > 0; i--)
	{
		if(Leap())
		{
			if((day + 1) <= leapDays[month - 1])
				day ++;
			else
			{
				if((month + 1) <= 12)
				{
					month ++;
					day = 1;
				}
				else
				{
					year ++;
					month = 1;
					day = 1;
				}
			}
		}
		else
		{
			
			if((day + 1) <= stdDays[month - 1])
				day ++;
			else
			{
				if((month + 1) <= 12)
				{
					month ++;
					day = 1;
				}
				else
				{
					year ++;
					month = 1;
					day = 1;
				}
			}
		}
	}
}

int Date::Compare(const Date& d) const
{
	int yearDiff = year - d.year;
	int dayDiff = Julian() - d.Julian();
	
	if(yearDiff < 0)
		return -1;
	else if(yearDiff > 0)
		return 1;
	else
 	{
		if(dayDiff < 0)
			return -1;
		else if(dayDiff > 0)
			return 1;
		else
			return 0;
	}
}
	
