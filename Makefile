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

shader.o: shader.cpp
	$(CC) $(CFLAGS) shader.cpp

window.o: window.cpp
	$(CC) $(CFLAGS) window.cpp

model.o: model.cpp
	$(CC) $(CFLAGS) model.cpp

clean:
	rm *.o war
