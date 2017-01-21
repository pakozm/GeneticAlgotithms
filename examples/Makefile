all: example01

example01: example01.cc ../source/*.h
	g++ -std=c++11 -I ../source/ -o example01 example01.cc -Wall -O3

clean:
	rm -f example01
