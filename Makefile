CC = g++
CFLAGS = -g -Wall -O3
INCLUDES = -I./ -I./input/inputreader -I./math -I./bcs -I./pot -I./output -I./optimize -I./queue
PGEN_PATH = ./pgen
PROB = melting
PGEN = $(PGEN_PATH)/$(PROB).cpp
DEPENDENCIES = ./input/inputreader/input_reader.cpp ./bcs/reflective.cpp ./math/vec3.cpp ./math/rand.cpp ./pot/lj-potential.cpp ./output/outputwriter.cpp  ./optimize/sweep-prune.cpp ./queue/queue.cpp
TARGET = DynaMol

all: main.cpp global.hpp $(PGEN)
	$(info Problem Selected: ${PROB})
	$(CC) $(CFLAGS) main.cpp $(PGEN) $(DEPENDENCIES) $(INCLUDES) -o $(TARGET)


debug: main.cpp global.hpp $(PGEN)
	$(info Problem Selected: ${PROB})
	$(CC) $(CFLAGS) global.cpp $(PGEN) $(DEPENDENCIES) $(INCLUDES) -o $(TARGET) -g

clean:
	rm $(TARGET)