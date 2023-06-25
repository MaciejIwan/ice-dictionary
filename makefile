iceFilename = dictionary

all: clean build_ice server
build_ice:
	slice2cpp $(iceFilename).ice
clean:
	rm -f $(iceFilename).cpp $(iceFilename).h *.o server
server:
	g++ -I. -I$ICE_HOME/include -c $(iceFilename).cpp server.cpp
	g++ -o server $(iceFilename).o server.o -L$ICE_HOME/lib -lIce
