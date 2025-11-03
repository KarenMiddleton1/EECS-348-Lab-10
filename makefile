CC = g++

CFLAGS = -g -Wall

prog: lab_10.o
	$(CC) $(CFLAGS) lab_10.o -o prog

lab_10.o: lab_10.cpp
	$(CC) $(CFLAGS) -c lab_10.cpp
	
clean:
	rm -f *.o prog