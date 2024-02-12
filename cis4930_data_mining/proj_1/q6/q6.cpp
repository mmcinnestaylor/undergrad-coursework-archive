#include <cmath>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <map>
#include <vector>

using namespace std;

struct Student
{
  char teamName[50];
  int id, t1, t2;
};

void max(Student arr[], const int SIZE);
void min(Student arr[], const int SIZE);
void mean_sd(Student arr[], const int SIZE);
void median(Student arr[], const int SIZE);
void mode(Student arr[], const int SIZE);
void sort(Student arr[], const int SIZE, int flag);
void quartiles(Student arr[], const int SIZE);

int main(){
	ifstream readFile;
	const int SIZE = 1000;

	Student students[SIZE];

	readFile.open("scores.txt");

	for(int i=0; i<SIZE; i++){
		readFile >> students[i].id >> students[i].t1 >> students[i].t2;
		//cout << students[i].id << ' ' << students[i].t1 << ' ' << students[i].t2 << '\n';
	}

	readFile.close();

	cout << fixed << showpoint << setprecision(3);

	min(students, SIZE);
	max(students, SIZE);
	mean_sd(students, SIZE);
	median(students, SIZE);
	mode(students, SIZE);
	quartiles(students, SIZE);



	return 0;		
}

void max(Student arr[], const int SIZE){
	int t1_max = 0;
	int t2_max = 0;

	for(int i=0; i<SIZE; i++){
		if(arr[i].t1 > t1_max)
			t1_max = arr[i].t1;
		if(arr[i].t2 > t2_max)
			t2_max= arr[i].t2;
	}	
	
	cout << "\n***** MAX *****\n";
	cout << "Midterm: " << t1_max << '\n';
	cout << "Final: " << t2_max << '\n';
}

void min(Student arr[], const int SIZE){
	int t1_min = arr[0].t1;
	int t2_min = arr[0].t2;

	for(int i=0; i<SIZE; i++){
		if(arr[i].t1 < t1_min)
			t1_min = arr[i].t1;
		if(arr[i].t2 < t2_min)
			t2_min = arr[i].t2;
	}	
	
	cout << "\n***** MIN *****\n";
	cout << "Midterm: " << t1_min << '\n';
	cout << "Final: " << t2_min << '\n';
}

void mean_sd(Student arr[], const int SIZE){
	int t1_sum = 0;
	int t2_sum = 0;
	int t1_mean_i;
	int t2_mean_i;
	double t1_mean_d;
	double t2_mean_d;
	double t1_total = 0;
	double t2_total = 0;
	double t1_sd;
	double t2_sd;
	

	for(int i=0; i<SIZE; i++){
		t1_sum += arr[i].t1;
		t2_sum += arr[i].t2;
	}

	cout << "\n***** MEAN *****\n";
	if(t1_sum % SIZE == 0){
		t1_mean_i = t1_sum/SIZE;
		cout << "Midterm: " << t1_mean_i << '\n';
		t1_mean_d = t1_mean_i;
	}
	else{
		t1_mean_d = double(t1_sum)/SIZE;
		cout << "Midterm: " << t1_mean_d << '\n';
	}

	if(t2_sum % SIZE == 0){
		t2_mean_i = t2_sum/SIZE;
		cout << "Midterm: " << t2_mean_i << '\n';
		t2_mean_d = t2_mean_i;
	}
	else{
		t2_mean_d = double(t2_sum)/SIZE;
		cout << "Midterm: " << t2_mean_d << '\n';
	}

	cout << "\n***** STANDARD DEVIATION *****\n";
	for(int i=0; i<SIZE; i++){
		t1_total += pow(arr[i].t1-t1_mean_d, 2);
		t2_total += pow(arr[i].t2-t2_mean_d, 2);
	}

	t1_sd = sqrt(t1_total/SIZE);
	t2_sd = sqrt(t2_total/SIZE);

	cout << "Midterm: " << t1_sd << '\n';
	cout << "Final: " << t2_sd << '\n';

}

void median(Student arr[], const int SIZE){
	cout << "\n***** MEDIAN *****\n";
	if(SIZE % 2 == 0){
		sort(arr, SIZE, 1);
		if((arr[SIZE/2 - 1].t1 + arr[SIZE/2].t1) % 2 == 0){
			cout << "Midterm: " << (arr[SIZE/2 - 1].t1 + arr[SIZE/2].t1) / 2 << '\n';
			sort(arr, SIZE, 2);
			cout << "Final: " << (arr[SIZE/2 - 1].t2 + arr[SIZE/2].t2) / 2 << '\n';
		}
		else{
			cout << "Midterm: " << double(arr[SIZE/2 - 1].t1 + arr[SIZE/2].t1)/2 << '\n';
			sort(arr, SIZE, 2);
			cout << "Final: " << double(arr[SIZE/2 - 1].t2 + arr[SIZE/2].t2)/2 << '\n';
		}
	}
	else{
		sort(arr, SIZE, 1);
		cout << "Midterm: " << arr[SIZE/2].t1 << '\n';
		sort(arr, SIZE, 2);
		cout << "Final: " << arr[SIZE/2].t2 << '\n';
	}
}

