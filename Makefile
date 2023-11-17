CC = gcc
CFLAGS = -std=gnu99
SOURCES = functions.c GA.c OF.c
OBJECTS = $(SOURCES:.c=.o)
HEADERS = functions.h 
EXECUTABLE = Algo

all: $(EXECUTABLE)
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(OBJECTS) -Ofast -lm 

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
