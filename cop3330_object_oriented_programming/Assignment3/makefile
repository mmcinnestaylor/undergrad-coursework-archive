all: driver.o time.o
	g++ -o qaz driver.o time.o
driver.o: driver.cpp
	g++ -c driver.cpp
house.o: time.cpp time.h
	g++ -c time.cpp
clean:
	rm *.o *.gch qaz
