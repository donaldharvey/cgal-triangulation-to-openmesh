CC=g++
PROJECT = test_convert
DEPS = convert.h
OBJ = test_convert.o
CFLAGS = -Wall -pedantic -std=c++11 -I.
LDFLAGS = -lOpenMeshCore -lCGAL -lgmp
all: $(PROJECT)

%.o: %.cpp $(DEPS)

test_convert: $(OBJ)
	g++ $(CFLAGS) $(LDFLAGS) -o test_convert $(OBJ)