main: main.o time.o
	g++ -o main main.o time.o

tests: tests.o time.o
	g++ -o tests tests.o time.o

tests.o: tests.cpp doctest.h 

main.o: main.cpp time.h

time.o: time.cpp time.h movie.h timeslot.h

clean:
	rm -f a.out main main.o tests tests.o time.o
