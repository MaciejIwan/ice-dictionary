iceFilename = dictionary

build_ice:
	slice2cpp $(iceFilename).ice
clean:
	rm $(iceFilename).cpp $(iceFilename).h *.o
build_server:
	g++ -I. -I$ICE_HOME/include -c $(iceFilename).cpp server.cpp