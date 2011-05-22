#CXX = g++
CXX = clang++

INCLUDE = -I./include `pkg-config --cflags mapnik2 freetype2`

DEFINES = -DHAVE_JPEG -DBOOST_REGEX_HAS_ICU -DDARWIN -DBOOST_SPIRIT_THREADSAFE -DMAPNIK_THREADSAFE -DNDEBUG

CXXFLAGS = $(DEFINES) $(INCLUDE) -Wall

LIBS = -lmapnik2 -lboost_thread-mt -lboost_regex-mt -licuuc


SRC = $(wildcard *.cpp)
#gen_building_sym.cpp gen_font_set.cpp rundemo.cpp

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
