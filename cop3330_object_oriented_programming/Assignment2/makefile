all: driver.o date.o
	g++ -o qaz driver.o date.o
driver.o: driver.cpp
	g++ -c driver.cpp
date.o: date.cpp date.h
	g++ -c date.cpp
clean:
	rm *.o *.gch qaz
