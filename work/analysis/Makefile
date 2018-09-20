ROOTCFLAGS = $(shell root-config --cflags)
ROOTLIBS = $(shell root-config --libs)
ROOTGLIBS = $(shell root-config --glibs)

CXXFLAGS = $(ROOTCFLAGS) -Wall -fPIC
CXXLIBS = $(ROOTLIBS)
CC = g++

TARGETS = radiation_length

all: $(TARGETS)

radiation_length: radiation_length.o
	$(CC) $(CXXLIBS) -o $@ $@.o

.cc.o:
	$(CC) $(CXXFLAGS) -c $< 

clean:
	rm -f *.o
	rm -f $(TARGETS)

