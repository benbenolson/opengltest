CC=clang++
CFLAGS=-c -Wall
LDFLAGS=-lglfw -lGL -lGLEW
SOURCES=war.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=war

all: war

war: war.o
	$(CC) $(LDFLAGS) war.o -o war
	rm *.o

war.o: war.cpp
	$(CC) $(CFLAGS) war.cpp

clean:
	rm *.o war
