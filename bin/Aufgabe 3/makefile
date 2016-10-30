CXX = gcc
CXXFLAGS = -std=c99 -g -mno-ms-bitfields
LDFLAGS = -g

all: Aufgabe3

Aufgabe3: main.o input.o output.o my_vla.o
	$(CXX) -o Aufgabe3 $(LDFLAGS) main.o input.o output.o my_vla.o

main.o: ../../aufgabe3/main.c ../../aufgabe3/input.h ../../aufgabe3/output.h ../../aufgabe3/my_vla.h ../../aufgabe3/bitmap_types.h ../../aufgabe3/ms_types.h ../../aufgabe3/errors.h
	$(CXX) -c $(CXXFLAGS) ../../aufgabe3/main.c 
	
input.o: ../../aufgabe3/input.c ../../aufgabe3/input.h ../../aufgabe3/my_vla.h ../../aufgabe3/bitmap_types.h ../../aufgabe3/ms_types.h ../../aufgabe3/errors.h
	$(CXX) -c $(CXXFLAGS) ../../aufgabe3/input.c

output.o: ../../aufgabe3/output.c ../../aufgabe3/output.h ../../aufgabe3/input.h  ../../aufgabe3/my_vla.h ../../aufgabe3/bitmap_types.h ../../aufgabe3/ms_types.h ../../aufgabe3/errors.h
	$(CXX) -c $(CXXFLAGS) ../../aufgabe3/output.c
	
my_vla.o: ../../aufgabe3/my_vla.c ../../aufgabe3/my_vla.h ../../aufgabe3/bitmap_types.h ../../aufgabe3/ms_types.h ../../aufgabe3/errors.h
	$(CXX) -c $(CXXFLAGS) ../../aufgabe3/my_vla.c