CC = g++
CFLAGS = -std=c++11 -c -Wall

all: prog

prog: main.o company.o project.o globals.o
	$(CC) -std=c++11 main.cpp company.cpp project.cpp globals.cpp -o prog

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

company.o: company.cpp company.h project.h employee.h
	$(CC) $(CFLAGS) company.cpp

project.o: project.cpp project.h employee.h
	$(CC) $(CFLAGS) project.cpp

globals.o: globals.cpp company.h project.h employee.h
	$(CC) $(CFLAGS) globals.cpp

clear:
	rm -rf *o prog

