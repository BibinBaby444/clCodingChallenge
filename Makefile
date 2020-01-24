CXX = g++ --std=c++11
CXXFLAGS=-I/usr/include/
LDDFLAGS=-lcurl
 
parse:Subtitle_image.o Downloader.o Subt_mdat.o Container.o Parse.o 
	$(CXX) $(CXXFLAGS) -o parse Subtitle_image.o Downloader.o Subt_mdat.o Container.o Parse.o $(LDDFLAGS)

clean :
	-rm *.o $(objects) 
