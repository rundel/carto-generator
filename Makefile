#CXX = g++
CXX = clang++

INCLUDE = `pkg-config --cflags mapnik2 freetype2`
LIBDIR  = `pkg-config --libs mapnik2`

DEFINES = -DHAVE_JPEG -DBOOST_REGEX_HAS_ICU -DDARWIN -DBOOST_SPIRIT_THREADSAFE -DMAPNIK_THREADSAFE -DNDEBUG

CXXFLAGS = $(DEFINES) $(INCLUDE) -Wall

#LIBS =  -L/usr/local/lib -L/usr/lib $(LIBDIR) -lboost_thread-mt -lboost_regex-mt -licuuc
LIBS =  -L/usr/local/lib -L/usr/lib -lmapnik2 -lboost_thread-mt -lboost_regex-mt -licuuc


SRC = $(wildcard *.cpp)
#gen_building_sym.cpp gen_font_set.cpp rundemo.cpp

OBJ = $(SRC:.cpp=.o)

BIN = rundemo

all : $(SRC) $(BIN)

$(BIN) : $(OBJ)
	$(CXX) $(OBJ) $(LIBS) -o $@  

.cpp.o :
	$(CXX) -c $(CXXFLAGS) $< -o $@

.PHONY : clean

clean: 
	rm -f $(OBJ)
	rm -f $(BIN)

#    g++ -o demo/c++/rundemo.o -c -ansi -Wall -Wno-parentheses -Wno-unused-function -Wno-char-subscripts -ftemplate-depth-200  -O2 -finline-functions -Wno-inline `pkg-config --cflags cairomm-1.0` -Iagg/include -I. -Iinclude -I/opt/X11/include/freetype2 -I/opt/X11/include -I/usr/local/Cellar/postgresql/9.0.3/include -I/usr/local/Cellar/gdal/1.8.0/include -I/usr/local/include -I/usr/include -I/usr/include/libxml2 demo/c++/rundemo.cpp
#    g++ -o demo/c++/rundemo demo/c++/rundemo.o -Lagg -Lsrc -L/opt/X11/lib -L/usr/local/Cellar/postgresql/9.0.3/lib -L/usr/local/Cellar/gdal/1.8.0/lib -L/usr/local/lib -L/usr/lib -lmapnik2 -lboost_thread-mt -lcairomm-1.0 -lboost_regex-mt -licuuc