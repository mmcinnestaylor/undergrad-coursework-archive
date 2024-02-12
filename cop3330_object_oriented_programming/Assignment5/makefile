all: driver.o mystring.o
	g++ -o qaz driver.o mystring.o
driver.o: driver.cpp
	g++ -c driver.cpp
house.o: mystring.cpp mystring.h
	g++ -c mystring.cpp
clean:
	rm *.o *.gch qaz
