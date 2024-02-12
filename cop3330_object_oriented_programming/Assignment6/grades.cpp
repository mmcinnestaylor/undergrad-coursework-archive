#include "grades.h"
using namespace std;

Student::Student(string fn, string ln, string c){
	firstName = fn;
	lastName = ln;
	course = c;
}
void Student::printName(ofstream& os) const{
	os << firstName << ' ' << lastName;
}	
string Student::getCourse() const{
	return course;
}
char Student::letterGrade(const double grade) const{
	if(grade >=90) return 'A';
	else if(grade < 90 && grade >= 80) return 'B';
	else if(grade < 80 && grade >= 70) return 'C';
	else if(grade < 70 && grade >= 60) return 'D';
	else if(grade < 60) return 'F';
}
void Student::fillArray(int* const grades, const int SIZE, ifstream& is){
	for(int i = 0; i < SIZE; i++)
		is >> grades[i];
}
int Student::getPrintLength() const{
	return firstName.length() + lastName.length() + 1;
}
//class BiologyStu:Student
BiologyStu::BiologyStu(string fn, string ln, string c, ifstream& is)
	:Student(fn, ln, c){
	Student::fillArray(grades, 5, is); 
} 
double BiologyStu::finalAverage() const{
	double total = 0;
	for(int i = 0; i < 5; i++){
		if(i == 0)
			total += (grades[i] * .3);
		else if(i>= 1 && i <= 3)
			total += (grades[i] * .15);
		else
			total += (grades[i] * .25);
	}
	return total;
}
char BiologyStu::getLetterGrade() const{
	return Student::letterGrade(finalAverage());
}
int BiologyStu::getFinalExam() const{
	return grades[4];
}
//class TheaterStu:Student
TheaterStu::TheaterStu(string fn, string ln, string c, ifstream& is)
	:Student(fn, ln, c){
	Student::fillArray(grades, 3, is);
}
double TheaterStu::finalAverage() const{
	double total = 0;
	for(int i = 0; i < 3; i++){
		if(i == 0)
			total += (grades[i] * .4);
		else if(i == 1)
			total += (grades[i] *  .25);
		else
			total += (grades[i] * .35);
	} 
	return total;
}
char TheaterStu::getLetterGrade() const{
	return Student::letterGrade(finalAverage());
}
int TheaterStu::getFinalExam() const{
	return grades[2];
}
//class CompSciStu:Student{
CompSciStu::CompSciStu(string fn, string ln, string c, ifstream& is)
	:Student(fn, ln, c){
	Student::fillArray(grades, 9, is);
}
double CompSciStu::finalAverage() const{
	double total = 0;
	for(int i = 0; i < 9; i++){
		if(i <= 5){
			total += grades[i];
			if(i == 5)
				total = ((total / 600) * 30);
		}
		else if(i == 6 || i == 7)
			total += grades[i] * .2;
			
		else
			total += grades[i] * .3;
	}
	return total;
}
char CompSciStu::getLetterGrade() const{
	return Student::letterGrade(finalAverage());
}
int CompSciStu::getFinalExam() const{
	return grades[8];
} 