void mode(Student arr[], const int SIZE){
	map<int,int> t1_freqs;
	map<int,int> t2_freqs;
	vector<int> t1_modes;
	vector<int> t2_modes;

	int t1_freqs_max = 0;
	int t2_freqs_max = 0;

	for(int i=0; i<SIZE; i++){
		auto it = t1_freqs.find(arr[i].t1);
  		if(it == t1_freqs.end())
    		t1_freqs[arr[i].t1] = 1;
		else
			t1_freqs[arr[i].t1] += 1;

		it = t2_freqs.find(arr[i].t2);
  		if(it == t2_freqs.end())
    		t2_freqs[arr[i].t2] = 1;
		else
			t2_freqs[arr[i].t2] += 1;
	}

	for (auto it=t1_freqs.begin(); it!=t1_freqs.end(); it++)
    	if(it->second > t1_freqs_max)
			t1_freqs_max = it->second;

	for (auto it=t2_freqs.begin(); it!=t2_freqs.end(); it++)
    	if(it->second > t2_freqs_max)
			t2_freqs_max = it->second;
		
	for (auto it=t1_freqs.begin(); it!=t1_freqs.end(); it++)
		if(it->second == t1_freqs_max)
			t1_modes.push_back(it->first);

	for (auto it=t2_freqs.begin(); it!=t2_freqs.end(); it++)
		if(it->second == t2_freqs_max)
			t2_modes.push_back(it->first);

	cout << "\n***** MODES *****\n";
	cout << "Midterm: ";
	for(int i=0; i<t1_modes.size(); i++)
		cout << t1_modes[i] << ' ';

	cout << "\nFinal: ";
	for(int i=0; i<t2_modes.size(); i++)
		cout << t2_modes[i] << ' ';
	cout << '\n';
}

void sort(Student arr[], const int SIZE, int flag){
	Student temp;

	if(flag == 1){
		for (int i = 0; i < SIZE-1; i++){      
			for (int j = 0; j < SIZE-i-1; j++){  
				if (arr[j].t1 > arr[j+1].t1){
					temp = arr[j];
					arr[j] = arr[j+1];
					arr[j+1] = temp;  
				}
			}
		}
	}
	else{
		for (int i = 0; i < SIZE-1; i++){      
			for (int j = 0; j < SIZE-i-1; j++){  
				if (arr[j].t2 > arr[j+1].t2){
					temp = arr[j];
					arr[j] = arr[j+1];
					arr[j+1] = temp;  
				}
			}
		}
	}
}

void quartiles(Student arr[], const int SIZE){
	int half_size = SIZE/2;

	cout << "\n***** Q1 *****\n";
	sort(arr, SIZE, 1);
	if((arr[half_size/2 - 1].t1 + arr[half_size/2].t1) % 2 == 0){
		cout << "Midterm: " << (arr[half_size/2 - 1].t1 + arr[half_size/2].t1) / 2;
	}
	else{
		cout << "Midterm: " << double(arr[half_size/2 - 1].t1 + arr[half_size/2].t1) / 2;
	}
	cout << '\n';
	sort(arr, SIZE, 2);
	if((arr[half_size/2 - 1].t2 + arr[half_size/2].t2) % 2 == 0){
		cout << "Final: " << (arr[half_size/2 - 1].t2 + arr[half_size/2].t2) / 2;
	}
	else{
		cout << "Final: " << double(arr[half_size/2 - 1].t2 + arr[half_size/2].t2) / 2;
	}
	cout << '\n';

	cout << "\n***** Q3 *****\n";
	sort(arr, SIZE, 1);
	if((arr[half_size/2 - 1 + 500].t1 + arr[half_size/2 + 500].t1) % 2 == 0){
		cout << "Midterm: " << (arr[half_size/2 - 1 + 500].t1 + arr[half_size/2 + 500].t1) / 2;
	}
	else{
		cout << "Midterm: " << double(arr[half_size/2 - 1 + 500].t1 + arr[half_size/2 + 500].t1) / 2;
	}
	cout << '\n';
	sort(arr, SIZE, 2);
	if((arr[half_size/2 - 1 + 500].t2 + arr[half_size/2 + 500].t2) % 2 == 0){
		cout << "Final: " << (arr[half_size/2 - 1 + 500].t2 + arr[half_size/2 + 500].t2) / 2;
	}
	else{
		cout << "Final: " << double(arr[half_size/2 - 1 + 500].t2 + arr[half_size/2 + 500].t2) / 2;
	}
}