/* Name: Marlan McInnes-Taylor 
Date: 11/11/2016 
Section: 20 
Assignment: 6 
Due Date: 11/11/2016 
About this project: This is a short c-string manipulation program. It allows the user to input a c-string, convert the string to
					all upper or lower case, count the number of vowels and consonants, and character type totals for the array.
Assumptions: Assumes correct user input, assumes the inputted string does not exceed 100 characters

All work below was performed by Marlan McInnes-Taylor */

#include <iostream>
#include <cctype>
#include <cstring>

using namespace std;

//Function prototypes
int Vowels(const char arr[]);
int Consonants(const char arr[]);
void CaseCount(const char arr[]);
void MakeLower(char arr[]);
void MakeUpper(char arr[]);
void MainMenu();
void FillArray(char arr[], const int size, bool refill = false);

int main()
{
  char menuSelection = '\0';
  const int SIZE = 100;
  char charArray[SIZE];

  //User is prompted to fill the array as soon as the program runs
  FillArray(charArray, SIZE);
  do
  {
   //Full menu which is displayed on the first run, or when the user selects 'M'
   if(menuSelection == '\0' || menuSelection == 'M' || menuSelection == 'm')
   {
     MainMenu();
     cin >> menuSelection;
   }
   //Short menu entry prompt which appears as a default after the first run
   else
   {
     cout << endl << "Enter your menu selection: ";
     cin >> menuSelection;
   }
   //Process the user's menu selection, the default case assumes an invalid entry has been made
   switch(menuSelection)
   {
     //Count the number of vowels
	 case 'A':
     case 'a':
     {
       cout << "Number of vowels: " << Vowels(charArray) << endl;
       break;
     }
     //Count the number of consonants
	 case 'B':
     case 'b':
     {
       cout << "Number of consonants: " << Consonants(charArray) << endl;
       break;
     }
     //Convert all alphabetic characters to upper case
	 case 'C':
     case 'c':
     {
       MakeUpper(charArray);
       break;
     }
     //Convert all alphabetic characters to lower case
	 case 'D':
     case 'd':
     {
       MakeLower(charArray);
       break;
     }
     //Display the C-string
	 case 'E':
     case 'e':
     {
       cout << "The string: " << endl << charArray << endl;
       break;
     }
     //Refill the array
	 case 'F':
     case 'f':
     {
		 cin.ignore();       
		 FillArray(charArray, SIZE, true);
       break;
     }
	 //Get array character details
	 case 'H':
	 case 'h':
	 {
		 CaseCount(charArray);
		 break;
	 }
	 //Display the Main Menu	
     case 'M':
     case 'm':
     {
         cout << endl;
		 continue;
     }
	 //Quit program
	 case 'X':
	 case 'x':
		 continue;
	 default:
		 cout << "Please enter a valid menu selection." << endl;

   }
  }while(menuSelection != 'x' && menuSelection != 'X');

  cout << "Goodbye" << endl;

  return 0;
}

//Count and display the total number of vowels in the C-string
int Vowels(const char arr[])
{
  int totalVowels = 0;

//Runs through array and counts number of vowel characters 
  for(int i = 0; i < strlen(arr); i++)
  {
    if(arr[i] == 'A'|| arr[i] == 'a' || arr[i] == 'E' || arr[i] == 'e'
       || arr[i] == 'I' || arr[i] == 'i' || arr[i] == 'O' || arr[i] == 'o'
       || arr[i] == 'U' || arr[i] == 'u')
       {
         totalVowels++;
       }
  }
  return totalVowels;
}
//Count and display the total number of consonants in the C-string
int Consonants(const char arr[])
{
 //Runs through array and total number of alphabetic characters 
  int totalLetters = 0, totalConsonants;
  for(int i = 0; i < strlen(arr); i++)
  {
	  if(isalpha(arr[i]))
		totalLetters++;
  }
//Calculates the number of consonants by finding the difference of the total number of alphabetic characters and the total number 
//of vowels
  totalConsonants = totalLetters - Vowels(arr);
  return totalConsonants;
}
//Counts and displays different typres of characters in the array
void CaseCount(const char arr[])
{
	int caseLower = 0, caseUpper = 0, digit = 0, punct = 0, wspace = 0;
	//Check array for different types of chacacters and keep a count of each type
	for(int i = 0; i < strlen(arr); i++)
	{
		if(isupper(arr[i]))
			caseUpper++;
		else if(islower(arr[i]))
			caseLower++;
		else if(isdigit(arr[i]))
			digit++;
		else if(ispunct(arr[i]))
			punct++;
		else if(isspace(arr[i]))
			wspace++;

	}
	//Display character type counts
	if(caseUpper == 1)
		cout << "There is " << caseUpper << " capital letter in the C-string." << endl;
	else if(caseUpper > 1)
		cout << "There are " << caseUpper << " capital letters in the C-string." << endl;
	else
		cout << "There are no capital letters in the C-string." << endl;
	
	if(caseLower == 1)
		cout << "There is " << caseLower << " lower case letter in the C-string." << endl;
	else if(caseLower > 1)
		cout << "There are " << caseLower << " lower case letters in the C-string." << endl;
	else
		cout << "There are no lower case letters in the C-string." << endl;

	if(digit == 1)
		cout << "There is " << digit << " decimal digit in the C-string." << endl;
	else if(digit > 1)
		cout << "There are " << digit << " decimal digits in the C-string." << endl;
	else
		cout << "There are no decimal digits in the C-string." << endl;

	if(punct == 1)
		cout << "There is " << punct << " punctuation character in the C-string." << endl;
	else if(punct > 1)
		cout << "There are " << punct << " punctuation characters in the C-string." << endl;
	else
		cout << "There are no punctuation characters in the C-string." << endl;

	if(wspace == 1)
		cout << "There is " << wspace << " white space character in the C-string." << endl;
	else if(wspace > 1)
		cout << "There are " << wspace << " white space characters in the C-string." << endl;
	else
		cout << "There are no white space characters in the C-string." << endl;
}
//Converts all characters to lower case
void MakeLower(char arr[])
{
  for(int i = 0; i < strlen(arr); i++)
    arr[i] = tolower(arr[i]);
}
//Converts all characters to upper case
void MakeUpper(char arr[])
{
  for(int i = 0; i < strlen(arr); i++)
    arr[i] = toupper(arr[i]);
}
//Displays the Main Menu
void MainMenu()
{
  cout << "A) Count the number of vowels in the string" << endl;
  cout << "B) Count the number of consonants in the string" << endl;
  cout << "C) Convert the string to uppercase" << endl;
  cout << "D) Convert the string to lowercase" << endl;
  cout << "E) Display the current string" << endl;
  cout << "F) Enter another string" << endl << endl;
  cout << "H) Display the chacarter type totals." << endl << endl;
  cout << "M) Display this menu" << endl;
  cout << "X) Exit the program" << endl << endl;
  cout << "Enter your menu selection: ";
}
//Fills the array with a C-string
void FillArray(char arr[], const int size, bool refill)
{
  //If the the array is being refilled the following displays
  if(refill)
  {
    cout << "Input a new line of text, up to 100 characters:" << endl << "> ";
    cin.getline(arr,size);
  }
 //If the array is being filled for the first time, the following displays 
  else
  {
    cout << "Input a line of text, up to 100 characters:" << endl << "> ";
    cin.getline(arr, size);
	cout << endl;
  }
}
