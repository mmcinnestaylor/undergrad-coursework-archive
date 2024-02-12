all: main7.o bitarray.o
	g++ -o qaz main7.o bitarray.o
main7.o: main7.cpp
	g++ -c main7.cpp
bitarry.o: bitarray.cpp bitarray.h sieve.h
	g++ -c bitarray.cpp
clean:
	rm *.o *.gch qaz
