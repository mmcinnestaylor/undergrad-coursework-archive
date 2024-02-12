#include <iostream>
#include <iomanip>
#include <cmath>
#include "house.h"

using namespace std;

House::House(int size, char border, char fill)
{
	if(size < 3)
		baseSize = 3;
	else if(size > 37)
		baseSize = 37;
	else 
		baseSize = size;
	SetBorder(border);
	SetFill(fill);
}

int House::GetSize()
{
	return baseSize;
}

int House::Perimeter()
{
	return (baseSize * 3) + (((baseSize + 2) * 2) + 2);
}

double House::Area()
{
	int squareArea = 0;
	double triangleHeight = 0, triangleArea = 0;
	
	squareArea = baseSize * baseSize;
	triangleHeight = sqrt((pow((baseSize + 2), 2) - pow((.5 * baseSize + 1), 2)));  
	triangleArea = .5 * ((baseSize + 2) * triangleHeight);
	
	return squareArea + triangleArea;
}

void House::Grow()
{
	if(baseSize < 37)
		baseSize = baseSize + 1;
}

void House::Shrink()
{
	if(baseSize > 3)
		baseSize = baseSize - 1;
}

void House::SetBorder(char border)
{
	if(border >= 33 && border <= 126)
		houseBorder = border;
	else
		houseBorder = 'X';
}

void House::SetFill(char fill)
{
	if(fill >= 33 && fill <= 126)
		houseFill = fill;
	else
		houseFill = '*';
}
			
void House::Draw()
{
	for(int i = 1; i <= baseSize + 2; i++)
	{
		for(int j = (baseSize + 2) - i; j > 0; j--)
		{
			cout << " ";
		}
		for(int k = 0; k < (1+ (2 * (i - 1))); k++)
		{
			if(i != baseSize + 2)
			{
				if(k == 0 || k == (1 + (2 * (i -  1))) - 1)
					cout << houseBorder;
				else if(k % 2 == 1)
					cout << " ";
				else
					cout << houseFill;
			}
			else
			{
				if(k == 0 || k == 2 || k == (1 + (2 * (i - 1))) - 3 || k == (1  + (2 * (i - 1))) - 1)
					cout << houseBorder;
				else if (k % 2 == 1)
					cout << " ";
				else
					cout << houseFill;
			} 
		}
		cout << endl;
	} 
	for(int i = 1; i < baseSize; i++)
	{
		cout << "  ";
		for(int j = 0; j < (baseSize * 2) -1; j++)
		{
			if(i != baseSize - 1)
			{
				if(j == 0 || j == (baseSize * 2) -2)
					cout << houseBorder;
				else if(j % 2 == 1)
					cout << " ";
				else
					cout << houseFill;
			}
			else
			{
				if(j % 2 == 0)
					cout << houseBorder;
				else
					cout << " ";
			}
		}
		cout << endl;
	}
}

void House::Summary()
{
	int oldprecision = cout.precision();
	ios_base::fmtflags oldflags = cout.flags();

	cout << "House width and height base to roof = " << baseSize << " units." << endl;
	cout << "Perimeter of house = " << Perimeter() << " units." << endl;
	cout << "Area of the house = " << fixed << showpoint << setprecision(2) << Area() << " units." << endl;
	cout << "House looks like: " << endl;
	Draw();

	cout.precision(oldprecision);
	cout.flags(oldflags);
}

