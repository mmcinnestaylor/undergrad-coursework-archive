all: proj4_driver.o bet.o
	g++ -o proj4.x -std=c++11 -Wall -pedantic proj4_driver.o bet.o
proj4_driver.o: proj4_driver.cpp
	g++ -c -std=c++11 -Wall -pedantic proj4_driver.cpp
bet.o: bet.cpp bet.h
	g++ -c -std=c++11 -Wall -pedantic bet.cpp
clean:
	rm -f *.o *.gch proj4.x
