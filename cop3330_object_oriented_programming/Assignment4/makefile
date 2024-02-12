all: test1.o grid.o
	g++ -o qaz test1.o grid.o
test1.o: test1.cpp
	g++ -c test1.cpp
grid.o: grid.cpp grid.h
	g++ -c grid.cpp
clean:
	rm *.o *.gch qaz
