#CXX = g++
CXX = clang++

INCLUDE = -I./include `pkg-config --cflags mapnik2 freetype2`

#DEFINES = -DHAVE_JPEG -DBOOST_REGEX_HAS_ICU -DDARWIN -DBOOST_SPIRIT_THREADSAFE -DMAPNIK_THREADSAFE -DNDEBUG
DEFINES = -DBOOST_REGEX_HAS_ICU -DMAPNIKDIR=\"`pkg-config --variable=prefix mapnik2`\"

#CXXFLAGS = $(DEFINES) $(INCLUDE) -Wall
CXXFLAGS = -g -I./include $(shell mapnik-config --cflags) -DMAPNIKDIR=\"$(shell mapnik-config --input-plugins)\"

LIBS = $(shell mapnik-config --libs)


SRC = $(wildcard *.cpp)

OBJ = $(SRC:.cpp=.o)

BIN = example

all : $(SRC) $(BIN)

$(BIN) : $(OBJ)
	$(CXX) $(OBJ) $(LIBS) -o $@  

.cpp.o :
	$(CXX) -c $(CXXFLAGS) $< -o $@

.PHONY : clean

clean: 
	rm -f $(OBJ)
	rm -f $(BIN)
