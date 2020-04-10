.phony: all clean

all: KingofFat

KingofFat: main.o
	$(CXX) -std=c++14 -o $@ $+

main.o: main.cpp board.h
	$(CXX) -std=c++14 -c -o $@ $<
