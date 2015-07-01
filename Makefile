CC=clang++
CFLAGS=-c -Wall
LDFLAGS=
LDLIBS=-lglfw -lGL -lGLEW
OBJECTS=shader.o war.o window.o model.o
EXECUTABLE=war

all: war

war: $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) $(LDLIBS) -o $(EXECUTABLE)
	rm *.o

war.o: war.cpp
	$(CC) $(CFLAGS) war.cpp

shader.o: gl/shader.cpp
	$(CC) $(CFLAGS) gl/shader.cpp

window.o: gl/window.cpp
	$(CC) $(CFLAGS) gl/window.cpp

model.o: gl/model.cpp
	$(CC) $(CFLAGS) gl/model.cpp

clean:
	rm *.o war
