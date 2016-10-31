CC = gcc
CCFLAGS = -std=c99 -g -mno-ms-bitfields
LDFLAGS = -g

SRC = main.c input.c output.c my_vla.c analyze.c
OBJ = $(SRC:%.c=%.o)

all: Aufgabe3

Aufgabe3: $(OBJ)
	$(CC) -o Aufgabe3 $(LDFLAGS) $(OBJ)

.PHONY: deps
deps:
	$(CC) -MM $(SRC) > makefile.dependencies

include makefile.dependencies