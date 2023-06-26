iceFile = dictionary

all: clean build_ice server client

build_ice:
	slice2cpp $(iceFile).ice
clean:
	rm -f $(iceFile).cpp $(iceFile).h *.o server client

server:
	g++ -I. -I$ICE_HOME/include -c $(iceFile).cpp server.cpp
	g++ -o server $(iceFile).o server.o -L$ICE_HOME/lib -lIce

client:
	g++ -I. -I$ICE_HOME/include -c $(iceFile).cpp client.cpp
	g++ -o client $(iceFile).o client.o -L$ICE_HOME/lib -lIce