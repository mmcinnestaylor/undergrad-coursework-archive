#include "grades.h"
#include <iostream>
#include <iomanip>
using namespace std;

int main(){
	char filename[50];
	int SIZE, numA, numB, numC, numD, numF;
	string firstName, lastName, course;
	ifstream fin;
	ofstream fout;	
	
	SIZE = numA = numB = numC = numD = numF = 0;
	
	do{
		cout << "Please enter the name of the input file.\nFilename: ";
		cin >> filename;
		fin.open(filename);
		if(!fin)
			cout << "Invalid filename. Please enter a vaild file name." << endl;
	}while(!fin);

	do{
		cout << "Please enter the name of the output file.\nFilename: ";
		cin >> filename;
		fout.open(filename);
		if(!fout)
			cout << "Invalid filename. Please enter a vaild file name." << endl;
	}while(!fout);

	fin >> SIZE;
	fin.ignore();
	Student** stuArr = new Student*[SIZE];

	for(int i= 0; i < SIZE; i++){
		getline(fin, lastName, ',');
		fin.ignore();
		getline(fin, firstName);
		fin >> course;
		if(course == "Computer"){
			fin >> course;
			stuArr[i] = new CompSciStu(firstName, lastName, course, fin);
		}
		else if(course == "Theater")
			stuArr[i] = new TheaterStu(firstName, lastName, course, fin);
		else
			stuArr[i] = new BiologyStu(firstName, lastName, course, fin);
		fin.ignore();
	}

	fin.close();

	fout << "Student Grade Summary" << endl;
	fout << "_____________________\n" << endl;
	fout << "BIOLOGY CLASS\n" << endl;
	fout << "Student\t\t\t\t\tFinal\tFinal\tLetter" << endl;
	fout << "Name   \t\t\t\t\tExam \tAvg  \tGrade" << endl;
	fout << "--------------------------------------------------------------" <<endl;
	for(int i = 0; i < SIZE; i++){
		if(stuArr[i]->getCourse() == "Biology"){
			stuArr[i]->printName(fout);
			for(int j = 0; j < 40 - (stuArr[i]->getPrintLength()); j++)
				fout << ' ';
			fout << stuArr[i]->getFinalExam() << '\t';
			fout << fixed<< showpoint << setprecision(2)
			     << stuArr[i]->finalAverage() << '\t';
			fout << stuArr[i]->getLetterGrade() << endl;
		}	
	}	
	fout << endl << endl << "THEATER CLASS\n" << endl;
	fout << "Student\t\t\t\t\tFinal\tFinal\tLetter" << endl;
	fout << "Name   \t\t\t\t\tExam \tAvg  \tGrade" << endl;
	fout << "--------------------------------------------------------------" <<endl;
	for(int i = 0; i < SIZE; i++){
		if(stuArr[i]->getCourse() == "Theater"){
			stuArr[i]->printName(fout);
			for(int j = 0; j < 40 - (stuArr[i]->getPrintLength()); j++)
				fout << ' ';
			fout << stuArr[i]->getFinalExam() << '\t';
			fout << fixed<< showpoint << setprecision(2)
			     << stuArr[i]->finalAverage() << '\t';
			fout << stuArr[i]->getLetterGrade() << endl;
		}	
	}	
	fout << endl << endl << "COMPUTER SCIENCE CLASS\n" << endl;
	fout << "Student\t\t\t\t\tFinal\tFinal\tLetter" << endl;
	fout << "Name   \t\t\t\t\tExam \tAvg  \tGrade" << endl;
	fout << "--------------------------------------------------------------" <<endl;
	for(int i = 0; i < SIZE; i++){
		if(stuArr[i]->getCourse() == "Science"){
			stuArr[i]->printName(fout);
			for(int j = 0; j < 40 - (stuArr[i]->getPrintLength()); j++)
				fout << ' ';
			fout << stuArr[i]->getFinalExam() << '\t';
			fout << fixed<< showpoint << setprecision(2)
			     << stuArr[i]->finalAverage() << '\t';
			fout << stuArr[i]->getLetterGrade() << endl;
		}	
	}
	
	for(int i = 0; i < SIZE; i++){
		switch(stuArr[i]->getLetterGrade()){
			case 'A': {numA++; break;}
			case 'B': {numB++; break;}
			case 'C': {numC++; break;}
			case 'D': {numD++; break;}
			case 'F': {numF++; break;}
		}
	}
				
	fout << endl << "OVERALL GRADE DISTRIBUTION\n" << endl;
	fout << "A:\t" << numA << endl;
	fout << "B:\t" << numB << endl;
	fout << "C:\t" << numC << endl;
	fout << "D:\t" << numD << endl;
	fout << "F:\t" << numF << endl;

	for(int i = 0; i < SIZE; i++)
		delete stuArr[i];

	delete [] stuArr;

	cout << "Processing Complete" << endl;
	 
	return 0;
}

