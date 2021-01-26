CXX=g++
CXXFLAGS=-O2 -Wall -lpng -ljpeg

all: img2benford

install_deps:
	brew install libpng libjpg



img2benford: img2benford.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@ 

clean:
	@rm -vf img2benford

