iceFilename = dictionary

all: clean build_ice server client
build_ice:
	slice2cpp $(iceFilename).ice
clean:
	rm -f $(iceFilename).cpp $(iceFilename).h *.o server client
server:
	g++ -I. -I$ICE_HOME/include -c $(iceFilename).cpp server.cpp
	g++ -o server $(iceFilename).o server.o -L$ICE_HOME/lib -lIce
client:
	g++ -I. -I$ICE_HOME/include -c $(iceFilename).cpp client.cpp
	g++ -o client $(iceFilename).o client.o -L$ICE_HOME/lib -lIce
