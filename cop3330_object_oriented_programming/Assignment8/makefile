all: driver.o house.o
	g++ -o testprog driver.o house.o
driver.o: driver.cpp
	g++ -c driver.cpp
house.o: house.cpp house.h
	g++ -c house.cpp
clean:
	rm *.o *.gch testprog
