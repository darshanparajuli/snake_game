CC=g++
CFLAGS=-std=c++11 -Wall -O0 -g -pipe
LFLAGS=-lSDL2 -lGL -lGLU -lGLEW
HEADERS=*.h
SOURCES=*.cpp
EXECUTABLE=snake

$(EXECUTABLE): $(HEADERS) $(SOURCES)
	$(CC) -o $@ $^ $(CFLAGS) $(LFLAGS)

run: $(EXECUTABLE)
	./$(EXECUTABLE)

clean:
	rm -f $(EXECUTABLE)
