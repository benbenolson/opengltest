CC=clang++
CFLAGS=-c -Wall -g
LDFLAGS=
LDLIBS=-lglfw -lGL -lGLEW -lpng
OBJECTS=shader.o war.o window.o model.o state.o lodepng.o tile.o map.o
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

state.o: gl/state.cpp
	$(CC) $(CFLAGS) gl/state.cpp

png.o: gl/png.cpp
	$(CC) $(CFLAGS) gl/png.cpp

lodepng.o: gl/lodepng.cpp
	$(CC) $(CFLAGS) gl/lodepng.cpp

tile.o: map/tile.cpp
	$(CC) $(CFLAGS) map/tile.cpp

map.o: map/map.cpp
	$(CC) $(CFLAGS) map/map.cpp

clean:
	rm *.o war
