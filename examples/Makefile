all: example01 example02

example01: example01.cc ../source/*.h
	g++ -std=c++11 -I ../source/ -o example01 example01.cc -Wall -O3 -pedantic

example02: example02.cc ../source/*.h
	g++ -std=c++11 -I ../source/ -o example02 example02.cc -Wall -O3 -pedantic

clean:
	rm -f example01 example02
