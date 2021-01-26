CXX=g++
CXXFLAGS=-O2 -Wall -lpng -ljpeg

all: img2benford

install_deps:
	brew install libpng libjpg

install:
	cp img2benford /usr/local/bin

uninstall:
	rm /usr/local/bin/img2benford

img2benford: img2benford.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@ 

clean:
	@rm -vf img2benford

