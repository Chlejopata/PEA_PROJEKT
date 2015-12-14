CC=clang++
CFLAGS=-c -O3 -std=c++11
LDFLAGS=
SOURCES=ConsoleAttributes.cpp main.cpp MatrixGraph.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=Grafy

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
