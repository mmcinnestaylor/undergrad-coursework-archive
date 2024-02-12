#include <fstream>
#include <string>
using namespace std;

class Student{
public:
	Student(string, string, string);
	void printName(ofstream&) const;
	string getCourse() const;
	int getPrintLength() const;
	virtual double finalAverage() const =0;
	virtual char getLetterGrade() const =0;
	virtual int getFinalExam() const =0;
	
protected:
	char letterGrade(const double)  const;
	void fillArray(int* const, const int, ifstream&);
	string firstName;
	string lastName;
	string course;	
};
class BiologyStu:public Student{
public:
	BiologyStu(string, string, string, ifstream&);
	double finalAverage() const;
	char getLetterGrade() const;
	int getFinalExam() const;
private:
	int grades[5];
};
class TheaterStu:public Student{
public:
	TheaterStu(string, string, string, ifstream&);
	double finalAverage() const;
	char getLetterGrade() const;
	int getFinalExam() const;
private:
	int grades[3];
};
class CompSciStu:public Student{
public:
	CompSciStu(string, string, string, ifstream&);
	double finalAverage() const;
	char getLetterGrade() const;
	int getFinalExam() const;
	
private:
	int grades[9];
};
