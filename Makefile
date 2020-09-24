CC=g++

EXECUTABLE=gistree.exe

CFLAGS=-c -Wall
LDFLAGS=
SOURCES=main.cpp 
SOURCES+=Node.cpp 
SOURCES+=Tree.cpp

OBJECTS=$(SOURCES:.cpp=.o)

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
