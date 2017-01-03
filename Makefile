CXX=g++
CXXFLAGS=`pkg-config --cflags opencv` 
LIBS=`pkg-config --libs opencv` -lwiringPi
SRC1=src/*.cpp
SRC2=detectorPosicion.cpp
OBJ1=$(SRC2:.cpp=.o)
TARGET1=bin/openbot

all: $(TARGET1)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<


$(TARGET1): $(OBJ1) Makefile
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ1) $(LIBS)


.PHONY: clean

clean:
	-rm $(OBJ1) $(TARGET1)

