#CXX = g++
CXX = clang++

CXXFLAGS = -I./include $(shell mapnik-config --cflags) -DMAPNIKDIR=\"$(shell mapnik-config --input-plugins)\"

LIBS = $(shell mapnik-config --libs --ldflags --dep-libs) -lboost_program_options

SRC = $(wildcard *.cpp)

OBJ = $(SRC:.cpp=.o)

BIN = xml2carto

all : $(SRC) $(BIN)

$(BIN) : $(OBJ)
	$(CXX) $(OBJ) $(LIBS) -o $@  

.cpp.o :
	$(CXX) -c $(CXXFLAGS) $< -o $@

.PHONY : clean

clean: 
	rm -f $(OBJ)
	rm -f $(BIN)
