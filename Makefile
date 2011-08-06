#CXX = g++
CXX = clang++

CXXFLAGS = -g -I./include $(shell mapnik-config --cflags) -DMAPNIKDIR=\"$(shell mapnik-config --input-plugins)\"

LIBS = $(shell mapnik-config --libs)


SRC = $(wildcard *.cpp)

OBJ = $(SRC:.cpp=.o)

BIN = example

all : $(SRC) $(BIN)

$(BIN) : $(OBJ)
	$(CXX) $(OBJ) $(LIBS) -lboost_program_options -o $@  

.cpp.o :
	$(CXX) -c $(CXXFLAGS) $< -o $@

.PHONY : clean

clean: 
	rm -f $(OBJ)
	rm -f $(BIN)
