/* Name: Marlan McInnes-Taylor
Date: 12-1-2016
Section: 20
Assignment: 7
Due Date: 12-7-2016
About this project: This program is a simple NFL team stats tool. It allows the
                    user to select and process an input file. Once processed,
                    the user can print the stats from the input file to the screen,
                    search through the inputted stats, view W/L differentials,
                    and sort the teams by their differential.
Assumptions: Correct user input; no spaces in the filename; correct input file
             formatting; and that the number of inputted teams does not exceed
             the largest number stored in a signed int; team name does not
             exceed 49 characters; input filename does not exceed 29 characters

All work below was performed by Marlan McInnes-Taylor */

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

//Create the teamInfo struct, which will be used to store team data
struct teamInfo
{
  char teamName[50];
  int wins, losses;
  bool playoffs;
  int recordDifferential;
};

/***Function prototypes***/
//Displays the main menu
void MainMenu();
/*Prompts the user to enter an input file name, reads the file, and stores
value in an array*/
teamInfo * FillArray(int &size);
//Prints each team's W/L record
void PrintRecords(const teamInfo arr[], const int size);
//Displays teams with at least a user inputted number of wins
void SearchRecords(const teamInfo arr[], const int size, const int searchVal);
//Displays teams who made the playoffs
void PlayoffTeams(const teamInfo arr[], const int size);
//Print each team's W/L differential
void PrintDiffrentials(const teamInfo arr[], const int size);
//Sorts and displays Teams by their W/L differential from best to worst
void SortTeams(teamInfo arr[], const int size);

int main()
{
  int menuSelection, searchVal, SIZE = 0;
  //Pointer to the array of structs received from FillArray function
  teamInfo * statsArray = FillArray(SIZE);
  /*Displays main menu and enters a loop which will run until the quit value is
  entere*/
  do
  {
    MainMenu();
    cin >> menuSelection;
	  cout << endl;

    switch(menuSelection)
    {
      case 1:
      {
        PrintRecords(statsArray, SIZE);
        break;
      }
      case 2:
      {
        cout << "Show teams with at least how many wins? --> ";
        cin >> searchVal;
        SearchRecords(statsArray, SIZE, searchVal);
        break;
      }
      case 3:
      {
        PlayoffTeams(statsArray, SIZE);
        break;
      }
      case 4:
      {
        PrintDiffrentials(statsArray, SIZE);
        break;
      }
      case 5:
      {
        SortTeams(statsArray, SIZE);
        break;
      }
      case 0:
        break;
      default:
        cout << "Invalid Choice." << endl << endl;
    }
  }while(menuSelection);
  //Deletes dynamic array
  delete [] statsArray;
  cout << "Goodbye!" << endl;

  return 0;
}
//Function displays the Main menu
void MainMenu()
{
  cout << "Select one of the following choices:" << endl;
  cout << "\t1 - View team Win/Loss records" << endl;
  cout << "\t2 - Show teams with at least x wins" << endl;
  cout << "\t3 - List teams that made the playoffs" << endl;
  cout << "\t4 - Print teams and their Win Loss Differentials" << endl;
  cout << "\t5 - Sort teams by their Win Loss Differentials" << endl;
  cout << "\t0 - Exit program" << endl;
  cout << "------------------------------------------" << endl;
  cout << "Choice : ";
}
//Function to read the file into a dynamically created array of structs
teamInfo * FillArray(int &size)
{
  char filename[50];
  ifstream readFile;
  /*Prompts user to enter a file name, if the name is invalid, the user is asked
  to input a different name until valid input is provided.*/
  do
  {
    cout << "Please enter the name of the input file." << endl;
    cout << "Filename: ";
    cin >> filename;

    readFile.open(filename);

    if(!readFile)
      cout << "That is not a valid file. Try again!" << endl;

  }while(!readFile);
  //Reads in the size of the array to be created
  readFile >> size;
  //Array of structs created based on the size read in from the file
  teamInfo * arr = new teamInfo[size];
  /*Array of structs is filled using file contents, and W/L differentials are
  calculated*/
  for(int i = 0; i < size; i++)
  {
    readFile.ignore();
    readFile.getline(arr[i].teamName, 50, ',');
    readFile >> arr[i].wins;
    readFile.ignore();
    readFile >> arr[i].losses;
    readFile.ignore();
    readFile >> arr[i].playoffs;
    arr[i].recordDifferential = arr[i].wins - arr[i].losses;
  }
  //Input file is closed
  readFile.close();
  //Pointer to struct array is returned
  return arr;
}
//Function to print the W/L record of all teams in the array
void PrintRecords(const teamInfo arr[], const int size)
{
  cout << "Team W-L:" << endl;

  for(int i = 0; i < size; i++)
  {
    cout << arr[i].teamName << " " << arr[i].wins << "-" << arr[i].losses << endl;
  }
  cout << endl;
}
//Function to display teams with at least a user defined number of wins
void SearchRecords(const teamInfo arr[], const int size, const int searchVal)
{
  for(int i = 0; i < size; i++)
  {
    /*If a struct's win value is greater than or equal to the user input, the
    team name is outputted*/
    if(arr[i].wins >= searchVal)
      cout << arr[i].teamName << endl;
  }
  cout << endl;
}
//Displays the teams which made the playoffs
void PlayoffTeams(const teamInfo arr[], const int size)
{
  //Bool test to help with formatting the list output
  bool firstHit = true;
  cout << "Playoff teams:" << endl;

  for(int i = 0; i < size; i++)
  {
    //If the output is the first in the list it is displayed without a comma
    if(arr[i].playoffs && firstHit)
    {
      cout << arr[i].teamName;
      firstHit = false;
    }
    //If the output is not first in the list, it is displayed with a comma
    else if(arr[i].playoffs)
      cout << ", " << arr[i].teamName;
  }
  cout << endl << endl;
}
//Function prints team names and their W/L differentials
void PrintDiffrentials(const teamInfo arr[], const int size)
{
  //Positive numbers will display a + in front of the value
  cout << showpos;
  for(int i = 0; i < size; i++)
    cout << arr[i].teamName << " " << arr[i].recordDifferential << endl;

  cout << noshowpos << endl;
}
//Function sorts and prints teams by their W/L diffrential, from best to worst
void SortTeams(teamInfo arr[], const int size)
{
  int swapCount;
  //struct to temp store a struct while the array is being reorganized
  teamInfo swapStore;
  do
  {
    swapCount = 0;
    for(int i = 0; i < size; i++)
    {
      if(arr[i].recordDifferential < arr[i + 1].recordDifferential)
      {
        swapStore = arr[i];
        arr[i] = arr[i + 1];
        arr[i + 1] = swapStore;
        swapCount++;
      }
    }
  } while(swapCount);
  cout << "The teams sorted by W/L differential:" << endl;
  PrintDiffrentials(arr, size);
}
