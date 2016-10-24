CXX = gcc
CXXFLAGS = -g -mno-ms-bitfields
LDFLAGS = -g

all: Aufgabe3

Aufgabe3: main.o input.o
	$(CXX) -o Aufgabe3 $(LDFLAGS) main.o input.o

main.o: ../../aufgabe3/main.c ../../aufgabe3/input.h ../../aufgabe3/bitmap_types.h ../../aufgabe3/ms_types.h ../../aufgabe3/errors.h
	$(CXX) -c $(CXXFLAGS) ../../aufgabe3/main.c 
	
input.o: ../../aufgabe3/input.c ../../aufgabe3/input.h ../../aufgabe3/bitmap_types.h ../../aufgabe3/ms_types.h ../../aufgabe3/errors.h
	$(CXX) -c $(CXXFLAGS) ../../aufgabe3/input.c