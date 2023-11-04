# Makefile for the 'thing' program
# Specify the compiler
CC = gcc
# Compiler flags
CFLAGS =  -Wall -Wextra -Werror -Wpedantic -std=c99 -g
# Source files
SOURCES = functions.c GA.c OF.c
# Object files
OBJECTS = $(SOURCES:.c=.o)
# Header file
HEADERS = functions.h
# EXECUTABLE executable
EXECUTABLE = Algo
# Default EXECUTABLE
all: $(EXECUTABLE)
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(OBJECTS)
# Compile source files into object files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
