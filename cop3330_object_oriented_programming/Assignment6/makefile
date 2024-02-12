all: main.o grades.o
	g++ -o qaz main.o grades.o
driver.o: main.cpp
	g++ -c main.cpp
house.o: grades.cpp grades.h
	g++ -c grades.cpp
clean:
	rm *.o *.gch qaz output.txt
