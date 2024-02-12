#include "passserver.h"
#include <iostream>

using namespace std;

void Menu();

int main(){

  int capacity;
  char selection = '\0';
  string filename, username, password, newpassword;

  cout << "Enter preferred hash table capacity: ";
  cin >> capacity;
  PassServer theServer(capacity);

  while(!cin.eof() && selection != 'x' && selection != 'X'){
    Menu();
    cin >> selection;
    switch(selection){
      case 'L':
      case 'l':{
        cout << "Enter password file name to load from: ";
        cin >> filename;
        theServer.load(filename.c_str());
        break;
      }
      case 'A':
      case 'a':{
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        if(theServer.addUser(std::make_pair(username, password))){
          cout << "\nUser " << username << " added.";
          break;
        }
        else{
          cout << "\nUser " << username << " could not be added.";
          break;
        }
      }
      case 'R':
      case 'r':{
        cout << "Enter username: ";
        cin >> username;
        if(theServer.removeUser(username)){
          cout << "\nUser " << username << " deleted.";
          break;
        }
        else{
          cout << "\n*****Error: User not found.  Could not delete user";
          break;
        }
      }
      case 'C':
      case 'c':{
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        cout << "Enter new password: ";
        cin >> newpassword;
        if(theServer.changePassword(std::make_pair(username, password), newpassword)){
          cout << "\nPassword changed for user " << username;
          break;
        }
        else{
          cout << "\n*****Error: Could not change user password";
          break;
        }
      }
      case 'F':
      case 'f':{
        cout << "Enter username: ";
        cin >> username;
        if(theServer.find(username)){
          cout << "\nUser '" << username << "' found.";
          break;
        }
        else{
          cout << "\nUser '" << username << "' not found.";
          break;
        }
      }
      case 'D':
      case 'd':{
         theServer.dump();
         break;
      }
      case 'S':
      case 's':{
        cout << "Size of hashtable: " << theServer.size();
        break;
      }
      case 'W':
      case 'w':{
        cout << "Enter password file name to write to: ";
        cin >> filename;
        if(theServer.write_to_file(filename.c_str()))
          break;
        else{
          cout << "\nCould not write to " << filename;
          break;
        }
      }
    }
  }

  return 0;
}

void Menu(){
  cout << "\n\n";
  cout << "l - Load From File" << endl;
  cout << "a - Add User" << endl;
  cout << "r - Remove User" << endl;
  cout << "c - Change User Password" << endl;
  cout << "f - Find User" << endl;
  cout << "d - Dump HashTable" << endl;
  cout << "s - HashTable Size" << endl;
  cout << "w - Write to Password File" << endl;
  cout << "x - Exit program" << endl;
  cout << "\nEnter choice : ";
}
