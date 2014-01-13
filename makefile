CC=g++
CFLAGS=-c 
LDFLAGS=
LIBS=-lglut -lGLU -lGL
SOURCES=main.cpp drawings.cpp callbacks.cpp globals.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=main

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(LIBS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@ $(LIBS)
