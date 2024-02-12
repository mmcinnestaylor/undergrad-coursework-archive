CC = g++
CFLAGS = -std=c++11 -Wall -pedantic

all: proj5.o sproj5.o passserver.o
	g++ $(CFLAGS) -lcrypt -o proj5.x proj5.o passserver.o
	g++ $(CFLAGS) -lcrypt -o sproj5.x sproj5.o passserver.o
sproj5.o: sproj5.cpp
	g++ $(CFLAGS) -c sproj5.cpp
proj5.o: proj5.cpp
	g++ $(CFLAGS) -c proj5.cpp
passserver.o: passserver.cpp
	g++ $(CFLAGS) -c passserver.cpp
clean:
	rm -f *.o *.gch *proj5.x
